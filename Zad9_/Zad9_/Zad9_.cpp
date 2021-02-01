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
	printf("\t\t��������� ����-�����");
	//������������ ������� � �����
	printf("\n\n������� ���������� �����, ������� ���������� �������� � ����: ");
	scanf("%d", &n);
	if (!formFile("file1.txt", n))
	{
		printf("������ ��� ������ ���������� � ����");
		return 0;
	}

	printf("\n\n���������� ���������� �����:\n");
	//������� �������������� ������
	if (!printFile("file1.txt"))
	{
		printf("������ ��� ������ ���������� �� �����");
		return 0;
	}

	printf("\n\n���������� ���������� ����� file1.txt ����������� � file1_copy.txt\n");
	copyFile("file1.txt", "file1_copy.txt");

	printf("\n\n������ ������ ���������� ����� file1.txt ����������� � file2.txt\n");
	copyEvenLines("file1.txt", "file2.txt");

	printf("\n\n���������� ���������� ����� file2.txt:\n");
	//������� �������������� ������
	if (!printFile("file2.txt"))
	{
		printf("������ ��� ������ ���������� �� �����");
		return 0;
	}

	printf("\n\n������ ���������� ����� file1.txt %d ����\n", getFileSize("file1.txt"));
	printf("\n\n������ ���������� ����� file2.txt %d ����\n", getFileSize("file2.txt"));

	_getch();
	return 0;
}

//������ n ����� � ����
int formFile(const char* fname, int n)
{
	char buf[MAXLINE];
	FILE* pf;
	//�������� �����
	if ((pf = fopen(fname, "w")) == NULL)
	{
		perror("\n������ ��� �������� �����");
		return 0;
	}
	printf("������� ��������� ���������� ��� ������ � ����:\n");
	//������������ ������� � �����
	for (int i = 0; i < n; i++)
	{
		printf("%d: ", i + 1);
		getchar();
		gets_s(buf);
		fputs(buf, pf);
		fputs("\n", pf);
		if (ferror(pf))
		{
			perror("\n������ ��� ������ ���������� � ����");
			return 0; //��� ������������� ������ ������������ �������� 0
		}
	}
	fclose(pf);
	return 1;
}

//����� ����������� ����� �� �����
int printFile(const char* fname)
{
	char buf[MAXLINE];
	FILE* pf;
	//���������� ���������� � �����
	if ((pf = fopen(fname, "r")) == NULL)
	{
		perror("\n������ ��� �������� �����");
		return 0;
	}
	while (fgets(buf, MAXLINE, pf) != NULL)
		printf("%s", buf);

	fclose(pf);
	return 1;
}

//����������� ����
int copyFile(const char* fname1, const char* fname2)
{
	char buf[MAXLINE];
	FILE* in;
	FILE* out;
	//���������� ���������� � �����
	if ((in = fopen(fname1, "r")) == NULL)
	{
		perror("\n������ ��� �������� �����");
		return 0;
	}
	if ((out = fopen(fname2, "w")) == NULL)
	{
		perror("\n������ ��� �������� �����");
		return 0;
	}
	while (fgets(buf, MAXLINE, in) != NULL)
		fputs(buf, out);

	fclose(in);
	fclose(out);
	return 1;
}

//����������� ������ ����� �� �����1 � ����2
int copyEvenLines(const char* fname1, const char* fname2)
{
	char buf[MAXLINE];
	FILE* in;
	FILE* out;
	//���������� ���������� � �����
	if ((in = fopen(fname1, "r")) == NULL)
	{
		perror("\n������ ��� �������� �����");
		return 0;
	}
	if ((out = fopen(fname2, "w")) == NULL)
	{
		perror("\n������ ��� �������� �����");
		return 0;
	}
	int i = 1;
	while (fgets(buf, MAXLINE, in) != NULL)
	{
		if (i % 2 == 0) //���� ����� ������ ������, �� ���������� �� � ����2
			fputs(buf, out);
		i++;
	}

	fclose(in);
	fclose(out);
	return 1;
}

//��������� ������� ����� � ������
int getFileSize(const char* fname)
{
	char buf[MAXLINE];
	FILE* pf;
	//���������� ���������� � �����
	if ((pf = fopen(fname, "r")) == NULL)
	{
		perror("\n������ ��� �������� �����");
		return 0;
	}
	int fsize = 0; //������ �����
	while (fgets(buf, MAXLINE, pf) != NULL)
		fsize += strlen(buf) + 1; //����������� ����� ����������� �� ����� ������ + 1 �������������� ���� ��� ��� � ���� ����� /n ������������ ��� /r

	fclose(pf);
	return fsize;  //����� ���� ���� ����� � ����� � ���� ��� ������ � ������
}
