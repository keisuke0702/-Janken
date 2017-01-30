#include "DatagramSocketImpl.h"
#include "InetSocketAddress.h"
#include "SocketException.h"
#include <memory>
// �R���X�g���N�^�D
DatagramSocketImpl::DatagramSocketImpl() :
	mSocket(INVALID_SOCKET)
{}
// �f�X�g���N�^�D
DatagramSocketImpl::~DatagramSocketImpl()
{
	// �\�P�b�g�����
	close();
}
// �t�c�o�\�P�b�g�̍쐬�D
void DatagramSocketImpl::create()
{
	// �L���ȃ\�P�b�g�������Ă���ꍇ�͍쐬���Ȃ�
	if (mSocket != INVALID_SOCKET) {
		return;
	}
	// �V�����\�P�b�g���쐬����
	mSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
	// �\�P�b�g���쐬�ł������H
	if (mSocket == INVALID_SOCKET) {
		throw SocketException("�t�c�o�\�P�b�g���쐬�ł��܂���");
	}
}
// �\�P�b�g�����D
void DatagramSocketImpl::close()
{
	if (mSocket != INVALID_SOCKET) {
		// �\�P�b�g�����
		::closesocket(mSocket);
		// �\�P�b�g�n���h����������
		mSocket = INVALID_SOCKET;
	}
}
// �w�肳�ꂽ�|�[�g�ԍ��Ƀ\�P�b�g���o�C���h�D
void DatagramSocketImpl::bind(int port)
{
	// �\�P�b�g���쐬����
	create();
	// �\�P�b�g�ɖ��O��t����
	SOCKADDR_IN serverAddress;
	std::memset(&serverAddress, 0, sizeof(SOCKADDR_IN));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons((u_short)port);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	if (::bind(mSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		close();
		throw SocketException("�o�C���h�Ɏ��s���܂���");
	}
}
// �f�[�^�𑗐M�D
int DatagramSocketImpl::send(const void* buffer, int size, const InetSocketAddress& addr)
{
	// �\�P�b�g���쐬����
	create();
	// ���M��̃A�h���X��ݒ�
	SOCKADDR_IN sendAddress;
	std::memset(&sendAddress, 0, sizeof(sendAddress));
	sendAddress.sin_family = AF_INET;
	sendAddress.sin_port = htons((u_short)addr.getPort());
	sendAddress.sin_addr.s_addr = addr.getInetAddress().getAddress();
	// �f�[�^�𑗐M����
	int result = ::sendto(
		mSocket,
		(const char*)buffer, size,
		0,
		(LPSOCKADDR)&sendAddress, sizeof(sendAddress)
		);
	// ���M�G���[�̃`�F�b�N
	if (result != size) {
		throw SocketException("���M�ł��܂���ł���");
	}
	// ���M�����f�[�^�T�C�Y��Ԃ�
	return result;
}
// �f�[�^����M�D
int DatagramSocketImpl::receive(void* buffer, int size, InetSocketAddress& addr)
{
	// �\�P�b�g���쐬����
	create();
	// ��M�f�[�^�̃A�h���X
	SOCKADDR_IN fromAddress;
	int fromSize = sizeof(fromAddress);
	int result = ::recvfrom(
		mSocket,
		(char*)buffer, size,
		0,
		(SOCKADDR*)&fromAddress,
		&fromSize
		);
	// ��M�G���[�̃`�F�b�N
	if (result == SOCKET_ERROR) {
		throw SocketException("��M�ł��܂���ł���");
	}
	// ���M���̃A�h���X��ݒ�
	addr = InetSocketAddress(fromAddress.sin_addr.s_addr, ::ntohs(fromAddress.sin_port));
	// ��M�����f�[�^�T�C�Y��Ԃ�
	return result;
}
