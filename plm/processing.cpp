#include <iostream>
#include "tele_cons.h"
#include "processing.h"
using namespace std;
// Подключение заголовочных файлов
int time_to_int(times x) {
	return x.hours* 3600 + x.minutes* 60 + x.seconds;
}
float Difference(marafon* subscribtions[], int size) {//разница между ценой покупки и продажи для каждой подписки,
	int id = 0;
	float value = 0;
	for (int i = 0; i < size; i++) {
		int temp1 = time_to_int(subscribtions[i]->finish_time);// Получение значения цены покупки
		int temp2 = time_to_int(subscribtions[i]->start_time);// Получение значения цены продажи
		if ((abs(temp1 - temp2)) > value)// Если разница между ценами больше сохранённого значения
		{
			value = (abs(temp1 - temp2));// Обновление значения наибольшей разницы цен
			id = i; // Сохранение индекса текущей подписки

		}

	}

	// Вывод данных о подписке с наибольшей разницей цен
	cout << subscribtions[id]->number << ' ';
	cout << subscribtions[id]->name << ' ';
	cout << subscribtions[id]->club << ' ';
	cout << subscribtions[id]->start_time.hours << ':';
	cout << subscribtions[id]->start_time.minutes << ':';
	cout << subscribtions[id]->start_time.seconds << ' ';
	cout << subscribtions[id]->finish_time.hours << ':';
	cout << subscribtions[id]->finish_time.minutes << ':';
	cout << subscribtions[id]->finish_time.seconds << ' ';
	'\n';
	return value;
}