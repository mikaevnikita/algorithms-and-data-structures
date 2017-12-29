#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void quicksort(vector<T>& array, int begin, int end){
    int pivot = array[int((begin+end)/2)];
    int left = begin;
    int right = end;
    while(left <= right){
        while(array[left] < pivot)
            left++;
        while(array[right] > pivot)
            right--;
        if(left <= right){
            T temp = array[left];
            array[left] = array[right];
            array[right] = temp;
            left++;
            right--;
        }
    }
    if(begin < right)
        quicksort(array, begin, right);
    if(end > left)
        quicksort(array, left, end);
}

template <typename T>
void printVector(vector<T>& v){
    for(T x:v){
        cout << x << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    vector<int> v = {1,2,3,2,2,10,3,3,-1,-100,-500};
    quicksort(v,0,v.size()-1);
    printVector(v);
    return 0;
}
