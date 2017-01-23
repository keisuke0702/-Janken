#ifndef _INETSOCKETADDRESS_H_
#define _INETSOCKETADDRESS_H_
#include "InetAddress.h"

// �C���^�[�l�b�g�\�P�b�g�A�h���X�N���X�D
class InetSocketAddress
{
public:
	// �R���X�g���N�^�D
	InetSocketAddress(const InetAddress& address = InetAddress(), int port = 0);
	// �C���^�[�l�b�g�A�h���X�̎擾�D
	const InetAddress& getInetAddress() const;
	// �|�[�g�ԍ��̎擾�D
	int getPort() const;
private:
	// �C���^�[�l�b�g�A�h���X
	InetAddress mAddress;
	// �|�[�g�ԍ�
	int mPort;
};

#endif