#include <sdsl/suffix_trees.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sdsl/construct.hpp>

using namespace sdsl;
using namespace std;
using namespace std::chrono;
using timer = std::chrono::high_resolution_clock;

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

void SABinarySearchPSI(string P, int *PSI, bit_vector *BSa, vector<char> *Chars,int &Sp,int &Ep)
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

void BackwardLF(string P,int* LF,bit_vector *BSa, vector<char> *Chars,int &Sp,int &Ep){
    int m,r,b,e,k;
    m = P.length();
    bit_vector::select_1_type Bc_Sel1(&Bc);
    rank_support_v<1> rankBc_1(&Bc);
    r = find(Chars,Chars.length(),P[m-1]);
    b = Bc_Sel1(r);
    e = Bc_Sel1(r+1)-1;
    for(int i=m; i > 2; i--){
        k = b;
        j = LF(k);
        while(Chars[rankBc_1(j)]!=P[i-1] and k<=e){
            k = k+1;
            j = LF(k);
        }
        b = k;
        *Sp = k;
        k = e;
        j = LF(k);
        while(Chars[rankBc_1(j)]!=P[i-1] and k>=b){
            k = k-1;
            j = LF(k);
        }
        e = k;
        *Ep = k;
        if(b<=e){
            *Sp = LF(b);
            *Ep = LF(e);
        }
    }
}
int main()
{
    bit_vector *Bc;    //Bit vector de cambio de letras
    bit_vector *BSa;   //Bit vector de SA
    vector<char> *Cr;  //vector de letras por run
    vector<char> *ABC; //vector de alfabeto
    vector<int> *Ar;   //Arreglo de runs acumulados
    int Sp = 0;       //Start point
    int Ep = 0;       //End point
    int *Psi;
    int *LastF;
    string file = "LolTest.txt";
    //store_to_file((const char*)v.c_str(), file);
    cout << "---------" << endl;
    cout << util::file_size(file) << endl;
    cout << "---------" << endl;
    cout << "--------- construct csa_wt<> ----------" << endl;
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
    cout << "csa.size()=" << csa.size() << endl;
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
    string P = "sal";
    SABinarySearchPSI(P, Psi, BSa, ABC,Sp,Ep);
    cout << Sp << " " << Ep;
}