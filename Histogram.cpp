//7.	Створіть програму, що буде підраховувати частоти монограм (байтів) 
//в бінарному файлі. Який байт найчастіше зустрічається в текстовому файлі (*.txt)? 
//Виконуваному файлі (*.exe)? Для роботи з файлами використовуйте функції cstdio.

#include <stdlib.h> //Для очистки экрана
#include <iostream> //Для работы с клавиатурой
#include <fstream> //Для работы с файловыми потоками
#include <stdio.h>
using namespace std;

int main ()
{
	FILE * file;
	int i;
	char letter, a=0;
	int* histogram = new int[256];
	for (int i=0;i<256;i++)	histogram[i] = 0;

	file = fopen("1.txt", "rb");
	for(i=0; fscanf(file, "%c", &letter) != EOF; i++) histogram[letter]++;
	fclose(file);

	for (i=0; i<256; i++)
	{
		cout  << "\""<< a << "\"\t" << histogram[i] << endl;
		a++;
	}

	system("pause");
	return 0;
}

