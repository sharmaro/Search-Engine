#include <string>
#include <iostream>
#include <vector>
 
using namespace std;

template <class T, class Comparator>
void helperMerge(vector<T> &a, Comparator comp){

	int l = 0;
	int r = (a.size()-1);

	MergeSort(a, l, r, comp);

}

template <class T, class Comparator>
void MergeSort(vector<T> &a, int l, int r, Comparator comp)
{
    if (l<r) { // otherwise, just one element, which is sorted
        int m = (l+r)/2;
        MergeSort(a, l, m, comp);
        MergeSort(a, m+1, r, comp);
        Merge(a, l, r, m, comp); // this is a separate function given below
    }
}

template <class T, class Comparator>
void Merge(vector<T> &a, int l, int r, int m, Comparator comp)
{
    T temp[r+1-l];
    // trace through the two subarrays, copying into a temporary
    int i = l, j = m+1, k = 0;
    while (i <= m || j <= r)  // at least one subarray contains another element
    {
        if (i <= m && (j > r || comp(a[i], a[j])))
            // next smallest element in left subarray
        { temp[k] = a[i]; i ++; k ++; }
        else { temp[k] = a[j]; j ++; k ++; }
        // next smallest element in right subarray
    }
    // now copy over the merged array into the original
    for (k = 0; k < r+1-l; k ++)
        a[k+l] = temp[k];
}
