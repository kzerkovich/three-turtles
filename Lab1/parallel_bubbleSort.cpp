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
Параллельная сортировка пузырьком
Алгоритм:
    1) Создаём массив подмассивов по количеству используемых потоков
    2) Определяем максимальный элемент в исходном в массиве
    3) Используя максимальный элемент и количество потоков, определяем разбиение для более удобного распределения элементов на подмассивы
    4) Добавляем в подмассивы (с номерами от 1 до NUM_THREADS - 1) элементы, не забывая удалять из основного массива
    5) Оставшиеся элементы добавляем в подмассив с номером NUM_THREADS
    6) Создаём вектор потоков и для каждого подмассива запускаем свой поток
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
    //Размер массива
    int n;
    cout << "Enter the size of array:" << endl; cin >> n;

    //Заполнение массива рандомными значениями
    vector<int> vec(n);
    for (int i = 0; i < n; i++)
        vec[i] = rand();
    
    //Счётчик начала работы сортировки
    clock_t start = clock();

    //Параллельная сортировка пузырьком
    pBubbleSort(vec, n);

    //Вывод времени работы сортировки
    double work = (double)(clock() - start) / CLOCKS_PER_SEC;
    cout << "Time: " << work;
}