#ifndef _SOCKETEXCEPTION_H_
#define _SOCKETEXCEPTION_H_
#include <stdexcept>

// �\�P�b�g��O�N���X�D
class SocketException : public std::runtime_error
{
public:
	// �R���X�g���N�^�D
	SocketException(const std::string& msg)
		: std::runtime_error(msg)
	{
	}
};

#endif