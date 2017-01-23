#ifndef _SOCKETEXCEPTION_H_
#define _SOCKETEXCEPTION_H_
#include <stdexcept>

// ソケット例外クラス．
class SocketException : public std::runtime_error
{
public:
	// コンストラクタ．
	SocketException(const std::string& msg)
		: std::runtime_error(msg)
	{
	}
};

#endif