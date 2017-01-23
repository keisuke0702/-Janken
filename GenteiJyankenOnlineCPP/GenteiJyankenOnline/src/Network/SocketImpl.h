#ifndef _SOCKETIMPL_H_
#define _SOCKETIMPL_H_
#include <winsock2.h>
#include "InetSocketAddress.h"
// �\�P�b�g�����N���X
class SocketImpl
{
public:
	// �R���X�g���N�^�D
	SocketImpl();
	// �f�X�g���N�^�D
	~SocketImpl();
	// �\�P�b�g�̐ڑ��D
	void connect(const InetSocketAddress& address);
	// �\�P�b�g�����D
	void close();
	// �ڑ���̃\�P�b�g�Ƀf�[�^�𑗐M�D
	int send(const void* buffer, int size);
	// �ڑ���̃\�P�b�g����f�[�^����M�D
	int receive(void* buffer, int size);
	// �ڑ����󂯓����D
	SocketImpl* accept();
	// �w�肳�ꂽ�|�[�g�ԍ��Ƀ\�P�b�g���o�C���h����D
	void bind(int port);
	// �\�P�b�g�����X����Ԃɂ���D
	void listen(int backlog = 0);
	// �\�P�b�g�̃V���b�g�_�E�����s���D
	void shutdown(int how);
	// �ڑ���̃\�P�b�g�̃\�P�b�g�A�h���X���擾�D
	InetSocketAddress getInetSocketAddress() const;
	// ���[�J���\�P�b�g�A�h���X���擾�D
	InetSocketAddress getLocalInetSocketAddress() const;
	// �ڑ��������ׂ�D
	bool isConnected() const;
private:
	// �R�s�[�֎~
	SocketImpl(const SocketImpl& other);
	SocketImpl& operator = (const SocketImpl& other);
public:
	// ��M���V���b�g�_�E��
	const static int SHUTDOWN_RECEIVE;
	// ���M���V���b�g�_�E��
	const static int SHUTDOWN_SEND;
	// ����M���V���b�g�_�E��
	const static int SHUTDOWN_BOTH;
private:
	// �\�P�b�g�n���h��
	SOCKET mSocket;
	// �\�P�b�g�A�h���X
	InetSocketAddress mSocketAddress;
};
#endif