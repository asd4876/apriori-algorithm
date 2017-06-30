#ifndef APRIORI_H
#define APRIORI_H

#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
typedef set<int>::iterator sit;
typedef map<set<int>, int>::iterator mit;

class Apriori
{
    public:
        // constructor, here, to speed up the process of calculation,
        // we used a simple bimap to convert input term value to an
        // unique index.
        Apriori(vector<set<string>> input, double low_bound);

        virtual ~Apriori();
        // calculate;
        void calculate();
        // run one step;
        void run(int step);
        // print input dataset;
        void printInput();
        // low bound used to delete item sets.
        int bound;

    private:
        // a vector, saves all candidate item sets.
        vector<map<set<int>, int>> itemsets;
        // original data;
        vector<set<int>> origin_data;
        // two normal map used as bimap;
        // map saves value => index;
        map<string, int> vmap;
        // map saves index => value;
        map<int, string> imap;
        // convert index => value;
        string getValue(int id);
        // convert value => index;
        int getId(string value);
        // index number;
        int index;
        // join two set;
        set<int> join(set<int> s1, set<int> s2);
        // test if 1st set is a sub set of second one.
        bool isSubSet(set<int> s_small, set<int> s_big);
        // test if set s is a frequent item set.
        bool isFreq(set<int> s, int step);

};

#endif // APRIORI_H
