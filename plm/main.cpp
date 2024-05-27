#include <iostream>
#include <fstream>
#include <cstring>
#include "file_reader.h"
#include "tele_cons.h"
#include "const.h"
#include "processing.h"
#include <string>
using namespace std;
void print_stuff(marafon* runners,int i)
{
   
        cout << runners[i].number << ' ';
        cout << runners[i].name << ' ';
        cout << runners[i].club << ' ';
        cout << runners[i].start_time.hours << ':';
        cout << runners[i].start_time.minutes << ':';
        cout << runners[i].start_time.seconds << ' ';
        cout << runners[i].finish_time.hours << ':';
        cout << runners[i].finish_time.minutes << ':';
        cout << runners[i].finish_time.seconds << ' ';
        cout << endl;
   
}

int getRaceTime(const marafon& runner) {
    return (runner.finish_time.hours * 3600 + runner.finish_time.minutes * 60 + runner.finish_time.seconds) -
        (runner.start_time.hours * 3600 + runner.start_time.minutes * 60 + runner.start_time.seconds);
}
times int_to_times(int x) {
    times result;
    if (x >= 3600) {
        result.hours = (x - (x % 3600)) / 3600;
        x = x - 3600 * result.hours;
    }
    if (x >= 60) {
        result.minutes = (x - (x % 60)) / 60;
        x = x - 60 * result.minutes;
    }
    if (x <= 60) {
        result.seconds = x;
            x = x - x;
    }
    return result;
}
bool compareRaceTime(const marafon& a, const marafon& b) {
    return getRaceTime(a) > getRaceTime(b);
}
bool compareClubAndName(const marafon& a, const marafon& b) {
    int clubComparison = strcmp(a.club, b.club);
    if (clubComparison == 0) {
        return strcmp(a.name, b.name) < 0;
    }
    return clubComparison < 0;
}
void bubbleSort(marafon* runners, int n, int criterion) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < n - 1; i++) {
            switch (criterion) {
            case 1:
                if (compareRaceTime(runners[i], runners[i + 1])) {
                    swap(runners[i], runners[i + 1]);
                    swapped = true;
                }
                break;
            case 2:
                if (compareClubAndName(runners[i], runners[i + 1])) {
                    swap(runners[i], runners[i + 1]);
                    swapped = true;
                }
                break;
            }
        }

       
       
        
     
    } while (swapped);
    
    for (int i = 0; i < n; i++) {
        print_stuff(runners, i);
    }
}

times best_time(marafon* runners, int size) {
    int min = getRaceTime(runners[0]);
    int ind = 0;
    for (int i = 1; i < size; i++) {
        if (min > getRaceTime(runners[i])) {
            min = getRaceTime(runners[i]);
            ind = i;
        }

    }
    cout << min << endl;
    return int_to_times(getRaceTime(runners[ind]));
}
int partition(marafon* runners, int left, int right, int criterion) {
    marafon pivot = runners[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        switch (criterion) {
        case 1:
            if (compareRaceTime(runners[j], pivot)) {
                i++;
                swap(runners[i], runners[j]);
            }
            break;
        case 2:
            if (compareClubAndName(runners[j], pivot)) {
                i++;
                swap(runners[i], runners[j]);
            }
            break;
        }
    }
    swap(runners[i + 1], runners[right]);
    return i + 1;
}
void quickSort(marafon* runners, int left, int right, int criterion) {
    if (left > right) {
        int pivot = partition(runners, left, right, criterion);
        quickSort(runners, left, pivot - 1, criterion);
        quickSort(runners, pivot + 1, right, criterion);
    }

    

}




void only_spartak(marafon* runners, int size)
{


    for (int i = 0; i < size; i++)
    {
        if (strstr(runners[i].club, "Spartak") != NULL)
        {
            print_stuff(runners, i);
            
        }
    }
}
void only_min_time(marafon* runners, int size)//<2 50 00
{


    for (int i = 0; i < size; i++)
    {
        if (getRaceTime(runners[i])< 10200)

        {
            print_stuff(runners, i);
        }
    }
}


