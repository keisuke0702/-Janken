#include "ServerSocket.h"
#include "SocketImpl.h"

// �R���X�g���N�^�D
ServerSocket::ServerSocket() :
mImpl(new SocketImpl())
{
}

// �R���X�g���N�^�D
ServerSocket::ServerSocket(int port, int backlog) :
mImpl(new SocketImpl())
{
	bind(port, backlog);
}

// �f�X�g���N�^�D
ServerSocket::~ServerSocket()
{
}

// �ڑ��v����ҋ@���āC�\�P�b�g���󂯓����D
std::auto_ptr<Socket> ServerSocket::accept()
{
	return std::auto_ptr<Socket>(new Socket(mImpl->accept()));
}

// �\�P�b�g���o�C���h���āC���X����Ԃɂ���D
void ServerSocket::bind(int port, int backlog)
{
	mImpl->bind(port);
	mImpl->listen(backlog);
}

// �\�P�b�g�����D
void ServerSocket::close()
{
	if (mImpl->isConnected() == true) {
		mImpl->close();
	}
}

// �\�P�b�g�̃A�h���X���擾�D
InetAddress ServerSocket::getAddress() const
{
	return mImpl->getLocalInetSocketAddress().getInetAddress();
}

// �\�P�b�g�̃|�[�g�ԍ����擾�D
int ServerSocket::getPort() const
{
	return mImpl->getLocalInetSocketAddress().getPort();
}