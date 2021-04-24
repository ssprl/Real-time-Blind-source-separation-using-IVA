#define _CRT_OBSOLETE_NO_WARNINGS
#ifndef TRANSFORMS_H
#define TRANSFORMS_H
#define _USE_MATH_DEFINES


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Transform {
	int points;
	double* sine;
	double* cosine;
	double* real;
	double* imaginary;
	void(*doTransform)(struct Transform* transform, double* input);
	void(*invTransform)(struct Transform* transform, double* inputreal, double* inputimaginary);
} Transform;

Transform* newTransform(int points);
void transformMagnitude(Transform* transform, double* output);
void invtranMagnitude(Transform* transform, double* output);
void destroyTransform(Transform** transform);


#endif
#pragma once

