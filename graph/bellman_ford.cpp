#include <iostream>
#include <limits>
using namespace std;

struct edge
{
    int from, to, cost;
};

const int MAX_E = 20;
const int MAX_V = 10;
edge es[MAX_E];
int d[MAX_V]; // 最短距离
int V, E;     // V是顶点数，E是边数

void shortest_path(int s)
{
    for (int i = 0; i < V; i++)
    {
        d[i] = numeric_limits<int>::max();
    }

    d[s] = 0;
    while (true)
    {
        bool update = false;
        for (int i = 0; i < E; i++)
        {
            edge e = es[i];
            if (d[e.from] != numeric_limits<int>::max() && d[e.to] > d[e.from] + e.cost)
            {
                d[e.to] = d[e.from] + e.cost;
                update = true;
            }
        }
        if (!update)
            break;
    }
}
