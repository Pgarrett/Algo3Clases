// Resuelve LCS mediante usando una formulación recursiva con y sin memoización (método D, método R).
// Para cada n y m en un rango de valores, crea K instancias con un string de tamaño n y otro de tamaño m, 
// y las resuelve con ambos métodos tomando los tiempos. Luego, para cada (n, m) toma el promedio de tiempo 
// de ejecuciones.

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>

using namespace std;

// Toma lineas de codigo y mide el tiempo que tarda en ejecutarlas.
// Ejecuta el código K veces y toma un tiempo promedio.
#define medir_tiempo(K, CODIGO) \
    [&] () -> double {\
        double tiempo_promedio = 0.0;\
        for (int i = 0; i < K; ++i)\
        {\
            auto tiempo_inicio = chrono::steady_clock::now();\
            CODIGO \
            auto tiempo_fin = chrono::steady_clock::now();\
            tiempo_promedio += chrono::duration<double, milli>(tiempo_fin - tiempo_inicio).count();\
        }\
        return tiempo_promedio / (double)K;\
    }();

// Genera una instancia del peor caso de LCS con dos strings de longitudes n y m.
// El peor caso para PD es cuando no comparten caracteres porque tiene que entrar siempre
// por el caso que bifurca en dos llamadas.
void generar_instancia_peor_caso(int n, int m, string* s1, string* s2)
{
    for (int i = 0; i < n; ++i) s1->push_back('a');
    for (int i = 0; i < m; ++i) s2->push_back('b');
}

// Genera una instancia del mejor caso de LCS con dos strings de longitudes n y m.
// El mejor caso para PD es cuando son iguales, porque en la versión top_down termina siendo 
// lineal O(n+m), ya que en cada paso se saca un caracter de cada string.
void generar_instancia_mejor_caso(int n, int m, string* s1, string* s2)
{
    for (int i = 0; i < n; ++i) s1->push_back('a');
    for (int i = 0; i < m; ++i) s2->push_back('a');
}

// Resuelve Longest Common Subsequence usando programacion dinamica (Top down)
int lcs_top_down(const string& s1, const string& s2, int i, int j, vector<vector<int>>& M)
{
    int n = s1.size(), m = s2.size();

    if (i == n || j == m) return 0;
    if (M[i][j] == -1)
    {
        if (s1[i] == s2[j]) M[i][j] = 1 + lcs_top_down(s1, s2, i+1, j+1, M);
        else M[i][j] = max(lcs_top_down(s1, s2, i+1, j, M), lcs_top_down(s1, s2, i, j+1, M));
    }
    return M[i][j];
}

// Resuelve Longest Common Subsequence usando programacion dinamica (Bottom up)
int lcs_bottom_up(const string& s1, const string& s2)
{
    int n = s1.size(), m = s2.size();
    vector<vector<int>> M(n+1, vector<int>(m+1, -1));
    for (int i = 0; i < n; ++i) M[i][m] = 0;
    for (int j = 0; j < m; ++j) M[n][j] = 0;
    for (int i = n-1; i >= 0; --i)
    {
        for (int j = m-1; j >= 0; --j)
        {
            if (s1[i] == s2[j]) M[i][j] = 1 + M[i+1][j+1];
            else M[i][j] = max(M[i+1][j], M[i][j+1]);
        }
    }
    return M[0][0];
}

// Toma tres parametros opcionales N, M, tipo_instancia.
//  N: máximo tamaño del primer string. (default: 10)
//  M: máximo tamaño del segundo string. (default: 10)
//  tipo_instancia: 1 si usa instancias de mejor caso, 0 si usa instancias del peor caso.
int main(int argc, char** argv)
{
    int N = argc > 1 ? atoi(argv[1]) : 1000;
    int M = argc > 2 ? atoi(argv[2]) : 1000;
    bool tipo_instancia = argc > 3 ? atoi(argv[3]) : 0;

    cout << "instance,n,m,TD,BU" << endl;

    // Generamos instancias con n, m \in [0..N]x[0..M]
    int i = 0;
    for (int n = 100; n <= N; n+=100)
    {
        for (int m = 100; m <= M; m+=100)
        {
            // Generamos una instancia de tamaño (n, m).
            string s1, s2;
            if (tipo_instancia == 0) generar_instancia_peor_caso(n, m, &s1, &s2);
            else if (tipo_instancia == 1) generar_instancia_mejor_caso(n, m, &s1, &s2);

            // Ejecutamos el algoritmo de PD top down.
            auto tiempo_total_pd_td = medir_tiempo(100,
                vector<vector<int>> M(n, vector<int>(m, -1));
                lcs_top_down(s1, s2, 0, 0, M);
            );

            // Ejecutamos el algoritmo de PD bottom up.
            auto tiempo_total_pd_bu = medir_tiempo(100,
                lcs_bottom_up(s1, s2);
            );

            // Imprimimos el tiempo de ambos algoritmos.
            cout << i++ << "," << n << "," << m << "," << tiempo_total_pd_td << "," << tiempo_total_pd_bu << endl;
        }
    }

    return 0;
}
