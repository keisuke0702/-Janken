#ifndef _SOCKET_H_
#define _SOCKET_H_
#include "InetSocketAddress.h"
#include "SocketException.h"
#include <string>
#include <memory>
class SocketImpl;

// �\�P�b�g�N���X�D
class Socket
{
public:
	// �R���X�g���N�^�D
	Socket();
	// �R���X�g���N�^�D
	Socket(const InetSocketAddress& address);
	// �R���X�g���N�^�D
	Socket(const InetAddress& address, int port);
	// �R���X�g���N�^�D
	Socket(const std::string& host, int port);
	// �R���X�g���N�^�D
	Socket(SocketImpl* impl);
	// �f�X�g���N�^�D
	virtual ~Socket();
	// �\�P�b�g�̐ڑ��D
	void connect(const InetSocketAddress& address);
	// �\�P�b�g�̐ڑ��D
	void connect(const InetAddress& address, int port);
	// �\�P�b�g�̐ڑ��D
	void connect(const std::string& host, int port);
	// �\�P�b�g�����D
	void close();
	// �ڑ���̃\�P�b�g�Ƀf�[�^�𑗐M�D
	int send(const void* buffer, int size);
	// �ڑ���̃\�P�b�g�ɕ�����𑗐M�D
	int send(const std::string& msg);
	// �ڑ���̃\�P�b�g����f�[�^����M�D
	int receive(void* buffer, int size);
	// �ڑ���̃\�P�b�g���當�������M�D
	std::string receive();
	// �\�P�b�g�̃A�h���X���擾�D
	InetAddress getAddress() const;
	// �\�P�b�g�̃|�[�g���擾�D
	int getPort() const;
	// �\�P�b�g�̃��[�J���A�h���X���擾�D
	InetAddress getLocalAddress() const;
	// �\�P�b�g�̃��[�J���|�[�g�ԍ����擾�D
	int getLocalPort() const;
	// �ڑ��������ׂ�D
	bool isConnected() const;
	// �\�P�b�g�̃V���b�g�_�E�����s���D
	void shutdown(int how = Socket::SHUTDOWN_BOTH);
public:
	// ��M���V���b�g�_�E��
	const static int SHUTDOWN_RECEIVE;
	// ���M���V���b�g�_�E��
	const static int SHUTDOWN_SEND;
	// ����M���V���b�g�_�E��
	const static int SHUTDOWN_BOTH;
private:
	// �R�s�[�֎~
	Socket(const Socket& other);
	Socket& operator = (const Socket& other);
private:
	// �\�P�b�g�����N���X
	std::auto_ptr<SocketImpl> mImpl;
};

#endif