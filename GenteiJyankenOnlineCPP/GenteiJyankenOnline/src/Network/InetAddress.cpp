#include "InetAddress.h"
#include <winsock2.h>

// 無効なＩＰアドレス
const unsigned long InetAddress::NONE = INADDR_NONE;

// コンストラクタ．
InetAddress::InetAddress(unsigned int address) :
mIPAddress(address)
{
}

// コンストラクタ．
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

// ホストアドレスの取得．
std::string InetAddress::getHostAddress() const
{
	in_addr addr;
	addr.S_un.S_addr = mIPAddress;
	return std::string(inet_ntoa(addr));
}

// 代入演算子オーバーロード．
InetAddress& InetAddress::operator = (const InetAddress& other)
{
	mIPAddress = other.mIPAddress;
	return *this;
}

// 代入演算子オーバーロード．
InetAddress& InetAddress::operator = (const std::string& host)
{
	*this = InetAddress(host);
	return *this;
}

// ＩＰアドレスを返す．
unsigned long InetAddress::getAddress() const
{
	return mIPAddress;
}