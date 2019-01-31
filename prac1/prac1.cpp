#include <stdio.h>
#include <unordered_map>
#include <set>
#include <algorithm>
 
using namespace std;
 
int main(int argc, char const *argv[])
{
   size_t n, m, q;
   scanf("%lu %lu %lu", &n, &m, &q);
 
   size_t *dict = new size_t[m];
 
   for (size_t i = 0; i != m; i++)
   {
      size_t p1, p2;
      scanf("%lu %lu", &p1, &p2);
      if (p1 > p2)
         swap(p1, p2);
      dict[i] = ((p1 << 32) | p2);
   }
 
   sort(dict, dict + m);
 
   for (size_t i = 0; i != q; i++)
   {
      size_t p1, p2;
      scanf("%lu %lu", &p1, &p2);
      if (p1 > p2)
         swap(p1, p2);
      if (binary_search(dict, dict + m, (p1 << 32) | p2))
         printf("yes\n");
      else
         printf("no\n");
   }
 
   return 0;
}
