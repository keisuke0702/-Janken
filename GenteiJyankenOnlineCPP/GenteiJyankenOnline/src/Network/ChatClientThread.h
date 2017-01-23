#ifndef _CHATCLIENTTHREAD_H_
#define _CHATCLIENTTHREAD_H_
#include "Thread.h"
#include "MessageBuffer.h"
#include "CriticalSection.h"
#include "Socket.h"
#include "InetSocketAddress.h"
#include <string>

// チャットクライアントスレッドクラス
class ChatClientThread : public Thread
{
public:
	// コンストラクタ
	ChatClientThread(unsigned int bufferSize);
	// デストラクタ
	~ChatClientThread();
	// ユーザー名の設定
	void setName(const std::string& name);
	// サーバーのソケットアドレスの設定
	void setServerAddress(const InetSocketAddress& address);
	// スレッドの実行
	void run();
	// メッセージを送信
	void sendMessage(const std::string& message);
	// メッセージの出力
	void printMessgae(std::ostream& out);
	// 接続中か？
	bool isConnect();
	// 強制終了する
	void end();
private:
	// サーバーのソケットアドレス
	InetSocketAddress mServerAddress;
	// ユーザー名
	std::string mName;
	// メッセージバッファ
	MessageBuffer mMessageBuffer;
	// 通信用ソケット
	Socket mSocket;

};
#endif