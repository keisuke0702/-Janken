#include "JyankenGame.h"
#include <winsock2.h> // WinSockのヘッダファイル
#include "../Network/Socket.h"
#include "../Network/ServerSocket.h"
#include <iostream>
#include <memory>
// WinSockライブラリの指定
#pragma comment ( lib, "WSock32.lib" )
#include <gslib.h>


std::string JyankenGame::NumberToHand(int num)
{
	std::string result = "パー";
	if (num <= 1)
		result = "グー";
	else if (num == 2)
		result = "チョキ";

	return result;
}

void JyankenGame::Server()
{
	// ポート番号の入力
	std::cout << "使用するポート番号--> ";
	int port;
	std::cin >> port;
	std::cin.sync();
	// サーバー用のソケットを用意
	ServerSocket server(port);
	// 接続を待機する
	std::cout << "クライアントからの接続があるまで待機します" << std::endl;
	std::auto_ptr<Socket> client = server.accept();
	// 接続してきたクライアントのIPアドレスを表示
	std::cout << client->getAddress().getHostAddress() << "が接続してきました" << std::endl;
	// 会話開始
	std::cout << "限定ジャンケン開始です。" << std::endl;
	while (1) {
		// データの受信
		std::cout << "相手のターンです。" << std::endl;
		std::cout << "相手の出す手を待っています…" << std::endl;
		std::string recvMessage = client->receive();
		// 接続切断のチェック
		if (recvMessage == "c_end") {
			std::cout << "クライアントが接続を切断しました" << std::endl;
			break;
		}
		//相手が出した手
		int enemyhand = std::atoi(recvMessage.c_str());

		// 受信メッセージの表示
		std::cout << "相手が出す手を決定しました。" << std::endl;
		std::cout << "あなたのターンです。" << std::endl;
		// 送信メッセージの入力
		std::cout << "出す手を数値で選んでください。" << std::endl;
		std::cout << "グー：1　　チョキ：2　　パー：3" << std::endl;
		std::string handstr;
		//自分の出した手
		int hand;
		do {
			std::cout << "-->";
			std::cin >> handstr;
			hand = std::atoi(handstr.c_str());
			if (hand < 1 || hand > 3)
				std::cout << "無効な数値です。" << std::endl;
		} while (hand < 1 || hand > 3);
		std::cin.sync();

		//対戦結果の表示
		std::string my, enemy;
		my = NumberToHand(hand);
		enemy = NumberToHand(enemyhand);
		//結果の計算　0->あいこ	1->自分の負け	2->自分の勝ち
		int result = (hand - enemyhand + 3) % 3;
		std::string resultMessage = "\n結果\nあなた：" + my + "\n相　手：" + enemy + "\n";
		std::string sendResultMessage = "\n結果\nあなた：" + enemy + "\n相　手：" + my + "\n";

		if (result == 0)
		{
			resultMessage += "あいこです。\n";
			sendResultMessage += "あいこです。\n";
		}			
		else if (result == 1)
		{
			resultMessage += "あなたの負けです。\n";
			sendResultMessage += "あなたの勝ちです。\n";
		}
		else
		{
			resultMessage += "あなたの勝ちです。\n";
			sendResultMessage += "あなたの負けです。\n";
		}
		
		//結果の表示
		std::cout << resultMessage << std::endl;
		// 対戦結果の送信
		client->send(sendResultMessage);

		// サーバーからの接続切断
		if (handstr == "s_end") {
			break;
		}
	}
	// ソケットを閉じる
	client->close();
}

void JyankenGame::Client()
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
	std::cout << "限定ジャンケン開始です。" << std::endl;
	while (1) {
		// 送信メッセージの入力
		std::cout << "あなたのターンです。" << std::endl;
		std::cout << "出す手を数値で選んでください。" << std::endl;
		std::cout << "グー：1　　チョキ：2　　パー：3" << std::endl;
		std::string handstr;
		int hand;
		do {
			std::cout << "-->";
			std::cin >> handstr;
			hand = std::atoi(handstr.c_str());
			if (hand < 1 || hand > 3)
				std::cout << "無効な数値です。" << std::endl;
		} while (hand < 1 || hand > 3);
		std::cin.sync();
		// データを送信する
		socket.send(handstr);

		// 接続を切断するか？
		if (handstr == "c_end") {
			break;
		}

		// サーバーからのデータを受信する
		std::cout << "相手のターンです。" << std::endl;
		std::cout << "相手の出す手を待っています…" << std::endl;
		std::string recvMessage = socket.receive();
		// サーバーの接続要求があったか？
		if (recvMessage == "s_end") {
			std::cout << "サーバーが接続を切断しました" << std::endl;
			break;
		}
		// 受信データの表示
		std::cout << recvMessage << std::endl;
	}
	// ソケットを閉じる
	socket.close();
}

void JyankenGame::Draw()
{

}

void JyankenGame::Run()
{
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
