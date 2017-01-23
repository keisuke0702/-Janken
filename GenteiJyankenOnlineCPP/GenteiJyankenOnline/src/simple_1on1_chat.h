
////簡易チャットプログラム
#include <winsock2.h> // WinSockのヘッダファイル
#include "./Network/Socket.h"
#include "./Network/ServerSocket.h"
#include <iostream>
#include <string>
#include <memory>
// WinSockライブラリの指定
#pragma comment ( lib, "WSock32.lib" )

// プログラム サーバー関数
void Server(void)
{
	// ポート番号の入力
	std::cout << "使用するポート番号--> ";
	int port;
	std::cin >> port;
	std::cin.sync();
	// サーバー用のソケットを用意
	ServerSocket server(port);
	// 接続を待機する
	std::cout << "acceptで待機します" << std::endl;
	std::auto_ptr<Socket> client = server.accept();
	// 接続してきたクライアントのIPアドレスを表示
	std::cout << client->getAddress().getHostAddress() << "が接続してきました" << std::endl;
	// 会話開始
	std::cout << "会話開始です" << std::endl;
	while (1) {
		// データの受信
		std::cout << "受信を待っています" << std::endl;
		std::string recvMessage = client->receive();
		// 接続切断のチェック
		if (recvMessage == "c_end") {
			std::cout << "クライアントが接続を切断しました" << std::endl;
			break;
		}
		// 受信メッセージの表示
		std::cout << "受信 --> " << recvMessage << std::endl;
		// 送信メッセージの入力
		std::cout << "送信 --> ";
		std::string sendMessage;
		std::cin >> sendMessage;
		std::cin.sync();
		// データの送信
		client->send(sendMessage);
		// サーバーからの接続切断
		if (sendMessage == "s_end") {
			break;
		}
	}
	// ソケットを閉じる
	client->close();
}
// プログラム クライアント関数
void Client()
{
	// ポート番号の入力
	std::cout << "使用するポート番号--> ";
	int port;
	std::cin >> port;
	std::cin.sync();

	// サーバー名の入力
	std::cout << "サーバー名 --> ";
	std::string serverAddress;
	std::cin >> serverAddress;
	std::cin.sync();
	// 通信用ソケットを用意
	Socket socket(InetSocketAddress(serverAddress, port));
	std::cout << "サーバーに接続できました" << std::endl;
	while (1) {
		// 送信メッセージの入力
		std::cout << "送信 --> ";
		std::string sendMessage;
		std::cin >> sendMessage;
		std::cin.sync();
		// データを送信する
		socket.send(sendMessage);
		// 接続を切断するか？
		if (sendMessage == "c_end") {
			break;
		}
		// サーバーからのデータを受信する
		std::string recvMessage = socket.receive();
		// サーバーの接続要求があったか？
		if (recvMessage == "s_end") {
			std::cout << "サーバーが接続を切断しました" << std::endl;
			break;
		}
		// 受信データの表示
		std::cout << "受信 --> " << recvMessage << std::endl;
	}
	// ソケットを閉じる
	socket.close();
}


void main_function_simplechat()
{
	////簡易チャット実行
	// WinSockの初期化
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		// 初期化エラー
		std::cout << "WinSockの初期化に失敗しました" << std::endl;
		return;
	}
	// サーバーか？ クライアントか？
	std::cout << "サーバーなら0を入力 クライアントなら1を入力 --> ";
	int mode;
	std::cin >> mode;
	std::cin.sync();
	try {
		if (mode == 0) {
			// サーバーとして起動
			Server();
		}
		else {
			// クライアントとして起動
			Client();
		}
	}
	catch (SocketException& e) {
		// エラーメッセージを出力
		std::cout << e.what() << std::endl;
	}
	// WinSockの終了処理
	WSACleanup();
}


