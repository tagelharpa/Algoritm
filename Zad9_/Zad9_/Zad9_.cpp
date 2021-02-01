#include <locale.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
using namespace std;

int formFile(const char*, int);
int printFile(const char*);
int copyFile(const char*, const char*);
int copyEvenLines(const char*, const char*);
int getFileSize(const char*);

const int MAXLINE = 255;

int main()
{
	int n;
	setlocale(2, "");
	printf("\t\tСтроковый ввод-вывод");
	//формирование записей в файле
	printf("\n\nВведите количество строк, которые необходимо записать в файл: ");
	scanf("%d", &n);
	if (!formFile("file1.txt", n))
	{
		printf("Ошибка при записи информации в файл");
		return 0;
	}

	printf("\n\nСодержимое текстового файла:\n");
	//выведем сформированные данные
	if (!printFile("file1.txt"))
	{
		printf("Ошибка при чтении информации из файла");
		return 0;
	}

	printf("\n\nСодержимое текстового файла file1.txt скопировано в file1_copy.txt\n");
	copyFile("file1.txt", "file1_copy.txt");

	printf("\n\nЧетные строки текстового файла file1.txt скопированы в file2.txt\n");
	copyEvenLines("file1.txt", "file2.txt");

	printf("\n\nСодержимое текстового файла file2.txt:\n");
	//выведем сформированные данные
	if (!printFile("file2.txt"))
	{
		printf("Ошибка при чтении информации из файла");
		return 0;
	}

	printf("\n\nРазмер текстового файла file1.txt %d байт\n", getFileSize("file1.txt"));
	printf("\n\nРазмер текстового файла file2.txt %d байт\n", getFileSize("file2.txt"));

	_getch();
	return 0;
}

//Запись n строк в файл
int formFile(const char* fname, int n)
{
	char buf[MAXLINE];
	FILE* pf;
	//открытие файла
	if ((pf = fopen(fname, "w")) == NULL)
	{
		perror("\nошибка при открытии файла");
		return 0;
	}
	printf("Введите построчно информацию для записи в файл:\n");
	//формирование записей в файле
	for (int i = 0; i < n; i++)
	{
		printf("%d: ", i + 1);
		getchar();
		gets_s(buf);
		fputs(buf, pf);
		fputs("\n", pf);
		if (ferror(pf))
		{
			perror("\nошибка при записи информации в файл");
			return 0; //при возникновении ошибки возвращается значение 0
		}
	}
	fclose(pf);
	return 1;
}

//Вывод содержимого файла на экран
int printFile(const char* fname)
{
	char buf[MAXLINE];
	FILE* pf;
	//считывание информации с файла
	if ((pf = fopen(fname, "r")) == NULL)
	{
		perror("\nошибка при открытии файла");
		return 0;
	}
	while (fgets(buf, MAXLINE, pf) != NULL)
		printf("%s", buf);

	fclose(pf);
	return 1;
}

//Копирование фала
int copyFile(const char* fname1, const char* fname2)
{
	char buf[MAXLINE];
	FILE* in;
	FILE* out;
	//считывание информации с файла
	if ((in = fopen(fname1, "r")) == NULL)
	{
		perror("\nошибка при открытии файла");
		return 0;
	}
	if ((out = fopen(fname2, "w")) == NULL)
	{
		perror("\nошибка при открытии файла");
		return 0;
	}
	while (fgets(buf, MAXLINE, in) != NULL)
		fputs(buf, out);

	fclose(in);
	fclose(out);
	return 1;
}

//Копирование четных строк из файла1 в файл2
int copyEvenLines(const char* fname1, const char* fname2)
{
	char buf[MAXLINE];
	FILE* in;
	FILE* out;
	//считывание информации с файла
	if ((in = fopen(fname1, "r")) == NULL)
	{
		perror("\nошибка при открытии файла");
		return 0;
	}
	if ((out = fopen(fname2, "w")) == NULL)
	{
		perror("\nошибка при открытии файла");
		return 0;
	}
	int i = 1;
	while (fgets(buf, MAXLINE, in) != NULL)
	{
		if (i % 2 == 0) //если номер строки четный, то записываем ей в файл2
			fputs(buf, out);
		i++;
	}

	fclose(in);
	fclose(out);
	return 1;
}

//Получение размера файла в байтах
int getFileSize(const char* fname)
{
	char buf[MAXLINE];
	FILE* pf;
	//считывание информации с файла
	if ((pf = fopen(fname, "r")) == NULL)
	{
		perror("\nошибка при открытии файла");
		return 0;
	}
	int fsize = 0; //Размер файла
	while (fgets(buf, MAXLINE, pf) != NULL)
		fsize += strlen(buf) + 1; //добавляется длина прочитанной из файла строки + 1 дополнительный байт так как в файл кроме /n записывается еще /r

	fclose(pf);
	return fsize;  //Сумма длин всех строк в файле и есть его размер в байтах
}
