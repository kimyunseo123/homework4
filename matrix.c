#include <stdio.h>
#include <stdlib.h> 
#include <time.h> // rand() 함수 사용을 위함

/* Method Declaration (선언) */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{
    char command;
    printf("[----- [Kim Yun Seo]  [2020021016] -----]\n");

	int row, col; // 행렬
	srand(time(NULL)); // random

	printf("Input row and col : ");
	scanf("%d %d", &row, &col); // 행렬값 받기
    int** matrix_a = create_matrix(row, col); // scanf 로 받은 행렬값을 matrix_a 에 받기
	int** matrix_b = create_matrix(row, col); // scanf 로 받은 행렬값을 matrix_b 에 받기
    int** matrix_a_t = create_matrix(col, row); // scanf 로 받은 행렬값을 matrix_c 에 받기

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;} // 행렬값이 NULL 이면, return -1

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // command 값 받기

		switch(command) {
		case 'z': case 'Z': // command 값이 z 또는 Z 일 경우
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col); // (matrix_a) 행렬값 채우기
			fill_data(matrix_b, row, col); // (matrix_b) 행렬값 채우기
			break;
        case 'p': case 'P': // command 값이 p 또는 P 일 경우
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col); // (matrix_a) 행렬 출력하기
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col); // (matrix_b) 행렬 출력하기
			break;
        case 'a': case 'A': // command 값이 a 또는 A 일 경우
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col); // (matrix_a) + (matrix_b)
			break;
        case 's': case 'S': // command 값이 s 또는 S 일 경우
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); // (matrix_a) - (matrix_b)
			break;
        case 't': case 'T': // command 값이 t 또는 T 일 경우
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); // (matrix_a)의 전지행렬 (matrix_a_t) 구현
            print_matrix(matrix_a_t, col, row);
			break;
        case 'm': case 'M': // command 값이 m 또는 M 일 경우
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); // (matrix_a)의 전지행렬 (matrix_a_t) 구현
            multiply_matrix(matrix_a, matrix_a_t, row, col); // (matrix_a) * (matrix_a_t)
			break;
        case 'q': case 'Q': // command 값이 q 또는 Q 일 경우
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); // 행렬 (matrix_a_t) 사용을 끝내고, 재사용 가능하도록 설정
            free_matrix(matrix_a, row, col); // 행렬 (matrix_a) 사용을 끝내고, 재사용 가능하도록 설정
            free_matrix(matrix_b, row, col); // 행렬 (matrix_b) 사용을 끝내고, 재사용 가능하도록 설정
			break;

		default: // 기본값
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	} while(command != 'q' && command != 'Q'); // 입력받은 command 값이 q 또는 Q 이 아닐 경우 동안 진행

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
// malloc()을 이용하여 2차원 배열(행렬) 생성
int** create_matrix(int row, int col)
{
	/* Check pre conditions (전처리 검사) */
	if (row <= 0 || col <= 0) { // 만약 (행/열)의 값이 0보다 작거나 같을 경우
		printf("Check the size of row and col!\n"); // (= 값을 다시 확인하도록 함)
		return NULL; // NULL
	}
	// 비순차 사상 (메모리 주소가 비연속적)
	int** matrix = (int**)malloc(sizeof(int*) * row); // matrix 메모리를 각 행의 (포인터 수) 만큼 확보
	for (int r = 0; r < row; r++) {
		matrix[r] = (int*)malloc(sizeof(int) * col); // matrix의 메모리를 각 행의 (원소 수) 만큼 확보
	}

	/* Check post conditions (후처리 검사) */
	if (matrix == NULL) { // matrix의 값이 NULL일 경우
		printf("Memory Allocation Failed.\n"); // (= 메모리 할당 실패)
		return NULL; // NULL
	}

	return matrix; // matrix 값 return
}

/* print matrix whose size is row x col */
// matrix(행렬) 출력
void print_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions (전처리 검사) */
	if (row <= 0 || col <= 0) { // 만약 (행/열)의 값이 0보다 작거나 같을 경우
		printf("Check the size of row and col!\n"); // (= 값을 다시 확인하도록 함)
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) { // 첫번째 행부터 마지막 행까지 진행
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // 첫번째 열부터 마지막 열까지 진행
			printf("%3d ", matrix[matrix_row][matrix_col]); // [행][열] 값 출력
		printf("\n");
	}
	printf("\n"); // 줄바꿈

	/* Check post conditions (후처리 검사) */
	 if (matrix == NULL) { // matrix의 값이 NULL일 경우
		printf("Memory Allocation Failed.\n"); // (= 메모리 할당 실패)
		return;
	}

	return;
}

/* free memory allocated by create_matrix() */
// create_matrix()에 할당된 빈 메모리
int free_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions (전처리 검사) */
	if (row <= 0 || col <= 0) { // 만약 (행/열)의 값이 0보다 작거나 같을 경우
		printf("Check the size of row and col!\n"); // (= 값을 다시 확인하도록 함)
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // 첫번째 행부터 마지막 행까지 진행
		free(matrix[matrix_row]); // matrix[matrix_row]의 사용을 끝내고, 재사용 가능하도록 설정
	}

	free(matrix); // matrix의 사용을 끝내고, 재사용 가능하도록 설정
	return 1;
}

