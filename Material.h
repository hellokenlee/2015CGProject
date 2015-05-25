/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#ifndef MATERIAL_H
#define MATERIAL_H
#include <array>
#include "Texture.h"
#include "util.h"
//根据 glMaterial{if}(GLenum face, GLenum pname, TYPE param);
//array<float,4> for array[0]->R array[1]->G array[2]->B array[3]->A
class cMaterial
{
friend cOBJ;
public:
	cMaterial();
	cMaterial();
	~cMaterial();
	bool initTexture();				//load texture from texturePath[];
	void setMaterial();
	//!TODO: 增加各材质参数的Set和Get函数

private:
	array<float, 4> ambient;		//材质的环境颜色
	array<float, 4> diffuse;		//漫反射后形成的光线强度
	array<float, 4> specular;		//镜面反射后形成的光线强度
	array<float, 4> emission;		//该材质本身就微微的向外发射光线的颜色
	float fShiness;					//镜面指数
	float fTrans;					//透明度

	cTexture tex;					//纹理
	char texturePath[PATH_SIZE];	//纹理路径 *.png *.jpg *.tga etc.
};
#endif