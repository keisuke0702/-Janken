#include "ChatMain1.h"
#include <iostream>

using namespace std;

//�R���X�g���N�^
ChatMain1::ChatMain1():
mImpl()
{

}

//�T�[�o�[�֐�
void ChatMain1::ChatServer()
{
	//�|�[�g�ԍ��̓���
	u_short uport;
	cout << "�g�p����|�[�g�ԍ������-->";
	cin >> uport;
	fflush(stdin);

	InetSocketAddress mSocket = InetSocketAddress(uport);	

	//���X���\�P�b�g���I�[�v�����A�\�P�b�g���o�C���h
	mImpl.bind(uport);
	cout << "bind����" << endl;

	//�N���C�A���g����̐ڑ��҂�
	mImpl.listen();
	cout << "listen����" << endl;

	//�ڑ���ҋ@����
	mImpl.accept();
	cout << "accept����" << endl;

	//��b�J�n
	cout << "��b�J�n" << endl;
	while (1)
	{

	}

	//�\�P�b�g�����
}

//�N���C�A���g�֐�
void ChatMain1::ChatClient()
{

}

//���s
void ChatMain1::Run()
{

}