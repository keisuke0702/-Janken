#ifndef _DATAGRAMSOCKET_H_
#define _DATAGRAMSOCKET_H_
#include "InetSocketAddress.h"
#include <memory>
// �t�c�o�\�P�b�g�����N���X
class DatagramSocketImpl;
// �t�c�o�\�P�b�g�N���X�D
class DatagramSocket
{
public:
	// �R���X�g���N�^�D
	DatagramSocket();
	// �R���X�g���N�^�D
	DatagramSocket(int port);
	// �f�X�g���N�^�D
	virtual ~DatagramSocket();
	// �\�P�b�g���o�C���h����D
	void bind(int port);
	// �f�[�^�𑗐M�D
	int send(const void* buffer, int size, const InetSocketAddress& addr);
	// �f�[�^����M�D
	int receive(void* buffer, int size, InetSocketAddress& addr);
	// �\�P�b�g�����D
	void close();
private:
	// �R�s�[�֎~
	DatagramSocket(const DatagramSocket& other);
	DatagramSocket& operator = (const DatagramSocket& other);
private:
	// �t�c�o�\�P�b�g�����N���X
	std::auto_ptr<DatagramSocketImpl> mImpl;
};
#endif