#include "Thread.h"

#include <windows.h>
#include <process.h>

// コンストラクタ
Thread::Thread(IRunnable* runnable) :
	mHandle(0),
	mRunnable(runnable)
{
	if (mRunnable == 0) {
		mRunnable = this;
	}
}
// デストトラクタ
Thread::~Thread()
{
}
// スレッドの開始
void Thread::start()
{
	// スレッドを開始
	mHandle = reinterpret_cast<void*>(::_beginthread(callback, 0, this));
}
// スレッドの開始
void Thread::start(IRunnable* runnable)
{
	mRunnable = runnable;
	start();
}
// スレッドの終了を待つ
void Thread::join()
{
	if (mHandle != 0) {
		::WaitForSingleObject(mHandle, INFINITE);
	}
}
// スリープする
void Thread::sleep(unsigned int millsecond)
{
	::Sleep(millsecond);
}
// スレッドの実行
void Thread::run()
{
}
// コールバック関数
void Thread::callback(void* runnable)
{
	Thread* thread = reinterpret_cast<Thread*>(runnable);
	// スレッドの処理を実行する
	thread->mRunnable->run();
	// スレッドハンドルを無効にする
	thread->mHandle = 0;
}