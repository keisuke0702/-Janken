#include "Game.h"
#include "../Def.h"
#include "../AssetID.h"

Game::Game() : 
	gslib::Game(WINDOW_WIDTH, WINDOW_HEIGHT,false) 
{

}

void Game::start()
{
	gsLoadTexture(TEXTURE_ID::GOO_TEX,		"res/J_goo.png");
	gsLoadTexture(TEXTURE_ID::CHOKEY_TEX,	"res/J_chokey.png");
	gsLoadTexture(TEXTURE_ID::PAR_TEX,		"res/J_par.png");
	gsLoadTexture(TEXTURE_ID::WIN_TEX,		"res/J_win_320x132.png");
	gsLoadTexture(TEXTURE_ID::LOSE_TEX,		"res/J_lose_320x132.png");
}

void Game::update(float deltaFrame)
{
	
}

void Game::draw() 
{
	gsDrawSprite2D(TEXTURE_ID::GOO_TEX, NULL, NULL, NULL, NULL, NULL, 0.0f);
}

void Game::end() 
{
}
