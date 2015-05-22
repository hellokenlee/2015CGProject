/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#ifndef MATERIAL_H
#define MATERIAL_H
#include <array>
#include "Texture.h"
#include "util.h"
//根据 glMaterial{if}(GLenum face, GLenum pname, TYPE param);
class cMaterial
{
public:
	cMaterial();
	~cMaterial();
	bool initTexture();
	void setMaterial();

private:
	array<float, 3> ambient;		//材质的环境颜色
	array<float, 3> diffuse;		//漫反射后形成的光线强度
	array<float, 3> specular;		//镜面反射后形成的光线强度
	array<float, 3> emission;		//该材质本身就微微的向外发射光线的颜色
	float fShiness;					//镜面指数
	float fTrans;					//透明度

	cTexture tex;					//素材
	char texturePath[PATH_SIZE];	//素材路径
};
#endif