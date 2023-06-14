#include <vector>
#include <algorithm>


// based on https://e-maxx.ru/algo/dijkstra
const int INF = 1000000000;

void deikstra(int n, int m, const std::vector<std::pair<std::pair<int,int>,int>>& edges_input) {
    std::vector<std::vector<std::pair<int,int> > > g (n);
    for (const auto& i : edges_input) {
        g[i.first.first].emplace_back(i.first.second, i.second);
    }
    int s = 0;

    std::vector<int> d (n, INF),  p (n);
    d[s] = 0;
    std::vector<char> u (n);
    for (int i=0; i<n; ++i) {
        int v = -1;
        for (int j=0; j<n; ++j)
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        if (d[v] == INF)
            break;
        u[v] = true;

        for (size_t j=0; j<g[v].size(); ++j) {
            int to = g[v][j].first,
                    len = g[v][j].second;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
}