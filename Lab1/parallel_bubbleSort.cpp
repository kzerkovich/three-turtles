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
void bubbleSortOE(vector<int>& arr) {
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
    1) ��������� �������� ������ �� ��� ����� (������/��������)
    2) ������ ��� ������, � ������� ��������� ��� �����
    3) ������� ��������������� ���������� ������� � ����
*/
void pBubbleSort(vector<int>& arr, int n) {
    int NUM_THREADS = 2;
    vector<int> evenPhase, oddPhase;

    for (int i = 0; i < n - 1; i = i + 2) {
        evenPhase.push_back(arr[i]);
    }

    for (int i = 1; i < n - 1; i = i + 2) {
        oddPhase.push_back(arr[i]);
    }

    thread first = thread(bubbleSortOE, ref(evenPhase));
    thread second = thread(bubbleSortOE, ref(oddPhase));

    first.join();
    second.join();

    int i = 0, j = 0, k = 0;

    while (i < evenPhase.size() && j < oddPhase.size())
    {
        if (evenPhase[i] < oddPhase[j])
            arr[k++] = evenPhase[i++];
        else
            arr[k++] = oddPhase[j++];
    }

    while (i < evenPhase.size())
        arr[k++] = evenPhase[i++];

    while (j < oddPhase.size())
        arr[k++] = oddPhase[j++];
}

int main() {
    //������ �������
    int n;
    cout << "Enter the size of array:" << endl; cin >> n;

    //���������� ������� ��� ������������ ���������� ���������� ����������
    vector<int> vec_p(n);
    for (int i = 0; i < n; i++)
        vec_p[i] = rand();

    //������� ������ ������ ������������ ����������
    clock_t start_parallel = clock();

    //������������ ���������� ���������
    pBubbleSort(vec_p, n);

    //����� ������� ������ ������������ ����������
    double work_p = (double)(clock() - start_parallel) / CLOCKS_PER_SEC;
    cout << "Time parallel sort: " << work_p << endl;

    //���������� ������� ��� ������� ���������� ���������� ����������
    vector<int> vec_np(n);
    for (int i = 0; i < n; i++)
        vec_np[i] = rand();

    //������� ������ ������ ������� ����������
    clock_t start_nonparallel = clock();

    //������� ���������� ���������
    bubbleSortOE(vec_np);

    //����� ������� ������ ������� ����������� ����������
    double work_np = (double)(clock() - start_nonparallel) / CLOCKS_PER_SEC;
    cout << "Time nonparallel sort: " << work_np;
}