#pragma once

#include <GSgame.h>

class Game : public gslib::Game {
public:
	//�R���X�g���N�^
	Game();
private:
	//�J�n
	virtual void start() override;
	//�X�V
	virtual void update(float deltaFrame)  override;
	//�`��
	virtual void draw() override;
	//�`��
	virtual void end() override;

	
};
