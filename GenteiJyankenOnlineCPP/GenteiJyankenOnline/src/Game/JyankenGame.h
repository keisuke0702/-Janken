#pragma once

#include <string>

class JyankenGame
{
public:
	//コンストラクタ
	JyankenGame() = default;
	// 入力した数値をジャンケンの手の文字列に変換する関数 1->グー 2->チョキ 3->パー
	std::string NumberToHand(int num);

	// サーバー関数
	void Server();
	// クライアント関数
	void Client();
	//描画
	void Draw();
	// 実行
	void Run();
};