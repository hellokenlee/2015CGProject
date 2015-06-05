#include "Camera.h"

// print vector
std::ostream & operator << (std::ostream &output, const array<double, 3> vect) {
	output << "(" << vect[0];
	output << ", " << vect[1];
	output << ", " << vect[2];
	output << ")";
	return output;
}

// calculate the norm for a vector
double norm(array<double, 3> vect) {
	return sqrt(vect[0] * vect[0] +
		vect[1] * vect[1] +
		vect[2] * vect[2]);
}

// standardize a vector
array<double, 3> standardize(array<double, 3> vect) {
	double n = norm(vect);
	array<double, 3> stdVect;
	if (n != 0.0) {
		stdVect[0] = vect[0] / n;
		stdVect[1] = vect[1] / n;
		stdVect[2] = vect[2] / n;
	} else {
		stdVect[0] = stdVect[1] = stdVect[2] = 0.0;
	}
	return stdVect;
}

// numerical multiplication for a vector
array<double, 3> operator * (double n, array<double, 3> vect) {
	array<double, 3> result;
	result[0] = n * vect[0];
	result[1] = n * vect[1];
	result[2] = n * vect[2];
	return result;
}

// addition of two vectors
array<double, 3> operator + (array<double, 3> x, array<double, 3> y) {
	array<double, 3> result;
	result[0] = x[0] + y[0];
	result[1] = x[1] + y[1];
	result[2] = x[2] + y[2];
	return result;
}

// subtraction of two vectors
array<double, 3> operator - (array<double, 3> x, array<double, 3> y) {
	array<double, 3> result;
	result[0] = x[0] - y[0];
	result[1] = x[1] - y[1];
	result[2] = x[2] - y[2];
	return result;
}

// calculate dot product
double dot(array<double, 3> x, array<double, 3> y) {
	return x[0] * y[0] + x[1] * y[1] + x[2] * y[2];
}

// calculate cross product
array<double, 3> cross(array<double, 3> x, array<double, 3> y) {
	array<double, 3> n;
	n[0] = x[1] * y[2] - x[2] * y[1];
	n[1] = -(x[0] * y[2] - x[2] * y[0]);
	n[2] = x[0] * y[1] - x[1] * y[0];
	return n;
}

// 四元数类，用于计算旋转
struct cQuaternion {
	double real;  // real part
	double i, j, k;  // vector part
};

// print quaternion
std::ostream & operator << (std::ostream &output, const cQuaternion quat) {
	output << quat.real << " + ";
	output << quat.i << "i" << " + ";
	output << quat.j << "j" << " + ";
	output << quat.k << "k";
	return output;
}

// generate a quaternion for a vector
cQuaternion getQuaternion(array<double, 3> vector) {
	cQuaternion result;
	array<double, 3> unitVector = standardize(vector);
	result.real = 0;
	result.i = unitVector[0];
	result.j = unitVector[1];
	result.k = unitVector[2];
	return result;
}

// generate rotation quaternion factor
cQuaternion getRotationQuaternion(double angle, array<double, 3> axis) {
	cQuaternion result;
	result.real = result.i = result.j = result.k = 0;
	if (norm(axis) == 0.0) return result;
	array<double, 3> unitAxis = standardize(axis);
	double cosHalfAngle = cos(angle / 2);
	double sinHalfAngle = sin(angle / 2);
	result.real = cosHalfAngle;
	result.i = sinHalfAngle * unitAxis[0];
	result.j = sinHalfAngle * unitAxis[1];
	result.k = sinHalfAngle * unitAxis[2];
	return result;
}

// quaternion multiplication
cQuaternion operator * (cQuaternion left, cQuaternion right) {
	cQuaternion result;
	result.real = left.real * right.real - left.i * right.i - left.j * right.j - left.k * right.k;
	result.i = left.real * right.i + right.real * left.i + left.j * right.k - left.k * right.j;
	result.j = left.real * right.j + right.real * left.j + left.k * right.i - left.i * right.k;
	result.k = left.real * right.k + right.real * left.k + left.i * right.j - left.j * right.i;
	return result;
}

