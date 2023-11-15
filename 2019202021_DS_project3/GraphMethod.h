//
// Created by 정성엽 on 2022/12/10.
//

#ifndef DSPRO3_GRAPHMETHOD_H
#define DSPRO3_GRAPHMETHOD_H

#include "ListGraph.h"
#include "MatrixGraph.h"

bool BFS(Graph *graph, int vertex);

bool DFS(Graph *graph, int vertex);

bool DFS_R(Graph *graph, vector<bool> &visit, int vertex);

bool recursion(Graph *graph, vector<bool> &visited, int vertex);

bool Kruskal(Graph *graph);

int find_Root(int node, int parent[]);

void union_Root(int node1, int node2, int parent[]);

void quicksort(vector<pair<int, pair<int, int>>> *arr, const int low, const int high);

void insertionSort(vector<pair<int, pair<int, int>>> *arr, const int low, const int high);

int partition(vector<pair<int, pair<int, int>>> *arr, int low, int high);

bool Dijkstra(Graph *graph, int vertex);

bool Bellmanford(Graph *graph, int s_vertex, int e_vertex);

void find_path(int s, int e, int dist[], int prev[]);

bool FLOYD(Graph *graph);

#endif //DSPRO3_GRAPHMETHOD_H
