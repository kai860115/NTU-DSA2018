#include <stdio.h>
#include <algorithm>

using namespace std;

struct node
{
    node()
    {
        _pre = 0;
        _next = 0;
    }
    node *_pre;
    node *_next;
};

void print_list(node *list)
{
    node *n = list->_next;
    size_t count = 0;
    while (n != list)
    {
        printf("%llu ", (n - list));
        count++;
        n = n->_next;
    }
    if (count == 0)
    {
        printf("*");
    }
    printf("\n");
}

void print_list_pre(node *list)
{
    node *n = list->_pre;
    size_t count = 0;
    while (n != list)
    {
        printf("%llu ", (n - list));
        count++;
        n = n->_pre;
    }
    if (count == 0)
    {
        printf("*");
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    size_t T, N, M, a1;
    scanf("%llu", &T);
    for (size_t i = 0; i != T; i++)
    {
        size_t count = 0;
        scanf("%llu %llu %llu", &N, &M, &a1);
        node *mylist = new node[N + 1];
        size_t *check = new size_t[N + 1];
        size_t check_n = 0;
        fill(check, check + N + 1, 0);
        //set dummy node
        mylist->_next = mylist + a1;
        mylist->_pre = mylist + a1;
        (mylist + a1)->_pre = mylist;
        (mylist + a1)->_next = mylist;

        size_t K, A, B, C;
        for (size_t j = 0; j != M; j++)
        {
            scanf("%llu %llu %llu %llu", &K, &A, &B, &C);
            //printf("===%llu %llu %llu %llu\n", K, A, B, C);
            if (K == 1)
            {
                if (C == 2)
                {
                    node *temp = (mylist + B)->_next;
                    (mylist + B)->_next = mylist + A;
                    (mylist + A)->_pre = mylist + B;

                    temp->_pre = mylist + A;
                    (mylist + A)->_next = temp;
                }
                else
                {
                    node *temp = (mylist + B)->_pre;
                    (mylist + B)->_pre = mylist + A;
                    (mylist + A)->_next = mylist + B;

                    temp->_next = mylist + A;
                    (mylist + A)->_pre = temp;
                }

                //printf("+++print+++\n");
                //print_list(mylist);
                //printf("+++print+++\n");
            }
            else if (K == 2)
            {
                node *left = (mylist + A)->_pre;
                node *right = (mylist + B)->_next;
                left->_next = right;
                right->_pre = left;

                left = (mylist + C)->_pre;
                right = mylist + C;

                left->_next = mylist + A;
                (mylist + A)->_pre = left;
                right->_pre = mylist + B;
                (mylist + B)->_next = right;

                //printf("+++print+++\n");
                //print_list(mylist);
                //printf("+++print+++\n");
            }
            else if (K == 3)
            {
                if (C == 1)
                {
                    node *left = mylist + A;
                    node *right = (mylist + A)->_next;
                    while (left != mylist && B != 0)
                    {
                        //printf("+++add+++\n");
                        //printf("%llu\n", left - mylist);
                        //printf("+++add+++\n");
                        check[check_n++] = left - mylist;
                        B--;
                        left = left->_pre;
                    }
                    left->_next = right;
                    right->_pre = left;
                    count += B;
                }
                else
                {
                    node *left = (mylist + A)->_pre;
                    node *right = mylist + A;
                    while (right != mylist && B != 0)
                    {
                        //printf("+++add+++\n");
                        //printf("%llu\n", right - mylist);
                        //printf("+++add+++\n");
                        check[check_n++] = right - mylist;
                        B--;
                        right = right->_next;
                    }
                    left->_next = right;
                    right->_pre = left;
                    count += B;
                }
            }
            //printf("+++print+++\n");
            //print_list(mylist);
            //printf("+++print+++\n");
            //print_list_pre(mylist);
        }
        //printf("+++++++++\n");
        printf("%llu\n", count);
        for (size_t j = 0; j != N + 1; j++)
        {
            if (check[j] == 0)
                break;
            printf("%llu\n", check[j]);
        }
        delete[] check;
        delete[] mylist;
    }
    return 0;
}
