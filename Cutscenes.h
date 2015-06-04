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

	//��ʼ��
	void Init(int SCREEN_WIDTH,int SCREEN_HEIGHT);  
	//��ֱ��
	void drawLine(Point p1, Point p2) ; 
	//�����ı��������Ƕ�����Ƶ㱴�������ߵĻ���
	Point basicBezier(Point p1,Point p2,double delta);
	//���������Ƶ�ĵ�delta == tʱ���������ߵ�ĳ������ĵ�
	Point calBezierPoint(list<Point> Point_list,double delta,int n);
	//�ڴ��ڻ�������������
	void drawBezier(list<Point> Point_list);

};

#endif
