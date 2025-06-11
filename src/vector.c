#include "vector.h"

/*
These vector datastructures and functions are specifically for 3D vectors, 
not for higher or lower dimensional vectors
*/

vector* initializeVector(float x, float y, float z)
{
    vector* v = (vector *)malloc(sizeof(vector));

    v->nums[0] = x;
    v->nums[1] = y;
    v->nums[2] = z;

    return v;
}

vector* makeVector(point* p1, point* p2)
{
    vector* v = (vector *)malloc(sizeof(vector));

    v->nums[0] = p2->nums[0] - p1->nums[0];
    v->nums[1] = p2->nums[1] - p1->nums[1];
    v->nums[2] = p2->nums[2] - p1->nums[2];

    return v;
}

point* initializePoint(float x, float y, float z)
{
    point* p = (point *)malloc(sizeof(point));

    p->nums[0] = x;
    p->nums[1] = y;
    p->nums[2] = z;

    return p;
}

void normalize(vector* v)
{
    float length = vectorLength(v);

    if(length == 0.0f)
        return;

    v->nums[0] /= length;
    v->nums[1] /= length;
    v->nums[2] /= length;
}

vector* addition(vector* v1, vector* v2)
{
    vector* v = (vector *)malloc(sizeof(vector));

    v->nums[0] = v1->nums[0] + v2->nums[0];
    v->nums[1] = v1->nums[1] + v2->nums[1];
    v->nums[2] = v1->nums[2] + v2->nums[2];

    return v;
}

vector* subtraction(vector* v1, vector* v2)
{
    vector* v = (vector *)malloc(sizeof(vector));

    v->nums[0] = v1->nums[0] - v2->nums[0];
    v->nums[1] = v1->nums[1] - v2->nums[1];
    v->nums[2] = v1->nums[2] - v2->nums[2];

    return v;
}

vector* multiplication(int x, vector* v1)
{
    vector* v = (vector *)malloc(sizeof(vector));

    v->nums[0] = v1->nums[0] * x;
    v->nums[1] = v1->nums[1] * x;
    v->nums[2] = v1->nums[2] * x;

    return v;
}

float vectorLength(vector* v)
{
    float f = 0;

    float num1 = v->nums[0];
    float num2 = v->nums[1];
    float num3 = v->nums[3];

    f += num1 * num1 + num2 * num2 + num3 * num3;

    f = sqrtf(f);

    return f;
}

inline float dotProduct(vector* v1, vector* v2)
{
    return v1->nums[0] * v2->nums[0] + v1->nums[1] * v2->nums[1] + v1->nums[2] * v2->nums[2];
}

vector* crossProduct(vector* v1, vector* v2)
{
    vector* v = (vector *)malloc(sizeof(vector));

    float* l1 = v1->nums;
    float* l2 = v2->nums;

    v->nums[0] = l1[2] * l2[3] - l1[3] * l2[2];
    v->nums[1] = l1[3] * l2[1] - l1[1] * l2[3];
    v->nums[2] = l1[1] * l2[2] - l1[2] * l2[1];

    return v;
}

line* initializeLine(vector* start, vector* dir)
{
    line* l = (line *)malloc(sizeof(line));

    l->start = start;
    l->direction = dir;

    return l;
}

plane* initializePlane(vector* n, vector* p)
{
    plane* newPlane = (plane *)malloc(sizeof(plane));

    newPlane->n = n;
    newPlane->p = p;

    return newPlane;
}

circle* initializeCircle(float x, float y, float z, float r)
{
    circle* c = (circle *)malloc(sizeof(circle));

    c->x = x;
    c->y = y;
    c->z = z;
    c->r = r;

    return c;
}

ellips* initializeEllips(circle* circle, float a, float b, float c)
{
    ellips* e = (ellips *)malloc(sizeof(ellips));

    e->circle = circle;

    e->a = a;
    e->b = b;
    e->c = c;

    return e;
}

triangle* initializeTriangle(plane* p, vector* a, vector* b, vector* c)
{
    triangle* t = (triangle *)malloc(sizeof(triangle));

    t->p = p;

    t->a = a;
    t->b = b;
    t->c = c;

    return t;
}

int circleCollision(circle* circle, line* l, float epsilon)
{
    float   vx = l->direction->nums[0],
            vy = l->direction->nums[1],
            vz = l->direction->nums[2];

    float   x0 = l->start->nums[0],
            y0 = l->start->nums[1],
            z0 = l->start->nums[2];

    float   x1 = circle->x,
            y1 = circle->y,
            z1 = circle->z;

    float radius = circle->r;

    float a = vx * vx + vy * vy + vz * vz;
    float b = 2 * (x0 * vx + y0 * vy + z0 * vz - vx * x1 - vy * y1 - vz * z1);
    float c = x0 * x0 + y0 * y0 + z0 * z0 - 2 * x0 * x1 - 2 * y0 * y1 - 2 * z0 * z1
        + x1 * x1 + y1 * y1 + z1 * z1 - radius * radius;

    float D = b * b - 4 * a * c;

    if(D < 0)
        return -1;

    float d = sqrtf(D);

    float t = (d - b) / (2 * a);
    float s = (-1 * d - b) / (2 * a);

    if(s > epsilon && s <= t)
    {
        return s;
    }
    if(t > epsilon)
    {
        return t;
    }

    return -1;
}

