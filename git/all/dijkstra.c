#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define SIZE 10

typedef struct {
    int* vector;
    int size;
}array;

typedef struct {
    int x;
    int y;
} pos;

pos pos_init(int x, int y) {
    pos ret = {x, y};
    return ret;
}

array array_init(int size) {
    array ret_val;
    ret_val.size = size;
    ret_val.vector = malloc(sizeof(*ret_val.vector) * size);
    return ret_val;
}

void array_free(array v) {
    free(v.vector);
} 

int** matrix_init(int n) {
    int i;
    int** matrix = malloc(sizeof(int*) * n);
    for(i = 0; i < n; i++) 
        matrix[i] = malloc(sizeof(int) * n);
        
    return matrix;
}

int matrix_free(int** m, int n) {
    int i;
    for(i = 0; i < n; i++)
        free(m[i]);
    free(m);
    return 1;
}

int matrix_clean(int** matrix, int n) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            matrix[i][j] = 0;

    return 1;
}

void matrix_print(int** matrix, int n) {
    int i, j;
    printf("   ");
    for(i = 0; i < n; i++)
        printf("%2d", i+1);
    printf("\n");
    for(i = 0; i < n; i++) {
        printf("%2d ", i+1);
        for(j = 0; j < n; j++)
            if(matrix[i][j] != INT_MAX)
                printf("%2d", matrix[i][j]);
            else printf("%2d", 0);
        printf("\n");
    }
}

pos min_val(int** mat, pos* q, int qsize) {
    pos x;
    int min = INT_MAX;
    int i;
    for(i = 0; i < qsize; i++)
        if(mat[q[i].y][q[i].x] < min) {
            min = mat[q[i].y][q[i].x];
            x = pos_init(q[i].x, q[i].y);
        }
    
    return x;
}

int pos_compare(pos a, pos b) {
    return (a.x == b.x) && (a.y == b.y);
}

void pos_print_arr(pos* arr, int size) {
    int i;
    for(i = 0; i < size; i++)
        printf("[%d-%d]", arr[i].x, arr[i].y);
    printf("\n\n");
}

void delete_pos(pos* arr, int size, pos d) {
    int i = 0;

    while(!pos_compare(arr[i++], d));
    i--;
    for(; i < size-1; i++) {
        arr[i] = arr[i+1];
    }
}

int in_bounds(pos p, int size) {
    if(p.x >= size) return 0;
    if(p.y >= size) return 0;
    if(p.x < 0) return 0;
    if(p.y < 0) return 0;
    return 1;
}

int is_present(pos* v, pos x, int size) {
    int i = 0;
    for(i = 0; i < size; i++)
        if(pos_compare(v[i], x))
            return 1;

    return 0;
}

void dijkstra(int** mat,int msize, pos s_pos) {
    int i, j;
    int alt;
    int c = 0;
    
    pos sums[4] = { {0,1}, {1, 0},
                    {0,-1},{-1,0}};

    pos* prev = malloc(sizeof(pos) * msize * msize);
    pos* q = malloc(sizeof(pos) * msize * msize);
    
    for(i = 0; i < msize; i++)
        for(j = 0; j < msize; j++) {
            mat[i][j] = INT_MAX;
            prev[i*msize + j] = pos_init(j, i);
            q[c++] = pos_init(j, i);
        }
    mat[s_pos.y][s_pos.x] = 0;

    pos u;
    pos temp;
    
    while(c != 0) {
        u = min_val(mat, q, c);
        delete_pos(q, c--, u);

        for(i = 0; i < 4; i++){
            temp = pos_init(u.x+sums[i].x, u.y+sums[i].y);
            if(in_bounds(temp, msize) && is_present(q, temp, c)) {
                alt = mat[u.y][u.x] + 1;
                if(alt < mat[temp.y][temp.x]) {
                    mat[temp.y][temp.x] = alt;
                    prev[temp.y*msize + temp.x] = u;
                }
            }
        }
    }

    free(prev);
    free(q);
}

int main() {
    int** m = matrix_init(SIZE);

    matrix_clean(m, SIZE);
    matrix_print(m, SIZE);
    
    dijkstra(m, SIZE, pos_init(SIZE/2, SIZE/2));

    matrix_print(m, SIZE);

    matrix_free(m, SIZE);
}