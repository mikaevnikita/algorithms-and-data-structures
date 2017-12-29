#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H
#include <vector>
using namespace std;

template <typename T>
int find_min(vector<T>& v, int left, int right){
    int min_index=left;
    for(int i=left+1;i<right;i++){
        if(v[i]<v[min_index])
            min_index=i;
    }
    return min_index;
}

template <typename T>
void swap(const T& arg1, const T& arg2){
    T temp = arg1;
    arg1 = arg2;
    arg2 = temp;
}

template <typename T>
void selection_sort(vector<T>& v){
    for(int i=0;i<v.size();i++){
        int index=find_min(v,i,v.size());
        if(index!=i)
            swap(v[i],v[index]);
    }
}

#endif // SELECTION_SORT_H
