#pragma once
#define f first
#define s second

// Bibliotecas padrao
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

// Tipos basicos de dados
typedef pair<vector<int>, vector<int>> seq_pair;
typedef pair<double, double> coord;

// Tipos do Clock
typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::seconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()