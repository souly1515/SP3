#include "UI.h"

CUI* CUI::instance = NULL;

CUI* CUI::getInstance()
{
	//Only one instance of UI
	if (instance == NULL)
		instance = new CUI;
	return instance;
}

CUI::CUI()
	: ui_panel(true)
{
	//UI Textures
	LoadTGA(&UI[0], "images/backpanel.tga");
	LoadTGA(&UI[1], "images/settings.tga");

	//Start Button
	startButton = new CButton;

	//Add Start Button to Vector List
	buttonsList.push_back(startButton);

	//Start Button Texture
	LoadTGA(&(startButton->button[0]), "images/startScreen.tga");
	LoadTGA(&(startButton->button[1]), "images/startScreenHover.tga");

	//Pause Button
	for (int i = 0; i < 3; ++i)
	{
		pauseButton[i] = new CButton;
	}

	//Add Pause Button to Vector List
	for (int i = 0; i < 3; ++i)
	{
		buttonsList.push_back(pauseButton[i]);
	}

	//Pause Buttons Texture
	for (int i = 0; i < 3; ++i)
	{
		LoadTGA(&(pauseButton[i]->button[0]), "images/pause.tga");
	}
	LoadTGA(&(pauseButton[0]->button[1]), "images/pause1.tga");
	LoadTGA(&(pauseButton[1]->button[1]), "images/pause2.tga");
	LoadTGA(&(pauseButton[2]->button[1]), "images/pause3.tga");

	//Setting Button
	for (int j = 0; j < 3; ++j)
	{
		settingButton[j] = new CButton;
	}

	//Add setting button to vec list
	for (int j = 0; j < 3; ++j)
	{
		buttonsList.push_back(settingButton[j]);
	}

	//Setting button texture
	for (int j = 0; j < 3; ++j)
	{
		LoadTGA(&(settingButton[j]->button[0]), "images/settings.tga");
	}
	LoadTGA(&(settingButton[0]->button[1]), "images/settings1.tga");
	LoadTGA(&(settingButton[1]->button[1]), "images/settings2.tga");
	LoadTGA(&(settingButton[2]->button[1]), "images/settings3.tga");

	//Set Region for Buttons
	SetRegion();
}

CUI::~CUI() {}

//Set Regions for Buttons
void CUI::SetRegion()
{
	//Min X, Max X, Min Y, Max Y (Region)

	startButton->Set(385, 672, 554, 679);

	pauseButton[0]->Set(421, 483, 375, 452);
	pauseButton[1]->Set(508, 571, 374, 450);
	pauseButton[2]->Set(597, 659, 377, 449);

	settingButton[0]->Set(421, 483, 375, 452);
	settingButton[1]->Set(508, 571, 374, 450);
	settingButton[2]->Set(597, 659, 377, 449);
}

CButton* CUI::getStartButton()
{
	return startButton;
}

CButton* CUI::getPauseButton(short slot)
{
	return pauseButton[slot];
}

CButton* CUI::getSettingButton(short slot)
{
	return settingButton[slot];
}

void CUI::renderBackpanel()
{
	if(ui_panel == true)
	{
		glEnable(GL_TEXTURE_2D);

		glPushMatrix();
		glTranslatef(765,60,0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, UI[0].texID);
			glPushMatrix();
				glBegin(GL_QUADS);
				glTexCoord2f(0, 0); glVertex2f(0, 750);
				glTexCoord2f(1, 0); glVertex2f(250, 750);
				glTexCoord2f(1, 1); glVertex2f(250, 0);
				glTexCoord2f(0, 1); glVertex2f(0, 0);
				glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
	}
}

bool CUI::LoadTGA(TextureImage *texture, char *filename)
{
	GLubyte		TGAheader[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	// Uncompressed TGA Header
	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
	GLubyte		header[6];									// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										// Temporary Variable
	GLuint		type = GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)

	FILE *file = fopen(filename, "rb");						// Open The TGA File

	if (file == NULL ||										// Does File Even Exist?
		fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||	// Does The Header Match What We Want?
		fread(header, 1, sizeof(header), file) != sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
			return false;									// Return False
		else
		{
			fclose(file);									// If Anything Failed, Close The File
			return false;									// Return False
		}
	}

	texture->width = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)

	if (texture->width <= 0 ||								// Is The Width Less Than Or Equal To Zero
		texture->height <= 0 ||								// Is The Height Less Than Or Equal To Zero
		(header[4] != 24 && header[4] != 32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return false;										// Return False
	}

	texture->bpp = header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel = texture->bpp / 8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize = texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData = (GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

	if (texture->imageData == NULL ||							// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file) != imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if (texture->imageData != NULL)						// Was Image Data Loaded
			free(texture->imageData);						// If So, Release The Image Data

		fclose(file);										// Close The File
		return false;										// Return False
	}

	for (GLuint i = 0; i < int(imageSize); i += bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp = texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose(file);											// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered

	if (texture[0].bpp == 24)									// Was The TGA 24 Bits
	{
		type = GL_RGB;										// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;											// Texture Building Went Ok, Return True
}