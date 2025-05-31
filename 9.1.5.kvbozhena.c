#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct{
unsigned int rows;
unsigned int cols;
float *elem;
}MAT;

MAT mat;

#define ELEM(mat,i,j) ((mat).elem[(i)*(mat).cols+(j)])