/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#include "Texture.h"
cTexture::cTexture(){
	pic=0;
	fif=FIF_UNKNOWN;
	width=height=0;
	bits=0;
	texureId=0;
}
cTexture::cTexture(const char*FilePath){
	loadTexture(FilePath);
}
cTexture::~cTexture(){
	unloadTexture();
}
bool cTexture::loadTexture(const char* FilePath){
	//��ֹ�ظ�����ͬһ��ͼƬ
	if(strcmp(FilePath,_FilePath)==0){
		return true;
	}
	//��ȡͼƬ
	fif=FreeImage_GetFileType(FilePath,0);									
	//ʶ��ͼƬ��ʽ
	if(fif == FIF_UNKNOWN){
		fif=FreeImage_GetFIFFromFilename(FilePath);
	}
	if(fif==FIF_UNKNOWN || !FreeImage_FIFSupportsReading(fif)){
		printf("FIError: not support type");
		return false;
	}
	//����ͼƬ
	pic=FreeImage_Load(fif,FilePath);
	if(!pic){
		printf("Texture Error: cant not load!\n");
		return false;
	}
	//��ȡ���ظ�ʽ
	bits = FreeImage_GetBits(pic);
	width = FreeImage_GetWidth(pic);
	height = FreeImage_GetHeight(pic);

	if(bits==0 || width ==0 || height==0)
		return false;
	strcpy(_FilePath,FilePath);
	glGenTextures(1, &texureId);
	return true;
}
void cTexture::unloadTexture(){
	if(!pic)
		FreeImage_Unload(pic);
}
void cTexture::bindTexutre(){
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D,texureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Min Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Mag Filter
	glTexImage2D(GL_TEXTURE_2D,0,3,width,height,0,GL_BGR_EXT,GL_UNSIGNED_BYTE,bits);
}