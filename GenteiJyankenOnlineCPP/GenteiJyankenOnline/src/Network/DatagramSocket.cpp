#include "DatagramSocket.h"
#include "DatagramSocketImpl.h"
// コンストラクタ．
DatagramSocket::DatagramSocket() :
	mImpl(new DatagramSocketImpl())
{}
// コンストラクタ．
DatagramSocket::DatagramSocket(int port) :
	mImpl(new DatagramSocketImpl())
{
	// バインドする
	bind(port);
}
// デストラクタ．
DatagramSocket::~DatagramSocket()
{}
// ソケットをバインドする．
void DatagramSocket::bind(int port)
{
	mImpl->bind(port);
}
// データを送信．
int DatagramSocket::send(const void* buffer, int size, const InetSocketAddress& addr)
{
	return mImpl->send(buffer, size, addr);
}
// データを受信．
int DatagramSocket::receive(void* buffer, int size, InetSocketAddress& addr)
{
	return mImpl->receive(buffer, size, addr);
}
// ソケットを閉じる．
void DatagramSocket::close()
{
	mImpl->close();
}