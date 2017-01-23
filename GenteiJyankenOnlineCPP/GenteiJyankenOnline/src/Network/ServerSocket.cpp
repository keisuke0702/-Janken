#include "ServerSocket.h"
#include "SocketImpl.h"

// コンストラクタ．
ServerSocket::ServerSocket() :
mImpl(new SocketImpl())
{
}

// コンストラクタ．
ServerSocket::ServerSocket(int port, int backlog) :
mImpl(new SocketImpl())
{
	bind(port, backlog);
}

// デストラクタ．
ServerSocket::~ServerSocket()
{
}

// 接続要求を待機して，ソケットを受け入れる．
std::auto_ptr<Socket> ServerSocket::accept()
{
	return std::auto_ptr<Socket>(new Socket(mImpl->accept()));
}

// ソケットをバインドして，リスン状態にする．
void ServerSocket::bind(int port, int backlog)
{
	mImpl->bind(port);
	mImpl->listen(backlog);
}

// ソケットを閉じる．
void ServerSocket::close()
{
	if (mImpl->isConnected() == true) {
		mImpl->close();
	}
}

// ソケットのアドレスを取得．
InetAddress ServerSocket::getAddress() const
{
	return mImpl->getLocalInetSocketAddress().getInetAddress();
}

// ソケットのポート番号を取得．
int ServerSocket::getPort() const
{
	return mImpl->getLocalInetSocketAddress().getPort();
}