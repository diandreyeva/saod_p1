// saod_p1.cpp: определяет точку входа для консольного приложения.


#include "stdafx.h"
#include <iostream>
#include <stdio.h> 
#include <time.h> 
#include <ctime>
#include <fstream>

using namespace std;

void radix(int *ar, int *br, int *cr, int sizeC, int sizeAB)
{
	int i, k, n;
	k = sizeC;
	n = sizeAB;
	for (i = 0; i <= k; i++)
		cr[i] = 0;
	for (i = 0; i < n; i++)
		cr[ar[i]] += 1;
	for (i = 1; i < k + 1; i++)
		cr[i] += cr[i - 1];
	for (i = n - 1; i >= 0; i--)
	{
		br[cr[ar[i]] - 1] = ar[i];
		cr[ar[i]] -= 1;

	}
}

void selection(int *ar, int size)
{
	//clock_t start = clock();
	int i, j, mx, nmx;

	for (i = 0; i < size - 1; i++)
	{
		mx = ar[i];
		nmx = i;
		for (j = i + 1; j < size; j++)
		{
			if (ar[j]<mx)
			{
				mx = ar[j];
				nmx = j;
			}
		}
		ar[nmx] = ar[i];
		ar[i] = mx;
	}
	/*clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("The time: %f seconds\n", seconds);
	for (int i = 0; i < 20; i++) {	cout << ar[i] << " ";}
	cout << endl;*/
}

int main()
{
	setlocale(LC_ALL, "rus");
	int* numbers;	    numbers = new int[100000]; // динамический массив, что отсортировать
	int* numbers_radix; numbers_radix = new int[100000]; //динамический массив, после сортировки radix
	int* numbers_additional; numbers_additional = new int[300]; // динамический массив для radix
	int num;


	ifstream fin("numdata.txt");
	if (!fin.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
	else
	{
		for (int i = 0; i < 100000; i++)
		{
			fin >> numbers[i]; // считали первое слово из файла
		}
		fin.close(); // закрываем файл

	}
	
	/*	srand(2);
		for (int i = 0; i < 1000000; i++)
		{
			num = rand() % 300; // случайные числа от 0 до 300
			numbers[i] = num;
		}*/
		
	clock_t start = clock();
	radix(numbers, numbers_radix, numbers_additional, 300, 100000);
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("The time: %f seconds\n", seconds);
	ofstream fout1("numradix.txt"); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
	for (int i = 0; i < 20; i++) 
	{
		fout1 << numbers_radix[i]; // запись строки в файл
	}
	fout1.close(); // закрываем файл

	/*for (int i = 0; i < 20; i++) { cout << numbers_radix[i] << " "; }
	cout << endl;*/

	start = clock();
	selection(numbers, 100000);
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("The time: %f seconds\n", seconds);
	ofstream fout2("numselection.txt"); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
	for (int i = 0; i < 20; i++)
	{
		fout2 << numbers[i]; // запись строки в файл
	}
	fout2.close(); // закрываем файл
	/*for (int i = 0; i < 20; i++) { cout << numbers[i] << " "; }
	cout << endl;*/

	delete[]numbers; delete[]numbers_radix; delete[]numbers_additional; //очистка всего на свете
	system("pause");
	return 0;
}


