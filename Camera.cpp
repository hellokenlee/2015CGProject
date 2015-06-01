#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include "util.h"
#include "Camera.h"

cCamera *cCamera::p_Camera = NULL;

cCamera &cCamera::getCamera() {
	if (p_Camera == NULL) {
		p_Camera = new cCamera;
	}
	return *p_Camera;
}

void cCamera::setCamera(double posx, double posy, double posz,
						double viewx, double viewy, double viewz,
						double upx, double upy, double upz) {
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

void cCamera::setLook() {
	gluLookAt(position[0], position[1], position[2],
		view[0], view[1], view[2],
		up[0], up[1], up[2]);
}

array<double,3> cCamera::getPosition() { return position; }
array<double,3> cCamera::getView() { return view; } 
array<double,3> cCamera::getUp() { return up; }

double cCamera::getSpeed() { return speed; }
void cCamera::setSpeed(double speed) { this->speed = speed; }

void cCamera::rotateView(double angle, double x, double y, double z) {
	array<double, 3> newView;
	array<double, 3> viewVector = view - position;
	double cosAngle = cos(angle);
	double sinAngle = sin(angle);
	// x
	newView[0] = (cosAngle + (1 - cosAngle) * x * x) * viewVector[0];
	newView[0] += ((1 - cosAngle) * x * y - z * sinAngle) * viewVector[1];
	newView[0] += ((1 - cosAngle) * x * z - y * sinAngle) * viewVector[2];
	// y
	newView[1] = ((1 - cosAngle) * x * y + z * sinAngle)	 * viewVector[0];
	newView[1] += (cosAngle + (1 - cosAngle) * y * y) * viewVector[1];
	newView[1] += ((1 - cosAngle) * y * z - x * sinAngle) * viewVector[2];
	// z
	newView[2] = ((1 - cosAngle) * x * z - y * sinAngle)	 * viewVector[0];
	newView[2] += ((1 - cosAngle) * y * z + x * sinAngle) * viewVector[1];
	newView[2] += (cosAngle + (1 - cosAngle) * z * z) * viewVector[2];
	view = position + standardize(newView);
}

void cCamera::rotateUp(double angleRadian, double x, double y, double z) {
	array<double, 3> newUp;
	double cosAngle = cos(angleRadian);
	double sinAngle = sin(angleRadian);
	// x
	newUp[0] = (cosAngle + (1 - cosAngle) * x * x) * up[0];
	newUp[0] += ((1 - cosAngle) * x * y - z * sinAngle) * up[1];
	newUp[0] += ((1 - cosAngle) * x * z - y * sinAngle) * up[2];
	// y
	newUp[1] = ((1 - cosAngle) * x * y + z * sinAngle)	 * up[0];
	newUp[1] += (cosAngle + (1 - cosAngle) * y * y) * up[1];
	newUp[1] += ((1 - cosAngle) * y * z - x * sinAngle) * up[2];
	// z
	newUp[2] = ((1 - cosAngle) * x * z - y * sinAngle)	 * up[0];
	newUp[2] += ((1 - cosAngle) * y * z + x * sinAngle) * up[1];
	newUp[2] += (cosAngle + (1 - cosAngle) * z * z) * up[2];
	up = standardize(newUp);
}

void cCamera::yaw(double angleRadian) {
	array<double, 3> viewVector = view - position;
	array<double, 3> rightVector = cross(viewVector, up);
	array<double, 3> upVector = cross(rightVector, viewVector);
	array<double, 3> stdUpVector = standardize(upVector);
	rotateView(angleRadian, stdUpVector[0], stdUpVector[1], stdUpVector[2]);
}

void cCamera::pitch(double angleRadian) {
	array<double, 3> viewVector = view - position;
	array<double, 3> rightVector = cross(viewVector, up);
	array<double, 3> stdRightVector = standardize(rightVector);
	rotateView(angleRadian, stdRightVector[0], stdRightVector[1], stdRightVector[2]);
	rotateUp(angleRadian, stdRightVector[0], stdRightVector[1], stdRightVector[2]);
}

void cCamera::moveForward() {
	array<double, 3> viewVector = view - position;
	array<double, 3> stdViewVector = standardize(viewVector);
	position = position + speed * stdViewVector;
	view = view + speed * stdViewVector;
}

void cCamera::moveBack() {
	array<double, 3> viewVector = view - position;
	array<double, 3> stdViewVector = standardize(viewVector);
	position = position - speed * stdViewVector;
	view = view - speed * stdViewVector;
}

void cCamera::moveLeft() {
	array<double, 3> viewVector = view - position;
	array<double, 3> leftVector = cross(up, viewVector);
	array<double, 3> stdLeftVector = standardize(leftVector);
	position = position + speed * stdLeftVector;
	view = view + speed * stdLeftVector;
}

void cCamera::moveRight() {
	array<double, 3> viewVector = view - position;
	array<double, 3> rightVector = cross(viewVector, up);
	array<double, 3> stdRightVector = standardize(rightVector);
	position = position + speed * stdRightVector;
	view = view + speed * stdRightVector;
}

void cCamera::moveUp() {
	position = position + speed * standardize(up);
	view = view + speed * standardize(up);
}

void cCamera::moveDown() {
	position = position - speed * standardize(up);
	view = view - speed * standardize(up);
}

cCamera::cCamera() {
	position[0] = position[1] = position[2] = 0;
	view[0] = 0; view[1] = 0; view[2] = 1;
	up[0] = 0; up[1] = 1; up[2] = 0;
	speed = 1.0;
}

