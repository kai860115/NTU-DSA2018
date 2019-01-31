#include <stdio.h>
#include <vector>

using namespace std;

typedef vector<size_t>::iterator iter;

size_t count = 0;

void merge(vector<size_t> &vec, vector<size_t> &left, vector<size_t> &right)
{
    iter vec_it = vec.begin();
    iter left_it = left.begin();
    iter right_it = right.begin();
    size_t num = 0;
    while (left_it != left.end() && right_it != right.end())
    {
        if ((*left_it) > (*right_it))
        {
            *vec_it = *right_it;
            right_it++;
            vec_it++;
            num++;
        }
        else
        {
            *vec_it = *left_it;
            left_it++;
            vec_it++;
            count += num;
        }
    }
    while (left_it != left.end())
    {
        *vec_it = *left_it;
        left_it++;
        vec_it++;
        count += num;
    }
    while (right_it != right.end())
    {
        *vec_it = *right_it;
        right_it++;
        vec_it++;
    }
}

void mergesort(vector<size_t> &vec)
{
    if (vec.size() > 1)
    {
        vector<size_t> left(vec.begin(), vec.begin() + vec.size() / 2);
        vector<size_t> right(vec.begin() + vec.size() / 2, vec.end());
        mergesort(left);
        mergesort(right);
        merge(vec, left, right);
    }
}

int main(int argc, char const *argv[])
{
    size_t T, N, A;
    scanf("%llu", &T);
    for (size_t i = 0; i != T; i++)
    {
        scanf("%llu", &N);
        vector<size_t> vec;
        vec.reserve(N);
        for (size_t j = 0; j != N; j++)
        {
            scanf("%llu", &A);
            vec.push_back(A);
        }
        count = 0;
        mergesort(vec);
        printf("%llu\n", count);
    }

    return 0;
}
