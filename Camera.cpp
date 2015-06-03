#include "Camera.h"

double vect2Length(double a,double b){
	return sqrt(a*a+b*b);
}
double vect3Length(double a,double b,double c){
	return sqrt(a*a+b*b+c*c);
}
void normalize(float vect[3]){
	double len=vect3Length(vect[0],vect[1],vect[2]);
	vect[0]=vect[0]/len;
	vect[1]=vect[1]/len;
	vect[2]=vect[2]/len;
}
cCamera::cCamera(){
	speed=0.2;
	position[0]=0;
	position[1]=0;
	position[2]=0;

	view[0]=0;
	view[1]=0;
	view[2]=-100;

	up[0]=0;
	up[1]=1;
	up[2]=0;

}

cCamera* cCamera::getCamera(){
	if (p_Camera==NULL){
		p_Camera=new cCamera;
		return p_Camera;
	} else {
		return p_Camera;
	}
}

void cCamera::bindCamera(){
	gluLookAt(position[0],position[1],position[2],view[0],view[1],view[2],up[0],up[1],up[2]);
}
void cCamera::setCamera(double posx,double posy,double posz,double viewx,double viewy,double viewz,double upx,double upy,double upz){
	position[0]=posx;
	position[1]=posy;
	position[2]=posz;

	view[0]=viewx;
	view[1]=viewy;
	view[2]=viewz;

	up[0]=upx;
	up[1]=upy;
	up[2]=upz;
}
array<double,3> cCamera::getPosition(){
	return position;
}
array<double,3> cCamera::getView(){
	return view;
}
array<double,3> cCamera::getUp(){
	return up;
}

float cCamera::getSpeed(){
	return speed;
}
void cCamera::setSpeed(float speed){
	this->speed=speed;
}
//绕 x 旋转
void cCamera::pitchCamera(double angle){
	double sinT=sin(angle);
	double cosT=cos(angle);

	float dir[2]={(view[1]-position[1]),(view[2]-position[2])};
	
	//change y
	view[1]=dir[0]*cosT+dir[1]*sinT+position[1];
	//change z
	view[2]=-dir[0]*sinT+dir[1]*cosT+position[2];
}
//绕 y 旋转
void cCamera::yawCamera(double angle){
	double sinT=sin(angle);
	double cosT=cos(angle);

	float dir[2]={(view[0]-position[0]),(view[2]-position[2])};

	//change x
	view[0]=dir[0]*cosT+dir[1]*sinT+position[0];
	//change z
	view[2]=-dir[0]*sinT+dir[1]*cosT+position[2];
}
//							前一刻的鼠标位置(px,py)    后一刻的鼠标位置(nx,ny)
void cCamera::setViewByMouse(int px,int py,int nx,int ny){
	 double dx=nx-px;
	 double dy=ny-py;
	 //show(dx);
	 //show(dy);
	 pitchCamera(dy*0.003);
	 yawCamera(-dx*0.003);
}

void cCamera::moveForward(){
	//计算出方向向量 并且标准化方向向量dir[3]
	//posistion =position+dir[3]的值
	//view =view+dir
	float dir[3]={view[0]-position[0],view[1]-position[1],view[2]-position[2]};
	normalize(dir);
	position[0]=position[0]+dir[0]*speed;
	position[1]=position[1]+dir[1]*speed;
	position[2]=position[2]+dir[2]*speed;

	view[0]=view[0]+dir[0]*speed;
	view[1]=view[1]+dir[1]*speed;
	view[2]=view[2]+dir[2]*speed;
}					
void cCamera::moveBack(){
	float dir[3]={view[0]-position[0],view[1]-position[1],view[2]-position[2]};
	normalize(dir);
	position[0]=position[0]-dir[0]*speed;
	position[1]=position[1]-dir[1]*speed;
	position[2]=position[2]-dir[2]*speed;

	view[0]=view[0]-dir[0]*speed;
	view[1]=view[1]-dir[1]*speed;
	view[2]=view[2]-dir[2]*speed;
}	

void cCamera::moveLeft(){
	float dir[3]={view[0]-position[0],view[1]-position[1],view[2]-position[2]};
	normalize(dir);
	//float leftDir[3]={dir[0]*cos(90')+dir[2]*sin(90'),dir[1],-dir[0]*sin(90')+dir[2]*cos(90')};
	float leftDir[3]={dir[2],dir[1],-dir[0]+dir[2]};
	
	position[0]=position[0]-leftDir[0]*speed;
	position[1]=position[1]-leftDir[1]*speed;
	position[2]=position[2]-leftDir[2]*speed;

	view[0]=view[0]-leftDir[0]*speed;
	view[1]=view[1]-leftDir[1]*speed;
	view[2]=view[2]-leftDir[2]*speed;
}					
void cCamera:: moveRight(){
	position[0]+=speed;
	view[0]+=speed;
}					
void cCamera:: moveUp(){
	position[1]+=speed;
	view[1]+=speed;
}						
void cCamera::moveDown(){
	position[1]-=speed;
	view[0]+=speed;
}					