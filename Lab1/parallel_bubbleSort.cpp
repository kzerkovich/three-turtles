#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
#include <algorithm>

using namespace std;

//Количество используемых потоков
int NUM_THREADS = 12;

/*
Стандартная сортировка пузырьком по принципу чётное/нечётное
Пока массив не отсортирован выполняются две стадии:
    1) На нечётной стадии выполняется сортировка для элементов с нечётными индексами
    2) На чётной стадии выполняется сортировка для элементов с чётными индексами
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
Параллельная сортировка пузырьком
Алгоритм:
    1) Разбиваем исходный массив на две части (чётную/нечётную)
    2) Создвём два потока, в которых сортируем эти части
    3) Сливаем отсортированные подмассивы обратно в один
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
    //Размер массива
    int n;
    cout << "Enter the size of array:" << endl; cin >> n;

    //Заполнение массива для параллельной сортировки рандомными значениями
    vector<int> vec_p(n);
    for (int i = 0; i < n; i++)
        vec_p[i] = rand();

    //Счётчик начала работы параллельной сортировки
    clock_t start_parallel = clock();

    //Параллельная сортировка пузырьком
    pBubbleSort(vec_p, n);

    //Вывод времени работы параллельной сортировки
    double work_p = (double)(clock() - start_parallel) / CLOCKS_PER_SEC;
    cout << "Time parallel sort: " << work_p << endl;

    //Заполнение массива для обычной сортировки рандомными значениями
    vector<int> vec_np(n);
    for (int i = 0; i < n; i++)
        vec_np[i] = rand();

    //Счётчик начала работы обычной сортировки
    clock_t start_nonparallel = clock();

    //Обычная сортировка пузырьком
    bubbleSortOE(vec_np);

    //Вывод времени работы обычной пузырьковой сортировки
    double work_np = (double)(clock() - start_nonparallel) / CLOCKS_PER_SEC;
    cout << "Time nonparallel sort: " << work_np;
}