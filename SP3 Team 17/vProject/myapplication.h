#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <stdio.h>
#include <GL/glut.h>
#include "vector3D.h"
#include "Math.h"
#include <iostream>

#include "vector3D.h"
#include "Camera.h"
#include "Map.h"
#include "PlayerInfo.h"
#include "TextureImage.h"
#include "definitions.h"

#include "Goodies.h"
#include "GoodiesFactory.h"
#include "Inventory.h"
#include "ExpSystem.h"
#include "shop.h"
#include "Button.h"

#include "MVCtime.h"
#include "Skills.h"
#include "Monster.h"
#include "physics.h"

#include "UI.h"
#include "Sound.h"

//Mouse Info
typedef struct {
	bool mLButtonUp;
	bool mRButtonUp;
	bool middleButtonUp;
	int  lastX, lastY;
} theMouseInfo;

class myApplication 
{
public:
	// this is a constructor, it is implemented in myapplication.cpp
	myApplication();
	// this is a destructor, it is implemented in myapplication.cpp
	~myApplication();

	bool Init();
	void Update();
	void renderScene();
	void changeSize(int w, int h);

	//Input Functions
	void inputKey(int key, int x, int y);
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);

	static myApplication* getInstance();

private:
	
	bool muteOn;
	static myApplication *s_pInstance;

	//kennard testing stuff
	vector<MobInfo*> infoList;
	vector<Monster*> mobList;
	//Monster testMob;

	Skills testSkill;

	bool processTiles();

	std::vector<physicObj*> wallList;
	//end of kennard testing stuff

	//ryan testing stuff
	CUI* theUI;
	Sound* theSound;
	//end of ryan testing stuff

	//Camera
	Vector3D theCameraPosition;
	Vector3D theCameraDirection;
	float angle;

	//Textures
	TextureImage GameOver[1];
	TextureImage LevelComplete[1];
	TextureImage ground[3];
	TextureImage PauseTex[1];
	TextureImage WinScreen[1];

	//Goodies Factory
	CGoodiesFactory* theGoodiesFactory;

	//Shop
	CShop* theShop;

	//Scenes
	bool gameStart, gamePause, startDialogue2, bFlash;
	bool setting, pause, soundinit;
	bool trigger8, trigger9, allowGamePause;
	void renderStartScene();
	float dTrans1, dTrans2, dTrans3, dTrans4, dTrans5, dTrans6, dTrans7, dTrans8, dTrans9;
	int counterFlash, counterTime;

	//Dialogue
	TextureImage dialogueBG[1];
	TextureImage Stacey[5];
	TextureImage Patient[3];
	TextureImage Troy[2];
	TextureImage Flash[1];

	//Std Variables
	bool bGameOver, bComplete, stopMovement, bTutorial, 
		 tutorialEnd, programInit, winGame;
	int AGCredits;

	//Std Functions
	void renderComplete();
	void renderGameOver();
	void renderWin();
	void renderGround();
	void renderPause();
	void menuSequence();
	void renderTutorial();

	void RenderMiniMap(CMap* map);

	//Movement
	bool jump, bLeft, bRight, bMoving;
	void moveMeJump();
	void moveMeUpDown(bool mode, float timeDiff);
	void moveMeLeftRight(bool mode, float timeDiff);

	//Render Functions
	void RenderBackground();
	void RenderTileMap(CMap* map);
	void RenderMapBorder();
	TextureImage border[1];

	//Levels
	void LoadLevel(short level);
	short currentLevel;

	//The hero
	CPlayerInfo *theHero;
	void HeroUpdate();
	bool heroInit;

	//The number of frames
	int frameCount;
	//Number of frames per second
	float fps;
	//currentTime - previousTime is the time elapsed
	//between every call of the Idle function
	int currentTime, previousTime;
	//Pointer to a font style..
	//Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13, 
	//GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10, 
	//GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
	//GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
	//GLvoid *font_style;
	void *font_style;
	//Calculate the FPS
	void calculateFPS();
	//Display FPS
	void drawFPS();
	//Draws a string at the specified coordinates.
	void printw (float x, float y, float z, char* format, ...);

	//Display Text On Screen
	void DisplayText();

	//Realtime loop control
	long timelastcall;
	//Realtime loop control - frequency
	float frequency;

	bool myKeys[255];
	theMouseInfo mouseInfo;

	//The camera
	Camera* theCamera;

	//Background
	TextureImage BackgroundTexture[1];
	int mapOffset_x, mapOffset_y;
	int tileOffset_x, tileOffset_y;
	int mapFineOffset_x, mapFineOffset_y;

	//Tile mapping
	CMap *theMap, *theBorder;
	TextureImage TileMapTexture[2];

	//Hp Bar
	TextureImage HpBar[7];
	void RenderHpBar();

	//Loads A TGA File Into Memory
	bool myApplication::LoadTGA(TextureImage *texture, char *filename);

	void changeLevel(short nlevel);
};

#endif