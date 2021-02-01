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
	printf("\t\t�������� ����-�����");
	int k, m = 0, q = -1, u = 1;
	char temp[35];
	//������������ ������� � �����
	printf("\n\n������� ���������� ������������, � ������� �� ������ ������ �������� (<20): ");
	scanf("%d", &k);
	if (!form(k))
	{
		printf("������ ��� ������ ���������� � ����");
		return 0;
	}

	//������� �������������� ������
	if (!output(k))
	{
		printf("������ ��� ������ ���������� �� �����");
		return 0;
	}
	// ������� �������, ����� �������� � ����������.
	printf("\n�������� �������, ������� ��������� �������: ");
	scanf("%d", &m);
	if (!del(m, k))
	{
		printf("������ ��� �������� ������ �� �����");
		return 0;
	}
	k--;

	printf("\n���������� ����� ����� �������� �������� � �������� �������:\n");
	if (!output(k))
	{
		printf("������ ��� ������ ���������� �� �����");
		return 0;
	}

	//��������� ������� ����� ��������� �������
	printf("������� �������, ����� ������� ����� ������ ����� ��������: ");
	scanf("%s", temp);          //temp-��������� �������
	if (!add(temp, k))
	{
		printf("������ ��� ���������� ���������� � ����");
		return 0;
	}
	k++;

	printf("\n���������� ����� ����� ���������� ����� ������:\n");
	if (!output(k))
	{
		printf("������ ��� ������ ���������� �� �����");
		return 0;
	}
	_getch();
	return 0;
}

int form(int k)
{
	//�������� �����
	if ((pf = fopen(fname, "wb")) == NULL)
	{
		perror("\n������ ��� �������� �����");
		return 0;
	}
	//������������ ������� � �����
	printf("\n������� �������� � %d ������������:\n", k);
	for (int i = 0; i < k; i++)
	{
		printf("������� ���: ");
		getchar();                  //������� ������� ����� �� ������� \n
		gets_s(a.fio);              //������������ � VS ������ gets
		printf("������� ��� ��������: ");
		scanf("%d", &a.b_year);
		printf("������� ��� ������ �� �������: ");
		scanf("%d %d %d", &a.ocenki[0], &a.ocenki[1], &a.ocenki[2]);
		printf("������� ������� ��� ���������: ");
		scanf("%f", &a.sr_bal);
		printf("\n");
		fwrite(&a, sizeof(abiturient), 1, pf);
		if (ferror(pf))
		{
			perror("\n������ ��� ������ ���������� � ����");
			return 0; //��� ������������� ������ ������������ �������� 0
		}
	}
	fclose(pf);
	return 1;
}

int output(int k)
{
	//���������� ���������� � �����
	if ((pf = fopen(fname, "rb")) == NULL)
	{
		perror("\n������ ��� �������� �����");
		return 0;
	}
	int j = 0;
	while (!feof(pf) && j < k)
	{
		fread(&Arr[j], sizeof(abiturient), 1, pf);
		j++;
	}
	fclose(pf);

	printf("\n������ �� ������������\n");
	for (int i = 0; i < k; i++)
	{
		printf("���: %s", Arr[i].fio);
		printf("\n");
		printf("��� ��������: %d", Arr[i].b_year);
		printf("\n");
		printf("������ �� �������: %d, %d, %d", Arr[i].ocenki[0], Arr[i].ocenki[1], Arr[i].ocenki[2]);
		printf("\n");
		printf("������� ��� ���������: %f", Arr[i].sr_bal);
		printf("\n\n");
	}
	return 1;
}
// �������� ������ � ������� k �� �����
int del(int m, int k)
{
	//���������� ���������� � ����� � ���������� � �� ��������� ����, ����� ������ � ������� m
	if ((pf = fopen(fname, "rb")) == NULL)
	{
		perror("\n������ ��� �������� �����");
		return 0;
	}

	if ((pf2 = fopen("temp.dat", "wb")) == NULL)
	{
		perror("\n������ ��� �������� �����");
		return 0;
	}

	int j = 0;
	while (!feof(pf) && j < k)
	{
		fread(&a, sizeof(abiturient), 1, pf); //������ ��������� �� �����
		if (j != m)
		{
			fwrite(&a, sizeof(abiturient), 1, pf2); //���������� ��������� �� ��������� ����
			if (ferror(pf2))
			{
				perror("\n������ ��� ������ ���������� � ����");
				return 0;
			}

		}
		j++;
	}
	fclose(pf);
	fclose(pf2);

	remove(fname);//������� �������� ����
	rename("temp.dat", fname);//��������������� ��������� ����
	return 1;
}
//�������� � �������� ��������
int add(char* fio, int k)
{
	abiturient b;
	char name[30];

	printf("\n������� �������� �� �����������:\n");
	printf("������� ���: ");
	getchar();                                        //������� ������� ����� �� ������� \n
	gets_s(b.fio);                                    //������������ � VS ������ gets
	printf("������� ��� ��������: ");
	scanf("%d", &b.b_year);
	printf("������� ��� ������ �� �������: ");
	scanf("%d %d %d", &b.ocenki[0], &b.ocenki[1], &b.ocenki[2]);
	printf("������� ������� ��� ���������: ");
	scanf("%f", &b.sr_bal);

	//���������� ���������� � ����� � ���������� � �� ��������� ����, ������� ����� ������ ����� ��������� �������
	if ((pf = fopen(fname, "rb")) == NULL)
	{
		perror("\n������ ��� �������� �����");
		return 0;
	}

	if ((pf2 = fopen("temp.dat", "wb")) == NULL)
	{
		perror("\n������ ��� �������� �����");
		return 0;
	}
	int j = 0;
	while (!feof(pf) && j < k)
	{
		fread(&a, sizeof(abiturient), 1, pf); //������ ��������� �� �����
		fwrite(&a, sizeof(abiturient), 1, pf2); //���������� ��������� �� ��������� ����
		if (ferror(pf2))
		{
			perror("\n������ ��� ������ ���������� � ����");
			return 0;
		}
		//��������� ������� � ����������� ������ �� ���������� � ��������
		sscanf(a.fio, "%s", name);
		if (strcmp(name, fio) == 0)
		{
			fwrite(&b, sizeof(abiturient), 1, pf2); //���������� ����� ��������� �� ��������� ����
			if (ferror(pf2))
			{
				perror("\n������ ��� ������ ���������� � ����");
				return 0;
			}
		}
		j++;
	}
	fclose(pf);
	fclose(pf2);

	remove(fname);//������� �������� ����
	rename("temp.dat", fname);//��������������� ��������� ����
	return 1;
}

