#include "vector.h"

vector* initializeVector(int length, ...)
{
    vector* v = (vector *)malloc(sizeof(vector));

    v->nums = malloc(sizeof(float) * length);
    v->length = length;

    va_list args;
    va_start(args, length);
    for(int i = 0; i < length; i++)
    {
        v->nums[i] = (float)va_arg(args, double);
    }
    va_end(args);
    return v;
}

void normalize(vector* v)
{
    float length = 0;

    for(int i = 0; i < v->length; i++)
    {
        float num = v->nums[i];
        length += num * num;
    }

    length = sqrtf(length);

    if(length == 0.0f)
        return;

    for(int i = 0; i < v->length; i++)
    {
        v->nums[i] /= length;
    }
}

vector* addition(vector* v1, vector* v2)
{
    vector* v = (vector *)malloc(sizeof(vector));

    v->nums = malloc(sizeof(float) * v1->length);
    v->length = v1->length;

    for(int i = 0; i < v->length; i++)
    {
        v->nums[i] = v1->nums[i] + v2->nums[i];
    }

    return v;
}

vector* subtraction(vector* v1, vector* v2)
{
    vector* v = (vector *)malloc(sizeof(vector));

    v->nums = malloc(sizeof(float) * v1->length);
    v->length = v1->length;

    for(int i = 0; i < v->length; i++)
    {
        v->nums[i] = v1->nums[i] - v2->nums[i];
    }

    return v;
}

vector* multiplication(int x, vector* v1)
{
    vector* v = (vector *)malloc(sizeof(vector));

    v->nums = malloc(sizeof(float) * v1->length);
    v->length = v1->length;

    for(int i = 0; i < v->length; i++)
    {
        v->nums[i] = v1->nums[i] * x;
    }

    return v;
}
float dotProduct(vector* v1, vector* v2)
{
    if(v1->length == 2)
    {
        return v1->nums[0] * v2->nums[0] + v1->nums[1] * v2->nums[1];
    }
    else
    { //we assume 3rd dimension if it isnt the second dimension
        return v1->nums[0] * v2->nums[0] + v1->nums[1] * v2->nums[1] + v1->nums[2] * v2->nums[2];
    }
}