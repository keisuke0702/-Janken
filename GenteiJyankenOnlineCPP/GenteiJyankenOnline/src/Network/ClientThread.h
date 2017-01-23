#ifndef _CLIENTTHREAD_H_
#define _CLIENTTHREAD_H_
#include "Thread.h"
#include <string>
#include <memory>
// �T�[�o�[�X���b�h�N���X
class ServerThread;
// �\�P�b�g�N���X
class Socket;
// �N���C�A���g�X���b�h�N���X
class ClientThread : public Thread
{
public:
	// �R���X�g���N�^
	ClientThread(ServerThread& server, Socket* socket, const std::string& name);
	// �f�X�g���N�^�D
	~ClientThread();
	// �X���b�h�̋N���D
	void run();
	// �����I��
	void end();
	// �X���b�h���I�����Ă��邩�H
	bool isEnd();
	// ���b�Z�[�W�𑗐M
	void send(const std::string& message);
private:
	// �T�[�o�[�X���b�h
	ServerThread& mServer;
	// �N���C�A���g�p�̑���M�\�P�b�g
	std::auto_ptr<Socket> mSocket;
	// �I���t���O
	bool mIsEnd;
	// ���[�U�[��
	std::string mName;
};
#endif