#include "DatagramSocket.h"
#include "DatagramSocketImpl.h"
// �R���X�g���N�^�D
DatagramSocket::DatagramSocket() :
	mImpl(new DatagramSocketImpl())
{}
// �R���X�g���N�^�D
DatagramSocket::DatagramSocket(int port) :
	mImpl(new DatagramSocketImpl())
{
	// �o�C���h����
	bind(port);
}
// �f�X�g���N�^�D
DatagramSocket::~DatagramSocket()
{}
// �\�P�b�g���o�C���h����D
void DatagramSocket::bind(int port)
{
	mImpl->bind(port);
}
// �f�[�^�𑗐M�D
int DatagramSocket::send(const void* buffer, int size, const InetSocketAddress& addr)
{
	return mImpl->send(buffer, size, addr);
}
// �f�[�^����M�D
int DatagramSocket::receive(void* buffer, int size, InetSocketAddress& addr)
{
	return mImpl->receive(buffer, size, addr);
}
// �\�P�b�g�����D
void DatagramSocket::close()
{
	mImpl->close();
}