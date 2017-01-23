#include "ChatMain1.h"
#include <iostream>

using namespace std;

//コンストラクタ
ChatMain1::ChatMain1():
mImpl()
{

}

//サーバー関数
void ChatMain1::ChatServer()
{
	//ポート番号の入力
	u_short uport;
	cout << "使用するポート番号を入力-->";
	cin >> uport;
	fflush(stdin);

	InetSocketAddress mSocket = InetSocketAddress(uport);	

	//リスンソケットをオープンし、ソケットをバインド
	mImpl.bind(uport);
	cout << "bind成功" << endl;

	//クライアントからの接続待ち
	mImpl.listen();
	cout << "listen成功" << endl;

	//接続を待機する
	mImpl.accept();
	cout << "accept成功" << endl;

	//会話開始
	cout << "会話開始" << endl;
	while (1)
	{

	}

	//ソケットを閉じる
}

//クライアント関数
void ChatMain1::ChatClient()
{

}

//実行
void ChatMain1::Run()
{

}