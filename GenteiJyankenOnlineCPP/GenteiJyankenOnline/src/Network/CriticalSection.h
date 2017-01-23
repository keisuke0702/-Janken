#ifndef _CRITICALSECTION_H_
#define _CRITICALSECTION_H_
#include <windows.h>
// �N���e�B�J���Z�N�V�����N���X�D
class CriticalSection
{
public:
	// �R���X�g���N�^
	CriticalSection();
	// �f�X�g���N�^
	~CriticalSection();
	// �N���e�B�J���Z�N�V�����J�n
	void enter();
	// �N���e�B�J���Z�N�V�����I��
	void leave();
	// ���b�N�N���X
	class Lock
	{
	public:
		// �R���X�g���N�^�D
		Lock(CriticalSection& cs);
		// �f�X�g���N�^�D
		~Lock();
	private:
		// �N���e�B�J���Z�N�V����
		CriticalSection& mCriticalSection;
	};
private:
	// �N���e�B�J���Z�N�V����
	CRITICAL_SECTION mCriticalSection;
};
#endif