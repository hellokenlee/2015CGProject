#include "Controller.h"
cController::cController(){
	kDown='k';
	kUp='j';
	kForward='w';
	kBack='s';
	kLeft='a';
	kRight='d';
	kEsc=27;
	upFunc=downFunc=backFunc=forwardFunc=leftFunc=rightFunc=NULL;
}
cController::cController(char down,char up,char left,char right,char forward,char back,char esc){
	kDown=down;
	kUp=up;
	kForward=forward;
	kBack=back;
	kLeft=left;
	kRight=right;
}
void cController::initController(){
	glutKeyboardFunc(keyProcess);
}
void cController::setUpFunc(void (*Func)(void)){
	upFunc=Func;
}
void cController::setDownFunc(void (*Func)(void)){
	downFunc=Func;
}
void cController::setForwardFunc(void (*Func)(void)){
	forwardFunc=Func;
}
void cController::setBackFunc(void (*Func)(void)){
	backFunc=Func;
}
void cController::setLeftFunc(void (*Func)(void)){
	leftFunc=Func;
}
void cController::setRightFunc(void (*Func)(void)){
	rightFunc=Func;
}

void cController::keyProcess(unsigned char key,int x,int y){
	show(key);
	if(key==kForward)
		forwardFunc();
	else if(key==kBack)
		backFunc();
	else if(key==kUp)
		upFunc();
	else if(key==kDown)
		downFunc();
	else if(key==kLeft)
		leftFunc();
	else if(key==kRight)
		rightFunc();
	else if(key==27)
		exit(0);
}