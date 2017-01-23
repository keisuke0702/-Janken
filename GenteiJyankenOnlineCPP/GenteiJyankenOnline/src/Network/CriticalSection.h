#ifndef _CRITICALSECTION_H_
#define _CRITICALSECTION_H_
#include <windows.h>
// クリティカルセクションクラス．
class CriticalSection
{
public:
	// コンストラクタ
	CriticalSection();
	// デストラクタ
	~CriticalSection();
	// クリティカルセクション開始
	void enter();
	// クリティカルセクション終了
	void leave();
	// ロッククラス
	class Lock
	{
	public:
		// コンストラクタ．
		Lock(CriticalSection& cs);
		// デストラクタ．
		~Lock();
	private:
		// クリティカルセクション
		CriticalSection& mCriticalSection;
	};
private:
	// クリティカルセクション
	CRITICAL_SECTION mCriticalSection;
};
#endif