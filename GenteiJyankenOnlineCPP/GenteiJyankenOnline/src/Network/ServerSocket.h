#ifndef _SERVERSOCKET_H_
#define _SERVERSOCKET_H_
#include "Socket.h"
#include <memory>
class SocketImpl;

// �T�[�o�[�\�P�b�g�N���X�D
class ServerSocket
{
public:
	// �R���X�g���N�^�D
	ServerSocket();
	// �R���X�g���N�^�D�i�o�C���h����j
	ServerSocket(int port, int backlog = 0);
	// �f�X�g���N�^�D
	virtual ~ServerSocket();
	// �ڑ��v����ҋ@���āC�\�P�b�g���󂯓����D
	std::auto_ptr<Socket> accept();
	// �\�P�b�g���o�C���h���āC���X����Ԃɂ���D
	void bind(int port, int backlog = 0);
	// �\�P�b�g�����D
	void close();
	// �\�P�b�g�̃A�h���X���擾�D
	InetAddress getAddress() const;
	// �\�P�b�g�̃|�[�g�ԍ����擾�D
	int getPort() const;
private:
	// �R�s�[�֎~
	ServerSocket(const ServerSocket& other);
	ServerSocket& operator = (const ServerSocket& other);
private:
	// �\�P�b�g�����N���X
	std::auto_ptr<SocketImpl> mImpl;
};

#endif
