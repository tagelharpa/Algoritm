#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
using namespace std;

struct abiturient
{
	char fio[50];
	int b_year;
	int ocenki[3];
	float sr_bal;
};

FILE *pf, *pf2;
abiturient a, Arr[20];
const char* fname = "f.dat";

int form(int);
int del(int, int);
int add(char*, int);
int output(int);

int main()
{
	setlocale(2, "");
	printf("\t\tБлоковый ввод-вывод");
	int k, m = 0, q = -1, u = 1;
	char temp[35];
	//формирование записей в файле
	printf("\n\nВведите количество абитуриентов, о которых вы хотите внести сведения (<20): ");
	scanf("%d", &k);
	if (!form(k))
	{
		printf("Ошибка при записи информации в файл");
		return 0;
	}

	//выведем сформированные данные
	if (!output(k))
	{
		printf("Ошибка при чтении информации из файла");
		return 0;
	}
	// удалить элемент, номер вводится с клавиатуры.
	printf("\nвыберите элемент, который требуется удалить: ");
	scanf("%d", &m);
	if (!del(m, k))
	{
		printf("Ошибка при удалении записи из файла");
		return 0;
	}
	k--;

	printf("\nСодержимое файла после удаление элемента с заданным номером:\n");
	if (!output(k))
	{
		printf("Ошибка при чтении информации из файла");
		return 0;
	}

	//добавляем элемент после указанной фамилии
	printf("Укажите фамилию, после которой нужно внести новые сведения: ");
	scanf("%s", temp);          //temp-введенная фамилия
	if (!add(temp, k))
	{
		printf("Ошибка при добавлении информации в файл");
		return 0;
	}
	k++;

	printf("\nСодержимое файла после добавление новой записи:\n");
	if (!output(k))
	{
		printf("Ошибка при чтении информации из файла");
		return 0;
	}
	_getch();
	return 0;
}

int form(int k)
{
	//открытие файла
	if ((pf = fopen(fname, "wb")) == NULL)
	{
		perror("\nошибка при открытии файла");
		return 0;
	}
	//формирование записей в файле
	printf("\nВведите сведения о %d абитуриентах:\n", k);
	for (int i = 0; i < k; i++)
	{
		printf("Введите ФИО: ");
		getchar();                  //Очищаем входной буфер от символа \n
		gets_s(a.fio);              //Используется в VS вместо gets
		printf("Введите год рождения: ");
		scanf("%d", &a.b_year);
		printf("Введите три оценки за экзамен: ");
		scanf("%d %d %d", &a.ocenki[0], &a.ocenki[1], &a.ocenki[2]);
		printf("Введите средний бал аттестата: ");
		scanf("%f", &a.sr_bal);
		printf("\n");
		fwrite(&a, sizeof(abiturient), 1, pf);
		if (ferror(pf))
		{
			perror("\nошибка при записи информации в файл");
			return 0; //при возникновении ошибки возвращается значение 0
		}
	}
	fclose(pf);
	return 1;
}

int output(int k)
{
	//считывание информации с файла
	if ((pf = fopen(fname, "rb")) == NULL)
	{
		perror("\nошибка при открытии файла");
		return 0;
	}
	int j = 0;
	while (!feof(pf) && j < k)
	{
		fread(&Arr[j], sizeof(abiturient), 1, pf);
		j++;
	}
	fclose(pf);

	printf("\nДанные об абитуриентах\n");
	for (int i = 0; i < k; i++)
	{
		printf("ФИО: %s", Arr[i].fio);
		printf("\n");
		printf("Год рождения: %d", Arr[i].b_year);
		printf("\n");
		printf("Оценка за экзамен: %d, %d, %d", Arr[i].ocenki[0], Arr[i].ocenki[1], Arr[i].ocenki[2]);
		printf("\n");
		printf("Средний бал аттестата: %f", Arr[i].sr_bal);
		printf("\n\n");
	}
	return 1;
}
// Удаление записи с номером k из файла
int del(int m, int k)
{
	//считывание информации с файла и записываем её во временный файл, кроме записи с номером m
	if ((pf = fopen(fname, "rb")) == NULL)
	{
		perror("\nошибка при открытии файла");
		return 0;
	}

	if ((pf2 = fopen("temp.dat", "wb")) == NULL)
	{
		perror("\nошибка при открытии файла");
		return 0;
	}

	int j = 0;
	while (!feof(pf) && j < k)
	{
		fread(&a, sizeof(abiturient), 1, pf); //Читаем структуру из файла
		if (j != m)
		{
			fwrite(&a, sizeof(abiturient), 1, pf2); //Записываем структуру во временный файл
			if (ferror(pf2))
			{
				perror("\nошибка при записи информации в файл");
				return 0;
			}

		}
		j++;
	}
	fclose(pf);
	fclose(pf2);

	remove(fname);//удаляем исходный файл
	rename("temp.dat", fname);//переименовываем временный файл
	return 1;
}
//добавить с указаной фамилией
int add(char* fio, int k)
{
	abiturient b;
	char name[30];

	printf("\nВведите сведения об абитуриенте:\n");
	printf("Введите ФИО: ");
	getchar();                                        //Очищаем входной буфер от символа \n
	gets_s(b.fio);                                    //Используется в VS вместо gets
	printf("Введите год рождения: ");
	scanf("%d", &b.b_year);
	printf("Введите три оценки за экзамен: ");
	scanf("%d %d %d", &b.ocenki[0], &b.ocenki[1], &b.ocenki[2]);
	printf("Введите средний бал аттестата: ");
	scanf("%f", &b.sr_bal);

	//считывание информации с файла и записываем её во временный файл, добавив новую запись после введенной фамилии
	if ((pf = fopen(fname, "rb")) == NULL)
	{
		perror("\nошибка при открытии файла");
		return 0;
	}

	if ((pf2 = fopen("temp.dat", "wb")) == NULL)
	{
		perror("\nошибка при открытии файла");
		return 0;
	}
	int j = 0;
	while (!feof(pf) && j < k)
	{
		fread(&a, sizeof(abiturient), 1, pf); //Читаем структуру из файла
		fwrite(&a, sizeof(abiturient), 1, pf2); //Записываем структуру во временный файл
		if (ferror(pf2))
		{
			perror("\nошибка при записи информации в файл");
			return 0;
		}
		//Проверяем фамилию в прочитанной записи на совпадение с заданной
		sscanf(a.fio, "%s", name);
		if (strcmp(name, fio) == 0)
		{
			fwrite(&b, sizeof(abiturient), 1, pf2); //Записываем новую структуру во временный файл
			if (ferror(pf2))
			{
				perror("\nошибка при записи информации в файл");
				return 0;
			}
		}
		j++;
	}
	fclose(pf);
	fclose(pf2);

	remove(fname);//удаляем исходный файл
	rename("temp.dat", fname);//переименовываем временный файл
	return 1;
}

