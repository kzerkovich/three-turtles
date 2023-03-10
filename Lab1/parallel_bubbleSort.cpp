#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
#include <algorithm>

using namespace std;

//���������� ������������ �������
int NUM_THREADS = 12;

/*
����������� ���������� ��������� �� �������� ������/��������
���� ������ �� ������������ ����������� ��� ������:
    1) �� �������� ������ ����������� ���������� ��� ��������� � ��������� ���������
    2) �� ������ ������ ����������� ���������� ��� ��������� � ������� ���������
*/
void bubbleSortOE(vector<int> &arr) {
    int n = arr.size();
    bool isSorted = false;
    while (!isSorted) {
        isSorted = true;
        for (int i = 1; i < n - 1; i = i + 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
        for (int i = 0; i < n - 1; i = i + 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
    }
}

/*
������������ ���������� ���������
��������:
    1) ������ ������ ����������� �� ���������� ������������ �������
    2) ���������� ������������ ������� � �������� � �������
    3) ��������� ������������ ������� � ���������� �������, ���������� ��������� ��� ����� �������� ������������� ��������� �� ����������
    4) ��������� � ���������� (� �������� �� 1 �� NUM_THREADS - 1) ��������, �� ������� ������� �� ��������� �������
    5) ���������� �������� ��������� � ��������� � ������� NUM_THREADS
    6) ������ ������ ������� � ��� ������� ���������� ��������� ���� �����
*/
void pBubbleSort(vector<int> &arr, int n) {
    vector<vector<int>> sublists(NUM_THREADS);

    int split = *max_element(arr.begin(), arr.end()) / NUM_THREADS;

    for (size_t i = 1; i < NUM_THREADS; i++) {
        for (int j = 0; j < arr.size(); j++) {
            if (arr[j] < split * i){
                auto iter = arr.begin() + j;
                sublists[i - 1].push_back(arr[j]);
                arr.erase(iter);
            }
        }
    }
    sublists[NUM_THREADS - 1] = arr;

    vector<thread> threads(NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(bubbleSortOE, ref(sublists[i]));
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
}

int main() {
    //������ �������
    int n;
    cout << "Enter the size of array:" << endl; cin >> n;

    //���������� ������� ���������� ����������
    vector<int> vec(n);
    for (int i = 0; i < n; i++)
        vec[i] = rand();
    
    //������� ������ ������ ����������
    clock_t start = clock();

    //������������ ���������� ���������
    pBubbleSort(vec, n);

    //����� ������� ������ ����������
    double work = (double)(clock() - start) / CLOCKS_PER_SEC;
    cout << "Time: " << work;
}