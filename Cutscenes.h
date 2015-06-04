#ifndef CUTSCENES_H
#define CUTSCENES_H
#include<gl/glut.h>
#include<list>
using namespace std;

class Point  
{  
public:  
	Point():x(0.0),y(0.0),isPoint(true){}
	Point(float x_,float y_):x(x_),y(y_),isPoint(true){}
	Point(float x_,float y_,bool isPoint_):x(x_),y(y_),isPoint(isPoint_){}
	void setxy(float x2, float y2)  
	{  
		x = x2;  
		y = y2;  
	}  
	void setAPoint(bool isPoint_){
		isPoint = isPoint_;
	}
	float x, y;
	bool isPoint;
};  


class Cutscenes{
public:
	Cutscenes();
	void selectFont(int size, int charset, const char* face);
	void drawText(char* text);
	void drawIcon();

	//初始化
	void Init(int SCREEN_WIDTH,int SCREEN_HEIGHT);  
	//画直线
	void drawLine(Point p1, Point p2) ; 
	//两点间的贝塞尔，是多个控制点贝塞尔曲线的基础
	Point basicBezier(Point p1,Point p2,double delta);
	//任意多个控制点的当delta == t时贝塞尔曲线的某个具体的点
	Point calBezierPoint(list<Point> Point_list,double delta,int n);
	//在窗口画出贝塞尔曲线
	void drawBezier(list<Point> Point_list);

};

#endif
