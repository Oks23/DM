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
vector<vector<int>> show_matrix_vec(vector< vector<int> >& vector) { /* ������� ��� ������ ������� */
	ifstream in("lab1.txt"); /* ���� ���� ������������� */
	if (in.is_open()) /* ���� ����� ���� ���� */
	{ /* ���� ��� ������ �������� ������� */
		string line;
		getline(in, line); /* ���������� ����� �������� */
		for (int i = 0; i < vector_size; i++)
			for (int j = 0; j < vector_size; j++)
				in >> vector[i][j];
		for (int i = 0; i < vector_size; i++)
		{
			for (int j = 0; j < vector_size; j++)
				cout << "\t" << vector[i][j];
			cout << "\n";
		}

		in.close(); /* ��������� ���� */
		return vector; /* ��������� ������� */
	}
	else /* ���� �� ������� ������ / ������� ���� */
	{
		cout << "\t�� ����, ��� �� ������� ������� ����, ����� ����� ���� �������.\n\n";
		exit(0);
	}
}

int min_tree_vec(vector< vector<int>>& vector) { /* �������� ����� */
	cout << "\n\t����� ���������� �������� ������ �� ���������� �����\n" << endl;
	// That would be the main change
	int vector_size = vector.size();
	int weight = 0; /* ���� */
	int no_edge = 0; /* ������������ */
	std::vector<int> selected(vector_size); /* ������ ������� */
	int x;
	int y;

	selected[0] = true;

	cout << "\t�����" << " : " << "���� �����";
	cout << endl;
	while (no_edge < vector_size - 1) { /* ���� ������������ ����� �� ������� ������ - 1 */
		int min = INF;
		x = 0;
		y = 0;

		for (int i = 0; i < vector_size; i++) {
			if (selected[i]) {
				for (int j = 0; j < vector_size; j++) {
					if (!selected[j] && vector[i][j]) {
						if (min > vector[i][j]) { /* ���������� �� �������� */
							min = vector[i][j];
							x = i;
							y = j;
						}
					}
				}
			}
		}
		cout << "\t" << x << " - " << y << " :  " << vector[x][y] << endl;
		weight += vector[x][y]; /* ������ ���� */
		selected[y] = true;
		no_edge++;
	}
	cout << "\n\t�������� ���� ���������� ������������ ������: " << weight << "\n" << endl;
	return 0;
}


void main()
{

	setlocale(LC_ALL, "Ukrainian"); /* ��������� ��������� ���� */
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "\n\tʳ������ ������: " << vector_size << endl; 
	cout << "\n\t������� ���: " << endl; 

	vector<int> row(vector_size, 0);
	// ���������� ������ 2D
	vector<vector<int>> vec(vector_size, row);
	show_matrix_vec(vec);
	min_tree_vec(vec);
	system("pause");
}

