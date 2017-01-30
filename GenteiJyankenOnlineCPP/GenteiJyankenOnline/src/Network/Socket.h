#ifndef _SOCKET_H_
#define _SOCKET_H_
#include "InetSocketAddress.h"
#include "SocketException.h"
#include <string>
#include <memory>
class SocketImpl;

// ソケットクラス．
class Socket
{
public:
	// コンストラクタ．
	Socket();
	// コンストラクタ．
	Socket(const InetSocketAddress& address);
	// コンストラクタ．
	Socket(const InetAddress& address, int port);
	// コンストラクタ．
	Socket(const std::string& host, int port);
	// コンストラクタ．
	Socket(SocketImpl* impl);
	// デストラクタ．
	virtual ~Socket();
	// ソケットの接続．
	void connect(const InetSocketAddress& address);
	// ソケットの接続．
	void connect(const InetAddress& address, int port);
	// ソケットの接続．
	void connect(const std::string& host, int port);
	// ソケットを閉じる．
	void close();
	// 接続先のソケットにデータを送信．
	int send(const void* buffer, int size);
	// 接続先のソケットに文字列を送信．
	int send(const std::string& msg);
	// 接続先のソケットからデータを受信．
	int receive(void* buffer, int size);
	// 接続先のソケットから文字列を受信．
	std::string receive();
	// ソケットのアドレスを取得．
	InetAddress getAddress() const;
	// ソケットのポートを取得．
	int getPort() const;
	// ソケットのローカルアドレスを取得．
	InetAddress getLocalAddress() const;
	// ソケットのローカルポート番号を取得．
	int getLocalPort() const;
	// 接続中か調べる．
	bool isConnected() const;
	// ソケットのシャットダウンを行う．
	void shutdown(int how = Socket::SHUTDOWN_BOTH);
public:
	// 受信をシャットダウン
	const static int SHUTDOWN_RECEIVE;
	// 送信をシャットダウン
	const static int SHUTDOWN_SEND;
	// 送受信をシャットダウン
	const static int SHUTDOWN_BOTH;
private:
	// コピー禁止
	Socket(const Socket& other);
	Socket& operator = (const Socket& other);
private:
	// ソケット実装クラス
	std::auto_ptr<SocketImpl> mImpl;
};

#endif