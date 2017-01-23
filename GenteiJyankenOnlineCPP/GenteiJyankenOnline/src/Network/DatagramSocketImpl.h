#ifndef _DATAGRAMSOCKETIMPL_H_
#define _DATAGRAMSOCKETIMPL_H_
#include <winsock2.h>
// �\�P�b�g�A�h���X�N���X
class InetSocketAddress;
// �t�c�o�\�P�b�g�����N���X�D
class DatagramSocketImpl
{
public:
	// �R���X�g���N�^�D
	DatagramSocketImpl();
	// �f�X�g���N�^�D
	~DatagramSocketImpl();
	// �t�c�o�\�P�b�g�̍쐬�D
	void create();
	//�\�P�b�g�����D
	void close();
	// �w�肳�ꂽ�|�[�g�ԍ��Ƀ\�P�b�g���o�C���h�D
	void bind(int port);
	// �f�[�^�𑗐M�D
	int send(const void* buffer, int size, const InetSocketAddress& addr);
	// �f�[�^����M�D
	int receive(void* buffer, int size, InetSocketAddress& addr);
private:
	// �R�s�[�֎~�D
	DatagramSocketImpl(const DatagramSocketImpl& other);
	DatagramSocketImpl& operator = (const DatagramSocketImpl& other);
private:
	// �\�P�b�g�n���h���D
	SOCKET mSocket;
};
#endif