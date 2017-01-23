////UDP���g�p�����`���b�g�v���O����
#include "Network\DatagramSocket.h"
#include "Network\SocketException.h"
#include <iostream>
#include <string>
#include <memory>
#include <winsock2.h> // WinSock�̃w�b�_�t�@�C��
// WinSock���C�u�����̎w��
#pragma comment ( lib, "WSock32.lib" )
//�T�[�o�[�֐�
void UDPServer(void)
{
	// �|�[�g�ԍ��̓���
	std::cout << "�g�p����|�[�g�ԍ�--> ";
	int port;
	std::cin >> port;
	std::cin.sync();
	// �T�[�o�[�p�̃\�P�b�g��p��
	DatagramSocket server(port);
	// �N���C�A���g�̃A�h���X
	InetSocketAddress clientAddress;
	// ��b�J�n
	std::cout << "��b�J�n�ł�" << std::endl;
	while (true) {
		// �f�[�^�̎�M
		std::cout << "��M��҂��Ă��܂�" << std::endl;
		// �N���C�A���g����̃f�[�^����M����i�ő�Q�T�T�����j
		char buffer[256];
		int len = server.receive(buffer, sizeof(buffer) - 1, clientAddress);
		buffer[len] = '\0';
		std::string recvMessage(buffer);

		// �ڑ��ؒf�̃`�F�b�N
		if (recvMessage == "c_end") {
			std::cout << "�N���C�A���g���ڑ���ؒf���܂���" << std::endl;
			break;
		}
		// ��M���b�Z�[�W�̕\��
		std::cout << "��M--> " << recvMessage << std::endl;
		// ���M���b�Z�[�W�̓���
		std::cout << "���M--> ";
		std::string sendMessage;
		std::cin >> sendMessage;
		std::cin.sync();
		// �f�[�^�̑��M
		server.send(sendMessage.c_str(), (int)sendMessage.size(), clientAddress);
		// �T�[�o�[����̐ڑ��ؒf
		if (sendMessage == "s_end") {
			break;
		}
	}
}
// �N���C�A���g�֐�
void UDPClient()
{
	// �T�[�o�[���̓���
	std::cout << "�T�[�o�[�̂h�o�A�h���X--> ";
	std::string address;
	std::cin >> address;
	std::cin.sync();
	// �T�[�o�[�̃|�[�g�ԍ��̓���
	std::cout << "�T�[�o�[�̃|�[�g�ԍ�--> ";
	int port;
	std::cin >> port;
	std::cin.sync();
	// �T�[�o�[�̃\�P�b�g�A�h���X���쐬
	InetSocketAddress serverAddress(address, port);
	// �t�c�o�\�P�b�g�̍쐬
	DatagramSocket socket;
	while (true) {
		// ���M���b�Z�[�W�̓���
		std::cout << "���M--> ";
		std::string sendMessage;
		std::cin >> sendMessage;
		std::cin.sync();
		// �f�[�^�𑗐M����
		socket.send(sendMessage.c_str(), (int)sendMessage.size(), serverAddress);
		// �ڑ���ؒf���邩�H
		if (sendMessage == "c_end") {
			break;
		}
		// �f�[�^�̎�M
		std::cout << "��M��҂��Ă��܂�" << std::endl;
		// �T�[�o�[����̃f�[�^����M����i�ő�Q�T�T�����j
		char buffer[256];
		int len = socket.receive(buffer, sizeof(buffer) - 1, serverAddress);
		buffer[len] = '\0';
		std::string recvMessage(buffer);
		// �T�[�o�[�̐ڑ��v�������������H
		if (recvMessage == "s_end") {
			std::cout << "�T�[�o�[���ڑ���ؒf���܂���" << std::endl;
			break;
		}
		// ��M�f�[�^�̕\��
		std::cout << "��M--> " << recvMessage << std::endl;
	}
}
// �`���b�g�v���O�������C���֐�
void main_function_udp()
{
	// WinSock�̏�����
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		// �������G���[
		std::cout << "WinSock�̏������Ɏ��s���܂���" << std::endl;
		return;
	}
	// �T�[�o�[���H�N���C�A���g���H
	std::cout << "�T�[�o�[�Ȃ�O����̓N���C�A���g�Ȃ�P�����--> ";
	int mode;
	std::cin >> mode;
	std::cin.sync();
	try {
		if (mode == 0) {
			// �T�[�o�[�Ƃ��ċN��
			UDPServer();
		}
		else {
			// �N���C�A���g�Ƃ��ċN��
			UDPClient();
		}
	}
	catch (SocketException& e) {
		// �G���[���b�Z�[�W���o��
		std::cout << e.what() << std::endl;
	}
	// WinSock�̏I������
	WSACleanup();
}


////////�X���b�h�Ή��G�R�[�T�[�o�[�̍쐬
////#include <winsock2.h>
////#include <iostream>
////#include "./Network/ServerThread.h"
////#pragma comment ( lib, "WSock32.lib" )
////int main()
////{
////	// WinSock�̏�����
////	WSADATA wsaData;
////	WSAStartup(MAKEWORD(1, 1), &wsaData);
////	// �|�[�g�ԍ��̓���
////	int port;
////	std::cout << "�|�[�g�ԍ������ --> ";
////	std::cin >> port;
////	// �T�[�o�[�X���b�h���N��
////	ServerThread server(port);
////	server.start();
////	// �G�X�P�[�v�L�[���������܂�
////	while (GetAsyncKeyState(VK_ESCAPE) == 0) {
////		Thread::sleep(0);
////	}
////	// �T�[�o�[�X���b�h�������I��
////	server.end();
////	WSACleanup();
////}
