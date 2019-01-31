#include <stdio.h>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;
 
int main()
{
   int n_days;
   scanf("%d", &n_days);
   size_t *arr = new size_t[n_days + 1]{0};
   size_t *len = new size_t[n_days + 1]{0};
   size_t *cnt = new size_t[n_days + 1]{0};
   size_t *pre = new size_t[n_days + 1]{0};
   cnt[0] = 1;
   map<size_t, size_t> arr_maxlen;
   arr_maxlen[0] = 0;
   unordered_map<size_t, vector<size_t>> len_day;
   len_day[0].push_back(0);
 
   for (size_t i = 1; i != n_days + 1; i++)
   {
      scanf("%lu", &arr[i]);
      for (map<size_t, size_t>::iterator it = arr_maxlen.begin(); it != arr_maxlen.end(); it++)
      {
         if (it->first > arr[i])
            break;
         if (it->second + 1 > len[i])
         {
            len[i] = it->second + 1;
         }
      }
 
      if (len[i] > arr_maxlen[arr[i]])
         arr_maxlen[arr[i]] = len[i];
 
      len_day[len[i]].push_back(i);
 
      for (vector<size_t>::iterator it = --(len_day[len[i] - 1].end()); it != --(len_day[len[i] - 1].begin()); it--)
      {
         if (arr[*it] <= arr[i])
         {
            cnt[i] += (cnt[*it] % 1000000007);
            cnt[i] %= 1000000007;
            pre[i] = *it;
         }
      }
   }
 
   size_t m = 0;
   vector<size_t> idx;
   idx.reserve(n_days);
   size_t q = 0;
   size_t *met = new size_t[n_days];
   size_t p = n_days - 1;
   for (size_t i = 1; i != n_days + 1; i++)
   {
      if (len[i] > m)
      {
         m = len[i];
         idx.resize(0);
         idx.push_back(i);
      }
      else if (len[i] == m)
      {
         idx.push_back(i);
      }
   }
   for (size_t i = 0; i != idx.size(); i++)
   {
      q += cnt[(idx[i])];
      q = q % 1000000007;
   }
   for (size_t i = idx[i]; i != 0; i = pre[i])
   {
      met[p--] = i;
   }
   printf("%lu\n", m);
   printf("%lu\n", q % 1000000007);
   for (size_t i = p + 1; i != n_days; i++)
   {
      if (i != n_days - 1)
         printf("%lu ", met[i]);
      else
         printf("%lu", met[i]);
   }
   printf("\n");
 
   delete[] arr;
   delete[] len;
   delete[] cnt;
   delete[] pre;
   delete[] met;
   return 0;
}
