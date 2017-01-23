#ifndef _INETADDRESS_H_
#define _INETADDRESS_H_
#include <string>

// �C���^�[�l�b�g�A�h���X�N���X�D
class InetAddress
{
public:
	// �R���X�g���N�^�D
	InetAddress(unsigned int address = InetAddress::NONE);
	// �R���X�g���N�^�D
	InetAddress(const std::string& address);
	// �z�X�g�A�h���X�̎擾�D
	std::string getHostAddress() const;
	// ������Z�q�I�[�o�[���[�h�D
	InetAddress& operator = (const InetAddress& other);
	// ������Z�q�I�[�o�[���[�h�D
	InetAddress& operator = (const std::string& host);
	// �h�o�A�h���X��Ԃ��D
	unsigned long getAddress() const;
public:
	// �����Ȃh�o�A�h���X
	const static unsigned long NONE;
private:
	// IP�A�h���X
	unsigned long mIPAddress;
};

#endif