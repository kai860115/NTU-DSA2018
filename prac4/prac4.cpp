#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

int main(int argc, char const *argv[])
{
    size_t N, M, K;
    scanf("%llu %llu %llu", &N, &M, &K);
    char a1[N + 1];
    char a2[M + 1];
    scanf("%s", a1);
    scanf("%s", a2);
    size_t dp[2][M + 1][K + 1];
    size_t dp2[2][M + 1][K + 1];
    for (size_t i = 0; i != 2; i++)
    {
        for (size_t j = 0; j != M + 1; j++)
        {
            for (size_t k = 0; k != K + 1; k++)
            {
                dp[i][j][k] = 0;
                dp2[i][j][k] = 0;
            }
        }
    }
    for (size_t l = 1, i = 1; l != N + 1; l++, i ^= 1)
    {
        for (size_t j = 1; j != M + 1; j++)
        {
            for (size_t k = 1; k != K + 1; k++)
            {
                dp[i & 1][j][k] = max(dp[i & 1][j - 1][k], dp[i ^ 1][j][k]);
                dp2[i][j][k] = 0;
                if (a1[l - 1] == a2[j - 1])
                {
                    dp2[i & 1][j][k] = max(dp2[i ^ 1][j - 1][k], dp[i ^ 1][j - 1][k - 1]) + 2 * (a1[l - 1] == 'a');
                    dp[i & 1][j][k] = max(dp2[i & 1][j][k], dp[i & 1][j][k]);
                }
            }
        }
    }
    printf("%llu\n", dp[N & 1][M][K]);
    return 0;
}
