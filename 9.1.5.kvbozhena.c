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

void mat_free(MAT *mat){
	if(mat != NULL){
		if(mat->elem != NULL){
			free(mat->elem);
		}
	free(mat);
	}
}

int mat_is_square_or_not(MAT *mat){
	if(mat->rows == mat->cols){
		return 1;
	}else{
		return 0;
	}
}

void mat_generate_random_int_elems (MAT *mat, int min, int max){
	for (unsigned int i = 0; i < mat->rows; i++){
		for(unsigned int j = 0; j < mat->cols; j++){
			ELEM(*mat,i,j) = min + rand()% (max-min+1);
		}
	}
}

char mat_create_random_unimodular_integer(MAT *mat){
	if(mat == NULL && mat_is_square_or_not(mat) == 0){
		return 0;
	}
}