/*bool SortCase(int sort_id, marafon* subscriptions[], int size, int id, int id2)
{
    switch (sort_id)
    {
    case 1:
    {
        if ((subscriptions[id]->finish_time.hours) * 3600 + (subscriptions[id]->finish_time.minutes) * 60 + (subscriptions[id]->finish_time.seconds) - (subscriptions[id]->start_time.hours) * 3600 - (subscriptions[id]->start_time.minutes) * 60 - (subscriptions[id]->start_time.seconds))
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    }
    case 2:
    {
        if (subscriptions[id]->club < subscriptions[id2]->club)
        {
            return false;
        }
        if (subscriptions[id]->club > subscriptions[id2]->club)
        {
            return true;
        }
        if (subscriptions[id]->club == subscriptions[id2]->club)
        {
            if (subscriptions[id]->name < subscriptions[id2]->name)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        break;
    }
    }
}

void heapify(marafon* subscriptions[], int size, int i, int sort_id)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (sort_id == 1) {
        if (l < size && SortCase(sort_id, subscriptions, size, l, largest)) {
            largest = l;
        }
        if (r < size && SortCase(sort_id, subscriptions, size, r, largest)) {
            largest = r;
        }
    }
    else if (sort_id == 2) {
        if (l < size && SortCase(sort_id, subscriptions, size, l, largest)) {
            largest = l;
        }
        if (r < size&& SortCase(sort_id, subscriptions, size, r, largest)) {
            largest = r;
        }
    }

    if (largest != i) {
        marafon* temp = subscriptions[i];
        subscriptions[i] = subscriptions[largest];
        subscriptions[largest] = temp;
        heapify(subscriptions, size, largest, sort_id);
    }
}

void heapSort(marafon* subscriptions[], int size, int sort_id)
{
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(subscriptions, size, i, sort_id);
    }
    for (int i = size - 1; i > 0; i--) {
        marafon* temp = subscriptions[0];
        subscriptions[0] = subscriptions[i];
        subscriptions[i] = temp;
        heapify(subscriptions, i, 0, sort_id);
    }
}

int partition(marafon* arr[], int low, int high, int sort_id, int size) {
    marafon* pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (!SortCase(sort_id, arr, size, j, high)) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

void quickSort(marafon* arr[], int low, int high, int sort_id, int permament_size) {
    if (low < high) {
        int p = partition(arr, low, high, sort_id, permament_size);
        quickSort(arr, low, p - 1, sort_id, permament_size);
        quickSort(arr, p + 1, high, sort_id, permament_size);
    }

}
void BubbleSort(marafon* subscriptions[], int size, int sort_id) {
    
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (SortCase(sort_id, subscriptions, size, j + 1, j))// Вызов функции для сравнения
                swap(subscriptions[j + 1], subscriptions[j]);// Обмен элементов
        }
    }
    for (int d = 0; d < size; d++)
    {
        print_stuff(subscriptions, d); // Вывод данных после сортировки
    }
}*/
bool readDataFromFile(const char* filename, marafon* runners, int& n) {
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return false;
    }
   
    n = 0;
    while (file >> runners[n].number >> runners[n].name >> runners[n].club
        >> runners[n].start_time.hours >> runners[n].start_time.minutes >> runners[n].start_time.seconds
        >> runners[n].finish_time.hours >> runners[n].finish_time.minutes >> runners[n].finish_time.seconds) {
        n++;   
    }

    
    cout << "Данные из файла:" <<endl;
    print_stuff(runners, n);

    file.close();
    return true;
}
int main() {
    int sort_id;
    int size;
    setlocale(LC_ALL, "Russian");
    cout << "Laboratory work #10. GIT\n";
    cout << "Variant #1.marafon\n";
    cout << "Author: BBEBEBEBEBEBE\n";
    cout << "Group: QWEQEWQEQWEQEQWE\n";
    marafon runners[MAX_FILE_ROWS_COUNT];
    //if (!readDataFromFile("data.txt", runners, size)) {
      //  return 1; // Ошибка чтения файла
    //}

    const char* filename = "data.txt";
    
    try { //чтение файла 
        read("data.txt", runners, size);
        for (int i = 0; i < size; i++) {
            print_stuff(runners, i);
        }
    }
    catch (const char* error) {
        cout << error << '\n';
    }
    //string filename = "data.txt";

    bool rpts = true;
    int rpts_value = 0;
   while (rpts == true) {
        cout << "?? " << endl
            << "1. Spartak" << endl
            << "2. Luchshie " << endl
            << "3. Bubble" << endl
            << "4. Quick" << endl
            << "5. Exit " << endl
            << "6.Best time" << endl;
        cin >> rpts_value;
        switch (rpts_value)
        {
        case 1:
        {
            
            only_spartak(runners, size);
           
            break;
        }
        case 2:
        {
            only_min_time(runners, size);

            break;
        }

        case 3:
        {

            cout << "Kak" << endl
                << "1.Po vozrast dlit" << endl
                << "2.Po vozrast nazv club'a" << endl;
            cin >> sort_id;
            bubbleSort(runners, size, sort_id);
            
            break;
        }
        case 4:
        {

            cout << "Kak" << endl
                << "1.Po vozrast dlit" << endl
                << "2.Po vozrast nazv club'a" << endl;
            cin >> sort_id;
            quickSort(runners, 0, size - 1, sort_id);
            for (int i = 0; i < size; i++) {
                print_stuff(runners, i);
            }
           
            break;
        }
        case 5:
        {
            rpts = false;
            break;
        }
        case 6:
        {
            times best=best_time(runners,size);
            cout << best.hours <<":" << best.minutes<< ":" << best.seconds << endl;
        }
        }
    }

    return 0;
}