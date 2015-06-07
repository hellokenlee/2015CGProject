#ifndef SCENE_H
#define SCENE_H
#include "OBJ.h"
#include "Camera.h"
#include "Player.h"
class cScene
{
public:
	cScene();
	~cScene();
	void render();
	void initLanformFromOBJ(const char* FilePath);
	void initSkyBoxFromOBJ(const char* FilePath);
	void initPlayerFromOBJ(const char* FilePath);
private:
	cOBJ SkyBox;
	cOBJ LandForm;
	//cCamera *Camera;
	cPlayer Player;
}

#endif