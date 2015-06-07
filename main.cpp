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

/*初始化*/
void initWindow(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(winWidth,winHeight);
	glutInitWindowPosition(winPosX,winPosY);
	glDepthMask(GL_TRUE);
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
/*main scene Func*/
void scene(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	pCamera->bindCamera();
	OBJ.render();
	sOBJ.render();
	glutSwapBuffers();
}
//reshape func
void reshape(GLsizei w,GLsizei h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glFrustum(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
		2.0* (GLfloat)h / (GLfloat)w, 2.0, 500.0);
	else
		glFrustum(-2.0*(GLfloat)h/(GLfloat)w,
		2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0,2.0,500.0);

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
	glutTimerFunc(20, refresh, 0);
}


/*loading scene Func */
void loading(){
	gluOrtho2D(-winWidth/2, winWidth, -winHeight/2, winHeight/2);
	cg.selectFont(48,ANSI_CHARSET,"Comic Sans MS");
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glRasterPos2f(0.0,-winHeight/4);
	cg.drawIcon();
	glColor3f(1,1,1);
	cg.drawText("Loading...");
	glutSwapBuffers();

	//jump to main scene
	glViewport(0,0,winWidth,winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2.0, 2.0, -2.0 * (GLfloat)winHeight / (GLfloat)winWidth,2.0* (GLfloat)winHeight / (GLfloat)winWidth, 2.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
			printf("loading terrian...");
	OBJ.loadObjFromFile("minecraft.obj");
			printf("done!\nloading sky...");
	sOBJ.loadObjFromFile("skyBox5s.obj");
			printf("done!\nsetting camera...");
	pCamera=cCamera::getCamera();
			printf("done!\n");
	glutDisplayFunc(scene);
	glutReshapeFunc(reshape);
	glutTimerFunc(20,refresh,0);
	glutPostRedisplay();
}



/******************************controller debug func BEGINS **************************************/

void up(){
	pCamera->moveUp();
	//pCamera->pitchCamera(0.05);
	//glutPostRedisplay();
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
	printf("pos:(%d,%d,%d)\nview:(%d,%d,%d)",pCamera->getPosition()[0],)
}
void back(){
	pCamera->moveBack();
}
/******************************controller debug func  ENDS**************************************/

/*你可以在这里添加你的测试函数*/
int main(int argc, char* argv[]){
	initWindow(argc,argv);
	//设定控制
	SetCursorPos(700,400);
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
