#include "InetSocketAddress.h"

// コンストラクタ．
InetSocketAddress::InetSocketAddress(const InetAddress& address, int port) :
mAddress(address),
mPort(port)
{
}

// インターネットアドレスの取得．
const InetAddress& InetSocketAddress::getInetAddress() const
{
	return mAddress;
}

// ポート番号の取得．
int InetSocketAddress::getPort() const
{
	return mPort;
}