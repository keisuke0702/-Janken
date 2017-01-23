#include "Socket.h"
#include "SocketImpl.h"
#include <vector>

// ��M���V���b�g�_�E��*/
const int Socket::SHUTDOWN_RECEIVE = SocketImpl::SHUTDOWN_RECEIVE;
// ���M���V���b�g�_�E��*/
const int Socket::SHUTDOWN_SEND = SocketImpl::SHUTDOWN_SEND;
// ����M���V���b�g�_�E��*/
const int Socket::SHUTDOWN_BOTH = SocketImpl::SHUTDOWN_BOTH;

// �R���X�g���N�^�D
Socket::Socket()
: mImpl(new SocketImpl())
{
}

// �R���X�g���N�^�D
Socket::Socket(const InetSocketAddress& address)
: mImpl(new SocketImpl())
{
	connect(address);
}

// �R���X�g���N�^�D
Socket::Socket(const InetAddress& address, int port)
: mImpl(new SocketImpl())
{
	connect(address, port);
}

// �R���X�g���N�^�D
Socket::Socket(const std::string& host, int port)
: mImpl(new SocketImpl())
{
	connect(host, port);
}

// �R���X�g���N�^�D
Socket::Socket(SocketImpl* impl) :
mImpl(impl)
{
}

// �f�X�g���N�^�D
Socket::~Socket()
{
}

// �\�P�b�g�̐ڑ��D
void Socket::connect(const InetSocketAddress& address)
{
	mImpl->connect(address);
}

// �\�P�b�g�̐ڑ��D
void Socket::connect(const InetAddress& address, int port)
{
	connect(InetSocketAddress(address, port));
}

// �\�P�b�g�̐ڑ��D
void Socket::connect(const std::string& host, int port)
{
	connect(InetSocketAddress(InetAddress(host), port));
}

// �\�P�b�g�����D
void Socket::close()
{
	if (mImpl->isConnected() == true) {
		mImpl->close();
	}
}

// �ڑ���̃\�P�b�g�Ƀf�[�^�𑗐M�D
int Socket::send(const void* buffer, int size)
{
	int total = 0;
	while (total < size) {
		// �f�[�^�𑗐M����
		total += mImpl->send(reinterpret_cast<const char*>(buffer)+total, size - total);
	}
	return total;
}

// �ڑ���̃\�P�b�g�ɕ�����𑗐M�D
int Socket::send(const std::string& msg)
{
	// NUL�������܂߂đ��M����
	return send(msg.c_str(), (int)msg.size() + 1);
}

// �ڑ���̃\�P�b�g����f�[�^����M�D
int Socket::receive(void* buffer, int size)
{
	int total = 0;
	while (total < size) {
		// �f�[�^�𑗐M����
		total += mImpl->receive(reinterpret_cast<char*>(buffer)+total, size - total);
	}
	return total;
}

// �ڑ���̃\�P�b�g���當�������M�D
std::string Socket::receive()
{
	// ��M�o�b�t�@
	std::vector<char> buffer;
	char revchar;
	do {
		revchar = '\0';
		receive(&revchar, sizeof(revchar));
		buffer.push_back(revchar);
	} while (revchar != '\0');
	return std::string(&buffer[0]);
}

// �\�P�b�g�̃A�h���X���擾�D
InetAddress Socket::getAddress() const
{
	return mImpl->getInetSocketAddress().getInetAddress();
}

// �\�P�b�g�̃|�[�g���擾�D
int Socket::getPort() const
{
	return mImpl->getInetSocketAddress().getPort();
}

// �\�P�b�g�̃��[�J���A�h���X���擾�D
InetAddress Socket::getLocalAddress() const
{
	return mImpl->getLocalInetSocketAddress().getInetAddress();
}

// �\�P�b�g�̃��[�J���|�[�g�ԍ����擾�D
int Socket::getLocalPort() const
{
	return mImpl->getLocalInetSocketAddress().getPort();
}

// �ڑ��������ׂ�D
bool Socket::isConnected() const
{
	return mImpl->isConnected();
}

// �\�P�b�g�̃V���b�g�_�E�����s���D
void Socket::shutdown(int how)
{
	mImpl->shutdown(how);
}