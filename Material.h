/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#ifndef MATERIAL_H
#define MATERIAL_H
#include <array>
#include "Texture.h"
#include "util.h"
//���� glMaterial{if}(GLenum face, GLenum pname, TYPE param);
class cMaterial
{
public:
	cMaterial();
	~cMaterial();
	bool initTexture();
	void setMaterial();

private:
	array<float, 3> ambient;		//���ʵĻ�����ɫ
	array<float, 3> diffuse;		//��������γɵĹ���ǿ��
	array<float, 3> specular;		//���淴����γɵĹ���ǿ��
	array<float, 3> emission;		//�ò��ʱ����΢΢�����ⷢ����ߵ���ɫ
	float fShiness;					//����ָ��
	float fTrans;					//͸����

	cTexture tex;					//�ز�
	char texturePath[PATH_SIZE];	//�ز�·��
};
#endif