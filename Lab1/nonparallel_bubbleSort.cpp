#include <iostream>
#include <vector>

using namespace std;

void bubbleSort(vector<int>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec.size() - i - 1; j++) {
			if (vec[j] > vec[j + 1])
				swap(vec[j], vec[j + 1]);
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

	bubbleSort(vec);

	cout << endl << "Sorted array:" << endl;
	for (int i = 0; i < n; i++) {
		cout << vec[i] << " ";
	}
}