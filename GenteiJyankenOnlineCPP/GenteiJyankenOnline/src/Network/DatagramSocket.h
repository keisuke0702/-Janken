#ifndef _DATAGRAMSOCKET_H_
#define _DATAGRAMSOCKET_H_
#include "InetSocketAddress.h"
#include <memory>
// ＵＤＰソケット実装クラス
class DatagramSocketImpl;
// ＵＤＰソケットクラス．
class DatagramSocket
{
public:
	// コンストラクタ．
	DatagramSocket();
	// コンストラクタ．
	DatagramSocket(int port);
	// デストラクタ．
	virtual ~DatagramSocket();
	// ソケットをバインドする．
	void bind(int port);
	// データを送信．
	int send(const void* buffer, int size, const InetSocketAddress& addr);
	// データを受信．
	int receive(void* buffer, int size, InetSocketAddress& addr);
	// ソケットを閉じる．
	void close();
private:
	// コピー禁止
	DatagramSocket(const DatagramSocket& other);
	DatagramSocket& operator = (const DatagramSocket& other);
private:
	// ＵＤＰソケット実装クラス
	std::auto_ptr<DatagramSocketImpl> mImpl;
};
#endif