#include <iostream>
#include <stdio.h>

using namespace std;

//Описание струтуры
struct point
{
	int key;
	point* next;
};


point* make_list()
{
	int n;
	cout << "Введите количество элементов в однонаправленном  списке: ";
	cin >> n;
	if (n <= 0)
	{
		return 0;
	}
	point* first;
	point* p, *r;
	first = new point;
	cout << "\n?";
	cin >> first->key;
	first->next = 0;

	p = first;
	for (int i = 0; i < n - 1; i++)
	{
		r = new point;
		cout << "\n?";
		cin >> r->key;
		r->next = 0;
		p->next = r;
		
		p = r;
	}
	return first;

}


void print_list(point* first)
{
	if (first == NULL)
	{
		cout << "Список пустой\n";
		return;
	}

	point*p = first;
	while (p != NULL)
	{
		cout << p->key << " ";
		p = p->next;
	}
	cout << "\n";
	return;
}


point* add_element_to_list(point* first)
{
	int k;
	cout << "Введите номер (нумерация с нуля) элемента для добавления в список: ";
	cin >> k;
	if (k < 0)
	{
		cout << "Номер элемента не может быть отрицательным\n";
		return first;
	}

	point* r = new point;  
	cout << "Введите значение ключевого поля нового элемента: ";
	cin >> r->key;
	if (k == 0)     
	{
		r->next = first;
		first = r;
		return first;
	}
	point* p = first;
	int num = 0;
	while (p != 0 && num < k - 1)  
	{
		p = p->next;
		num++;
	}
	if (p == 0)
		cout << "Операция не выполнена. В списке всего " << num << " элементов\n";
	else
	{
		
		r->next = p->next; 
		p->next = r;	
	}
	return first;
}


point* delete_element_from_list(point* first)
{
	int k;
	cout << "Введите номер (нумерация с нуля) элемента для удаления из списка: ";
	cin >> k;
	if (k < 0)
	{
		cout << "Номер элемента не может быть отрицательным\n";
		return first;
	}

	point* p = first;

	
	if (k == 0)
	{
		first = p->next;
		delete p;
		cout << "Элемент с номером: " << k << " удален\n";
		return first;
	}

	int num = 0;
	while (p && num < k - 1)  
	{
		p = p->next;
		num++;
	}
	if (p == 0)
	{
		cout << "Элемент с номером: " << k << " в списке отсутствует\n";
		return first;
	}
	point* r = p->next;
	
	p->next = r->next;
	delete r; 
	cout << "Элемент с номером: " << k << " удален\n";
	return first;
}


point* delete_linked_list(point* first)
{
	point* p = first;  
	while (p != 0)              
	{
		first = p->next;       
		delete p;            
		p = first;               
	}
	cout << "Однонаправленный список удален из памяти\n";
	return NULL;
}


void save_linked_list(const char* fname, point* first)
{
	FILE *f;    
	
	f = fopen(fname, "wb");
	int a;
	point* p = first;

	while (p != 0)
	{
		a = p->key;
		fwrite(&a, sizeof(a), 1, f);
		p = p->next;
	}
	fclose(f);
	cout << "Список сохранен в файл\n";
}


point* read_linked_list(const char* fname)
{
	FILE *f;    
	
	f = fopen(fname, "rb");
	if (f == 0)
		return 0;
	int a;

	point* first;
	point* p, *r;
	first = new point;
	fread(&a, sizeof(a), 1, f); 
	first->key = a;
	first->next = 0;
	 
	p = first;
	fread(&a, sizeof(a), 1, f); 
	while (!feof(f))
	{
		r = new point;
		r->key = a;
		r->next = 0;
		p->next = r;
		
		p = r;
		fread(&a, sizeof(a), 1, f); 
	}
	fclose(f); 
	cout << "Список прочитан из файла\n";
	return first;
}




int main()
{
	const char* fname = "list.dat";
	setlocale(LC_ALL, "");

	//1. Создание списка
	point* first = make_list();

	//2. Печать списка
	cout << "Созданный список:\n";
	print_list(first);

	//3. Удаление из списка элемента с заданным номером
	first = delete_element_from_list(first);

	cout << "Список после удаления элемента:\n";
	print_list(first);

	//4. Добавление в список элемента с заданным номером
	first = add_element_to_list(first);

	cout << "Список после добавления элемента:\n";
	print_list(first);

	//5. Запишем список в файл
	save_linked_list(fname, first);

	//6. Удалим список из памяти и напечатаем его
	first = delete_linked_list(first);
	cout << "Список после удаления его из памяти:\n";
	print_list(first);

	//7. Прочитаем список из файла и и напечатаем его
	first = read_linked_list(fname);
	cout << "Список после чтения его из файла:\n";
	print_list(first);

	//8. Удалим список из памяти
	first = delete_linked_list(first);

	return 0;

}
