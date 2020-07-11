#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

void sortAscendingRows(int** massiv, int N, int SubmatrixCount, int PassesCount) {
	for (int k = 0; k < PassesCount; k++) {
		for (int j = 0, a = 0, b = 0, c = 0, d = 0, B = 0, C = 0; j < N; j += 2) {
			for (int i = 0; i < N; i += 2) {
				C = massiv[i][j] + massiv[i][j + 1] + massiv[i + 1][j] + massiv[i + 1][j + 1];
				if (C < B) {
					a = massiv[i][j];  b = massiv[i][j + 1]; c = massiv[i + 1][j]; d = massiv[i + 1][j + 1];

					massiv[i][j] = massiv[i - 2][j];
					massiv[i][j + 1] = massiv[i - 2][j + 1];
					massiv[i + 1][j] = massiv[i - 1][j];
					massiv[i + 1][j + 1] = massiv[i - 1][j + 1];

					massiv[i - 2][j] = a;
					massiv[i - 2][j + 1] = b;
					massiv[i - 1][j] = c;
					massiv[i - 1][j + 1] = d;
				}
				B = C;
			}
			B = 0, C = 0;
		}
	}
}

void sortAscendingColumns(int** massiv, int N, int SubmatrixCount, int PassesCount) {
	for (int k = 0; k < PassesCount; k++) {
		for (int i = 0, a = 0, b = 0, c = 0, d = 0, B = 0, C = 0; i < N; i += 2) {
			for (int j = 0; j < N; j += 2) {
				C = massiv[i][j] + massiv[i][j + 1] + massiv[i + 1][j] + massiv[i + 1][j + 1];
				if (C < B) {
					a = massiv[i][j];  b = massiv[i][j + 1]; c = massiv[i + 1][j]; d = massiv[i + 1][j + 1];

					massiv[i][j] = massiv[i][j - 2];
					massiv[i][j + 1] = massiv[i][j - 1];
					massiv[i + 1][j] = massiv[i + 1][j - 2];
					massiv[i + 1][j + 1] = massiv[i + 1][j - 1];

					massiv[i][j - 2] = a;
					massiv[i][j - 1] = b;
					massiv[i + 1][j - 2] = c;
					massiv[i + 1][j - 1] = d;
				}
				B = C;
			}
			B = 0, C = 0;
		}
	}
}

int main() {
	setlocale(LC_ALL, "Rus");
	srand((unsigned int)time(NULL));
	fstream fs; string path;
	char ch;  bool flag = 0;
	do
	{
		system("cls");
		cout << "/* Ввести с клавиатуры целочисленную матрицу А размером NxN (N-четно). <X> матриц записать в исходный файл. \nСчитая матрицу составленной из К квадратов (подматриц) размером 2х2, преобразовать матрицу следующим образом. \nДля любых двух квадратов В и С должны выполняться следующие условия: \nEсли сумма элементов В меньше суммы элементов С, то В лежит либо выше, либо левее \n(когда В и С на одной горизонтали) квадрата С. \nВ результирующий файл вынести исходные матрицы и полученные после перестановки. \\*\n\n\n";
		cout << "Выберите опцию:\n[1] Использовать результирующий файл по умолчанию.\n(Нужно, чтобы текстовый файл с названием MyFile.txt находился в одной директории с .exe файлом программы)\n[2] Использовать свой результирующий файл\n[3] Выход\n=>";
		cin >> ch;
		switch (ch)
		{
		case '1': {
			cin.get();
			system("cls");
			if (path.empty()) {
				path = "MyFile.txt";
			}
			else
			{
				path.clear();
				path = "MyFile.txt";
			}
			fs.open(path, fstream::in | fstream::out);
			if (!fs.is_open()) {
				cout << "Ошибка открытия файла! Возможно, что файл MyFile.txt не лежит в одной директории с программой!" << endl;
				system("PAUSE");
				break;
			}
			else {
				cout << "Файл открыт!" << endl; flag = 1;
				system("PAUSE");
				break;
			}
		case '2': {
			cin.get();
			system("cls");
			cout << "Перетащите файл в окно программы и нажмите Enter, либо введите путь к файлу в формате:\n  E:\\Admin\\Desktop\\New folder\\New Text Document.txt" << endl;
			if (path.empty()) {
				getline(cin, path);
				path.erase(remove(path.begin(), path.end(), '"'), path.end());
			}
			else
			{
				path.clear();
				getline(cin, path);
				path.erase(remove(path.begin(), path.end(), '"'), path.end());
			}
			fs.open(path, fstream::in | fstream::out);
			if (!fs.is_open()) {
				cout << "Ошибка открытия файла! Возможно, что путь к файлу неверен! " << endl;
				system("PAUSE");
				break;
			}
			else {
				cout << "Файл открыт!" << endl; flag = 1;
				system("PAUSE");
				break;
			}
		}
		case '3': {
			ch = '3';
			exit(0);
		}
		}
		default:
			break;
		}
	} while (ch != '3' && flag != 1);

	int N;
	do
	{
		system("cls");
		cout << "Введите N. (N - должен быть чётным!): "; cin >> N;
		if (N <= 0) {
			cout << "Ошибка ввода! Перезапустите программу.\n";
			return 1;
		}
	} while ((N % 2));

	int** TDA = new int* [N];
	for (int i = 0; i < N; i++)
		TDA[i] = new int[N];

	cout << "Исходная матрциа: " << endl; fs << "Исходная матрциа: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			TDA[i][j] = rand() % 10;
			cout << TDA[i][j] << " "; fs << TDA[i][j] << " ";
		}
		cout << endl; fs << endl;
	}

	int SubmatrixCount, PassesCount;
	__asm
	{
		mov eax, N
		mov ebx, N
		mov ecx, N

		mul ebx

		shr eax, 2
		shr ecx, 1

		mov SubmatrixCount, eax
		mov PassesCount, ecx
	}

	cout << "Количество подматриц 2x2: " << SubmatrixCount << endl; fs << "Количество подматриц 2x2: " << SubmatrixCount << endl;

	sortAscendingRows(TDA, N, SubmatrixCount, PassesCount);
	sortAscendingColumns(TDA, N, SubmatrixCount, PassesCount);

	cout << "После перестановки" << endl; fs << "После перестановки" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << TDA[i][j] << " "; fs << TDA[i][j] << " ";
		}
		cout << endl; fs << endl;
	} // NEW

	for (int i = 0; i < N; i++)
		delete[] TDA[i];
	delete[] TDA;
	TDA = NULL;

	fs.close();
	return 0;
}