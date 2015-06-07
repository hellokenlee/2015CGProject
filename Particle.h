#ifndef PARTICLE_H
#define  PARTICLE_H
#include "Texture.h"
#include "Camera.h"

#define MAX_PARTICLE 300
#define  halfParticleHeight 0.5
#define halfParticleWidth 0.5
struct sParticle
{
	bool active;
	float life;
	float fade;

	float r;
	float g;
	float b;

	float x;
	float y;
	float z;

	float xi;
	float yi;
	float zi;

	float xg;
	float yg;
	float zg;
};


class cSnow{
	friend class cCamera;
public:
	void init();
	void render();
private:
	float zoom;
	float colors[3];
	cTexture tex;
	sParticle particles[MAX_PARTICLE];
	cCamera *pCamera;
};
#endif