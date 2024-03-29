#include <iostream>
#include <iomanip> 
#define SIZE 10
using namespace std;

class Matrix
{
private:
	int	a[SIZE][SIZE];
public:
	Matrix() {
		int b[SIZE][SIZE] = {
		{0, 5, 0, 2, 7, 2, 1, 0, 4, 3},
		{5, 0, 6, 4, 0, 3, 2, 9, 7, 0},
		{0, 6, 0, 3, 6, 2, 0, 0, 1, 5},
		{2, 4, 3, 0, 8, 3, 1, 1, 0, 2},
		{7, 0, 6, 8, 0, 2, 2, 7, 3, 0},
		{2, 3, 2, 3, 2, 0, 0, 1, 6, 8},
		{1, 2, 0, 1, 2, 0, 0, 2, 9, 5},
		{0, 9, 0, 1, 7, 1, 2, 0, 4, 1},
		{4, 7, 1, 0, 3, 6, 9, 4, 0, 8},
		{3, 0, 5, 2, 0, 8, 5, 1, 8, 0},
		};
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				a[i][j] = b[i][j];
	}
	void AddToMatrix(int _i, int _j, int _temp)
	{
		if (_i == _j) a[_i][_j] = 0;
		a[_i][_j] = _temp;
		a[_j][_i] = _temp;	
	}

	int GetFromMatrix(int _i, int _j)
	{
		return a[_i][_j];
	}

	int* ShortWay(int _start)
	{
		int d[SIZE]; // минимальное расстояние
		int v[SIZE]; // посещенные вершины
		int temp, minindex, min;
		int begin_index = 0;
		//Инициализация вершин и расстояний
		for (int i = 0; i < SIZE; i++)
		{
			d[i] = 10000;
			v[i] = 1;
		}
		d[_start-1] = 0;
		// Шаг алгоритма
		do {
			minindex = 10000;
			min = 10000;
			for (int i = 0; i < SIZE; i++)
			{ // Если вершину ещё не обошли и вес меньше min
				if ((v[i] == 1) && (d[i] < min))
				{ // Переприсваиваем значения
					min = d[i];
					minindex = i;
				}
			}
			// Добавляем найденный минимальный вес
			// к текущему весу вершины
			// и сравниваем с текущим минимальным весом вершины
			if (minindex != 10000)
			{
				for (int i = 0; i < SIZE; i++)
				{
					if (a[minindex][i] > 0) //проверка есть ли путь
					{
						temp = min + a[minindex][i];
						if (temp < d[i])
						{
							d[i] = temp;
						}
					}
				}
				v[minindex] = 0;
			}
		} while (minindex < 10000);
		return d;
	}
};

Matrix CreateMatrix(Matrix m)
{
	int temp = 0;
	for (int i = 0; i < SIZE; i++)
		for (int j = i + 1; j < SIZE; j++) 
		{
			cout << "Введите расстояние " << i + 1 << " - " << j + 1 << ": ";
			cin >> temp;
			m.AddToMatrix(i, j, temp);
		}
	return m;
}

void OutputMatrix(Matrix m)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			cout << setfill(' ') << setw(5) << m.GetFromMatrix(i, j);
		cout << endl;
	}
}

void PrintShortWays(int _start, int _end, Matrix m)
{
	for (int i = _start - 1; i < _end; i++)
	{
		int* arr = m.ShortWay(_start);
		cout << _start << " - " << i + 1 << ": " << arr[i] << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Matrix m;
	int choice = 0;
	cout << "Будете вводить собственную матрицу(1) или взять готовую(0)?: ";
	cin >> choice;
	if (choice == 1)
		m = CreateMatrix(m);
	OutputMatrix(m);
	int start, end;
	cout << "\nВведите начальную и конечную вершины: ";
	cin >> start >> end;
	PrintShortWays(start, end, m);
	return 0;
}