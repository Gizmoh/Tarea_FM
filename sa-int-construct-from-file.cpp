/*
 * sa-int-construct-from-file.cpp
 *
 *  Created on: Aug 13, 2018
 *      Author: hferrada
 */

#include <iostream>
#include <fstream>
#include <sdsl/suffix_trees.hpp>

using namespace sdsl;
using namespace std;

int main(int argc, char* argv[])
{
    if (argc > 1) {
        string file  = string(argv[1]);
        string ofile = file + ".sa";
        if (argc > 2) {
            ofile = argv[2];
        }
        int_vector<> sa;
        {
            int_vector<64> temp;
            load_vector_from_file(temp, file, 8);
            cout << "input elements = " << temp.size() << endl;
            if (temp.size()==0 or temp[temp.size()-1] != 0) {
                cout << "Add 0 to input `" << file << "`" << endl;
                temp.resize(temp.size()+1);
                temp[temp.size()-1] = 0;
                store_to_plain_array<uint64_t>(temp, file);
            }
        }
        qsufsort::construct_sa(sa, file.c_str(), 8);
        cout << "done" << endl;
        cout << "sa.size()="<<sa.size() << endl;
        cout << "sa.width()=" <<(int)sa.width() << endl;
        cout << "bit_compress..." << endl;
        util::bit_compress(sa);
        cout << "sa.width()=" <<(int)sa.width() << endl;
        store_to_file(sa, ofile);

        cout << "SA = " << endl;
        for (int i=0; i<sa.size(); i++){
        	 cout << sa[i] << " ";
        }
        cout << endl;
        ifstream texto;
        char temp;
        texto.open(file);
        texto.seekg(0,texto.beg);
        for(int i=0;i<sa.size();i++){
            texto.seekg((sa[i]),texto.cur);
            texto.get(temp);
            cout << temp << " ";
            texto.seekg(0,texto.beg);
        }
        cout << endl;
    } else {
        cout << "Usage: " << argv[0] << " file [ofile]" << endl;
        cout << " Computes the SA from an array of 64-bit integers." << endl;
        cout << " Result is stored in `ofile`, or `file`.sa if `ofile`" << endl;
        cout << " is not specified." << endl;
    }
}