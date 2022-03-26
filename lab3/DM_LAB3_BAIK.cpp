#include <iostream>
#include <fstream>
#include<Windows.h>
#include <string>

using namespace std;

int read_first_line() {
	string line;
	ifstream filen("lab3.txt");
	if (filen.is_open())
	{
		getline(filen, line);
		filen.close();
		return stoi(line);
	}
}
int vector_size = read_first_line();

int show_matrix(int** matrix) {
	ifstream in("lab3.txt");
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
		cout << "\t�� ����, ��� �� ������� ������ ����, ���� ���� �������.";
		exit(0);
	}
}

int connect_matrix(int** con_matrix, int** matrix) {
	cout << "\n\t������� ��'������i �� ������: " << endl;
	for (int i = 0; i < vector_size; i++) {
		for (int j = 0; j < vector_size; j++) {
			if (matrix[i][j] > 0) {
				con_matrix[i][j] = 1;
			}
			else {
				con_matrix[i][j] = matrix[i][j];
			}
			cout << "\t" << con_matrix[i][j];
		}
		cout << endl;
	}

	return **con_matrix;
}

int hamilton(int k, int** con_matrix, int* c, int* path, int v0)
{
	int v, q1 = 0, k1;
	for (v = 0; v < vector_size && !q1; v++)
	{
		if (con_matrix[v][path[k - 1]] || con_matrix[path[k - 1]][v])
		{
			if (k == vector_size && v == v0) {
				q1 = 1;
			}
			else if (c[v] == -1)
			{
				c[v] = k; path[k] = v;
				k1 = k + 1;
				q1 = hamilton(k1, con_matrix, c, path, v0);
				if (!q1) c[v] = -1;
			}
			else continue;
		}
	}   return q1;
}

int if_hamilton(int** con_matrix, int* c, int* path, int v0) {
	cout << "\n\t���i�����i� ����:\n";
	for (int j = 0; j < vector_size; j++) {
		c[j] = -1;
	}
	path[0] = v0;
	c[v0] = v0;

	if (hamilton(1, con_matrix, c, path, v0)) {}
	else {
		cout << "\t�� ���, ��� �� ������� ������ ������\n";
	}
	return *path;
}

int result(int** matrix, int* path) {
	int weight = 0;
	cout << "\t�����" << " : " << "����\n";
	for (int i = 0; i < vector_size; i++) {
		if (i == vector_size - 1) {
			cout << "\t" << path[i] + 1 << " - " << path[0] + 1 << " : " << matrix[path[i]][path[0]] << endl;
			weight += matrix[path[i]][path[0]];
		}
		else {
			cout << "\t" << path[i] + 1 << " - " << path[i + 1] + 1 << " : " << matrix[path[i]][path[i + 1]] << endl;
			weight += matrix[path[i]][path[i + 1]];
		}
	}
	cout << "\n\t�������� ���� �����: " << weight << endl << endl;
	return  0;
}


void main()
{
	setlocale(LC_ALL, "Ukrainian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int** matr = new int* [vector_size];
	int** con_matr = new int* [vector_size];

	for (int i = 0; i < vector_size; ++i) {
		matr[i] = new int[vector_size];
		con_matr[i] = new int[vector_size];
	}

	int* c = new int[vector_size];
	int* path = new int[vector_size];;
	int v0 = 0;

	cout << "\n\t�i���i��� ������: " << vector_size << endl;
	cout << "\n\t������� ���: " << endl;
	show_matrix(matr);
	connect_matrix(con_matr, matr);

	if_hamilton(con_matr, c, path, v0);
	result(matr, path);

	system("pause");
}