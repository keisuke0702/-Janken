#include "DatagramSocketImpl.h"
#include "InetSocketAddress.h"
#include "SocketException.h"
#include <memory>
// コンストラクタ．
DatagramSocketImpl::DatagramSocketImpl() :
	mSocket(INVALID_SOCKET)
{}
// デストラクタ．
DatagramSocketImpl::~DatagramSocketImpl()
{
	// ソケットを閉じる
	close();
}
// ＵＤＰソケットの作成．
void DatagramSocketImpl::create()
{
	// 有効なソケットを持っている場合は作成しない
	if (mSocket != INVALID_SOCKET) {
		return;
	}
	// 新しいソケットを作成する
	mSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
	// ソケットが作成できたか？
	if (mSocket == INVALID_SOCKET) {
		throw SocketException("ＵＤＰソケットが作成できません");
	}
}
// ソケットを閉じる．
void DatagramSocketImpl::close()
{
	if (mSocket != INVALID_SOCKET) {
		// ソケットを閉じる
		::closesocket(mSocket);
		// ソケットハンドラを初期化
		mSocket = INVALID_SOCKET;
	}
}
// 指定されたポート番号にソケットをバインド．
void DatagramSocketImpl::bind(int port)
{
	// ソケットを作成する
	create();
	// ソケットに名前を付ける
	SOCKADDR_IN serverAddress;
	std::memset(&serverAddress, 0, sizeof(SOCKADDR_IN));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons((u_short)port);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	if (::bind(mSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		close();
		throw SocketException("バインドに失敗しました");
	}
}
// データを送信．
int DatagramSocketImpl::send(const void* buffer, int size, const InetSocketAddress& addr)
{
	// ソケットを作成する
	create();
	// 送信先のアドレスを設定
	SOCKADDR_IN sendAddress;
	std::memset(&sendAddress, 0, sizeof(sendAddress));
	sendAddress.sin_family = AF_INET;
	sendAddress.sin_port = htons((u_short)addr.getPort());
	sendAddress.sin_addr.s_addr = addr.getInetAddress().getAddress();
	// データを送信する
	int result = ::sendto(
		mSocket,
		(const char*)buffer, size,
		0,
		(LPSOCKADDR)&sendAddress, sizeof(sendAddress)
		);
	// 送信エラーのチェック
	if (result != size) {
		throw SocketException("送信できませんでした");
	}
	// 送信したデータサイズを返す
	return result;
}
// データを受信．
int DatagramSocketImpl::receive(void* buffer, int size, InetSocketAddress& addr)
{
	// ソケットを作成する
	create();
	// 受信データのアドレス
	SOCKADDR_IN fromAddress;
	int fromSize = sizeof(fromAddress);
	int result = ::recvfrom(
		mSocket,
		(char*)buffer, size,
		0,
		(SOCKADDR*)&fromAddress,
		&fromSize
		);
	// 受信エラーのチェック
	if (result == SOCKET_ERROR) {
		throw SocketException("受信できませんでした");
	}
	// 送信元のアドレスを設定
	addr = InetSocketAddress(fromAddress.sin_addr.s_addr, ::ntohs(fromAddress.sin_port));
	// 受信したデータサイズを返す
	return result;
}
