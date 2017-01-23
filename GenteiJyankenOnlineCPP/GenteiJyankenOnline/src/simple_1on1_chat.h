
////�ȈՃ`���b�g�v���O����
#include <winsock2.h> // WinSock�̃w�b�_�t�@�C��
#include "./Network/Socket.h"
#include "./Network/ServerSocket.h"
#include <iostream>
#include <string>
#include <memory>
// WinSock���C�u�����̎w��
#pragma comment ( lib, "WSock32.lib" )

// �v���O���� �T�[�o�[�֐�
void Server(void)
{
	// �|�[�g�ԍ��̓���
	std::cout << "�g�p����|�[�g�ԍ�--> ";
	int port;
	std::cin >> port;
	std::cin.sync();
	// �T�[�o�[�p�̃\�P�b�g��p��
	ServerSocket server(port);
	// �ڑ���ҋ@����
	std::cout << "accept�őҋ@���܂�" << std::endl;
	std::auto_ptr<Socket> client = server.accept();
	// �ڑ����Ă����N���C�A���g��IP�A�h���X��\��
	std::cout << client->getAddress().getHostAddress() << "���ڑ����Ă��܂���" << std::endl;
	// ��b�J�n
	std::cout << "��b�J�n�ł�" << std::endl;
	while (1) {
		// �f�[�^�̎�M
		std::cout << "��M��҂��Ă��܂�" << std::endl;
		std::string recvMessage = client->receive();
		// �ڑ��ؒf�̃`�F�b�N
		if (recvMessage == "c_end") {
			std::cout << "�N���C�A���g���ڑ���ؒf���܂���" << std::endl;
			break;
		}
		// ��M���b�Z�[�W�̕\��
		std::cout << "��M --> " << recvMessage << std::endl;
		// ���M���b�Z�[�W�̓���
		std::cout << "���M --> ";
		std::string sendMessage;
		std::cin >> sendMessage;
		std::cin.sync();
		// �f�[�^�̑��M
		client->send(sendMessage);
		// �T�[�o�[����̐ڑ��ؒf
		if (sendMessage == "s_end") {
			break;
		}
	}
	// �\�P�b�g�����
	client->close();
}
// �v���O���� �N���C�A���g�֐�
void Client()
{
	// �|�[�g�ԍ��̓���
	std::cout << "�g�p����|�[�g�ԍ�--> ";
	int port;
	std::cin >> port;
	std::cin.sync();

	// �T�[�o�[���̓���
	std::cout << "�T�[�o�[�� --> ";
	std::string serverAddress;
	std::cin >> serverAddress;
	std::cin.sync();
	// �ʐM�p�\�P�b�g��p��
	Socket socket(InetSocketAddress(serverAddress, port));
	std::cout << "�T�[�o�[�ɐڑ��ł��܂���" << std::endl;
	while (1) {
		// ���M���b�Z�[�W�̓���
		std::cout << "���M --> ";
		std::string sendMessage;
		std::cin >> sendMessage;
		std::cin.sync();
		// �f�[�^�𑗐M����
		socket.send(sendMessage);
		// �ڑ���ؒf���邩�H
		if (sendMessage == "c_end") {
			break;
		}
		// �T�[�o�[����̃f�[�^����M����
		std::string recvMessage = socket.receive();
		// �T�[�o�[�̐ڑ��v�������������H
		if (recvMessage == "s_end") {
			std::cout << "�T�[�o�[���ڑ���ؒf���܂���" << std::endl;
			break;
		}
		// ��M�f�[�^�̕\��
		std::cout << "��M --> " << recvMessage << std::endl;
	}
	// �\�P�b�g�����
	socket.close();
}


void main_function_simplechat()
{
	////�ȈՃ`���b�g���s
	// WinSock�̏�����
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		// �������G���[
		std::cout << "WinSock�̏������Ɏ��s���܂���" << std::endl;
		return;
	}
	// �T�[�o�[���H �N���C�A���g���H
	std::cout << "�T�[�o�[�Ȃ�0����� �N���C�A���g�Ȃ�1����� --> ";
	int mode;
	std::cin >> mode;
	std::cin.sync();
	try {
		if (mode == 0) {
			// �T�[�o�[�Ƃ��ċN��
			Server();
		}
		else {
			// �N���C�A���g�Ƃ��ċN��
			Client();
		}
	}
	catch (SocketException& e) {
		// �G���[���b�Z�[�W���o��
		std::cout << e.what() << std::endl;
	}
	// WinSock�̏I������
	WSACleanup();
}

