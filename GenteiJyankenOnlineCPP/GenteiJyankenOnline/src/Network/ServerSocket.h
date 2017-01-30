#ifndef _SERVERSOCKET_H_
#define _SERVERSOCKET_H_
#include "Socket.h"
#include <memory>
class SocketImpl;

// サーバーソケットクラス．
class ServerSocket
{
public:
	// コンストラクタ．
	ServerSocket();
	// コンストラクタ．（バインドする）
	ServerSocket(int port, int backlog = 0);
	// デストラクタ．
	virtual ~ServerSocket();
	// 接続要求を待機して，ソケットを受け入れる．
	std::auto_ptr<Socket> accept();
	// ソケットをバインドして，リスン状態にする．
	void bind(int port, int backlog = 0);
	// ソケットを閉じる．
	void close();
	// ソケットのアドレスを取得．
	InetAddress getAddress() const;
	// ソケットのポート番号を取得．
	int getPort() const;
private:
	// コピー禁止
	ServerSocket(const ServerSocket& other);
	ServerSocket& operator = (const ServerSocket& other);
private:
	// ソケット実装クラス
	std::auto_ptr<SocketImpl> mImpl;
};

#endif
