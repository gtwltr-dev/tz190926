#include <stdio.h>
#include <stddef.h>

#define MAX 1000

int *find_min(int *begin, int *end)
{
    int *result = begin;
    int *p = begin;
    while (p < end)
    {
        if (*p < *result)
        {
            result = p;
        }
        p = p + 1;
    }
    return result;
}

int *find_max(int *begin, int *end)
{
    int *result = begin;
    int *p = begin;
    while (p < end)
    {
        if (*p > *result)
        {
            result = p;
        }
        p = p + 1;
    }
    return result;
}

long long sum_between(const int *first, const int *second)
{
    const int *left;
    const int *right;

    if (first < second)
    {
        left = first;
        right = second;
    }
    else
    {
        left = second;
        right = first;
    }

    long long sum = 0;
    const int *p = left + 1;

    while (p < right)
    {
        sum = sum + *p;
        p = p + 1;
    }

    return sum;
}

size_t find_longest_increasing(int *begin, int *end, int **sequence_begin)
{
    int total = (int)(end - begin);

    if (total < 2)
    {
        *sequence_begin = begin;
        return 1;
    }

    size_t best_len = 1;
    int *best_start = begin;

    int *cur_start = begin;
    size_t cur_len = 1;

    int *p = begin + 1;

    while (p < end)
    {
        if (*(p - 1) < *p)
        {
            cur_len = cur_len + 1;
        }
        else
        {
            if (cur_len > best_len)
            {
                best_len = cur_len;
                best_start = cur_start;
            }
            cur_start = p;
            cur_len = 1;
        }
        p = p + 1;
    }

    if (cur_len > best_len)
    {
        best_len = cur_len;
        best_start = cur_start;
    }

    *sequence_begin = best_start;
    return best_len;
}

void reverse_range(int *begin, int *end)
{
    int *left = begin;
    int *right = end - 1;

    while (left < right)
    {
        int temp = *left;
        *left = *right;
        *right = temp;

        left = left + 1;
        right = right - 1;
    }
}

void print_array(const int *begin, const int *end)
{
    const int *p = begin;
    while (p < end)
    {
        printf("%d ", *p);
        p = p + 1;
    }
    printf("\n");
}

int main(void)
{
    int n;
    int arr[MAX];
    int i;

    printf("Vvedite kolichestvo elementov (2..1000): ");
    if (scanf("%d", &n) != 1)
    {
        printf("Oshibka vvoda\n");
        return 1;
    }
    if (n < 2 || n > MAX)
    {
        printf("Nepravilnyy razmer\n");
        return 1;
    }

    printf("Vvedite %d chisel:\n", n);
    for (i = 0; i < n; i = i + 1)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Oshibka vvoda\n");
            return 1;
        }
    }

    int *begin = arr;
    int *end = arr + n;

    printf("\nIshodnyy massiv:\n");
    print_array(begin, end);

    int *min_ptr = find_min(begin, end);
    int min_val = *min_ptr;
    int min_pos = (int)(min_ptr - begin);

    int *max_ptr = find_max(begin, end);
    int max_val = *max_ptr;
    int max_pos = (int)(max_ptr - begin);

    printf("\nMinimum: %d\n", min_val);
    printf("Pozitsiya minimuma: %d\n", min_pos);
    printf("Maksimum: %d\n", max_val);
    printf("Pozitsiya maksimuma: %d\n", max_pos);

    int dist = max_pos - min_pos;
    if (dist < 0)
    {
        dist = -dist;
    }
    printf("Rasstoyanie mezhdu nimi: %d\n", dist);

    long long sum = sum_between(min_ptr, max_ptr);
    printf("Summa elementov mezhdu nimi: %lld\n", sum);

    int *seq_begin = begin;
    size_t seq_len = find_longest_increasing(begin, end, &seq_begin);
    int *seq_end = seq_begin + seq_len;

    printf("\nSamyy dlinnyy vozrastayushchiy uchastok:\n");
    print_array(seq_begin, seq_end);
    printf("Dlina: %zu\n", seq_len);

    reverse_range(seq_begin, seq_end);

    printf("\nMassiv posle razvorota uchastka:\n");
    print_array(begin, end);

    return 0;
}