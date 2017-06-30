#include "Apriori.h"
using namespace std;

Apriori::Apriori(vector<set<string>> input, double low_bound){
    index = 0;
    // first round of frequent item sets;
    map<set<int>, int> init;

    for(unsigned int i=0;i<input.size();i++){
        set<string>::iterator it;
        set<int> iset;
        for(it=input[i].begin();it!=input[i].end();it++){
            // convert string term value to int index;
            int id = getId(*it);
            iset.insert(id);
            // count first round frequency;
            set<int> tmp;
            tmp.insert(id);
            init[tmp]++;
        }
        origin_data.push_back(iset);
    }
    itemsets.push_back(init);
    // change min support to an int frequency lower bound;
    bound = ceil(input.size()*low_bound);
}

Apriori::~Apriori(){
    //dtor
}

// join two set;
set<int> Apriori::join(set<int> s1, set<int> s2){
    set<int> result(s1);
    result.insert(s2.begin(), s2.end());
    return result;
}

// test if first set is sub set of second one;
bool Apriori::isSubSet(set<int> s_small, set<int> s_big){
    return join(s_small,s_big).size()==s_big.size();
}

// test if set s is frequent item set;
bool Apriori::isFreq(set<int> s, int step){
    set<int> tmp(s);
    // round K frequent item set must has all its subset with (K-1)
    // elements all in round (K-1) frequent items, that's the definition
    // of frequent item set.
    for(sit i=s.begin();i!=s.end();i++){
        // iteratively delete one element and check if the subset is
        // in round K-1 frequent item sets.
        tmp.erase(*i);
        if(itemsets[step-1].find(tmp)!=itemsets[step-1].end()){
            if(itemsets[step-1][tmp]<bound){
                // if not then can return false directly.
                return false;
            }
        }
        else return false;
        tmp.insert(*i);
    }
    return true;
}

void Apriori::calculate(){
    cout<<"-------start calculate-------"<<endl;
    // run from 1st step;
    run(1);
    cout<<"-------end calculate---------"<<endl;
}

void Apriori::run(int step){
    cout<<"Round "<<step<<": "<<endl;
    // round K-1 frequent item sets;
    map<set<int>, int> prev = itemsets[step-1];
    // print it;
    for(mit i = prev.begin();i!=prev.end();i++){
        set<int> tmp = i->first;
        cout<<"{ ";
        for(sit j = tmp.begin();j!=tmp.end();j++){
            cout<<getValue(*j)<<" ";
        }
        cout<<"}:  "<<i->second;
        // if less than bound, means this item is deleted;
        if(i->second<bound){
            cout<<"  DELETED";
        }
        cout<<endl;
    }
    // round K frequent item sets;
    map<set<int>, int> next;
    // a flag to check if the calculation can stop;
    bool flag = false;
    // each time choose two sets iteratively;
    for(mit it1 = prev.begin();it1!=prev.end();it1++){
        if(it1->second<bound) continue;
        for(mit it2 = prev.begin();it2!=prev.end();it2++){
            if(it2->second<bound) continue;
            // join two sets;
            set<int> result = join(it1->first, it2->first);
            int s = result.size();
            // if is frequent item set, then its size only add 1;
            // also test if satisfy the definition of frequent item set;
            if(s==step+1&&isFreq(result, step)){
                int num = 0;
                // count its number in original data;
                for(unsigned int j=0;j<origin_data.size();j++){
                    if(isSubSet(result, origin_data[j])){
                        num++;
                    }
                }
                // if exist then add it to item sets;
                if(num > 0){
                    next[result] = num;
                    // find one result, we should continue;
                    flag = true;
                }
            }
        }
    }
    // add round K result to the vector;
    itemsets.push_back(next);
    // if we get at least one result, we have to continue;
    if(flag) run(step+1);
}

// convert string value to an unique index;
int Apriori::getId(string value){
    if(vmap.find(value)==vmap.end()){
        index++;
        vmap[value]=index;
        imap[index]=value;
        return index;
    }
    else{
        return vmap[value];
    }
}

// get original string value by its index;
string Apriori::getValue(int id){
    return imap[id];
}

// print input dataset.
void Apriori::printInput(){
    cout<<"-------Input dataset-------"<<endl;
    cout<<"min support lower bound: "<<bound<<endl;
    cout<<"total item num: "<<origin_data.size()<<endl;
    for(unsigned int i= 0;i<origin_data.size();i++){
        cout<<"item "<<i<<": ";
        for(sit it = origin_data[i].begin();it!=origin_data[i].end();it++){
            cout<<getValue(*it)<<" ";
        }
        cout<<endl;
    }
}
