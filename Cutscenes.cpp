#include "Cutscenes.h"
#include <windows.h>



Cutscenes::Cutscenes(){}

void Cutscenes::selectFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
        charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

void Cutscenes::drawText(char* text){
	bool isFirstCall = true;
	static GLuint lists;
	if(isFirstCall) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
		// Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
		isFirstCall = false;

		// ����128����������ʾ�б���
		lists = glGenLists(128);

		// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
		wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, lists);
	}
	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
	for(; *text!='\0'; ++text){
		glCallList(lists + *text);
	}
}






void Cutscenes::drawIcon(){
	Point test10(0,0),test2(0,20);

	list<Point> l;
	Point x0(0,20),x1(-50,50),x2(-50,100);
	l.push_back(x0);
	l.push_back(x1);
	l.push_back(x2);
	drawBezier(l);

	l.clear();
	x0.setxy(-50,100);
	x1.setxy(-50,150);
	x2.setxy(-30,200);
	l.push_back(x0);
	l.push_back(x1);
	l.push_back(x2);
	drawBezier(l);

	l.clear();
	x0.setxy(-30,200);
	x1.setxy(-15,220);
	x2.setxy(-20,250);
	l.push_back(x0);
	l.push_back(x1);
	l.push_back(x2);
	drawBezier(l);

	l.clear();
	x0.setxy(0,20);
	x1.setxy(25,15);
	x2.setxy(50,20);
	l.push_back(x0);
	l.push_back(x1);
	l.push_back(x2);
	drawBezier(l);


	l.clear();
	x0.setxy(50,20);
	x1.setxy(80,25);
	x2.setxy(100,60);
	l.push_back(x0);
	l.push_back(x1);
	l.push_back(x2);
	drawBezier(l);

	l.clear();
	x0.setxy(100,60);
	x1.setxy(120,80);
	x2.setxy(90,120);
	l.push_back(x0);
	l.push_back(x1);
	l.push_back(x2);
	drawBezier(l);

	l.clear();
	x0.setxy(90,120);
	x1.setxy(50,60);
	x2.setxy(-20,250);
	l.push_back(x0);
	l.push_back(x1);
	l.push_back(x2);
	drawBezier(l);

	//����
	l.clear();
	x0.setxy(0,50);
	x1.setxy(-60,80);
	x2.setxy(-10,150);
	l.push_back(x0);
	l.push_back(x1);
	l.push_back(x2);
	drawBezier(l);

	l.clear();
	x0.setxy(0,50);
	x1.setxy(50,100);
	x2.setxy(10,130);
	l.push_back(x0);
	l.push_back(x1);
	l.push_back(x2);
	drawBezier(l);

	l.clear();
	x0.setxy(10,130);
	x1.setxy(-5,140);
	x2.setxy(-10,150);
	l.push_back(x0);
	l.push_back(x1);
	l.push_back(x2);
	drawBezier(l);


	//���

	drawLine(Point(-5,60),Point(15,80));


	l.clear();
	x0.setxy(-5,60);
	x1.setxy(-50,100);
	x2.setxy(15,80);
	l.push_back(x0);
	l.push_back(x1);
	l.push_back(x2);
	drawBezier(l);

	drawLine(Point(-5,60),Point(400,-133));
	drawLine(Point(400,-133),Point(420,-113));
	drawLine(Point(15,80),Point(420,-113));
	//drawLine(Point(-5,60),Point(15,80));
	//drawLine(Point(-5,60),Point(15,80));
	//drawLine(test1,test2);
}


//��ʼ��
void Cutscenes::Init(int SCREEN_WIDTH,int SCREEN_HEIGHT){  
	glClearColor(0.0,0.0,0.0,0.0);  
	glColor3f(1.0f, 0.0, 0.0);  
	glPointSize(5.0);  
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();  
	gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT);  
}  
//��ֱ��
void Cutscenes::drawLine(Point p1, Point p2){  
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0, 0.0);
	glVertex2f(p1.x, p1.y);  
	glVertex2f(p2.x, p2.y);  
	glEnd();  
	glFlush();  
}  
//�����ı��������Ƕ�����Ƶ㱴�������ߵĻ���
Point Cutscenes::basicBezier(Point p1,Point p2,double delta){
	Point P;
	P.x = p1.x * delta + p2.x * (1-delta);
	P.y = p1.y * delta + p2.y * (1-delta);
	return P;
}
//���������Ƶ�ĵ�delta == tʱ���������ߵ�ĳ������ĵ�
Point Cutscenes::calBezierPoint(list<Point> Point_list,double delta,int n){

	Point P;
	Point temp1,temp2;
	if(Point_list.size() == 1){
		return Point_list.front();
	}
	if(Point_list.empty()){
		return Point(-1.0,-1.0,false);
	}
	while(Point_list.size() > 1){
		int i = 0;
		while(i < n){
			temp1 = Point_list.front();
			Point_list.pop_front();
			temp2 = Point_list.front();
			P = basicBezier(temp1,temp2,delta);
			Point_list.push_back(P);
			i++;
		}
		Point_list.pop_front();
		n--;
	}
	return P;  
} 
//�ڴ��ڻ�������������
void Cutscenes::drawBezier(list<Point> Point_list){
	Point temp = Point_list.front();
	for (double t = 1.0; t >= 0.0;t-=0.1)  
	{  
		Point P = calBezierPoint(Point_list, t,Point_list.size() - 1);
		drawLine(temp, P);  
		temp = P;  
	}
}