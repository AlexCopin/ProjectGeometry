#include "MathUtils.h"

const float IIM_PI = 3.14159265358979323846f;

float ConvertRadToDeg(float radian) {
	return radian * 180.0f / IIM_PI;
}

float ConvertDegToRad(float degree) {
	return degree * IIM_PI / 180.0f;
}

float GetMax(float a, float b) {
	return a > b ? a : b;
}

float GetMin(float a, float b) {
	return a < b ? a : b;
}

int GetMax(int a, int b) {
	return a > b ? a : b;
}

int GetMin(int a, int b) {
	return a < b ? a : b;
}