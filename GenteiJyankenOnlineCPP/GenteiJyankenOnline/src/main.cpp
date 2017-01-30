#include "udpchat.h"
#include "simple_1on1_chat.h"
#include "Game\Game.h"
#include "Game\JyankenGame.h"
#include "Network\Thread.h"


//�Q�[���̕`����s���X���b�h
class DrawThread : public Thread
{
public:
	void run()
	{
		Game().run();
	}
};

//�W�����P�����s���X���b�h
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

	////�X���b�h�J�n
	//drawThread.start();
	//jyankenThread.start();


	////�I���ҋ@
	//drawThread.join();
	//jyankenThread.join();

	JyankenGame game;
	game.Run();

	//Game().run();
}