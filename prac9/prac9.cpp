#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <queue>
 
using namespace std;
 
struct Edge
{
    int pt;
    size_t dis;
    bool operator<(const Edge& i) const
    {
        return dis > i.dis;
    }
};
 
void Dijkstra(size_t& start, size_t* dist, vector<Edge>* edges, size_t N)
{
    bool* in_tree = new bool[N];
    fill(in_tree, in_tree + N, false);
    fill(dist, dist + N, -1);
    dist[start] = 0;
    priority_queue<Edge> pq;
    pq.push(Edge{start, 0});
    while(1)
    {
        while(!pq.empty() && in_tree[pq.top().pt])    pq.pop();
        if(pq.empty()) return;
        size_t now = pq.top().pt;
        in_tree[now] = true;
        for(vector<Edge>::iterator it = edges[now].begin(); it != edges[now].end(); it++)
        {
            if(!in_tree[it->pt] && dist[it->pt] > dist[now] + it->dis)
            {
                dist[it->pt] = dist[now] + it->dis;
                pq.push((Edge){it->pt, dist[it->pt]});
 
            }
        }
    }
    delete[] in_tree;
}
 
int main(int argc, char const *argv[])
{
    size_t T;
    scanf("%llu", &T);
    for(size_t i = 0; i != T; i++)
    {
        size_t N, M, A, B;
        scanf("%llu%llu", &N, &M);
        scanf("%llu%llu", &A, &B);
        vector<Edge>* graph = new vector<Edge>[N];
        vector<Edge>* reverse = new vector<Edge>[N];
        for(size_t j = 0; j != M; j++)
        {
            size_t Ai, Bi, Ki;
            scanf("%llu%llu%llu", &Ai, &Bi, &Ki);
            graph[Ai].push_back(Edge{Bi, Ki});
            reverse[Bi].push_back(Edge{Ai, Ki});
        }
        size_t* dis1 = new size_t[N];
        size_t* dis2 = new size_t[N];
        Dijkstra(A, dis1, graph, N);
        Dijkstra(B, dis2, reverse, N);
        size_t ans = -1;
        for(size_t k = 0; k != N; k++)
        {
            for(vector<Edge>::iterator it = graph[k].begin(); it != graph[k].end(); it++)
            {
                size_t len = dis1[k] + dis2[it->pt] + it->dis;
                if(len != dis1[B] && len < ans)
                {
                    ans = len;
                }
            }
        }
        printf("%llu\n", ans - dis1[B]);
        delete[] graph;
        delete[] reverse;
        delete[] dis1;
        delete[] dis2;
    }
 
 
    return 0;
}
