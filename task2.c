#include <stdio.h>
#include <stddef.h>

#define MAX_ROWS 50
#define MAX_COLS 50

void print_matrix(size_t rows, size_t cols, const int matrix[rows][cols])
{
    for(int i = 0; i < rows; i++){
        const int *row = *(matrix + i);
        for(const int *p = row; p < row + cols; p++){
            printf("%d", *p);
            if (p + 1 < row + cols) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

const int *find_matrix_max(size_t rows, size_t cols,
                           const int matrix[rows][cols],
                           size_t *max_row, size_t *max_col)
{
    const int *best = *(matrix + 0);
    size_t best_i = 0;
    size_t best_j = 0;

    for(size_t i = 0; i < rows; i++){
        const int *row = *(matrix + i);
        for(const int *p = row; p < row + cols; p++){
            if(*best < *p){
                best = p;
                best_i = i;
                best_j = (size_t)(p - row);
            }
        }
    }
    *max_row = best_i;   /* индекс с 0 */
    *max_col = best_j;   /* индекс с 0 */
    return best;
}

double matrix_average(size_t rows, size_t cols, const int matrix[rows][cols])
{
    long long sum = 0;
    for(size_t i = 0; i < rows; i++){
        const int *row = *(matrix + i);
        for(const int *p = row; p < row + cols; p++){
            sum += *p;
        }
    }
    return (double)sum / (double)(cols * rows);
}

size_t count_above_average(size_t rows, size_t cols,
                           const int matrix[rows][cols], double average)
{
    size_t count = 0;
    for(size_t i = 0; i < rows; i++){
        const int *row = *(matrix + i);
        for(const int *p = row; p < row + cols; p++){
            if ((double)(*p) > average){
                count += 1;
            }
        }
    }
    return count;
}

double row_average(size_t cols, const int *row)
{
    long long sum = 0;
    for(const int *p = row; p < row + cols; p++){
        sum += *p;
    }
    return (double)sum / (double)cols;
}

size_t hottest_row(size_t rows, size_t cols, const int matrix[rows][cols])
{
    size_t best_i = 0;
    double best_avg = row_average(cols, *(matrix + 0));

    for (size_t i = 1; i < rows; i++){
        double cur_avg = row_average(cols, *(matrix + i));
        if (cur_avg > best_avg){
            best_avg = cur_avg;
            best_i = i;
        }
    }
    return best_i;
}

void fill_row_with_average(size_t cols, int *row)
{
    double avg = row_average(cols, row);
    int value = (int)avg;

    for (int *p = row; p < row + cols; p++){
        *p = value;
    }
}

int max_neighbor_difference(size_t rows, size_t cols, const int matrix[rows][cols])
{
    int best = 0;

    for (size_t i = 0; i < rows; i++){
        const int *row = *(matrix + i);
        for (size_t j = 0; j + 1 < cols; j++){
            const int *left = row + j;
            const int *right = row + j + 1;
            int diff = *left - *right;
            if (diff < 0){
                diff = -diff;
            }
            if (diff > best){
                best = diff;
            }
        }
    }
    return best;
}

int main(void)
{
    size_t rows;
    size_t cols;

    printf("Vvedite kolichestvo strok i stolbtsov (2..50): ");
    if (scanf("%zu %zu", &rows, &cols) != 2){
        printf("Oshibka vvoda\n");
        return 1;
    }
    if (rows < 2 || rows > MAX_ROWS || cols < 2 || cols > MAX_COLS){
        printf("Nepravilnye razmery\n");
        return 1;
    }

    int matrix[rows][cols];
    printf("Vvedite %zu x %zu chisel:\n", rows, cols);
    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < cols; j++){
            if (scanf("%d", &matrix[i][j]) != 1){
                printf("Oshibka vvoda\n");
                return 1;
            }
        }
    }

    printf("\nIshodnaya karta:\n");
    print_matrix(rows, cols, matrix);

    size_t max_row = 0;
    size_t max_col = 0;
    const int *max_ptr = find_matrix_max(rows, cols, matrix, &max_row, &max_col);
    printf("\nMaksimalnaya temperatura: %d\n", *max_ptr);
    printf("Stroka: %zu\n", max_row +1);
    printf("Stolbets: %zu\n", max_col +1);

    double avg = matrix_average(rows, cols, matrix);
    printf("Srednyaya temperatura karty: %.2f\n", avg);

    size_t above = count_above_average(rows, cols, matrix, avg);
    printf("Kolichestvo znacheniy vyshe srednego: %zu\n", above);

    size_t hot = hottest_row(rows, cols, matrix);
    double hot_avg = row_average(cols, *(matrix + hot));
    printf("Stroka s maksimalnym srednim: %zu\n", hot +1);
    printf("Srednee vybrannoy stroki: %.2f\n", hot_avg);

    fill_row_with_average(cols, *(matrix + hot));

    int max_diff = max_neighbor_difference(rows, cols, matrix);

    printf("\nKarta posle zameny vybrannoy stroki:\n");
    print_matrix(rows, cols, matrix);

    printf("\nMaksimalnaya raznitsa sosednih temperatur: %d\n", max_diff);

    return 0;
}
