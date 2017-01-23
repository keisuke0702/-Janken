#include "ServerThread.h"
#include "ClientThread.h"
#include "AcceptThread.h"
#include "Socket.h"
#include <functional>
#include <algorithm>

// コンストラクタ
ServerThread::ServerThread(int port) :
	mPort(port),
	mIsEnd(false)
{
}
// デストラクタ
ServerThread::~ServerThread()
{
	// 強制終了
	end();
}
// ポート番号の取得
int ServerThread::getPort() const
{
	return mPort;
}
// スレッドの実行
void ServerThread::run()
{
	// スレッドを開始
	mIsEnd = false;
	// アクセプトスレッドを作成する
	std::auto_ptr<AcceptThread> acceptor(new AcceptThread(*this));
	// 受信スレッドを起動
	acceptor->start();
	// 終了するまで繰り返し
	while (isEnd() == false) {
		// 終了したクライアントを削除
		removeClient();
		// 他のスレッドに制御を渡す
		Thread::sleep(0);
	}
	// アクセプトスレッドを強制終了
	acceptor->end();
	// クライアントを全て消去
	clearClient();
	// 終了フラグを設定
	mIsEnd = true;
}
// クライアントの追加
void ServerThread::addClient(ClientThread* client)
{
	CriticalSection::Lock guard(mClientContainerLock);
	// クライアントを登録
	mClientContainer.push_back(ClientThreadPtr(client));
	// クライアントスレッド起動
	client->start();
}
// クライアントの削除
void ServerThread::removeClient()
{
	CriticalSection::Lock guard(mClientContainerLock);
	// 終了しているクライアントを削除
	mClientContainer.remove_if(std::mem_fn(&ClientThread::isEnd));
}
// クライアントを全て消去
void ServerThread::clearClient()
{
	CriticalSection::Lock guard(mClientContainerLock);
	// クライアント全て消去
	mClientContainer.clear();
}
// 強制終了
void ServerThread::end()
{
	// 終了フラグを設定する
	mIsEnd = true;
	// スレッドの終了を待つ
	join();
}
// 終了しているか？
bool ServerThread::isEnd()
{
	return mIsEnd;
}
// クライアントにメッセージを送信
void ServerThread::sendClient(const std::string & message)
{
	CriticalSection::Lock guard(mClientContainerLock);
	// 全クライアントにメッセージを送る
	std::for_each(
		mClientContainer.begin(),
		mClientContainer.end(),
		std::bind(std::mem_fn(&ClientThread::send), std::placeholders::_1, message)
		);
}
