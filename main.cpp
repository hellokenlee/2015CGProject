/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#include "main.h"
int winHeight =600;
int winWidth =600;
int winPosX=400;
int winPosY=100;
cTexture tex;
cTexture tex2;
array<float,4> a={0.8,0,0.8,1.0};
array<float,4> d={0.8,0,0.8,1.0};
array<float,4> s={1,0,1,1};
array<float,4> e={0,0,0,1};
float fs=50;
float ft=1;
cMaterial mat(a,d,s,e,fs,ft);
cMaterial mat2(a,d,s,e,fs,ft);
cOBJ OBJ;
cOBJ sOBJ;
cCamera *pCamera;
POINT mpos;

/*glut DisplayFunc*/
void scene(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	pCamera->bindCamera();
	OBJ.render();
	//sOBJ.render();
	glutSwapBuffers();
}

/*初始化*/
void initWindow(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(winWidth,winHeight);
	glutInitWindowPosition(winPosX,winPosY);
	glDepthMask(GL_TRUE);
	glutCreateWindow("3D Cube");

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
//reshape func
void reshape(GLsizei w,GLsizei h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glFrustum(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
			2.0* (GLfloat)h / (GLfloat)w, 2.0, 100.0);
		//glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,
		//2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else
		glFrustum(-2.0*(GLfloat)h/(GLfloat)w,
		2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0,2.0,100.0);
		//glOrtho(-2.0*(GLfloat)h/(GLfloat)w,
		//2.0*(GLfloat)h/(GLfloat)w,-2.0,2.0,-10.0,10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

/******************************controller debug func **************************************/

void up(){
	pCamera->moveUp();
	//pCamera->pitchCamera(0.05);
	//glutPostRedisplay();
}
void down(){
	pCamera->moveDown();
	//pCamera->pitchCamera(-0.05);

}
void left(){
	pCamera->moveLeft();
	//pCamera->yawCamera(0.05);
	//pCamera->pitchCamera(0.05);
	//cout<<"camPos:"<<pCamera->getPosition()[0]<<", "<<pCamera->getPosition()[1]<<" ,"<<pCamera->getPosition()[2]<<endl;
	//cout<<"camView:"<<pCamera->getView()[0]<<" ,"<<pCamera->getView()[1]<<" ,"<<pCamera->getView()[2]<<endl;
}
void right(){
	pCamera->moveRight();
	//pCamera->yawCamera(-0.05);
	//pCamera->pitchCamera(-0.05);
	//cout<<"camPos:"<<pCamera->getPosition()[0]<<", "<<pCamera->getPosition()[1]<<" ,"<<pCamera->getPosition()[2]<<endl;
	//cout<<"camView:"<<pCamera->getView()[0]<<" ,"<<pCamera->getView()[1]<<" ,"<<pCamera->getView()[2]<<endl;
}

void forward(){
	pCamera->moveForward();
}
void back(){
	pCamera->moveBack();
	cout<<"camPos:"<<pCamera->getPosition()[0]<<", "<<pCamera->getPosition()[1]<<" ,"<<pCamera->getPosition()[2]<<endl;
	cout<<"camView:"<<pCamera->getView()[0]<<" ,"<<pCamera->getView()[1]<<" ,"<<pCamera->getView()[2]<<endl;
}
void refresh(int i){
	//windows 鼠标设置
	GetCursorPos(&mpos);
	pCamera->setViewByMouse(700,400,mpos.x,mpos.y);
	SetCursorPos(700,400);
	
	glutPostRedisplay();
	glutTimerFunc(20, refresh, 0);
}


//default 0 0 0 / 0 0 -100 / 0 1 0
//默认情况下，相机位于原点，指向z轴的负向，同时把y轴的正向作为向上向量。这就相当于调用：gluLookAt(0.0,0.0,0.0,    0.0,0.0,-100.0,    0.0,1.0,0.0 )
/******************************controller debug func  ENDS**************************************/



/*你可以在这里添加你的测试函数*/
int main(int argc, char* argv[]){
	initWindow(argc,argv);
	SetCursorPos(700,400);
	//glutSetCursor(GLUT_CURSOR_NONE);
	
	OBJ.loadObjFromFile("aTree.obj");
	//sOBJ.loadObjFromFile("skyBox.obj");

	pCamera=cCamera::getCamera();

	cController controller;
	controller.setUpFunc(up);
	controller.setDownFunc(down);
	controller.setForwardFunc(forward);
	controller.setBackFunc(back);
	controller.setLeftFunc(left);
	controller.setRightFunc(right);
	controller.initController();
	glutReshapeFunc(reshape);
	glutDisplayFunc(scene);
	glutTimerFunc(20,refresh,0);
	glutMainLoop();
	return 0;
}
