#ifndef _SERVERTHREAD_H_
#define _SERVERTHREAD_H_
#include "Thread.h"
#include "CriticalSection.h"
#include <list>
#include <memory>
// クライアントスレッド
class ClientThread;
// サーバースレッドクラス
class ServerThread : public Thread
{
public:
	// コンストラクタ
	ServerThread(int port);
	// デストラクタ
	~ServerThread();
	// サーバースレッドの起動
	void run();
	// クライアントの追加
	void addClient(ClientThread* client);
	// クライアントの削除
	void removeClient();
	// クライアントを全て消去
	void clearClient();
	// サーバースレッドの終了
	void end();
	// ポート番号の取得
	int getPort() const;
	// 終了しているか調べる
	bool isEnd();
	// クライアントにメッセージを送信
	void sendClient(const std::string& message);

private:
	// クライアントスレッドのポインタ型
	typedef std::shared_ptr<ClientThread> ClientThreadPtr;
	//クライアントスレッドのコンテナ型
	typedef std::list<ClientThreadPtr> ClientContainer;
	// ポート番号
	int mPort;
	// 終了フラグ
	bool mIsEnd;
	// クライアントスレッドコンテナ
	ClientContainer mClientContainer;
	// クライアントスレッドコンテナロック
	CriticalSection mClientContainerLock;
};
#endif