#include "Socket.h"
#include "SocketImpl.h"
#include <vector>

// 受信をシャットダウン*/
const int Socket::SHUTDOWN_RECEIVE = SocketImpl::SHUTDOWN_RECEIVE;
// 送信をシャットダウン*/
const int Socket::SHUTDOWN_SEND = SocketImpl::SHUTDOWN_SEND;
// 送受信をシャットダウン*/
const int Socket::SHUTDOWN_BOTH = SocketImpl::SHUTDOWN_BOTH;

// コンストラクタ．
Socket::Socket()
: mImpl(new SocketImpl())
{
}

// コンストラクタ．
Socket::Socket(const InetSocketAddress& address)
: mImpl(new SocketImpl())
{
	connect(address);
}

// コンストラクタ．
Socket::Socket(const InetAddress& address, int port)
: mImpl(new SocketImpl())
{
	connect(address, port);
}

// コンストラクタ．
Socket::Socket(const std::string& host, int port)
: mImpl(new SocketImpl())
{
	connect(host, port);
}

// コンストラクタ．
Socket::Socket(SocketImpl* impl) :
mImpl(impl)
{
}

// デストラクタ．
Socket::~Socket()
{
}

// ソケットの接続．
void Socket::connect(const InetSocketAddress& address)
{
	mImpl->connect(address);
}

// ソケットの接続．
void Socket::connect(const InetAddress& address, int port)
{
	connect(InetSocketAddress(address, port));
}

// ソケットの接続．
void Socket::connect(const std::string& host, int port)
{
	connect(InetSocketAddress(InetAddress(host), port));
}

// ソケットを閉じる．
void Socket::close()
{
	if (mImpl->isConnected() == true) {
		mImpl->close();
	}
}

// 接続先のソケットにデータを送信．
int Socket::send(const void* buffer, int size)
{
	int total = 0;
	while (total < size) {
		// データを送信する
		total += mImpl->send(reinterpret_cast<const char*>(buffer)+total, size - total);
	}
	return total;
}

// 接続先のソケットに文字列を送信．
int Socket::send(const std::string& msg)
{
	// NUL文字も含めて送信する
	return send(msg.c_str(), (int)msg.size() + 1);
}

// 接続先のソケットからデータを受信．
int Socket::receive(void* buffer, int size)
{
	int total = 0;
	while (total < size) {
		// データを送信する
		total += mImpl->receive(reinterpret_cast<char*>(buffer)+total, size - total);
	}
	return total;
}

// 接続先のソケットから文字列を受信．
std::string Socket::receive()
{
	// 受信バッファ
	std::vector<char> buffer;
	char revchar;
	do {
		revchar = '\0';
		receive(&revchar, sizeof(revchar));
		buffer.push_back(revchar);
	} while (revchar != '\0');
	return std::string(&buffer[0]);
}

// ソケットのアドレスを取得．
InetAddress Socket::getAddress() const
{
	return mImpl->getInetSocketAddress().getInetAddress();
}

// ソケットのポートを取得．
int Socket::getPort() const
{
	return mImpl->getInetSocketAddress().getPort();
}

// ソケットのローカルアドレスを取得．
InetAddress Socket::getLocalAddress() const
{
	return mImpl->getLocalInetSocketAddress().getInetAddress();
}

// ソケットのローカルポート番号を取得．
int Socket::getLocalPort() const
{
	return mImpl->getLocalInetSocketAddress().getPort();
}

// 接続中か調べる．
bool Socket::isConnected() const
{
	return mImpl->isConnected();
}

// ソケットのシャットダウンを行う．
void Socket::shutdown(int how)
{
	mImpl->shutdown(how);
}