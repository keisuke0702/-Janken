#ifndef _INETSOCKETADDRESS_H_
#define _INETSOCKETADDRESS_H_
#include "InetAddress.h"

// インターネットソケットアドレスクラス．
class InetSocketAddress
{
public:
	// コンストラクタ．
	InetSocketAddress(const InetAddress& address = InetAddress(), int port = 0);
	// インターネットアドレスの取得．
	const InetAddress& getInetAddress() const;
	// ポート番号の取得．
	int getPort() const;
private:
	// インターネットアドレス
	InetAddress mAddress;
	// ポート番号
	int mPort;
};

#endif