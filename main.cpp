#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <Apriori.h>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    // test dataset;
    vector<set<string>> dataset;
    string a1[] = {"t1","t2","t3","t4","t5"};
    string a2[] = {"t1","t2","t4","t5"};
    string a3[] = {"t1","t2","t3","t5"};
    string a4[] = {"t1","t3","t4","t5","t6"};
    string a5[] = {"t2","t3","t4","t5"};
    string a6[] = {"t1","t2"};
    string a7[] = {"t3","t4","t5"};
    string a8[] = {"t1","t2","t5"};
    string a9[] = {"t1","t3","t4","t5"};
    string a10[] = {"t1","t4","t5"};
    set<string> s1(a1,a1+5);
    set<string> s2(a2,a2+4);
    set<string> s3(a3,a3+4);
    set<string> s4(a4,a4+5);
    set<string> s5(a5,a5+4);
    set<string> s6(a6,a6+2);
    set<string> s7(a7,a7+3);
    set<string> s8(a8,a8+3);
    set<string> s9(a9,a9+4);
    set<string> s10(a10,a10+3);
    dataset.push_back(s1);
    dataset.push_back(s2);
    dataset.push_back(s3);
    dataset.push_back(s4);
    dataset.push_back(s5);
    dataset.push_back(s6);
    dataset.push_back(s7);
    dataset.push_back(s8);
    dataset.push_back(s9);
    dataset.push_back(s10);

    // init;
    Apriori ap(dataset, 0.3);
    // print input;
    ap.printInput();
    // calculate;
    ap.calculate();

    system("pause");
    return 0;
}
