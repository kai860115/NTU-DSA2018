#include <stdio.h>
#include <vector>

using namespace std;
typedef long long ll;

int main(int argc, char const *argv[])
{
    size_t N;
    scanf("%llu", &N);
    ll *arr = new ll[N];
    ll sum = 0;
    ll torque = 0;
    for (size_t i = 0; i != N; i++)
    {
        scanf("%llu", &arr[i]);
        sum += arr[i];
        torque += arr[i] * i;
    }

    if (torque % sum == 0)
    {
        printf("%llu %llu\n", 0, torque / sum);
    }
    else
    {
        size_t x_max = N / 2 > 1 ? N / 2 : 1;

        for (size_t i = 0; i != x_max; i++)
        {
            torque += (N - 2 * i - 1) * (arr[i] - arr[N - i - 1]);
            if (torque % sum == 0)
            {
                printf("%llu %llu\n", i + 1, torque / sum);
                break;
            }
        }
    }

    return 0;
}