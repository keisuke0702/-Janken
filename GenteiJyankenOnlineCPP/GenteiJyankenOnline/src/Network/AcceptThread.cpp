#include "AcceptThread.h"
#include "ServerThread.h"
#include "ClientThread.h"
#include "Socket.h"
#include "SocketException.h"
#include "InetAddress.h"
#include <iostream>
// コンストラクタ
AcceptThread::AcceptThread(ServerThread& server) :
	mServer(server),
	mIsEnd(false)
{
}
// デストラクタ
AcceptThread::~AcceptThread()
{
	// 強制終了する
	end();
}
// スレッドの起動
void AcceptThread::run()
{
	mIsEnd = false;
	try {
		// サーバーソケットをバインドする
		mServerSocket.bind(mServer.getPort());
		while (isEnd() == false) {
			std::cout << "クライアント接続待ち" << std::endl;
			// クライアントを受け付ける
			std::auto_ptr<Socket> client(mServerSocket.accept());
			std::cout << client->getAddress().getHostAddress() << "接続しました" << std::endl;
			// ユーザー名を受信する
			std::string name = client->receive();
			// サーバーにクライアントを追加する
			mServer.addClient(new ClientThread(mServer, client.release(), "testname"));
			// 他のスレッドに制御を渡す
			Thread::sleep(0);
		}
	}
	catch (SocketException&) {
	}
	// ソケットを閉じる
	mServerSocket.close();
	// スレッドの終了
	mIsEnd = true;
}
// 強制終了
void AcceptThread::end()
{
	// 終了フラグを設定
	mIsEnd = true;
	// ソケットを閉じる
	mServerSocket.close();
	// スレッドの終了を待つ
	join();
}
// 終了しているか？
bool AcceptThread::isEnd()
{
	return mIsEnd;
}
