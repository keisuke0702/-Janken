#ifndef _THREAD_H_
#define _THREAD_H_

#include "IRunnable.h"

// スレッドクラス
class Thread : public IRunnable
{
public:
	// コンストラクタ
	Thread(IRunnable* runnable = 0);
	// デストトラクタ
	virtual ~Thread();
	// スレッドの開始．
	virtual void start();
	//スレッドの開始
	virtual void start(IRunnable* runnable);
	// スレッドの終了を待つ．
	void join();
	// スリープする
	static void sleep(unsigned int millsecond);
	// スレッドの実行
	virtual void run();
private:
	// コールバック関数
	static void callback(void* runnable);
private:
	// スレッドのハンドル
	void* mHandle;
	// 実行するスレッド
	IRunnable* mRunnable;
};

#endif