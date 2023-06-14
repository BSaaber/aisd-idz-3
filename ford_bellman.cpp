#include <vector>
#include <algorithm>


void ford_bellman(int n, int m, const std::vector<std::pair<std::pair<int,int>,int>>& edges_input) {
    std::vector<int> d (n, INF);
    struct edge {
        int a, b, cost;
    };
    std::vector<edge> e;
    for (const auto& i : edges_input) {
        e.push_back({i.first.first, i.first.second, i.second});
    }
    int v = 0;
    d[v] = 0;
    std::vector<int> p (n, -1);
    for (;;) {
        bool any = false;
        for (int j=0; j<m; ++j)
            if (d[e[j].a] < INF)
                if (d[e[j].b] > d[e[j].a] + e[j].cost) {
                    d[e[j].b] = d[e[j].a] + e[j].cost;
                    p[e[j].b] = e[j].a;
                    any = true;
                }
        if (!any)  break;
    }

    int t = -1;

    if (d[t] == INF)
        std::cout << "No path from " << v << " to " << t << ".";
    else {
        std::vector<int> path;
        for (int cur=t; cur!=-1; cur=p[cur])
            path.push_back (cur);
        reverse (path.begin(), path.end());

        for (size_t i=0; i<path.size(); ++i)
            std::cout << path[i] << ' ';
    }
}