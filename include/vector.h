#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef struct vector vector;
typedef struct vector
{
    float* nums;
    int length;
};

typedef struct point point;
typedef struct point
{
    float* point;
    int length;
};

vector* initializeVector(int length, ...);
void normalize(vector* v);
vector* addition(vector* v1, vector* v2);
vector* subtraction(vector* v1, vector* v2);
vector* multiplication(int x, vector* v1);
float dotProduct(vector* v1, vector* v2);
