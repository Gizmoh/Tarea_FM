#include <sdsl/suffix_trees.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sdsl/construct.hpp>

using namespace sdsl;
using namespace std;
using namespace std::chrono;
using timer = std::chrono::high_resolution_clock;

/*int LF(){

}

void comparePWithSuffix(i,P,PSI,bit_vector Bc,char []Chars){}

void SABinarySearchPSI(P,PSI,bit_vector Bc,char []Chars,int *Sp,int *Ep){
    //n es igual al largo del bitvector
    int b,t,n,s,e;
    b = 1;
    t = ;
    while (b<t){
        s = floor((b+t)/2);
        if(comparePWithSuffix(s,P,PSI,Bc,Chars)==">") b = s+1;
        else t = s;
    }
    e = b-1;
    t = n;
    while(e < t){
        s = floor((e+t)/2);
        if(comparePWithSuffix(s,P,PSI,Bc,Chars)=="=") b = s+1;
        else t = e-1;
    }
    *Sp = b;
    *Ep = e;
}

void BackwardLF(P,LF,bit_vector Bc, char []Chars,int *Sp,int *Ep){
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
*/
int main()
{
    bit_vector *Bc; //Bit vector de cambio de letras
    vector<char> * Cr;  //vector de letras por run
    vector<int> * Ar;   //Arreglo de runs acumulados
    int * Psi;
    string file = "Test.txt";
    //store_to_file((const char*)v.c_str(), file);
    cout<<"---------"<<endl;
    cout << util::file_size(file) << endl;
    cout<<"---------"<<endl;
    cout<<"--------- construct csa_wt<> ----------"<<endl;
    {
        csa_wt<> csa;
        Cr = new vector<char>;
        Ar = new vector<int>;
        char eval;
        vector<int> temp_AR;
        int counter = 0;
        int temp = 0;
        vector<char>::iterator pointer;
        construct(csa, file, 1);
        cout << "csa.size()="<<csa.size()<<endl;
        Psi = new int [csa.size()];
        eval = csa.bwt[0];
        Cr->push_back(csa.bwt[0]);
        Bc = new bit_vector(csa.size(),0);
        for (size_t i=0; i < csa.size(); ++i) {
            Psi[i] = csa.psi[i];
            if(eval!=csa.bwt[i]){
                (*Bc)[i] = 1;
                Cr->push_back(csa.bwt[i]);
                eval = csa.bwt[i];
                pointer = find(Cr->begin(),Cr->end(),csa.bwt[i]);
                temp = distance(Cr->begin(),pointer);
                if(temp_AR.size()>temp){
                    Ar->push_back(temp_AR[temp]);
                    temp_AR[temp]+=counter;
                }
                else{
                    Ar->push_back(0);
                    temp_AR.push_back(counter);
                }
                counter = 0;

            }
            eval = csa.bwt[i];
            counter++;
        }/*
        cout << endl;
        for (size_t i=0; i < csa.size(); ++i) {
            cout << csa.lf[i] << " ";
        }
        cout << endl;*/
    }
}