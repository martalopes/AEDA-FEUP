#include <vector>
using namespace std;

template <class Comparable, class Comparison> 
void insertionSort(vector<Comparable> &v, Comparison& c)
{
    for (unsigned int p = 1; p < v.size(); p++)
    {
    	Comparable tmp = v[p];
    	int j;
    	for (j = p; j > 0 && c(tmp,v[j-1]); j--)
    		v[j] = v[j-1];
    	v[j] = tmp;
    } 
}

