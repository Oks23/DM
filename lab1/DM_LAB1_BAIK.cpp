#include <iostream>
#include <fstream>
#include<Windows.h>
#include <string>
#include <vector>
using namespace std;

#define INF 99999
int read_first_line() {
	string line;
	ifstream filen("lab1.txt");
	if (filen.is_open())
	{
		getline(filen, line);
		filen.close();
		return stoi(line);
	}
}
int vector_size = read_first_line();
vector<vector<int>> show_matrix_vec(vector< vector<int> >& vector) { /* функція для виводу матриці */
	ifstream in("lab1.txt"); /* файл який використовуємо */
	if (in.is_open()) /* якщо такий файл існує */
	{ /* цикл для виводу елементів матриці */
		string line;
		getline(in, line); /* пропускаємо перше значення */
		for (int i = 0; i < vector_size; i++)
			for (int j = 0; j < vector_size; j++)
				in >> vector[i][j];
		for (int i = 0; i < vector_size; i++)
		{
			for (int j = 0; j < vector_size; j++)
				cout << "\t" << vector[i][j];
			cout << "\n";
		}

		in.close(); /* закриваємо файл */
		return vector; /* повертаємо матрицю */
	}
	else /* якщо не вдалося знайти / відкрити файл */
	{
		cout << "\tНа жаль, мені не вдалося відкрити файл, назву якого було вказано.\n\n";
		exit(0);
	}
}

int min_tree_vec(vector< vector<int>>& vector) { /* алгоритм Прима */
	cout << "\n\tПошук мінімального остового дерева за алгоритмом Прима\n" << endl;
	// That would be the main change
	int vector_size = vector.size();
	int weight = 0; /* вага */
	int no_edge = 0; /* інцидентність */
	std::vector<int> selected(vector_size); /* обрана вершина */
	int x;
	int y;

	selected[0] = true;

	cout << "\tРебро" << " : " << "Вага ребра";
	cout << endl;
	while (no_edge < vector_size - 1) { /* якщо інцидентність менша за кількість вершин - 1 */
		int min = INF;
		x = 0;
		y = 0;

		for (int i = 0; i < vector_size; i++) {
			if (selected[i]) {
				for (int j = 0; j < vector_size; j++) {
					if (!selected[j] && vector[i][j]) {
						if (min > vector[i][j]) { /* перевіряємо чи мінімальне */
							min = vector[i][j];
							x = i;
							y = j;
						}
					}
				}
			}
		}
		cout << "\t" << x << " - " << y << " :  " << vector[x][y] << endl;
		weight += vector[x][y]; /* додаємо вагу */
		selected[y] = true;
		no_edge++;
	}
	cout << "\n\tЗагальна вага мінімального покриваючого дерева: " << weight << "\n" << endl;
	return 0;
}


void main()
{

	setlocale(LC_ALL, "Ukrainian"); /* підключаємо українську мову */
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "\n\tКількість вершин: " << vector_size << endl; 
	cout << "\n\tМатриця ваг: " << endl; 

	vector<int> row(vector_size, 0);
	// ініціалізуємо вектор 2D
	vector<vector<int>> vec(vector_size, row);
	show_matrix_vec(vec);
	min_tree_vec(vec);
	system("pause");
}

