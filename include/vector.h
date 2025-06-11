#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum LISTTYPE
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
    point* p;
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

    point* a;
    point* b;
    point* c;
};

typedef struct collisionStruct collisionStruct;
typedef struct collisionStruct
{
    int success;
    point* p;
};

typedef struct listItem listItem;
typedef struct listItem
{
    enum LISTTYPE type;
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
plane* initializePlane(vector* n, point* p);
circle* initializeCircle(float x, float y, float z, float r);
ellips* initializeEllips(circle* circle, float a, float b, float c);
triangle* initializeTriangle(plane* p, point* a, point* b, point* c);

//for these, we return 0 if there is no collision, 1 if there is
int circleCollision(circle* c, line* l);
int planeCollision(plane* p, line* l);
int triangleCollision(triangle* t, line* l);
int pointCollision(point* p, line* l);

collisionStruct circleCollision2(circle* c, line* l);
collisionStruct planeCollision2(plane* p, line* l);
collisionStruct triangleCollision2(triangle* t, line* l);
collisionStruct pointCollision2(point* p, line* l);
