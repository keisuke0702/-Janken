#ifndef _INETADDRESS_H_
#define _INETADDRESS_H_
#include <string>

// インターネットアドレスクラス．
class InetAddress
{
public:
	// コンストラクタ．
	InetAddress(unsigned int address = InetAddress::NONE);
	// コンストラクタ．
	InetAddress(const std::string& address);
	// ホストアドレスの取得．
	std::string getHostAddress() const;
	// 代入演算子オーバーロード．
	InetAddress& operator = (const InetAddress& other);
	// 代入演算子オーバーロード．
	InetAddress& operator = (const std::string& host);
	// ＩＰアドレスを返す．
	unsigned long getAddress() const;
public:
	// 無効なＩＰアドレス
	const static unsigned long NONE;
private:
	// IPアドレス
	unsigned long mIPAddress;
};

#endif