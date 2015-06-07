/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#include "main.h"
int winHeight =600;
int winWidth =600;
int winPosX=400;
int winPosY=100;
cOBJ OBJ;
cOBJ sOBJ;
cCamera *pCamera;
POINT mpos;
Cutscenes cg;
cSnow snow;
/*初始化*/
void initWindow(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(winWidth,winHeight);
	glutInitWindowPosition(winPosX,winPosY);
	glDepthMask(GL_TRUE);
	glEnable(GL_POLYGON_SMOOTH);
	glutCreateWindow("MCRoaming");

	//设置光照模型
	GLfloat light_position[] = {1.0,1.0,1.0,1.0};
	GLfloat light_ambient [] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse [] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_specular[] = { 0.8, 0.8, 0.8, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT , light_ambient );
	glLightfv(GL_LIGHT0, GL_DIFFUSE , light_diffuse );
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void drawCross(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5,5,-5,5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);{
		glColor3f(1,1,1);
		glVertex2f(-0.01,0.15);
		glVertex2f(0.01,0.15);
		glVertex2f(0.01,-0.15);
		glVertex2f(-0.01,-0.15);

		glVertex2f(-0.15,0.01);
		glVertex2f(0.15,0.01);
		glVertex2f(0.15,-0.01);
		glVertex2f(-0.15,-0.01);
	}glEnd();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.1, 0.1, -0.1 * (GLfloat)winHeight / (GLfloat)winWidth,0.1* (GLfloat)winHeight / (GLfloat)winWidth, 0.1, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
}

/*main scene Func*/
void scene(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	drawCross();
	pCamera->bindCamera();
	OBJ.render();
	sOBJ.render();
	snow.render();
	glutSwapBuffers();
}
//reshape func
void reshape(GLsizei w,GLsizei h){
	if(h==0)
		h=1;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void refresh(int i){
	//windows 鼠标设置
	GetCursorPos(&mpos);
	pCamera->setViewByMouse(700,400,mpos.x,mpos.y);
	SetCursorPos(700,400);
	//刷新显示
	glutPostRedisplay();
	glutTimerFunc(40, refresh, 0);
}


/*loading scene Func */
void loading(){
	gluOrtho2D(-winWidth/2, winWidth, -winHeight/2, winHeight/2);
	cg.selectFont(48,ANSI_CHARSET,"Comic Sans MS");
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glRasterPos2f(0.0,-winHeight/4);
	cg.drawIcon();
	glColor3f(1,1,1);
	cg.drawText("loading...");
	glutSwapBuffers();

	//jump to main scene
	glViewport(0,0,winWidth,winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.1, 0.1, -0.1 * (GLfloat)winHeight / (GLfloat)winWidth,0.1* (GLfloat)winHeight / (GLfloat)winWidth, 0.1, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
			printf("loading terrain...");
	OBJ.loadObjFromFile("minecraft.obj");
			printf("done!\nloading sky...");
	sOBJ.loadObjFromFile("skyBox5s.obj");
	snow.init();
			printf("done!\nsetting camera...");
	pCamera=cCamera::getCamera();
	pCamera->setCamera(5.595848,7.462796,9.431834,5.408215,7.411818,8.450918,0,1,0);
			printf("done!\n");

	glutDisplayFunc(scene);
	glutReshapeFunc(reshape);
	glutTimerFunc(20,refresh,0);
	glutPostRedisplay();
}



/******************************controller func **************************************/
void up(){
	pCamera->moveUp();
	//printf("pos:(%lf,%lf,%lf)\nview:(%lf,%lf,%lf)\n",pCamera->getPosition()[0],pCamera->getPosition()[1],pCamera->getPosition()[2],
	//	pCamera->getView()[0],pCamera->getView()[1],pCamera->getView()[2]);
}
void down(){
	pCamera->moveDown();
}
void left(){
	pCamera->moveLeft();
}
void right(){
	pCamera->moveRight();
}

void forward(){
	pCamera->moveForward();
	//printf("pos:(%lf,%lf,%lf)\nview:(%lf,%lf,%lf)\n",pCamera->getPosition()[0],pCamera->getPosition()[1],pCamera->getPosition()[2],
	//	pCamera->getView()[0],pCamera->getView()[1],pCamera->getView()[2]);
}
void back(){
	pCamera->moveBack();
}
/******************************controller func  ENDS**************************************/

/*你可以在这里添加你的测试函数*/
int main(int argc, char* argv[]){
	initWindow(argc,argv);
	//设定控制
	SetCursorPos(700,400);
	pCamera=cCamera::getCamera();
	cController controller;
	controller.setUpFunc(up);
	controller.setDownFunc(down);
	controller.setForwardFunc(forward);
	controller.setBackFunc(back);
	controller.setLeftFunc(left);
	controller.setRightFunc(right);
	controller.initController();
	glutSetCursor(GLUT_CURSOR_NONE);
	//设定 显示函数
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glutDisplayFunc(loading);
	glutMainLoop();
	return 0;
}
