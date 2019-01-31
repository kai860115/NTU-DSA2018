#include <stdio.h>
#include <deque>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

void add(vector<size_t> &vec, size_t a)
{
    size_t left = 0;
    size_t right = vec.size() - 1;
    size_t mid = (left + right) / 2;
    if (a > vec[left])
    {
        vec[left] = a;
    }
    else if (a <= vec[right])
    {
        vec.push_back(a);
    }
    else
    {
        while (left + 1 != right)
        {
            if (a > vec[mid])
            {
                right = mid;
            }
            else
            {
                left = mid;
            }
            mid = (left + right) / 2;
        }
        vec[right] = a;
    }
}

int main(int argc, char const *argv[])
{
    size_t T, N, A;
    scanf("%llu", &T);
    for (size_t i = 0; i != T; i++)
    {
        scanf("%llu", &N);
        vector<size_t> arr;
        arr.reserve(N);
        for (size_t j = 0; j != N; j++)
        {
            //printf("========\n");
            scanf("%llu", &A);
            /*
            printf("A: %llu\n", A);
            printf("1: ");
            if (arr.size() == 0)
                printf("empty\n");
            else
            {
                for (size_t k = 0; k != arr.size(); k++)
                {
                    printf("%llu ", arr[k]);
                }
                printf("\n");
            }
            */
            if (j == 0)
                arr.push_back(A);
            else
            {
                add(arr, A);
            }
            /*
            printf("2: ");
            if (arr.size() == 0)
                printf("empty\n");
            else
            {
                for (size_t k = 0; k != arr.size(); k++)
                {
                    printf("%llu ", arr[k]);
                }
                printf("\n");
            }
            */
        }
        printf("%llu\n", arr.size());
    }
    return 0;
}
