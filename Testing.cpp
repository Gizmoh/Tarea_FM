
#include <sdsl/suffix_trees.hpp>
#include <string>

using namespace sdsl;
using namespace std;

int main()
{
    string file = "world_leaders";
    string v = "";
    cout<<v<<endl;
    //store_to_file((const char*)v.c_str(), file);
    cout<<"---------"<<endl;
    cout << util::file_size(file) << endl;
    cout<<"---------"<<endl;
    cout<<"--------- construct csa_wt<> ----------"<<endl;
    {
        csa_wt<> csa;
        construct(csa, file, 1);
        cout << "csa.size()="<<csa.size()<<endl;
        /*for (size_t i=0; i < csa.size(); ++i) {
            cout << csa[i] << " ";
        }
        cout << endl;
        for (size_t i=0; i < csa.size(); ++i) {
            cout << csa.bwt[i] << " ";
        }
        cout << endl;
        for (size_t i=0; i < csa.size(); ++i) {
            cout << csa.psi[i] << " ";
        }
        cout << endl;
        for (size_t i=0; i < csa.size(); ++i) {
            cout << csa.lf[i] << " ";
        }
        cout << endl;*/
    }
    cout<<"---------"<<endl;
}