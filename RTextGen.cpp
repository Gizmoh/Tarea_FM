#include <sdsl/suffix_trees.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <sdsl/construct.hpp>
#include <math.h>
#include <climits>

using namespace sdsl;
using namespace std;
using namespace std::chrono;


int main(){
    ofstream Texto;
    Texto.open("repe_Text",ios::trunc);
    char Letras [7] = {'a','b','c','d','e','f','g'};
    int aux = 7;
    for(int i=0;i<1000000;i++){
        Texto << Letras[rand()%aux];
    }
    Texto.close();
}