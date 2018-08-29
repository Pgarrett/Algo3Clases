#define Federico using
#define Javier namespace
#define Pousa std;
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>


Federico Javier Pousa





void imprimirSolucion(vector<int> &asignacion){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            cout << ((asignacion[i]==j)?"D":"*");
        }
        cout << endl;
    }
}

void solveFuerzaBruta4(vector<int> &asignacion, int &contadorIteraciones, bool &encontre){
    if(encontre)return;
    if(asignacion.size()==8){
        contadorIteraciones++;
        encontre = true;
        for(int i=0; i<8; i++){
            for(int j=i+1; j<8; j++){
                if(abs(j-i)==abs(asignacion[i]-asignacion[j])||(asignacion[i]==asignacion[j])){
                    encontre = false;
                }
            }
        }
        
        if(encontre){
            imprimirSolucion(asignacion);
        }
    }else{
        for(int i=0; i<8; i++){
            asignacion.push_back(i);
            solveFuerzaBruta4(asignacion, contadorIteraciones, encontre);
            asignacion.pop_back();
        }
    }
    return;
}

void ochoReinasFuerzaBruta4(){
    vector<int> asignacion;
    int contadorIteraciones = 0;
    bool encontre = false;
    solveFuerzaBruta4(asignacion,contadorIteraciones, encontre);
    cout << endl << endl << "Solucion encontrada despues de: " << contadorIteraciones << " iteraciones" << endl;
    return;
}


void ochoReinasFuerzaBruta5(){
    vector<int> asignacion;
    for(int i=0; i<8; i++){
        asignacion.push_back(i);
    }
    
    bool encontre = false;
    int iteraciones = 0;
    do{
        iteraciones++;
        encontre = true;
        for(int i=0; encontre&&i<8; i++){
            for(int j=i+1; encontre&&j<8; j++){
                if(abs(j-i)==abs(asignacion[i]-asignacion[j])){
                    encontre = false;
                }
            }
        }
        if(encontre){
            imprimirSolucion(asignacion);
            cout << endl << endl << "Solucion encontrada despues de: " << iteraciones << " iteraciones" << endl;
        }
    }while(next_permutation(asignacion.begin(),asignacion.end()) && !encontre);
    return;
}

void solveBacktracking(vector<int> &asignacion, vector<bool> &disponibles, int &contadorDeNodos, bool &encontre){
    if(encontre)return;
    contadorDeNodos++;
    if(asignacion.size()==8){
        imprimirSolucion(asignacion);
        encontre = true;
        cout << endl << endl << "Solucion encontrada despues de: " << contadorDeNodos << " nodos" << endl;
    }
    for(int i=0; i<8; i++){
        if(disponibles[i]){
            bool sirveParcial = true;
            for(int j=0; sirveParcial&&j<(int)asignacion.size(); j++){
                if(abs((int)asignacion.size()-j)==abs(i-asignacion[j])){
                    sirveParcial = false;
                }
            }
            if(sirveParcial){
                asignacion.push_back(i);
                disponibles[i] = false;
                solveBacktracking(asignacion, disponibles, contadorDeNodos, encontre);
                asignacion.pop_back();
                disponibles[i] = true;
            }
        }
    }
    return;
}

void ochoReinasBacktracking(){
    vector<int> asignacion;
    vector<bool> disponibles;
    int contadorDeNodos = 0;
    bool encontre = false;
    for(int i=0; i<8; i++){
        disponibles.push_back(true);
    }
    solveBacktracking(asignacion, disponibles, contadorDeNodos, encontre);
    return;
}

int main(){
     
    cout << "steady_clock" << endl;
    cout << chrono::steady_clock::period::num << endl;
    cout << chrono::steady_clock::period::den << endl;
    cout << "steady = " << boolalpha << chrono::steady_clock::is_steady << endl << endl;
    
    
    
    
    cout << endl << endl;
    auto startFuerzaBruta4 = chrono::steady_clock::now();
    ochoReinasFuerzaBruta4();
    auto endFuerzaBruta4 = chrono::steady_clock::now();
    auto diffFuerzaBruta4 = endFuerzaBruta4 - startFuerzaBruta4;
    cout << "Tiempo utilizado por Fuerza bruta 4" << chrono::duration <double, milli> (diffFuerzaBruta4).count() << " ms" << endl;
    
    
    cout << endl << endl;
    auto startFuerzaBruta5 = chrono::steady_clock::now();
    ochoReinasFuerzaBruta5();
    auto endFuerzaBruta5 = chrono::steady_clock::now();
    auto diffFuerzaBruta5 = endFuerzaBruta5 - startFuerzaBruta5;
    cout << "Tiempo utilizado por Fuerza bruta 5" << chrono::duration <double, milli> (diffFuerzaBruta5).count() << " ms" << endl;
    
    
    cout << endl << endl;
    auto startBacktracking = chrono::steady_clock::now();
    ochoReinasBacktracking();
    auto endBacktracking = chrono::steady_clock::now();
    auto diffBacktracking = endBacktracking - startBacktracking;
    cout << "Tiempo utilizado por Backtracking " <<chrono::duration <double, milli> (diffBacktracking).count() << " ms" << endl;

    return 0;
}
