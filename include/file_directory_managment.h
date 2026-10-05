#pragma once
#include "common.h"


int get_trailing_num(const char *str)
{
    int i = TextLength(str) - 1;
    while (i >= 0 && str[i] != '.')
        i--;
    i--;
    int num_end = i;
    while (i >= 0 && str[i] >= '0' && str[i] <= '9')
        i--;
    if (i + 1 > num_end)
        return DEFAULT_ERROR_CODE; // No number found

    int val = 0;
    for (int j = i + 1; j <= num_end; j++)
    {
        val = val * 10 + (str[j] - '0');
    }
    return val;
}

int compare_by_suffix(const void *a, const void *b)
{
    return get_trailing_num(*(const char **)a) - get_trailing_num(*(const char **)b);
}

FilePathList get_sorted_dir(const char *dir)
{
    FilePathList list = LoadDirectoryFiles(dir);
    qsort(list.paths, list.count, sizeof(char *), compare_by_suffix);
    return list;
}