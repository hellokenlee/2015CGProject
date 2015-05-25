#ifndef SCENE_H
#define SCENE_H
#include "OBJ.h"
#include "Camera.h"
class cScene
{
public:
	cScene();
	~cScene();
	void render();
private:
	cOBJ LandForm;
	cCamera *Camera;
	//cPlayer Player;
}

#endif