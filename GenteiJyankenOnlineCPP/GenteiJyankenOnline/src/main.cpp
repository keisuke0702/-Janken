#include "udpchat.h"
#include "simple_1on1_chat.h"
#include "Game\Game.h"
#include "Game\JyankenGame.h"
#include "Network\Thread.h"


//ゲームの描画を行うスレッド
class DrawThread : public Thread
{
public:
	void run()
	{
		Game().run();
	}
};

//ジャンケンを行うスレッド
class JyankenThread : public Thread
{
private:
	JyankenGame g;

public:
	JyankenGame GetInstance()
	{
		return g;
	}

	void run()
	{
		g.Run();
	}
};

void main()
{
	//DrawThread drawThread;
	//JyankenThread jyankenThread;

	////スレッド開始
	//drawThread.start();
	//jyankenThread.start();


	////終了待機
	//drawThread.join();
	//jyankenThread.join();

	JyankenGame game;
	game.Run();

	//Game().run();
}