#include "SocketImpl.h"

class ChatMain1
{
public:
	//�R���X�g���N�^
	ChatMain1();

	//�T�[�o�[�֐�
	void ChatServer();

	//�N���C�A���g�֐�
	void ChatClient();

	//���s
	void Run();
private:
	SocketImpl mImpl;
};
