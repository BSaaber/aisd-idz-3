#include <iostream>
#include <vector>
#include <algorithm>

int64_t max_edge_weight = 1000000;
int64_t maximum = INT64_MAX / 2 - max_edge_weight - 1;

void floyd_worshell(int n, int m, const std::vector<std::pair<std::pair<int, int>, int>>& edges_input) {
    std::vector<std::vector<int64_t>> edges(n, std::vector<int64_t>(n, maximum));
    int64_t my_i, my_j, my_w;
    for (int64_t i = 0; i < m; ++i) {
        my_i = edges_input[i].first.first;
        my_j = edges_input[i].first.second;
        my_w = edges_input[i].second;
        edges[my_i][my_j] = my_w;
    }

    for (int q = 0; q < n; ++q) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                edges[i][j] = std::min(edges[i][j], edges[i][q] + edges[q][j]);
            }
        }
    }

//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            if (i == j) {
//                continue;
//            }
//            if (edges[i][j] != maximum) {
//                std::cout << i << ' ' << j << ' ' << edges[i][j] << '\n';
//            } else {
//                std::cout << i << ' ' << j << ' ' << -1 << '\n';
//            }
//        }
//    }
}

