#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "deikstra.cpp"
#include "floyd_worshell.cpp"
#include "ford_bellman.cpp"

std::pair<std::pair<int, int>, int> splitstr(std::string& str, const std::string& deli = ",")
{
    int start = 0;
    int end = str.find(deli);
    int arr [3];
    int itr = 0;
    while (end != -1) {
        std::string number = str.substr(start, end - start);
        start = end + deli.size();
        end = str.find(deli, start);
        arr[itr++] = std::stoi(number);
    }
    std::string number = str.substr(start, str.size() - start);
    arr[itr++] = std::stoi(number);

    return {{arr[0], arr[1]}, arr[2]};
}

int main() {
    // i dont give a fuck about this not working on anothers computer
    // i fucking hate this university
    std::string path_prefix = "/Users/maxim-movshin/CLionProjects/graph_algorithms/build_test_data/input__";
    std::string result_prefix = "/Users/maxim-movshin/CLionProjects/graph_algorithms/results/";
    for (int i = 10; i < 1010 + 1; i += 50) {
        int n = i;
        for (const auto& size_name : {"small", "half", "full"}) {
            std::ifstream file;
            file.open(path_prefix + size_name + "/" + std::to_string(i) + ".csv");
            std::vector<std::pair<std::pair<int, int>, int>> data;
            while (file) {
                std::string line;
                file >> line;
                if (line == "") {
                    break;
                }
                auto res = splitstr(line);
                data.push_back(res);
            }

            std::string deikstra_diff_str, floyd_diff_str, ford_diff_str;

            auto start = std::chrono::steady_clock::now();
            deikstra(n, data.size(), data);
            auto end = std::chrono::steady_clock::now();
            auto deikstra_diff = end - start;
            deikstra_diff_str = std::to_string(std::chrono::duration <double, std::milli> (deikstra_diff).count());

            start = std::chrono::steady_clock::now();
            floyd_worshell(n, data.size(), data);
            end = std::chrono::steady_clock::now();
            auto floyd_worshell_diff = end - start;
            floyd_diff_str = std::to_string(std::chrono::duration <double, std::milli> (floyd_worshell_diff).count());

            start = std::chrono::steady_clock::now();
            ford_bellman(n, data.size(), data);
            end = std::chrono::steady_clock::now();
            auto ford_bellman_diff = end - start;
            ford_diff_str = std::to_string(std::chrono::duration <double, std::milli> (ford_bellman_diff).count());

            std::vector<std::pair<std::string, int>> types {{"edges", data.size()}, {"vertexes", n}};
            for (const auto& type : types) {


                // write time
                std::ofstream out_deikstra(result_prefix + size_name + "_" + "deikstra" + "_" + type.first, std::ios_base::app);
                out_deikstra << deikstra_diff_str << ',' << std::to_string(type.second) << ";";
                out_deikstra.close();

                std::ofstream out_floyd(result_prefix + size_name + "_" + "floyd" + "_" + type.first, std::ios_base::app);
                out_floyd << floyd_diff_str << ',' << std::to_string(type.second) << ";";
                out_floyd.close();

                std::ofstream out_ford(result_prefix + size_name + "_" + "ford" + "_" + type.first, std::ios_base::app);
                out_ford << ford_diff_str << ',' << std::to_string(type.second) << ";";
                out_ford.close();

            }

        }
    }
}
