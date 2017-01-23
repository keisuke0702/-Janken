#ifndef _CLIENTTHREAD_H_
#define _CLIENTTHREAD_H_
#include "Thread.h"
#include <string>
#include <memory>
// サーバースレッドクラス
class ServerThread;
// ソケットクラス
class Socket;
// クライアントスレッドクラス
class ClientThread : public Thread
{
public:
	// コンストラクタ
	ClientThread(ServerThread& server, Socket* socket, const std::string& name);
	// デストラクタ．
	~ClientThread();
	// スレッドの起動．
	void run();
	// 強制終了
	void end();
	// スレッドが終了しているか？
	bool isEnd();
	// メッセージを送信
	void send(const std::string& message);
private:
	// サーバースレッド
	ServerThread& mServer;
	// クライアント用の送受信ソケット
	std::auto_ptr<Socket> mSocket;
	// 終了フラグ
	bool mIsEnd;
	// ユーザー名
	std::string mName;
};
#endif