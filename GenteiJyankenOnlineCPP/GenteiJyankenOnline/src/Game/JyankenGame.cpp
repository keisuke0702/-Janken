#include "JyankenGame.h"
#include <winsock2.h> // WinSock�̃w�b�_�t�@�C��
#include "../Network/Socket.h"
#include "../Network/ServerSocket.h"
#include <iostream>
#include <memory>
// WinSock���C�u�����̎w��
#pragma comment ( lib, "WSock32.lib" )
#include <gslib.h>


std::string JyankenGame::NumberToHand(int num)
{
	std::string result = "�p�[";
	if (num <= 1)
		result = "�O�[";
	else if (num == 2)
		result = "�`���L";

	return result;
}

void JyankenGame::Server()
{
	// �|�[�g�ԍ��̓���
	std::cout << "�g�p����|�[�g�ԍ�--> ";
	int port;
	std::cin >> port;
	std::cin.sync();
	// �T�[�o�[�p�̃\�P�b�g��p��
	ServerSocket server(port);
	// �ڑ���ҋ@����
	std::cout << "�N���C�A���g����̐ڑ�������܂őҋ@���܂�" << std::endl;
	std::auto_ptr<Socket> client = server.accept();
	// �ڑ����Ă����N���C�A���g��IP�A�h���X��\��
	std::cout << client->getAddress().getHostAddress() << "���ڑ����Ă��܂���" << std::endl;
	// ��b�J�n
	std::cout << "����W�����P���J�n�ł��B" << std::endl;
	while (1) {
		// �f�[�^�̎�M
		std::cout << "����̃^�[���ł��B" << std::endl;
		std::cout << "����̏o�����҂��Ă��܂��c" << std::endl;
		std::string recvMessage = client->receive();
		// �ڑ��ؒf�̃`�F�b�N
		if (recvMessage == "c_end") {
			std::cout << "�N���C�A���g���ڑ���ؒf���܂���" << std::endl;
			break;
		}
		//���肪�o������
		int enemyhand = std::atoi(recvMessage.c_str());

		// ��M���b�Z�[�W�̕\��
		std::cout << "���肪�o��������肵�܂����B" << std::endl;
		std::cout << "���Ȃ��̃^�[���ł��B" << std::endl;
		// ���M���b�Z�[�W�̓���
		std::cout << "�o����𐔒l�őI��ł��������B" << std::endl;
		std::cout << "�O�[�F1�@�@�`���L�F2�@�@�p�[�F3" << std::endl;
		std::string handstr;
		//�����̏o������
		int hand;
		do {
			std::cout << "-->";
			std::cin >> handstr;
			hand = std::atoi(handstr.c_str());
			if (hand < 1 || hand > 3)
				std::cout << "�����Ȑ��l�ł��B" << std::endl;
		} while (hand < 1 || hand > 3);
		std::cin.sync();

		//�ΐ팋�ʂ̕\��
		std::string my, enemy;
		my = NumberToHand(hand);
		enemy = NumberToHand(enemyhand);
		//���ʂ̌v�Z�@0->������	1->�����̕���	2->�����̏���
		int result = (hand - enemyhand + 3) % 3;
		std::string resultMessage = "\n����\n���Ȃ��F" + my + "\n���@��F" + enemy + "\n";
		std::string sendResultMessage = "\n����\n���Ȃ��F" + enemy + "\n���@��F" + my + "\n";

		if (result == 0)
		{
			resultMessage += "�������ł��B\n";
			sendResultMessage += "�������ł��B\n";
		}			
		else if (result == 1)
		{
			resultMessage += "���Ȃ��̕����ł��B\n";
			sendResultMessage += "���Ȃ��̏����ł��B\n";
		}
		else
		{
			resultMessage += "���Ȃ��̏����ł��B\n";
			sendResultMessage += "���Ȃ��̕����ł��B\n";
		}
		
		//���ʂ̕\��
		std::cout << resultMessage << std::endl;
		// �ΐ팋�ʂ̑��M
		client->send(sendResultMessage);

		// �T�[�o�[����̐ڑ��ؒf
		if (handstr == "s_end") {
			break;
		}
	}
	// �\�P�b�g�����
	client->close();
}

void JyankenGame::Client()
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
	std::cout << "����W�����P���J�n�ł��B" << std::endl;
	while (1) {
		// ���M���b�Z�[�W�̓���
		std::cout << "���Ȃ��̃^�[���ł��B" << std::endl;
		std::cout << "�o����𐔒l�őI��ł��������B" << std::endl;
		std::cout << "�O�[�F1�@�@�`���L�F2�@�@�p�[�F3" << std::endl;
		std::string handstr;
		int hand;
		do {
			std::cout << "-->";
			std::cin >> handstr;
			hand = std::atoi(handstr.c_str());
			if (hand < 1 || hand > 3)
				std::cout << "�����Ȑ��l�ł��B" << std::endl;
		} while (hand < 1 || hand > 3);
		std::cin.sync();
		// �f�[�^�𑗐M����
		socket.send(handstr);

		// �ڑ���ؒf���邩�H
		if (handstr == "c_end") {
			break;
		}

		// �T�[�o�[����̃f�[�^����M����
		std::cout << "����̃^�[���ł��B" << std::endl;
		std::cout << "����̏o�����҂��Ă��܂��c" << std::endl;
		std::string recvMessage = socket.receive();
		// �T�[�o�[�̐ڑ��v�������������H
		if (recvMessage == "s_end") {
			std::cout << "�T�[�o�[���ڑ���ؒf���܂���" << std::endl;
			break;
		}
		// ��M�f�[�^�̕\��
		std::cout << recvMessage << std::endl;
	}
	// �\�P�b�g�����
	socket.close();
}

void JyankenGame::Draw()
{

}

void JyankenGame::Run()
{
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
