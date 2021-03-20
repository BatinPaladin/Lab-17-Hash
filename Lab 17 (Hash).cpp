#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct People{
	string fio;
	string birth_data;
	string number;
};
//H(k) = [M(kAmod1)]
int HashFunction(string k, int n) {
	unsigned long long int key = stoll(k);
	int M = 12/n;
	int A = 3;
	return M * (A * key % 10);
}
int main() {
	system("chcp 1251");
	ifstream input("F1.txt");
	if (input.is_open()) {
		int index, size = -1, count = 0;
		while ((size < 2) || (size > 10)) {
			cout << "\n������� ������ �������:\n";
			cin >> size;
		}
		const int N = size;
		People el;
		People* data = new People[N];
		string* key = new string[N];
		for (int i = 0; i < size; i++) {
			key[i] = "-";
		}
		for (int i = 0; i < N; i++) {
			getline(input, el.fio);
			getline(input, el.birth_data);
			getline(input, el.number);
			index = HashFunction(el.number, N);
			while ((index >= size) || (key[size - 1] != "-")) {
				People* dataR = new People[size*2];
				string* keyR = new string[size*2];
				for (int j = 0; j < size; j++) {
					dataR[j] = data[j];
					keyR[j] = key[j];
				}
				for (int j = size; j < size * 2; j++) {
					keyR[j] = "-";
				}
				delete[]data;
				delete[]key;
				data = dataR;
				key = keyR;
				size = size * 2;
			}
			if ((key[index] != "-") && (index < size-1)) {
				count++;
				while ((key[index] != "-") && (index < size-1)) {
					index++;
				}
			}
			data[index] = el;
			key[index] = el.number;
		}
		cout << "\n��� �������:\n";
		for (int i = 0; i < size; i++) {
			cout << "[" << i + 1 << "] " << key[i] << endl;
		}
		cout << "\n���-�� ������� = " << count << endl;
		string otvet = "��";
		while (otvet != "���") {
			string search;
			bool flag = true;
			cout << "\n������� ������:\n";
			cin >> search;
			index = HashFunction(search, N);
			while ((index < size) && (flag == true)) {
				if (key[index] == search) {
					cout << "\n��������� �������\n���: " << data[index].fio;
					cout << "\n���� ��������: " << data[index].birth_data;
					cout << "\n����� ��������: " << data[index].number << endl;
					flag = false;
				}
				if (key[index] == "-") {
					cout << "\n������! ����������� �������!\n";
					flag = false;
				}
				index++;
			}
			if (index == size) {
				cout << "\n������! ����������� �������!\n";
			}
			cout << "\n����������? (��/���)\n";
			cin >> otvet;
		}
		delete[]data;
		delete[]key;
	}
	else {
		cout << "\n������! �� ������� ������� ���� F1.txt\n";
	}
	system("pause");
	return 0;
}