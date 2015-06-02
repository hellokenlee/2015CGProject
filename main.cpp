/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#include "main.h"
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
float angle=1;
float posX=0,posY=0,posZ=0,viewX=0,viewY=0,viewZ=-100, upX=0,upY=1,upZ=0;
cCamera *pCamera;
/*glut DisplayFunc*/
void scene(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	pCamera->bindCamera();
	//glRotatef(angle,0,1,0);
	//gluLookAt( posX,posY,posZ,viewX,viewY,viewZ, upX,upY,upZ);
	OBJ.render();
	
	glutSwapBuffers();
}
//时间回调
void onTimer( int iTimerIndex){
	glutPostRedisplay();//刷新显示
	angle++;
	if(angle>=360)
		angle=0;
	glutTimerFunc( 10, onTimer, 0);
}
/*初始化*/
void initWindow(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(200,200);
	glDepthMask(GL_TRUE);
	glutCreateWindow("3D Cube");
	glEnable(GL_TEXTURE_2D);
	//光源
	GLfloat light_position[]={1.0,1.0,1.0,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	//将光源设置应用
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//着色消隐
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
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
}
int px=-1,py=-1;
void mouse(int nx,int ny){
	if(px!=-1)
		pCamera->setViewByMouse(px,py,nx,ny);
	px=nx;
	py=ny;
}

//default 0 0 0 / 0 0 -100 / 0 1 0
//默认情况下，相机位于原点，指向z轴的负向，同时把y轴的正向作为向上向量。这就相当于调用：gluLookAt(0.0,0.0,0.0,    0.0,0.0,-100.0,    0.0,1.0,0.0 )
/******************************controller debug func  ENDS**************************************/




/*你可以在这里添加你的测试函数*/
int main(int argc, char* argv[]){
	initWindow(argc,argv);
	OBJ.loadObjFromFile("one_block.obj");
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	OBJ.print_vetor();
	pCamera=cCamera::getCamera();


	cController controller;
	controller.setUpFunc(up);
	controller.setDownFunc(down);
	controller.setForwardFunc(forward);
	controller.setBackFunc(back);
	controller.setLeftFunc(left);
	controller.setRightFunc(right);
	controller.setMouseDragFunc(mouse);
	controller.initController();
	glutTimerFunc(10,onTimer,0);
	glutReshapeFunc(reshape);
	glutDisplayFunc(scene);
	glutMainLoop();
	return 0;
}
