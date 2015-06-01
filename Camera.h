/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#ifndef CAMERA_H
#define CAMERA_H
#include <array>
using namespace std;
//暂定做为一个单例吧
//根据 glutLookAt(position[3]，view[3]，up[3])
class cCamera
{
public:
	static cCamera &getCamera();
	
	void setCamera(double posx,double posy,double posz,double viewx,double viewy,double viewz,double upx,double upy,double upz);
	array<double,3> getPosition();
	array<double,3> getView();
	array<double,3> getUp();

	double getSpeed();
	void setSpeed(double speed);
	
	void yaw(double angleRadian);
	void pitch(double angleRadian);
	void moveForward();					//向前
	void moveBack();					//向后
	void moveLeft();					//向左
	void moveRight();					//向右
	void moveUp();						//向上
	void moveDown();					//向下

private:
	cCamera();
	static cCamera *p_Camera;
	double speed;
	array<double,3> position;
	array<double,3> view;
	array<double,3> up;

public:
	void setLook();
private:
	void rotateView(double angle, double x, double y, double z);
	void rotateUp(double angle, double x, double y, double z);
};
#endif