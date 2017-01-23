////UDPを使用したチャットプログラム
#include "Network\DatagramSocket.h"
#include "Network\SocketException.h"
#include <iostream>
#include <string>
#include <memory>
#include <winsock2.h> // WinSockのヘッダファイル
// WinSockライブラリの指定
#pragma comment ( lib, "WSock32.lib" )
//サーバー関数
void UDPServer(void)
{
	// ポート番号の入力
	std::cout << "使用するポート番号--> ";
	int port;
	std::cin >> port;
	std::cin.sync();
	// サーバー用のソケットを用意
	DatagramSocket server(port);
	// クライアントのアドレス
	InetSocketAddress clientAddress;
	// 会話開始
	std::cout << "会話開始です" << std::endl;
	while (true) {
		// データの受信
		std::cout << "受信を待っています" << std::endl;
		// クライアントからのデータを受信する（最大２５５文字）
		char buffer[256];
		int len = server.receive(buffer, sizeof(buffer) - 1, clientAddress);
		buffer[len] = '\0';
		std::string recvMessage(buffer);

		// 接続切断のチェック
		if (recvMessage == "c_end") {
			std::cout << "クライアントが接続を切断しました" << std::endl;
			break;
		}
		// 受信メッセージの表示
		std::cout << "受信--> " << recvMessage << std::endl;
		// 送信メッセージの入力
		std::cout << "送信--> ";
		std::string sendMessage;
		std::cin >> sendMessage;
		std::cin.sync();
		// データの送信
		server.send(sendMessage.c_str(), (int)sendMessage.size(), clientAddress);
		// サーバーからの接続切断
		if (sendMessage == "s_end") {
			break;
		}
	}
}
// クライアント関数
void UDPClient()
{
	// サーバー名の入力
	std::cout << "サーバーのＩＰアドレス--> ";
	std::string address;
	std::cin >> address;
	std::cin.sync();
	// サーバーのポート番号の入力
	std::cout << "サーバーのポート番号--> ";
	int port;
	std::cin >> port;
	std::cin.sync();
	// サーバーのソケットアドレスを作成
	InetSocketAddress serverAddress(address, port);
	// ＵＤＰソケットの作成
	DatagramSocket socket;
	while (true) {
		// 送信メッセージの入力
		std::cout << "送信--> ";
		std::string sendMessage;
		std::cin >> sendMessage;
		std::cin.sync();
		// データを送信する
		socket.send(sendMessage.c_str(), (int)sendMessage.size(), serverAddress);
		// 接続を切断するか？
		if (sendMessage == "c_end") {
			break;
		}
		// データの受信
		std::cout << "受信を待っています" << std::endl;
		// サーバーからのデータを受信する（最大２５５文字）
		char buffer[256];
		int len = socket.receive(buffer, sizeof(buffer) - 1, serverAddress);
		buffer[len] = '\0';
		std::string recvMessage(buffer);
		// サーバーの接続要求があったか？
		if (recvMessage == "s_end") {
			std::cout << "サーバーが接続を切断しました" << std::endl;
			break;
		}
		// 受信データの表示
		std::cout << "受信--> " << recvMessage << std::endl;
	}
}
// チャットプログラムメイン関数
void main_function_udp()
{
	// WinSockの初期化
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		// 初期化エラー
		std::cout << "WinSockの初期化に失敗しました" << std::endl;
		return;
	}
	// サーバーか？クライアントか？
	std::cout << "サーバーなら０を入力クライアントなら１を入力--> ";
	int mode;
	std::cin >> mode;
	std::cin.sync();
	try {
		if (mode == 0) {
			// サーバーとして起動
			UDPServer();
		}
		else {
			// クライアントとして起動
			UDPClient();
		}
	}
	catch (SocketException& e) {
		// エラーメッセージを出力
		std::cout << e.what() << std::endl;
	}
	// WinSockの終了処理
	WSACleanup();
}


////////スレッド対応エコーサーバーの作成
////#include <winsock2.h>
////#include <iostream>
////#include "./Network/ServerThread.h"
////#pragma comment ( lib, "WSock32.lib" )
////int main()
////{
////	// WinSockの初期化
////	WSADATA wsaData;
////	WSAStartup(MAKEWORD(1, 1), &wsaData);
////	// ポート番号の入力
////	int port;
////	std::cout << "ポート番号を入力 --> ";
////	std::cin >> port;
////	// サーバースレッドを起動
////	ServerThread server(port);
////	server.start();
////	// エスケープキーが押されるまで
////	while (GetAsyncKeyState(VK_ESCAPE) == 0) {
////		Thread::sleep(0);
////	}
////	// サーバースレッドを強制終了
////	server.end();
////	WSACleanup();
////}
