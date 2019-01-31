#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    priority_queue<size_t, vector<size_t>, greater<size_t>> pq;
    size_t N, M;
    scanf("%llu %llu", &N, &M);
    for (size_t i = 0; i != M; i++)
    {
        pq.push(0);
    }

    for (size_t i = 0; i != N; i++)
    {
        size_t t;
        scanf("%llu", &t);
        size_t temp = pq.top() + t;
        pq.pop();
        pq.push(temp);
    }

    for (size_t i = 0; i != M - 1; i++)
    {
        pq.pop();
    }
    printf("%llu\n", pq.top());
    return 0;
}