#include <sdsl/suffix_trees.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sdsl/construct.hpp>
#include <math.h>
#include "include/BasicCDS.h"

using namespace sdsl;
using namespace std;
using namespace cds;

/*
int LF(int pos,vector<int> Ar,vector<int> Acum,bit_vector Bc,size_t rankBc, size_t selBc, vector<char> Cr,int LF[]){
    vector<char>::iterator pointer = find(Cr.begin(),Cr.end(),Cr[rankBc]);
    int temp = distance(Cr.begin(),pointer);
    int Ari = Ar[rankBc];
    int output = Acum[temp] + Ari + 1 + pos - selBc;
    cout << temp << " " << Cr[temp] << endl;
    //cout << LF[pos] << " " << output << " " << Ari << " " << pos << " " << Ar[rankBc] << " " << Acum[temp] <<endl;
    return 0;
}*/

char comparePWithSuffix(int i, string P, int *PSI, bit_vector *BSa, vector<char> *Chars)
{
    rank_support_v<1> rankBSa(&(*BSa));
    int j = 1;
    char c;
    while (j < P.length())
    {
        c = (*Chars)[rankBSa(i)];
        if (P[j] < c)
            return '<';
        if (P[j] > c)
            return '>';
        i = PSI[i];
        j = j + 1;
    }
    return '=';
}

void SABinarySearchPSI(string P, int *PSI, bit_vector *BSa, vector<char> *Chars, int &Sp, int &Ep)
{
    //n es igual al largo del bitvector
    int b = 0;
    int t = 0;
    int s = 0;
    int e = 0;
    b = 1;
    t = BSa->size() - 1;
    while (b < t)
    {
        s = floor((b + t) / 2);
        if (comparePWithSuffix(s, P, PSI, BSa, Chars) == '>')
            b = s + 1;
        else
            t = s;
    }
    e = b - 1;
    t = BSa->size();
    while (e < t)
    {
        s = floor((e + t) / 2);
        if (comparePWithSuffix(s, P, PSI, BSa, Chars) == '=')
            e = s;
        else
            t = e - 1;
    }
    Sp = b;
    Ep = e;
}
void BackwardLF(string P, int *LF, bit_vector *BSa, vector<char> *Chars, int &Sp, int &Ep)
{
    int m, r, b, e, j, k;
    m = P.length();
    vector<char>::iterator pointer = find(Chars->begin(), Chars->end(), P[m - 1]);
    bit_vector::select_1_type Bc_Sel1(&(*BSa));
    rank_support_v<1> rankBc_1(&(*BSa));
    r = distance(Chars->begin(), pointer);
    b = Bc_Sel1(r);
    e = Bc_Sel1(r + 1) - 1;
    for (int i = m; i > 2; i--)
    {
        k = b;
        j = LF[k];
        while ((*Chars)[rankBc_1(j)] != P[i - 1] and k <= e)
        {
            k = k + 1;
            j = LF[k];
        }
        b = k;
        k = e;
        j = LF[k];
        while ((*Chars)[rankBc_1(j)] != P[i - 1] and k >= b)
        {
            k = k - 1;
            j = LF[k];
        }
        e = k;
        if (b <= e)
        {
            Sp = LF[b];
            Ep = LF[e];
        }
    }
    Sp = b;
    Ep = e;
}

void testing(int largo, int *PSI, bit_vector *BSa, vector<char> *ABC, int &Sp, int &Ep, double &promPsi, double &promLF)
{
    string palabra;
    int aux = ABC->size() - 1;
    double t;
    for (int i = 0; i < 100; i++)
    {
        palabra = "";
        while (palabra.length() < largo)
        {
            palabra.push_back((*ABC)[rand() % aux]);
            cout << palabra << " " << palabra.length();
        }
        t = getTime_ms();
        SABinarySearchPSI(palabra, PSI, BSa, ABC, Sp, Ep);
        promPsi += getTime_ms() - t;
        t = getTime_ms();
        BackwardLF(palabra, PSI, BSa, ABC, Sp, Ep);
        promLF += getTime_ms() - t;
    }
    cout << endl;
    promPsi = (promPsi / 100);
    promLF = (promLF / 100);
}

int main()
{
    bit_vector *Bc;    //Bit vector de cambio de letras
    bit_vector *BSa;   //Bit vector de SA
    vector<char> *Cr;  //vector de letras por run
    vector<char> *ABC; //vector de alfabeto
    vector<int> *Ar;   //Arreglo de runs acumulados
    int Sp = 0;        //Start point
    int Ep = 0;        //End point
    int *Psi;
    int *LastF;
    string file = "LolTest.txt";
    csa_wt<> csa;
    Cr = new vector<char>;
    Ar = new vector<int>;
    ABC = new vector<char>;
    char eval;
    char eval2;
    vector<int> temp_AR;
    int counter = 0;
    int temp = 0;
    vector<char>::iterator pointer;
    construct(csa, file, 1);
    Psi = new int[csa.size()];
    LastF = new int[csa.size()];
    eval = csa.bwt[0];
    eval2 = csa.text[csa[0]];
    Cr->push_back(csa.bwt[0]);
    Bc = new bit_vector(csa.size(), 0);
    BSa = new bit_vector(csa.size(), 0);
    for (size_t i = 0; i < csa.size(); ++i)
    {
        Psi[i] = csa.psi[i];
        LastF[i] = csa.lf[i];
        if (eval2 != csa.text[csa[i]])
        {
            (*BSa)[i] = 1;
            ABC->push_back(csa.text[csa[i]]);
        }
        if (eval != csa.bwt[i])
        {
            (*Bc)[i] = 1;
            Cr->push_back(csa.bwt[i]);
            eval = csa.bwt[i];
            pointer = find(Cr->begin(), Cr->end(), csa.bwt[i]);
            temp = distance(Cr->begin(), pointer);
            if (temp_AR.size() > temp)
            {
                Ar->push_back(temp_AR[temp]);
                temp_AR[temp] += counter;
            }
            else
            {
                Ar->push_back(0);
                temp_AR.push_back(counter);
            }
            counter = 0;
        }
        eval = csa.bwt[i];
        eval2 = csa.text[csa[i]];
        counter++;
    }
    ofstream Resultados;
    double promPsi = 0;
    double promLF = 0;
    Resultados.open("Resultados.csv", ios::app);
    Resultados << "Largo palabra,T promedio Busqueda Binaria,T promedio BackWardSearch";
    for (int i = 0; i < 10; i++)
    {
        testing(i, Psi, BSa, ABC, Sp, Ep, promPsi, promLF);
        Resultados << i << "," << promPsi << "," << promLF << "\n";
    }
    Resultados.close();
}