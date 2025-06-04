#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct{
unsigned int rows;
unsigned int cols;
float *elem;
}MAT;

#define ELEM(mat,i,j) ((mat)->elem[(i)*(mat)->cols+(j)])

MAT *mat_create_with_type(unsigned int rows, unsigned int cols){
	if (rows == 0 || cols == 0){
		return NULL;
	}
	
	
	MAT *mat = (MAT*)malloc(sizeof(MAT));
	if (mat == NULL){
		return NULL;
	}
	mat->rows = rows;
	mat->cols = cols;
	mat->elem = (float*)malloc(rows*cols*sizeof(float));
	if (mat->elem == NULL){
		free(mat);
		return NULL;
	}
	return mat;
}

void mat_free(MAT *mat){
	if (mat != NULL){
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
	if(mat == NULL){
		return 0;
	}
}

void mat_generate_random_int_elems(MAT *mat, int min, int max){
	if (mat == NULL || mat->elem == NULL){
		return;
	}
	for (unsigned int i = 0; i < mat->rows; i++){
		for(unsigned int j = 0; j < mat->cols; j++){
		int el = min + rand() % (max - min + 1);
		ELEM(mat,i,j) = (float)el;
		}
	}
}

int mat_determinant(MAT *mat){
	if(mat == NULL || mat->elem == NULL || mat_is_square_or_not(mat) == 0){
		return 0;
	}
	unsigned int n = mat->rows;
	int det = 0;
	
	if (n == 1){
		det = (int)ELEM(mat, 0, 0);
	}
	
	if (n == 2){
		det = (int)ELEM(mat, 0, 0)*ELEM(mat, 1, 1)-ELEM(mat, 0, 1)*ELEM(mat, 1, 0);
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
				ELEM(minor, minor_i, minor_j) = ELEM(mat, i, j);
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
		int minor_det = mat_determinant(minor);
		int term_det = sign * (int)ELEM(mat, 0, ji0) * minor_det;
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
	if (temp_mat == NULL){
		return 0;
	}
	int attempts = 0;
	int maxpocet_attempts = 1000;
	while (attempts < maxpocet_attempts){
		mat_generate_random_int_elems(temp_mat, -10, 10);
		int det = mat_determinant(temp_mat);
		if (abs(det) == 1){
			int all_int = 1;
			for (unsigned int i = 0; i < temp_mat->rows; i++){
			   if (all_int == 0){
			    	break;
			   }
			   for (unsigned int j = 0; j < temp_mat->cols; j++){
			      float element = ELEM(temp_mat, i, j);
			      if (element != floorf(element)){
			   	  all_int = 0;
			   	  break;
			      }
	    	    }
    	    }
			for (unsigned int i = 0; i < mat->rows; i++){
			   for (unsigned int j = 0; j < mat->cols; j++){
			       ELEM(mat, i, j) = ELEM(temp_mat, i, j);
			   }	
			}
		    mat_free(temp_mat);
		    return 1;
		}
		attempts++;
	}
	mat_free(temp_mat);
	return 0;
}

void mat_print(MAT *mat){
	for (unsigned int i = 0; i < mat->rows; i++){
		for (unsigned int j = 0; j < mat->cols; j++){
			printf("%4.0f", ELEM(mat, i, j));
	    }
	printf("\n");
   }
}

int main (){
	srand(time(NULL));
	unsigned int size = 3;
	MAT *mat = mat_create_with_type(size, size);
	if (mat == NULL){
		printf("Nepodarilo sa vytvorit maticu.\n");
		return 1;
	}
	if (mat_create_random_unimodular_integer(mat) == 1){
		printf("Vygenerovana unimodularna matica:\n");
		mat_print(mat);
		int det = mat_determinant(mat);
		printf("Jej determinant: %d\n", det);
	}else{
		printf("Nepodarilo sa vygenerovat unimodularnu maticu po 1000 pokusoch.\n");
	}
	mat_free(mat);
	return 0;
}
