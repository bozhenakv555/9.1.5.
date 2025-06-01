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

void mat_generate_random_int_elems(MAT *mat, int min, int max){
	for (unsigned int i = 0; i < mat->rows; i++){
		for(unsigned int j = 0; j < mat->cols; j++){
			ELEM(*mat,i,j) = min + rand()% (max-min+1);
		}
	}
}

float mat_determinant(MAT *mat){
	if(mat == NULL || mat_is_square_or_not(mat) == 0){
		return 0;
	}
	unsigned int n = mat->rows;
	float det = 0;
	
	if (n == 1){
		det = ELEM(mat, 0, 0);
	}
	
	if (n == 2){
		det = ELEM(mat, 0, 0)*ELEM(mat, 1, 1)-ELEM(mat, 0, 1)*ELEM(mat, 1, 0);
	}
	
	if (n > 2){
		for (unsigned int ji0 = 0; ji0 < n; ji0++){
		MAT *minor = mat_create_with_type(n-1, n-1);
		unsigned int minor_i = 0;
		for (unsigned int i = 1; i < n; i++){
			unsigned int minor_j = 0;
			for (unsigned int j = 0; j < n; j++){
				if(j == ji0){
					continue;
				}
				ELEM(*minor, minor_i, minor_j) = ELEM(*mat, i, j);
				minor_j++;
			}
			minor_i++;
		}	
		int sign;
		if(ji0 % 2 == 0){
			sign = 1;
		}else{
			sign = -1;
		}
		float minor_det = mat_determinant(minor);
		float term_det = sign * ELEM(*mat, 0, ji0) * minor_det;
		det = det + term_det;
		mat_free(minor);
	    }
	}
return det;
}


char mat_create_random_unimodular_integer(MAT *mat){
	if(mat == NULL || mat_is_square_or_not(mat) == 0){
		return 0;
	}
    MAT *temp_mat = mat_create_with_type(mat->rows, mat->cols);
	
	int attempts = 0;
	int maxpocet_attempts = 1000;
	while (attempts < maxpocet_attempts){
		mat_generate_random_int_elems(temp_mat, -10, 10);
		float det = mat_determinant(temp_mat);
		if (abs(det) == 1.0){
			for (unsigned int i = 0; i < mat->rows; i++){
			   for (unsigned int j = 0; j < mat->cols; j++){
			       ELEM(*mat, i, j) = ELEM(*temp, i, j);
			   }	
			}
		    mat_free(temp);
		    return 1;
		}
		attempts++;
	}
	return 0;
}
