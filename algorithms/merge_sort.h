#ifndef MERGE_SORT_H
#define MERGE_SORT_H
#include <vector>
using namespace std;

template<typename T>
vector<T> merge(const vector<T>& v1, const vector<T>& v2){
    int i=0;
    int j=0;
    vector<T> merged_v;
    for(;i<v1.size() and j<v2.size();){
        if(v1[i] < v2[j])
            merged_v.push_back(v1[i++]);
        else
            merged_v.push_back(v2[j++]);
    }
    for(;i<v1.size();i++)
        merged_v.push_back(v1[i]);
    for(;j<v2.size();j++)
        merged_v.push_back(v2[j]);
    return merged_v;
}

template <typename T>
vector<T> merge_sort(vector<T>& v){
    if(v.size() == 0 or v.size() == 1)
        return v;
    if(v.size() == 2)
        if(v[0] > v[1]){
            std::reverse(v.begin(),v.end());
            return v;
        }
    vector<T> left_v;
    vector<T> right_v;
    for(int i=0;i<v.size();i++){
        if(i < v.size() / 2)
            left_v.push_back(v[i]);
        else
            right_v.push_back(v[i]);
    }
    return merge<T>( merge_sort(left_v), merge_sort(right_v) );
}
#endif // MERGE_SORT_H
