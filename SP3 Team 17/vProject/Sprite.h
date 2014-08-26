#include <GL/freeglut.h>
#include <iostream>
#include "definitions.h"

#include "TextureImage.h"

#ifndef SPRITE_H
#define SPRITE_H
class Sprite
{
public:
	Sprite();
	~Sprite();

	// Textures
	TextureImage Images;
	// LoadTGA
	bool Stop;
	bool ImageInit(int SubImage, int ImageVar);
	bool LoadTGA( char *filename);
	void update(void);
	void changeVariation(int newVar);
	void render(void);
	void changeStop(bool nStop);
	// Set Animation Invert status of the sprite
	void SetAnimationInvert(bool AnimationInvert);
	// Get Animation Invert status of the sprite
	bool GetAnimationInvert(void);

private:
	int SubImage; // animation counter
	int ImageVar; 
	int CurrentVar;
	int CurSubImage;
	/*bool AnimationInvert;*/


};
#endif
