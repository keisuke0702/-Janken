#include "SocketImpl.h"
#include "SocketException.h"
#include <memory>
/** 受信をシャットダウン*/
const int SocketImpl::SHUTDOWN_RECEIVE = SD_RECEIVE;
/** 送信をシャットダウン*/
const int SocketImpl::SHUTDOWN_SEND = SD_SEND;
/** 送受信をシャットダウン*/
const int SocketImpl::SHUTDOWN_BOTH = SD_BOTH;
// コンストラクタ．
SocketImpl::SocketImpl()
: mSocket(INVALID_SOCKET)
{
}
// デストラクタ．
SocketImpl::~SocketImpl()
{
	// ソケットを閉じる
	close();
}
// ソケットの接続．
void SocketImpl::connect(const InetSocketAddress& address)
{
	// 新しいソケットを作成する
	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, 0);
	// ソケットが作成できたか？
	if (sock == INVALID_SOCKET) {
		throw SocketException("ソケットが作成できません");
	}
	// サーバーへのアドレスを作成
	SOCKADDR_IN serverAddress;
	std::memset(&serverAddress, 0, sizeof(SOCKADDR_IN));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(address.getPort());
	serverAddress.sin_addr.s_addr = address.getInetAddress().getAddress();
	// サーバーと接続する
	if (::connect(sock, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		::closesocket(sock);
		throw SocketException("接続できませんでした");
	}
	// 既にオープンしている場合は閉じる
	close();
	// ソケットのアドレスを設定
	mSocketAddress = address;
	// ソケットのハンドルを設定
	mSocket = sock;
}
// ソケットを閉じる．
void SocketImpl::close()
{
	// 接続中か？
	if (isConnected() == false) {
		return;
	}
	// ソケットをシャットダウンする
	shutdown(SHUTDOWN_BOTH);
	// ソケットを閉じる
	::closesocket(mSocket);
	// ソケットアドレスを初期化
	mSocketAddress = InetSocketAddress();
	// ソケットハンドラを初期化
	mSocket = INVALID_SOCKET;
}
// 接続先のソケットにデータを送信．
int SocketImpl::send(const void* buffer, int size)
{
	int result = ::send(mSocket, (const char*)buffer, size, 0);
	if (result == SOCKET_ERROR || result == 0) {
		throw SocketException("送信できませんでした");
	}
	return result;
}
// 接続先のソケットからデータを受信．
int SocketImpl::receive(void* buffer, int size)
{
	int result = ::recv(mSocket, (char*)buffer, size, 0);
	if (result == SOCKET_ERROR || result == 0) {
		throw SocketException("受信できませんでした");
	}
	return result;
}
// 接続を受け入れる．
SocketImpl* SocketImpl::accept()
{
	std::auto_ptr<SocketImpl> client(new SocketImpl());
	// 接続の受け入れを行う
	SOCKADDR_IN saddr;
	int len = (int)sizeof(saddr);
	SOCKET sock = ::accept(mSocket, (SOCKADDR*)&saddr, &len);
	if (sock == INVALID_SOCKET) {
		throw SocketException("接続の受け入れに失敗しました");
	}
	// 受け入れた接続のソケットアドレスを設定
	client->mSocketAddress = InetSocketAddress(InetAddress(::inet_ntoa(saddr.sin_addr)), saddr.sin_port);
	// 受け入れた接続のソケットハンドラを設定
	client->mSocket = sock;
	return client.release();
}
// 指定されたポート番号にソケットをバインド．
void SocketImpl::bind(int port)
{
	// 新しいソケットを作成する
	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, 0);
	// ソケットが作成できたか？
	if (sock == INVALID_SOCKET) {
		throw SocketException("ソケットが作成できません");
	}
	// ソケットに名前を付ける
	SOCKADDR_IN serverAddress;
	std::memset(&serverAddress, 0, sizeof(SOCKADDR_IN));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	// バインドをする
	if (::bind(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		::closesocket(sock);
		throw SocketException("バインドに失敗しました");
	}
	// ソケットのアドレスを設定
	mSocketAddress = InetSocketAddress(InetAddress(INADDR_ANY), port);
	// ソケットのハンドルを設定
	mSocket = sock;
}
// ソケットをリスン状態にする．
void SocketImpl::listen(int backlog)
{
	// クライアントからの接続待ちの状態にする
	if (::listen(mSocket, backlog) == SOCKET_ERROR) {
		throw SocketException("接続待ちの失敗");
	}
}
// ソケットのシャットダウンを行う．
void SocketImpl::shutdown(int how)
{
	::shutdown(mSocket, how);
}
// 接続先のソケットのソケットアドレスを取得．
InetSocketAddress SocketImpl::getInetSocketAddress() const
{
	return mSocketAddress;
}
// ソケットのローカルソケットアドレスを取得．
InetSocketAddress SocketImpl::getLocalInetSocketAddress() const
{
	SOCKADDR_IN saddr;
	int len = (int)sizeof(saddr);
	if (::getsockname(mSocket, (struct sockaddr *)&saddr, &len) == SOCKET_ERROR){
		return InetSocketAddress(InetAddress());
	}
	return InetSocketAddress(saddr.sin_addr.s_addr, saddr.sin_port);
}
// 接続中か調べる．
bool SocketImpl::isConnected() const
{
	return mSocket != INVALID_SOCKET;
}