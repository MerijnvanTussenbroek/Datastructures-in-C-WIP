#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum vectorType
{
    LINE,
    CIRCLE,
    PLANE,
    ELLIPS,
    TRIANGLE
};

typedef struct vector vector;
typedef struct vector
{
    float nums[3];
};

typedef struct point point;
typedef struct point
{
    float nums[3];
};

typedef struct line line;
typedef struct line
{
    vector* start;

    vector* direction;
};

typedef struct plane plane;
typedef struct plane
{
    vector* n;
    vector* p;
};

typedef struct circle circle;
typedef struct circle
{
    float x;
    float y;
    float z;

    float r;
};

typedef struct ellips ellips;
typedef struct ellips
{
    circle* circle;

    float a;
    float b;
    float c;
};

typedef struct triangle triangle;
typedef struct triangle
{
    plane* p;

    vector* a;
    vector* b;
    vector* c;
};

typedef struct collisionStruct collisionStruct;
typedef struct collisionStruct
{
    int success;
    vector* v;
};

typedef struct figure figure;
typedef struct figure
{
    enum vectorType type;
    union 
    {
        line* l;
        plane* p;
        circle* c;
        ellips* e;
        triangle* t;
    };  
};

vector* initializeVector(float x, float y, float z);
vector* makeVector(point* p1, point* p2);
point* initializePoint(float x, float y, float z);
void normalize(vector* v);
vector* addition(vector* v1, vector* v2);
vector* subtraction(vector* v1, vector* v2);
vector* multiplication(int x, vector* v1);
float vectorLength(vector* v);
float dotProduct(vector* v1, vector* v2);
vector* crossProduct(vector* v1, vector* v2);

line* initializeLine(vector* start, vector* dir);
plane* initializePlane(vector* n, vector* p);
circle* initializeCircle(float x, float y, float z, float r);
ellips* initializeEllips(circle* circle, float a, float b, float c);
triangle* initializeTriangle(plane* p, vector* a, vector* b, vector* c);

//for these, we return -1 if there is no collision, if there is, we return a value more than 1
int circleCollision(circle* c, line* l, float epsilon);
int planeCollision(plane* p, line* l, float epsilon);
int triangleCollision(triangle* t, line* l, float epsilon);
int ellipsCollision(ellips* e, line* l, float epsilon);
int pointCollision(point* p, line* l, float epsilon);

collisionStruct circleCollision2(circle* c, line* l, float epsilon);
collisionStruct planeCollision2(plane* p, line* l, float epsilon);
collisionStruct triangleCollision2(triangle* t, line* l, float epsilon);
collisionStruct ellipsCollision2(ellips* e, line* l, float epsilon);
collisionStruct pointCollision2(point* p, line* l, float epsilon);
