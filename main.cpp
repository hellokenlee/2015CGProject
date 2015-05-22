/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#include "main.h"
cTexture tex;
/*glut DisplayFunc*/
void scene(){
	//tex.bindTexutre();
	glEnable(GL_TEXTURE_2D);
	tex.bindTexutre();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_QUADS);{
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-0.5,0.5,0.0);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(0.5,0.5,0.0);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(0.5,-0.5,0.0);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-0.5,-0.5,0.0);
	}
	glEnd();
	glutSwapBuffers();
}
/*初始化*/
void initWindow(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(winWidth,winHeight);
	glutInitWindowPosition(200,200);
	glDepthMask(GL_TRUE);
	glutCreateWindow("3D Cube");
	glutDisplayFunc(scene);
	//glutReshapeFunc(reSize);
}
/*你可以在这里添加你的测试函数*/
int main(int argc, char* argv[]){
	initWindow(argc,argv);
	tex.loadTexture("Resources/mc.jpg");
	glutMainLoop();
	return 0;
}