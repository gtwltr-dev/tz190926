#include <stdio.h>
#include <stddef.h>

#define MAX_ROWS 50
#define MAX_COLS 50

void print_matrix(size_t rows, size_t cols, const int matrix[rows][cols])
{
    size_t i;
    size_t j;
    for (i = 0; i < rows; i = i + 1)
    {
        for (j = 0; j < cols; j = j + 1)
        {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

const int *find_matrix_max(size_t rows, size_t cols,
                           const int matrix[rows][cols],
                           size_t *max_row, size_t *max_col)
{
    const int *best = *(matrix + 0);
    *max_row = 0;
    *max_col = 0;

    size_t i;
    size_t j;
    for (i = 0; i < rows; i = i + 1)
    {
        const int *row = *(matrix + i);
        const int *p = row;

        for (j = 0; j < cols; j = j + 1)
        {
            if (*p > *best)
            {
                best = p;
                *max_row = i;
                *max_col = (size_t)(p - row);
            }
            p = p + 1;
        }
    }

    return best;
}

double matrix_average(size_t rows, size_t cols, const int matrix[rows][cols])
{
    long long sum = 0;

    size_t i;
    size_t j;
    for (i = 0; i < rows; i = i + 1)
    {
        const int *row = *(matrix + i);
        const int *p = row;
        for (j = 0; j < cols; j = j + 1)
        {
            sum = sum + *p;
            p = p + 1;
        }
    }

    double total = (double)(rows * cols);
    return (double)sum / total;
}

size_t count_above_average(size_t rows, size_t cols,
                           const int matrix[rows][cols], double average)
{
    size_t count = 0;

    size_t i;
    size_t j;
    for (i = 0; i < rows; i = i + 1)
    {
        const int *row = *(matrix + i);
        const int *p = row;
        for (j = 0; j < cols; j = j + 1)
        {
            double val = (double)(*p);
            if (val > average)
            {
                count = count + 1;
            }
            p = p + 1;
        }
    }

    return count;
}

double row_average(size_t cols, const int *row)
{
    long long sum = 0;
    const int *p = row;

    size_t j;
    for (j = 0; j < cols; j = j + 1)
    {
        sum = sum + *p;
        p = p + 1;
    }

    double total = (double)cols;
    return (double)sum / total;
}

size_t hottest_row(size_t rows, size_t cols, const int matrix[rows][cols])
{
    size_t best_row = 0;
    double best_avg = row_average(cols, *(matrix + 0));

    size_t i;
    for (i = 1; i < rows; i = i + 1)
    {
        double avg = row_average(cols, *(matrix + i));
        if (avg > best_avg)
        {
            best_avg = avg;
            best_row = i;
        }
    }

    return best_row;
}

void fill_row_with_average(size_t cols, int *row)
{
    double avg = row_average(cols, row);
    int value = (int)avg;

    int *p = row;
    size_t j;
    for (j = 0; j < cols; j = j + 1)
    {
        *p = value;
        p = p + 1;
    }
}

int max_neighbor_difference(size_t rows, size_t cols, const int matrix[rows][cols])
{
    int best = 0;

    size_t i;
    size_t j;
    for (i = 0; i < rows; i = i + 1)
    {
        const int *row = *(matrix + i);

        for (j = 0; j + 1 < cols; j = j + 1)
        {
            const int *left = row + j;
            const int *right = row + j + 1;
            int diff = *left - *right;
            if (diff < 0)
            {
                diff = -diff;
            }
            if (diff > best)
            {
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
    if (scanf("%zu %zu", &rows, &cols) != 2)
    {
        printf("Oshibka vvoda\n");
        return 1;
    }
    if (rows < 2 || rows > MAX_ROWS || cols < 2 || cols > MAX_COLS)
    {
        printf("Nepravilnye razmery\n");
        return 1;
    }

    int matrix[rows][cols];

    printf("Vvedite %zu x %zu chisel:\n", rows, cols);
    size_t i;
    size_t j;
    for (i = 0; i < rows; i = i + 1)
    {
        for (j = 0; j < cols; j = j + 1)
        {
            if (scanf("%d", &matrix[i][j]) != 1)
            {
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
    printf("Stroka: %zu\n", max_row);
    printf("Stolbets: %zu\n", max_col);

    double avg = matrix_average(rows, cols, matrix);
    printf("Srednyaya temperatura karty: %.2f\n", avg);

    size_t above = count_above_average(rows, cols, matrix, avg);
    printf("Kolichestvo znacheniy vyshe srednego: %zu\n", above);

    size_t hot = hottest_row(rows, cols, matrix);
    double hot_avg = row_average(cols, *(matrix + hot));
    printf("Stroka s maksimalnym srednim: %zu\n", hot);
    printf("Srednee vybrannoy stroki: %.2f\n", hot_avg);

    fill_row_with_average(cols, *(matrix + hot));

    int max_diff = max_neighbor_difference(rows, cols, matrix);

    printf("\nKarta posle zameny vybrannoy stroki:\n");
    print_matrix(rows, cols, matrix);

    printf("\nMaksimalnaya raznitsa sosednih temperatur: %d\n", max_diff);

    return 0;
}