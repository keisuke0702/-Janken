#include "ServerThread.h"
#include "ClientThread.h"
#include "AcceptThread.h"
#include "Socket.h"
#include <functional>
#include <algorithm>

// �R���X�g���N�^
ServerThread::ServerThread(int port) :
	mPort(port),
	mIsEnd(false)
{
}
// �f�X�g���N�^
ServerThread::~ServerThread()
{
	// �����I��
	end();
}
// �|�[�g�ԍ��̎擾
int ServerThread::getPort() const
{
	return mPort;
}
// �X���b�h�̎��s
void ServerThread::run()
{
	// �X���b�h���J�n
	mIsEnd = false;
	// �A�N�Z�v�g�X���b�h���쐬����
	std::auto_ptr<AcceptThread> acceptor(new AcceptThread(*this));
	// ��M�X���b�h���N��
	acceptor->start();
	// �I������܂ŌJ��Ԃ�
	while (isEnd() == false) {
		// �I�������N���C�A���g���폜
		removeClient();
		// ���̃X���b�h�ɐ����n��
		Thread::sleep(0);
	}
	// �A�N�Z�v�g�X���b�h�������I��
	acceptor->end();
	// �N���C�A���g��S�ď���
	clearClient();
	// �I���t���O��ݒ�
	mIsEnd = true;
}
// �N���C�A���g�̒ǉ�
void ServerThread::addClient(ClientThread* client)
{
	CriticalSection::Lock guard(mClientContainerLock);
	// �N���C�A���g��o�^
	mClientContainer.push_back(ClientThreadPtr(client));
	// �N���C�A���g�X���b�h�N��
	client->start();
}
// �N���C�A���g�̍폜
void ServerThread::removeClient()
{
	CriticalSection::Lock guard(mClientContainerLock);
	// �I�����Ă���N���C�A���g���폜
	mClientContainer.remove_if(std::mem_fn(&ClientThread::isEnd));
}
// �N���C�A���g��S�ď���
void ServerThread::clearClient()
{
	CriticalSection::Lock guard(mClientContainerLock);
	// �N���C�A���g�S�ď���
	mClientContainer.clear();
}
// �����I��
void ServerThread::end()
{
	// �I���t���O��ݒ肷��
	mIsEnd = true;
	// �X���b�h�̏I����҂�
	join();
}
// �I�����Ă��邩�H
bool ServerThread::isEnd()
{
	return mIsEnd;
}
// �N���C�A���g�Ƀ��b�Z�[�W�𑗐M
void ServerThread::sendClient(const std::string & message)
{
	CriticalSection::Lock guard(mClientContainerLock);
	// �S�N���C�A���g�Ƀ��b�Z�[�W�𑗂�
	std::for_each(
		mClientContainer.begin(),
		mClientContainer.end(),
		std::bind(std::mem_fn(&ClientThread::send), std::placeholders::_1, message)
		);
}
