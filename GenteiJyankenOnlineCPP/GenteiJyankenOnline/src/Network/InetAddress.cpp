#include "InetAddress.h"
#include <winsock2.h>

// �����Ȃh�o�A�h���X
const unsigned long InetAddress::NONE = INADDR_NONE;

// �R���X�g���N�^�D
InetAddress::InetAddress(unsigned int address) :
mIPAddress(address)
{
}

// �R���X�g���N�^�D
InetAddress::InetAddress(const std::string& address)
{
	unsigned long uaddr = ::inet_addr(address.c_str());
	if (uaddr == INADDR_NONE) {
		hostent* ent = ::gethostbyname(address.c_str());
		if (ent != 0 && ent->h_addr_list[0] != 0) {
			uaddr = *(unsigned long*)ent->h_addr_list[0];
		}
	}
	mIPAddress = uaddr;
}

// �z�X�g�A�h���X�̎擾�D
std::string InetAddress::getHostAddress() const
{
	in_addr addr;
	addr.S_un.S_addr = mIPAddress;
	return std::string(inet_ntoa(addr));
}

// ������Z�q�I�[�o�[���[�h�D
InetAddress& InetAddress::operator = (const InetAddress& other)
{
	mIPAddress = other.mIPAddress;
	return *this;
}

// ������Z�q�I�[�o�[���[�h�D
InetAddress& InetAddress::operator = (const std::string& host)
{
	*this = InetAddress(host);
	return *this;
}

// �h�o�A�h���X��Ԃ��D
unsigned long InetAddress::getAddress() const
{
	return mIPAddress;
}