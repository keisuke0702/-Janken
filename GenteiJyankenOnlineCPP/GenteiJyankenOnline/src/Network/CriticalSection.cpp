#include "CriticalSection.h"
// コンストラクタ
CriticalSection::CriticalSection()
{
	::InitializeCriticalSection(&mCriticalSection);
}
//デストラクタ
CriticalSection::~CriticalSection()
{
	::DeleteCriticalSection(&mCriticalSection);
}
// クリティカルセクション開始
void CriticalSection::enter()
{
	::EnterCriticalSection(&mCriticalSection);
}
// クリティカルセクション終了
void CriticalSection::leave()
{
	::LeaveCriticalSection(&mCriticalSection);
}
// コンストラクタ
CriticalSection::Lock::Lock(CriticalSection& cs) :
	mCriticalSection(cs)
{
	mCriticalSection.enter();
}
// デストラクタ
CriticalSection::Lock::~Lock()
{
	mCriticalSection.leave();
}