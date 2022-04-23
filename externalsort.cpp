// External Sorting
// Read the chapter on external sorting from Raghu Ramakrishnan’s book.
// The input file format is as follows:
// • Number of available buffer pages
// • Number of records per page
// • Number of records in the data file
// • List of records. Assume that each record is just a non-negative integer. There could be duplicates in the data file.
// Output:
// Print the records in the ascending order. Perform sorting using the external sorting algorithm.

#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> v(k);
    for(int i = 0; i < k; i++)
        cin >> v[i];
    sort(v.begin(), v.end());
    for(int i = 0; i < k; i++)
        cout << v[i] << endl;
    return 0;
}