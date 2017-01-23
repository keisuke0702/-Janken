#ifndef _SOCKETIMPL_H_
#define _SOCKETIMPL_H_
#include <winsock2.h>
#include "InetSocketAddress.h"
// ソケット実装クラス
class SocketImpl
{
public:
	// コンストラクタ．
	SocketImpl();
	// デストラクタ．
	~SocketImpl();
	// ソケットの接続．
	void connect(const InetSocketAddress& address);
	// ソケットを閉じる．
	void close();
	// 接続先のソケットにデータを送信．
	int send(const void* buffer, int size);
	// 接続先のソケットからデータを受信．
	int receive(void* buffer, int size);
	// 接続を受け入れる．
	SocketImpl* accept();
	// 指定されたポート番号にソケットをバインドする．
	void bind(int port);
	// ソケットをリスン状態にする．
	void listen(int backlog = 0);
	// ソケットのシャットダウンを行う．
	void shutdown(int how);
	// 接続先のソケットのソケットアドレスを取得．
	InetSocketAddress getInetSocketAddress() const;
	// ローカルソケットアドレスを取得．
	InetSocketAddress getLocalInetSocketAddress() const;
	// 接続中か調べる．
	bool isConnected() const;
private:
	// コピー禁止
	SocketImpl(const SocketImpl& other);
	SocketImpl& operator = (const SocketImpl& other);
public:
	// 受信をシャットダウン
	const static int SHUTDOWN_RECEIVE;
	// 送信をシャットダウン
	const static int SHUTDOWN_SEND;
	// 送受信をシャットダウン
	const static int SHUTDOWN_BOTH;
private:
	// ソケットハンドラ
	SOCKET mSocket;
	// ソケットアドレス
	InetSocketAddress mSocketAddress;
};
#endif