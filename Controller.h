#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <gl/glut.h>
#include "util.h"
//当作一个静态类
class cController
{
public:
	cController();
	cController(char down,char up,char left,char right,char forward,char back,char esc);
	void initController();
	void setUpFunc(void (*Func)(void));
	void setDownFunc(void (*Func)(void));
	void setForwardFunc(void (*Func)(void));
	void setBackFunc(void (*Func)(void));
	void setLeftFunc(void (*Func)(void));
	void setRightFunc(void (*Func)(void));
	
private:
	static char kDown;
	static char kUp;
	static char kForward;
	static char kBack;
	static char kLeft;
	static char kRight;
	static char kEsc;
	static void keyProcess(unsigned char key,int x,int y);
	static void (*upFunc)(void);
	static void (*downFunc)(void);
	static void (*backFunc)(void);
	static void (*forwardFunc)(void);
	static void (*leftFunc)(void);
	static void (*rightFunc)(void);
};
#endif