#include <stdio.h>
//#include <bitset>
//#include <iostream>
using namespace std;
 
typedef long long ll;
int main(int argc, char const *argv[])
{
   size_t T;
   scanf("%lu", &T);
   for (size_t q = 0; q != T; q++)
   {
      //printf("%d\n", q);
      size_t n;
      scanf("%lu", &n);
      ll *x = new ll[n];
      ll *y = new ll[n];
      for (size_t i = 0; i != n; i++)
      {
         scanf("%lld %lld", &x[i], &y[i]);
      }
 
      size_t **para = new size_t *[n];
      for (size_t i = 0; i != n; i++)
      {
         para[i] = new size_t[n];
      }
 
      for (size_t i = 0; i != n; i++)
      {
         for (size_t j = 0; j != n; j++)
         {
            ll cross = x[i] * y[j] - x[j] * y[i];
            if (i == j)
            {
               para[i][j] = (1 << i);
            }
            else if (x[i] == x[j])
            {
               para[i][j] = 0;
            }
            else if (cross <= 0 && x[i] > x[j])
            {
               para[i][j] = 0;
            }
            else if (cross >= 0 && x[i] < x[j])
            {
               para[i][j] = 0;
            }
            else
            {
               para[i][j] = 0 | (1 << i) | (1 << j);
               for (size_t k = 0; k != n; k++)
               {
                  if (x[k] == x[j] || x[k] == x[i])
                     continue;
                  ll lv = y[k] * x[i] * (x[i] - x[j]) * x[j];
                  ll rv = y[i] * x[k] * (x[k] - x[j]) * x[j] - y[j] * x[k] * (x[k] - x[i]) * x[i];
                  if (lv == rv)
                     para[i][j] |= (1 << k);
               }
            }
            //cout << i << " " << j << " " << cross << " xi " << x[i] << " yi " << y[i] << " xj " << x[j] << " yj " << y[j] << '\n';
            //cout << bitset<64>(para[i][j]) << "\n";
         }
      }
      delete[] x;
      delete[] y;
 
      size_t *dp = new size_t[(size_t(1) << n)]{0};
      for (size_t i = 0; i != (size_t(1) << n); i++)
      {
         if (i == 0)
            dp[i] = 0;
         else if (i == (size_t(1) << (__builtin_ffsl(i) - 1)))
            dp[i] = 1;
         else
         {
            for (size_t j = 0; j != n; j++)
            {
               if ((i & (size_t(1) << j)) != 0)
               {
                  for (size_t k = 0; k != n; k++)
                  {
                     if (i == (i & (~(para[j][k]))))
                     {
                     }
                     else if (dp[i] == 0)
                     {
                        dp[i] = dp[i & (~(para[j][k]))] + 1;
                     }
                     else if (dp[i] > dp[i & (~(para[j][k]))] + 1)
                     {
                        dp[i] = dp[i & (~(para[j][k]))] + 1;
                     }
                     //printf("%lu %lu %lu %lu %lu %lu\n", i, j, k, dp[i], dp[i & (~(para[j][k]))] + 1, i & (~(para[j][k])));
                  }
                  //printf("%lu %lu\n", i, dp[i]);
                  break;
               }
            }
         }
      }
      printf("%lu\n", dp[((size_t(1) << n) - 1)]);
 
      for (size_t i = 0; i != n; i++)
      {
         delete[] para[i];
      }
      delete[] para;
 
      delete[] dp;
   }
   return 0;
}
