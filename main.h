/*All copyrights reversed by KenLee@2015, SS, SYSU*/
//��׼��
#include <iostream>
#include <windows.h>
#include <gl/glut.h>

//���->>ͻȻ�����е����ڿ�
#include "Camera.h"
#include "OBJ.h"
#include "Controller.h"
 
//���ú� & ����


//��̬��Ա��������
char cController::kDown;
char cController::kUp;
char cController::kForward;
char cController::kBack;
char cController::kLeft;
char cController::kRight;
char cController::kEsc;

void (*cController::upFunc)(void);
void (*cController::downFunc)(void);
void (*cController::backFunc)(void);
void (*cController::forwardFunc)(void);
void (*cController::leftFunc)(void);
void (*cController::rightFunc)(void);
void (*cController::mouseClickFunc)(int buttom,int state,int x,int y);
void (*cController::mouseMovFunc)(int x,int y);
void (*cController::mouseDragFunc)(int x,int y);
void (*cController::mouseLefrFunc)(int state);
cCamera* cCamera::p_Camera=NULL;