/* assign random values to the given matrix */
// 주어진 matrix에 random으로 값 할당
int fill_data(int** matrix, int row, int col)
{
	/* Check pre conditions (전처리 검사) */
	if (row <= 0 || col <= 0) { // 만약 (행/열)의 값이 0보다 작거나 같을 경우
		printf("Check the size of row and col!\n"); // (= 값을 다시 확인하도록 함)
		return -1;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) // 첫번째 행부터 마지막 행까지 진행
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // 첫번째 열부터 마지막 열까지 진행
			matrix[matrix_row][matrix_col] = rand() % 20; // [행][열]의 값으로 0~19 사이의 값을 random으로 지정

	/* Check post conditions (후처리 검사) */
    if (matrix == NULL) { // matrix의 값이 NULL일 경우
		printf("Memory Allocation Failed.\n"); // (= 메모리 할당 실패)
		return -1;
	}
	return 1;
}

/* mmatrix_sum = matrix_a + matrix_b (덧셈 연산) */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col);
	/* Check pre conditions (전처리 검사) */
	if (row <= 0 || col <= 0) { // 만약 (행/열)의 값이 0보다 작거나 같을 경우
		printf("Check the size of row and col!\n"); // (= 값을 다시 확인하도록 함)
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // 첫번째 행부터 마지막 행까지 진행
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // 첫번째 열부터 마지막 열까지 진행
			matrix_sum[matrix_row][matrix_col]  
			= matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col]; // matrix_a와 matrix_b 의 [행]과 [열]끼리 더하기
	}
	/* Check post conditions (후처리 검사) */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) { // matrix(a/b/sum)의 값이 NULL일 경우
		printf("Memory Allocation Failed.\n"); // (= 메모리 할당 실패)
		return -1;
	}

	print_matrix(matrix_sum, row, col); // matrix_sum 값 출력
	free_matrix(matrix_sum, row, col); // matrix의 사용을 끝내고, 재사용 가능하도록 설정

	return 1;
}

/* matrix_sub = matrix_a - matrix_b (뺄셈 연산) */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col);
	/* Check pre conditions (전처리 검사) */
	if (row <= 0 || col <= 0) { // 만약 (행/열)의 값이 0보다 작거나 같을 경우
		printf("Check the size of row and col!\n"); // (= 값을 다시 확인하도록 함)
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // 첫번째 행부터 마지막 행까지 진행
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // 첫번째 열부터 마지막 열까지 진행
			matrix_sub[matrix_row][matrix_col] 
			= matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col]; // matrix_a와 matrix_b 의 [행]과 [열]끼리 빼기
	}
	/* Check post conditions (후처리 검사) */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) { // matrix(a/b/sum)의 값이 NULL일 경우
		printf("Memory Allocation Failed.\n"); // (= 메모리 할당 실패)
		return -1;
	}
	print_matrix(matrix_sub, row, col); // matrix_sub 값 출력
	free_matrix(matrix_sub, row, col); // matrix의 사용을 끝내고, 재사용 가능하도록 설정

	return 1;
}

/* transpose the matrix to matrix_t */
// matrix 의 전치행렬 matrix_t 구현하기
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 만약 (행/열)의 값이 0보다 작거나 같을 경우
		printf("Check the size of row and col!\n"); // (= 값을 다시 확인하도록 함)
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // 첫번째 행부터 마지막 행까지 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // 첫번째 열부터 마지막 열까지 반복
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row]; // [행][열] -> [열][행]
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) { // matrix 또는 matrix_t의 값이 NULL일 경우
		printf("Memory Allocation Failed.\n"); // (= 메모리 할당 실패)
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_axt = create_matrix(row, row);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 만약 (행/열)의 값이 0보다 작거나 같을 경우
		printf("Check the size of row and col!\n"); // (= 값을 다시 확인하도록 함)
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) { // (matrix_a)의 첫번째 행부터 마지막 행까지 진행
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) { // 전치행렬 (matrix_t)의 첫번째 행부터 마지막 행까지 진행
			int temp = 0; // temp 를 0으로 초기화
			for (int matrix_col = 0; matrix_col < col; matrix_col++) // (matrix)의 첫번째 열부터 마지막 열까지 진행
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];
				// temp = temp + 행렬A[행][열] * 전지행렬T[열][행]
			matrix_axt[matrix_a_row][matrix_t_row] = temp; // (matrix_axt)의 행 = 행렬A의 행, (matrix_axt)의 열 = 전치행렬T의 행
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) { // matrix_t 또는 matrix_axt의 값이 NULL일 경우
		printf("Memory Allocation Failed.\n"); // (= 메모리 할당 실패)
		return -1;
	}

	print_matrix(matrix_axt, row, row); // matrix_axt 값 출력
	free_matrix(matrix_axt, row, col); // matrix_axt의 사용을 끝내고, 재사용 가능하도록 설정

	return 1;
}
