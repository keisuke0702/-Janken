#include "ChatClientThread.h"
#include "SocketException.h"
// コンストラクタ
ChatClientThread::ChatClientThread(unsigned int bufferSize) :
	mMessageBuffer(bufferSize)
{
}
// デストラクタ
ChatClientThread::~ChatClientThread()
{
	// 強制終了する
	end();
}
// ユーザー名の設定
void ChatClientThread::setName(const std::string& name)
{
	mName = name;
}
// サーバーのソケットアドレスの設定
void ChatClientThread::setServerAddress(const InetSocketAddress& address)
{
	mServerAddress = address;
}
// スレッドの実行
void ChatClientThread::run()
{
	// メッセージバッファを初期化
	mMessageBuffer.clear();
	mMessageBuffer.add("サーバーに接続しています…");
	try {
		// サーバーに接続する
		mSocket.connect(mServerAddress);
		mMessageBuffer.add("サーバーに接続できました");
		// ユーザー名を送信する
		sendMessage(mName);
		// 接続中は受信をする
		while (isConnect() == true) {
			// サーバーからのメッセージをバッファに追加
			mMessageBuffer.add(mSocket.receive());
			// 他のスレッドに制御を渡す
			Thread::sleep(0);
		}
	}
	catch (SocketException& e) {
		mMessageBuffer.add(e.what());
	}
	// ソケットを閉じる
	mSocket.close();
	mMessageBuffer.add("切断しました");
}
// メッセージを送信
void ChatClientThread::sendMessage(const std::string& message)
{
	// 接続中でなければ送信できない
	if (isConnect() == false) {
		return;
	}
	// メッセージの送信を行う
	try {
		mSocket.send(message);
	}
	catch (SocketException& e) {
		mMessageBuffer.add(e.what());
	}
}
// メッセージの出力
void ChatClientThread::printMessgae(std::ostream& out)
{
	mMessageBuffer.print(out);
}
// 接続中か？
bool ChatClientThread::isConnect()
{
	return mSocket.isConnected();
}
// 強制終了
void ChatClientThread::end()
{
	// ソケットを強制的に閉じる
	mSocket.close();
	// スレッドの終了を待つ
	join();
}
