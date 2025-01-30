#pragma once
#define f first
#define s second

// Bibliotecas padrao
#include <bits/stdc++.h>
using namespace std;
constexpr int64_t INF = 0x3f3f3f3f3f3f3f3f;

// Tipos basicos de dados
typedef pair<vector<int>, vector<int>> seq_pair;
typedef pair<int64_t, int64_t> coord;

// Tipos do Clock
typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::seconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()