int planeCollision(plane* p, line* l, float epsilon)
{
    float dotProduct1 = dotProduct(p->n, l->direction);

    float   DTOx = p->p->nums[0],
            DTOy = p->p->nums[1],
            DTOz = p->p->nums[2];

    float   nx = p->n->nums[0],
            ny = p->n->nums[1],
            nz = p->n->nums[2];            

    float   startx = l->start->nums[0],
            starty = l->start->nums[1],
            startz = l->start->nums[2];

    float   dirx = l->direction->nums[0],
            diry = l->direction->nums[1],
            dirz = l->direction->nums[2];

    float L = 0;

    if(dotProduct1 > 0)
    {
        L = (DTOx * nx + DTOy * ny + DTOz * nz);

        L -= (startx * nx + starty * ny + startz * nz);

        L /= (nx * dirx + ny * diry + nz * dirz);
    }
    else
    {
        L = (DTOx * -1 * nx + DTOy * -1 * ny + DTOz * -1 * nz);

        L -= (startx * -1 * nx + starty * -1 * ny + startz * -1 * nz);

        L /= (-1 * nx * dirx + -1 * ny * diry + -1 * nz * dirz);
    }

    if(L > epsilon)
    {
        return L;
    }

    return -1;
}

int triangleCollision(triangle* t, line* l, float epsilon)
{
    collisionStruct s = planeCollision2(t->p, l, epsilon);

    int succes = 0;

    if(s.success != -1)
    {
        vector* p = s.v;

        vector* bMina = subtraction(t->b, t->a);
        vector* aMinc = subtraction(t->a, t->c);
        vector* cMinb = subtraction (t->c, t->b);

        vector* pMina = subtraction(p, t->a);
        vector* pMinc = subtraction(p, t->b);
        vector* pMinb = subtraction(p, t->c);

        vector* crossProduct1 = crossProduct(bMina, pMina);
        if(dotProduct(crossProduct1, t->p->n) >= 0)
        {
            vector* crossProduct2 = crossProduct(aMinc, pMinc);
            float dotProduct2 = dotProduct(crossProduct2, t->p->n);
                if(dotProduct2 >= 0)
                {
                    vector* crossProduct3 = crossProduct(cMinb, pMinb);
                    float dotProduct3;
                    if(dotProduct3 >= 0)
                    {
                        succes = 1;
                    }
                    free(crossProduct3);
                }

            free(crossProduct2);
        }
        free(crossProduct1);

        free(p);
        
        free(bMina);
        free(aMinc);
        free(cMinb);

        free(pMina);
        free(pMinb);
        free(pMinc);
    }
    

    return succes;
}

int ellipsCollision(ellips* e, line* l, float epsilon)
{
    return 0;
}

int pointCollision(point* p, line* l, float epsilon)
{
    return 0;
}

collisionStruct circleCollision2(circle* c, line* l, float epsilon)
{
    collisionStruct cs = { 0 };
    cs.success = 0;

    float f = circleCollision(c, l, epsilon);

    if(f != -1)
    {
        cs.success = 1;
        cs.v = (vector *)malloc(sizeof(vector));
        cs.v->nums[0] = l->start->nums[0] + f * l->direction->nums[0];
        cs.v->nums[1] = l->start->nums[1] + f * l->direction->nums[1];
        cs.v->nums[2] = l->start->nums[2] + f * l->direction->nums[2];
    }

    return cs;
}

collisionStruct planeCollision2(plane* p, line* l, float epsilon)
{
    collisionStruct cs = { 0 };
    cs.success = 0;

    float f = planeCollision(p, l, epsilon);

    if(f != -1)
    {
        cs.success = 1;
        cs.v = (vector *)malloc(sizeof(vector));
        cs.v->nums[0] = l->start->nums[0] + f * l->direction->nums[0];
        cs.v->nums[1] = l->start->nums[1] + f * l->direction->nums[1];
        cs.v->nums[2] = l->start->nums[2] + f * l->direction->nums[2];
    }

    return cs;
}

collisionStruct triangleCollision2(triangle* t, line* l, float epsilon)
{
    collisionStruct s = planeCollision2(t->p, l, epsilon);

    s.success = 0;

    if(s.success != -1)
    {
        vector* p = s.v;

        vector* bMina = subtraction(t->b, t->a);
        vector* aMinc = subtraction(t->a, t->c);
        vector* cMinb = subtraction (t->c, t->b);

        vector* pMina = subtraction(p, t->a);
        vector* pMinc = subtraction(p, t->b);
        vector* pMinb = subtraction(p, t->c);

        vector* crossProduct1 = crossProduct(bMina, pMina);
        if(dotProduct(crossProduct1, t->p->n) >= 0)
        {
            vector* crossProduct2 = crossProduct(aMinc, pMinc);
            float dotProduct2 = dotProduct(crossProduct2, t->p->n);
                if(dotProduct2 >= 0)
                {
                    vector* crossProduct3 = crossProduct(cMinb, pMinb);
                    float dotProduct3 = dotProduct(crossProduct3, t->p->n);
                    if(dotProduct3 >= 0)
                    {
                        s.success = 1;
                    }
                    free(crossProduct3);
                }
            free(crossProduct2);
        }
        free(crossProduct1);
        
        free(bMina);
        free(aMinc);
        free(cMinb);

        free(pMina);
        free(pMinb);
        free(pMinc);
    }
    
    free(s.v);

    return s;
}

collisionStruct ellipsCollision2(ellips* e, line* l, float epsilon)
{
    collisionStruct cs = { 0 };
    cs.success = 0;

    return cs;   
}

collisionStruct pointCollision2(point* p, line* l, float epsilon)
{
    collisionStruct cs = { 0 };
    cs.success = 0;

    return cs;
}