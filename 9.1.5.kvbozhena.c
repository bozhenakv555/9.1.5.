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

MAT *mat_create_with_type(unsigned int rows, unsigned int cols){
	MAT *mat = (MAT*)malloc(sizeof(MAT));
	if (mat == NULL){
		return NULL;
	}
	mat->rows = rows;
	mat->cols = cols;
	mat->elem = (float*)malloc(rows*cols*sizeof(float));
	if(mat->elem == NULL){
		free(mat);
		return NULL;
	}
	return mat;
}

