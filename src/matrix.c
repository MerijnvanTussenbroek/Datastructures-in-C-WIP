#include "matrix.h"

matrix* initializeEmptyMatrix(int width, int height)
{
    if(width <= 0 || height <= 0)
        return NULL;

    matrix* s = malloc(sizeof(matrix));

    s->width = width;
    s->height = height;

    s->a = malloc(sizeof(int *) * width);

    for(int i = 0; i < width; i++)
    {
        s->a[i] = malloc(sizeof(int) * height);
        for(int j = 0; j < height; j++)
        {
            s->a[i][j] = 0;
        }
    }

    return s;
}

matrix* initializeMatrix(int width, int height, ...)
{
    if(width <= 0 || height <= 0)
        return NULL;

    matrix* s = malloc(sizeof(matrix));

    s->width = width;
    s->height = height;

    va_list l;

    va_start(l, height);

    s->a = malloc(sizeof(int *) * width);

    for(int i = 0; i < width; i++)
    {
        s->a[i] = malloc(sizeof(int) * height);
        for(int j = 0; j < height; j++)
        {
            s->a[i][j] = va_arg(l, int);
        }
    }

    va_end(l);

    return s;
}

matrix* matrixAdd(matrix* a, matrix* b)
{
    if(a == NULL || b == NULL)
        return NULL;
    if(a->height != b->height || a->width != b->width)
        return NULL;

    
    matrix* s = initializeEmptyMatrix(a->width, a->height);

    int width = a->width;
    int height = a->height;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            s->a[i][j] = a->a[i][j] + b->a[i][j];
        }
    }

    return s;
}

matrix* matrixSub(matrix* a, matrix* b)
{
    if(a == NULL || b == NULL)
        return NULL;
    if(a->height != b->height || a->width != b->width)
        return NULL;

    matrix* s = initializeEmptyMatrix(a->width, a->height);

    int width = a->width;
    int height = a->height;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            s->a[i][j] = a->a[i][j] - b->a[i][j];
        }
    }


    return s;
}

matrix* matrixScal(matrix* a, int b)
{
    if(a == NULL)
        return NULL;

    int width = a->width;
    int height = a->height;

    matrix* s = initializeEmptyMatrix(width, height);

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            s->a[i][j] = a->a[i][j] * b;
        }
    }

    return s;
}

matrix* matrixMul(matrix* a, matrix* b)
{
    if(a == NULL || b == NULL)
        return NULL;
    if(a->width != b->height)
        return NULL;
    
    matrix* s = initializeEmptyMatrix(b->width, a->height);

    int width = b->width;
    int height = a->height;

    int size = b->height;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            int total = 0;
            for(int k = 0; k < size; k++)
            {
                total += a->a[i][k] * b->a[k][j];
            }
            s->a[i][j] = total;
        }
    }

    return s;
}

matrix* giveIdentityMatrix(int size)
{
    matrix* s = initializeEmptyMatrix(size, size);

    for(int i = 0; i < size; i++)
    {
        s->a[i][i] = 1;
    }

    return s;
}

matrix* giveNullMatrix(int size)
{
    return initializeEmptyMatrix(size, size);
}

matrix* matrixTranspose(matrix* a)
{
    int width = a->width;
    int height = a->height;

    matrix* s = initializeEmptyMatrix(height, width);

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            s->a[j][i] = a->a[width - i][height - j];
        }
    }

    return s;
}

matrix* matrixInv(matrix* a)
{
    matrix* s = initializeEmptyMatrix(a->width, a->height);

    int width = a->width;
    int height = a->height;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            s->a[i][j] = a->a[width - i][height - j];
        }
    }

    return s;
}

void matrixDestroy(matrix* a)
{
    free(a->a);
    free(a);
}