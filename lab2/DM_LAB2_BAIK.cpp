#include <iostream>
#include <fstream>
#include<Windows.h>
#include <string>
#include <vector>
using namespace std;

#define K 100000


int read_first_line() {
	string line;
	ifstream filen("lab2.txt");
	if (filen.is_open())
	{
		getline(filen, line);
		filen.close();
		return stoi(line);
	}
}
int vector_size = read_first_line();


int show_matrix(int** matrix) {
	ifstream in("lab2.txt");
	if (in.is_open())
	{
		string line;
		getline(in, line);
		for (int i = 0; i < vector_size; i++)
			for (int j = 0; j < vector_size; j++)
				in >> matrix[i][j];

		for (int i = 0; i < vector_size; i++)
		{
			for (int j = 0; j < vector_size; j++)
				cout << "\t" << matrix[i][j];
			cout << "\n";
		}

		in.close();
		return **matrix;
	}
	else
	{
		cout << "\tНа жаль, мені не вдалося знайти файл, який було вказано.\n\n";
		exit(0);
	}
}

int sum_edges_vertexes(int** con_matr) {
	int sum = 0;
	for (int i = 0; i < vector_size; i++) {
		for (int j = 0; j < vector_size; j++) {
			sum += con_matr[i][j];
		}
	}
	return sum;
}

int euler(int** matr, int** con_matr_) {
	int** con_matrix = new int* [vector_size];

	for (int i = 0; i < vector_size; ++i) {
		con_matrix[i] = new int[vector_size];
	}

	for (int i = 0; i < vector_size; i++) {
		for (int j = 0; j < vector_size; j++) {
			con_matrix[i][j] = con_matr_[i][j];
		}
	}
	int p[K + 1];
	int p1;
	int p2;
	int s = 0;
	int k = sum_edges_vertexes(con_matrix) / 2;
	int weight = 0;

	p1 = 0;
	p2 = k + 1;
	p[p1] = s;

	while (p1 >= 0)
	{
		int i, v = p[p1];
		for (i = 0; i < vector_size; ) {
			if (con_matrix[v][i] != 0)
			{
				con_matrix[v][i] = con_matrix[v][i] - 1;
				con_matrix[i][v] = con_matrix[i][v] - 1;
				p[++p1] = i;
				v = i;
				i = 0;
			}
			else {
				i++;
			}
		}
		if (i >= vector_size) {
			p[--p2] = p[p1--];
		}
	}

	if (p2 > 0)
	{
		cout << "\tОтже, граф не є Ейлеровим" << endl;
	}
	else {
		cout << "\tРебро" << " : " << "Вага ребра\n";
		for (int i = 0; i < k; i++) {
			cout << "\t" << p[i] + 1 << " - " << p[i + 1] + 1 << " : " << matr[p[i]][p[i + 1]] << endl;
			weight += matr[p[i]][p[i + 1]];
		}
		cout << "\n\tЗагальна вага шляху становить: " << weight << endl << endl;
	}

	return 0;
}

int add_edges(int** con_matr, vector<int> vert_degr, int** matr) {
	for (int i = 0; i < vector_size; i++) {
		if (vert_degr[i] % 2 != 0) {
			for (int j = 0; j < vector_size; j++) {
				if (vert_degr[j] % 2 != 0 && con_matr[i][j] != 0) {
					con_matr[i][j] = con_matr[i][j] + 1;
				}
			}
		}
	}

	cout << "\n\tЗмiнена матриця зв'язностi: " << endl;
	for (int i = 0; i < vector_size; i++) {
		for (int j = 0; j < vector_size; j++) {
			cout << "\t" << con_matr[i][j];
		}
		cout << endl;
	}
	cout << endl;

	euler(matr, con_matr);

	return 0;
}


int connect_matrix(int** con_matr, int** matr) {
	cout << "\n\tМатриця зв'язностi має вигляд: " << endl;
	for (int i = 0; i < vector_size; i++) {
		for (int j = 0; j < vector_size; j++) {
			if (matr[i][j] > 0) {
				con_matr[i][j] = 1;
			}
			else {
				con_matr[i][j] = matr[i][j];
			}
			cout << "\t" << con_matr[i][j];
		}
		cout << endl;
	}

	return **con_matr;
}


int if_euler(int** con_matr, vector<int> vert_degr, int** matr) {
	for (int i = 0; i < vector_size; i++) {
		if (vert_degr[i] != 0) {
			add_edges(con_matr, vert_degr, matr);
			break;
		}
		else {
			euler(matr, con_matr);
		}
	}

	return 0;
}

int vertex_degree(int** con_matr, vector<int> vert_degr, int** matr) {
	cout << endl;

	for (int i = 0; i < vector_size; i++) {
		for (int j = 0; j < vector_size; j++) {
			vert_degr[i] += con_matr[i][j];
		}
		if (vert_degr[i] % 2 != 0)
		{
			cout << "\tВершина " << i + 1 << " - непарна \n";
		}
	}

	if_euler(con_matr, vert_degr, matr);

	return 0;
}


void main()
{

	setlocale(LC_ALL, "Ukrainian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int** matr = new int* [vector_size];
	int** con_matr = new int* [vector_size];
	vector<int> vert_degr(vector_size);

	for (int i = 0; i < vector_size; ++i) {
		matr[i] = new int[vector_size];
		con_matr[i] = new int[vector_size];
	}

	cout << "\tКiлькiсть вершин: " << vector_size << endl << "\n";
	cout << "\tМатриця ваг: " << endl;


	show_matrix(matr);
	connect_matrix(con_matr, matr);
	vertex_degree(con_matr, vert_degr, matr);

	system("pause");
}