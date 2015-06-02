/*All copyrights reversed by KenLee@2015, SS, SYSU*/
//标准库
#include <iostream>
#include <gl/glut.h>
//类库->>突然发现有点像内裤
#include "Camera.h"
#include "OBJ.h"
#include "Controller.h"
 
//常用宏 & 常量
#define winHeight 400
#define winWidth 400

//静态成员变量定义
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

cCamera* cCamera::p_Camera=NULL;