// rotate a vector with a given angle through a given axis
array<double, 3> rotateVector(array<double, 3> vector, double angle, array<double, 3> axis) {
	cQuaternion rotQuat = getRotationQuaternion(angle, axis);
	cQuaternion vectQuat = getQuaternion(vector);
	cQuaternion invRotQuat = getRotationQuaternion(-angle, axis);
	cQuaternion rotVectQuat = rotQuat * vectQuat * invRotQuat;
	array<double, 3> rotVect = {rotVectQuat.i, rotVectQuat.j, rotVectQuat.k};
	return rotVect;
}

cCamera::cCamera(){
	speed = 0.2;

	position[0] = 0;
	position[1] = 0;
	position[2] = 0;

	view[0] = 0;
	view[1] = 0;
	view[2] = -100;

	up[0] = 0;
	up[1] = 1;
	up[2] = 0;

}

cCamera* cCamera::getCamera(){
	if (p_Camera == NULL){
		p_Camera = new cCamera;
	}
	return p_Camera;
}

void cCamera::bindCamera(){
	gluLookAt(position[0],position[1],position[2],view[0],view[1],view[2],up[0],up[1],up[2]);
}

void cCamera::setCamera(double posx,double posy,double posz,double viewx,double viewy,double viewz,double upx,double upy,double upz){
	position[0] = posx;
	position[1] = posy;
	position[2] = posz;

	view[0] = viewx;
	view[1] = viewy;
	view[2] = viewz;

	up[0] = upx;
	up[1] = upy;
	up[2] = upz;
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
	this->speed = speed;
}

//绕 x 旋转
void cCamera::pitchCamera(double angle){
	array<double, 3> viewDir = view - position;
	array<double, 3> rightDir = cross(viewDir, up);
	array<double, 3> rotViewDir = rotateVector(viewDir, angle, rightDir);
	// 判断right向量是否反向，不反向则应用旋转
	if (dot(cross(rotViewDir, up), rightDir) > 0) view = position + rotViewDir;
}

//绕 y 旋转
void cCamera::yawCamera(double angle){
	/*
	double sinT=sin(angle);
	double cosT=cos(angle);

	float dir[2]={(view[0]-position[0]),(view[2]-position[2])};

	//change x
	view[0]=dir[0]*cosT+dir[1]*sinT+position[0];
	//change z
	view[2]=-dir[0]*sinT+dir[1]*cosT+position[2];
	*/
	array<double, 3> viewDir = view - position;
	array<double, 3> rotViewDir = rotateVector(viewDir, angle, up);
	view = position + rotViewDir;
}

//							前一刻的鼠标位置(px,py)    后一刻的鼠标位置(nx,ny)
void cCamera::setViewByMouse(int px,int py,int nx,int ny){
	 double dx=nx-px;
	 double dy=ny-py;
	 //show(dx);
	 //show(dy);
	 pitchCamera(-dy*0.003);
	 yawCamera(-dx*0.003);
}

void cCamera::moveForward() {
	// 计算出前向向量，标准化，更新position和view
	array<double, 3> unitViewDir = standardize(view - position);
	position = position + speed * unitViewDir;
	view = view + speed * unitViewDir;
}					
void cCamera::moveBack() {
	array<double, 3> unitViewDir = standardize(view - position);
	position = position - speed * unitViewDir;
	view = view - speed * unitViewDir;
}	

void cCamera::moveLeft() {
	// 用叉乘计算向左向量，标准化，更新position和view
	array<double, 3> viewDir = view - position;
	array<double, 3> leftDir = standardize(cross(up, viewDir));
	position = position + speed * leftDir;
	view = view + speed * leftDir;
}					
void cCamera::moveRight() {
	array<double, 3> viewDir = view - position;
	array<double, 3> leftDir = standardize(cross(up, viewDir));
	position = position - speed * leftDir;
	view = view - speed * leftDir;
}				

void cCamera::moveUp() {
	// 直接用上方向量移动，避免倾斜移动
	array<double, 3> unitUp = standardize(up);
	position = position + speed * unitUp;
	view = view + speed * unitUp;
}						
void cCamera::moveDown() {
	array<double, 3> unitUp = standardize(up);
	position = position - speed * unitUp;
	view = view - speed * unitUp;
}
