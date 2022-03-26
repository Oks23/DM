#include <memory.h>
#include <iostream>
#include <fstream>
#include<Windows.h>
#include <string>
#include <stack>
#include <vector>

using namespace std;

const int MAX_E = (int)10000;
const int MAX_V = (int)1000;
const int INF = (int)1000000;

int firstVert[MAX_V], visited[MAX_V];
int edgeCount = 0, capacity[MAX_E], onEnd[MAX_E], nextEdge[MAX_E];

int read_first_line() {
	string line;
	ifstream filen("lab4.txt");
	if (filen.is_open())
	{
		getline(filen, line);
		filen.close();
		return stoi(line);
	}
}
int vector_size = read_first_line();
vector<vector<int>> show_matrix_vec(vector< vector<int> >& vector) { /* ??????? ??? ?????? ??????? */
	ifstream in("lab4.txt"); /* ???? ???? ?????????????? */
	if (in.is_open()) /* ???? ????? ???? ????? */
	{ /* ???? ??? ?????? ????????? ??????? */
		string line;
		getline(in, line); /* ??????????? ????? ???????? */
		for (int i = 0; i < vector_size; i++)
			for (int j = 0; j < vector_size; j++)
				in >> vector[i][j];
		for (int i = 0; i < vector_size; i++)
		{
			for (int j = 0; j < vector_size; j++)
				cout << "\t" << vector[i][j];
			cout << "\n";
		}

		in.close(); /* ?????????? ???? */
		return vector; /* ?????????? ??????? */
	}
	else /* ???? ?? ??????? ?????? / ???????? ???? */
	{
		cout << "\tНа жаль, мені не вдалося знайти файл, який було вказано.\n\n";
		exit(0);
	}
}
int one_way_or_another(vector< vector<int>>& vec, int* min, int* way) {
	int v = 1;
	int u, i = 0;
	stack <int> plan;
	plan.push(--v);

	vec[v][v] = 1;
	int counter = 1;
	do {
		way[i] = v;
		plan.pop();
		for (u = 0; u < vector_size; u++) {
			if (vec[v][u] > 0 && !vec[u][u]) {
				i++;
				if (u == vector_size) {
					break;
				}
				if (vec[v][vector_size - 1] != 0) {
					u = vector_size - 1;
					plan.push(u);
					vec[u][u] = 1;
					cout << "\t" << v + 1 << ", " << u + 1 << " - " << vec[v][u] << endl;
					min[u] = vec[v][u];
					way[i] = u;
				}
				else {
					plan.push(u);
					vec[u][u] = 1;
					counter++;
					cout << "\t" << v + 1 << ", " << u + 1 << " - " << vec[v][u] << endl;
					min[u] = vec[v][u];
					v = u;
					way[i] = v;
				}
			}
		}
	} while (false);
	return *min, * way;
}

int look_for_flow(vector< vector<int>>& vec) {
	int vector_size = read_first_line();

	int* min = new int[vector_size];
	int* way = new int[vector_size];

	int minim, max = 0;
	int w;
	bool flag;

	do {
		w = 0;
		minim = INF;
		flag = false;
		cout << "\tШлях: \n";
		one_way_or_another(vec, min, way);

		for (int i = 0; i < vector_size; i++) {
			if (minim >= min[i] && min[i] > 0) {
				minim = min[i];
			}
		}
		cout << "\tМiнiмум шляху - " << minim << endl;

		for (int i = 0; i < vector_size; i++) {
			for (int j = 0; j < vector_size; j++) {
				if (vec[i][i] != 0) {
					if (i != vector_size - 1) {
						vec[i][i] = 0;
						vec[way[w]][way[w + 1]] = vec[way[w]][way[w + 1]] - minim;
						w++;
					}
					else {
						vec[i][i] = 0;
					}
				}
			}
		}

		for (int i = 0; i < vector_size; i++) {
			if (way[i] == vector_size - 1) {
				flag = true;
				cout << "\t + Додаємо шлях до суми" << endl;
			}
		}

		cout << "_________________________________________________________________\n";

		if (flag == true) {
			max += minim;
			for (int i = 0; i < vector_size; i++) {
				way[i] = 0;
			}
		}
		else {
			cout << "\n\tМiнiмальний розрiз мережi: ";
			for (int i = 0; i < vector_size; i++) {
				if (way[i] >= 0 && way[i + 1] > 0) {
					cout << way[i] + 1 << ", " << way[i + 1] + 1 << endl;
				}
			}
		}


	} while (flag == true);

	cout << "\tМаксимальний потiк - " << max << endl << endl;
	return 0;
}

void main()
{
	setlocale(LC_ALL, "Ukrainian"); /* підключаємо українську мову */
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "\tКiлькiсть вершин: " << vector_size << "\n" << endl;
	cout << "\tМатриця ваг: " << endl;
	vector<int> row(vector_size, 0);
	vector<vector<int>> vec(vector_size, row);
	show_matrix_vec(vec);
	cout << "_________________________________________________________________\n";
	look_for_flow(vec);


	system("pause");
}