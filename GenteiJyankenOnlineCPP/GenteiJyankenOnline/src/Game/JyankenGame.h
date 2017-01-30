#pragma once

#include <string>

class JyankenGame
{
public:
	//�R���X�g���N�^
	JyankenGame() = default;
	// ���͂������l���W�����P���̎�̕�����ɕϊ�����֐� 1->�O�[ 2->�`���L 3->�p�[
	std::string NumberToHand(int num);

	// �T�[�o�[�֐�
	void Server();
	// �N���C�A���g�֐�
	void Client();
	//�`��
	void Draw();
	// ���s
	void Run();
};