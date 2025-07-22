#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

typedef struct matrix matrix;
typedef struct matrix
{
    int** a;
    int width;
    int height;
};

matrix* initializeEmptyMatrix(int width, int height);
matrix* initializeMatrix(int width, int height, ...);
matrix* matrixAdd(matrix* a, matrix* b);
matrix* matrixSub(matrix* a, matrix* b);
matrix* matrixScal(matrix* a, int b);
matrix* matrixMul(matrix* a, matrix* b);
matrix* giveIdentityMatrix(int size);
matrix* giveNullMatrix(int size);
matrix* matrixTranspose(matrix* a);
matrix* matrixInv(matrix* a);
void matrixDestroy(matrix* a);