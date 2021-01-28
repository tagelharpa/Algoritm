#include <iostream>
#include <ctime>
using namespace std;
//------------------------------------------------------------------
void out(int *a, int n, int k);
void vvod(int *a, int n);
void vstavka(int *a, int *b, int n, int k, int j);
//------------------------------------------------------------------
int main(int argc, char* argv[])
{
	setlocale(0, "");
	int *ar1, *ar2,
		i,
		n, k;
	cout << "Введите количество рядов в матрице: ";
	cin >> n;
	cout << "\nВведите количество столбцов в матрице: ";
	cin >> k;
	do {
		cout << "\nВведите номер столбца который нужно добавить в матрицу( <= " << k << ") : ";
		cin >> i;
	} while (i > k);
	_flushall();
	i--;
	srand(time(0));
	ar1 = new int[n*k];
	ar2 = new int[n*k + n];
	vvod(ar1, n*k);
	out(ar1, n, k);
	vstavka(ar1, ar2, n, k, i);
	out(ar2, n, k + 1);
	delete[]ar1;
	delete[]ar2;
	getchar();
	return 0;
}
//--------------------------------------------------------------------
void out(int *a, int n, int k) {
	int x = k;
	for (int i = 0; i < n*k; i++) {
		cout << a[i] << "   ";
		if (i == x - 1) {
			cout << endl;
			x += k;
		}
	}
	cout << "\n\n";
}
//--------------------------------------------------------------------
void vvod(int *a, int n) {
	for (int i = 0; i < n; i++)
		a[i] = rand() % 400 - 200;
}
//---------------------------------------------------------------------
void vstavka(int *a, int *b, int n, int k, int j) {
	int *buf,
		x = j,
		z = 0,
		l = 0,
		q;
	buf = new int[n - 1];
	for (int i = 0; i < n*k; i++)
		if (i = x) {
			buf[z++] = a[i];
			x += k;
		}
	x = j;
	q = 0;
	for (int i = 0; i < n*k + n; i++) {
		if ((i == x) && (l != z)) {
			b[i] = buf[l++];
			q++;
			x += (k + 1);
		}
		else
			b[i] = a[i - q];
	}
}