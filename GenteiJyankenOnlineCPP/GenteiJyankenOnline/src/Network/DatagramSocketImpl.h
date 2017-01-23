#ifndef _DATAGRAMSOCKETIMPL_H_
#define _DATAGRAMSOCKETIMPL_H_
#include <winsock2.h>
// ソケットアドレスクラス
class InetSocketAddress;
// ＵＤＰソケット実装クラス．
class DatagramSocketImpl
{
public:
	// コンストラクタ．
	DatagramSocketImpl();
	// デストラクタ．
	~DatagramSocketImpl();
	// ＵＤＰソケットの作成．
	void create();
	//ソケットを閉じる．
	void close();
	// 指定されたポート番号にソケットをバインド．
	void bind(int port);
	// データを送信．
	int send(const void* buffer, int size, const InetSocketAddress& addr);
	// データを受信．
	int receive(void* buffer, int size, InetSocketAddress& addr);
private:
	// コピー禁止．
	DatagramSocketImpl(const DatagramSocketImpl& other);
	DatagramSocketImpl& operator = (const DatagramSocketImpl& other);
private:
	// ソケットハンドラ．
	SOCKET mSocket;
};
#endif