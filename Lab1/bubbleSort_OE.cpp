#include <iostream>
#include <vector>

using namespace std;

void bubbleSortOE(vector<int>& vec) {
    int n = vec.size();
    bool isSorted = false;
    while (!isSorted)
    {
        isSorted = true;
        for (int i = 1; i < n - 1; i = i + 2)
        {
            if (vec[i] > vec[i + 1])
            {
                swap(vec[i], vec[i + 1]);
                isSorted = false;
            }
        }
        for (int i = 0; i < n - 1; i = i + 2)
        {
            if (vec[i] > vec[i + 1])
            {
                swap(vec[i], vec[i + 1]);
                isSorted = false;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the size of array:" << endl;
    cin >> n;
    cout << "Enter an array:" << endl;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }

    bubbleSortOE(vec);

    cout << endl << "Sorted array:" << endl;
    for (int i = 0; i < n; i++) {
        cout << vec[i] << " ";
    }
}