#include <Windows.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;



string in(string str) {
	do {
		getline(cin, str);
	} while (str.empty());
	return str;
}
//�������� ��� ����� �����
string checkNumber(string input) {
	string buf = "", res = "";
	while (true) {
		int length = 0, ctr_err = 0;
		int first_numb = NULL, find_err = 0;
		length = input.length();
		for (int i = 0; i <= length; i++) {
			if (input[i] < '0' || input[i] > '9' ||
				input[i] == '\0' || input[i] == '\n') {
				if (!find_err) {
					buf.assign(input, first_numb, i - (res.length() + ctr_err));
					res += buf;
					first_numb = NULL;
					find_err = 1;
					ctr_err++;
				}
			}
			else
				if (find_err) {
					first_numb = i;
					find_err = 0;
				}
		}
		return res;
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	int N = 0;		//���-�� ������
	int N_work = -1;
	int mem = -1;
	int T = 0;		//������� ������
	int T_stop = 0;		//��������� ���� ������
	int T_free = -1;
	int Pn = 100;		//����������� ��������� � ��������������� ����� ������
	int Kr = 100;		//����������� ��������� � ���������
	int M;			//����� ������� � ������
	cout << "���-�� ����������� � ������ ������ N = ";
	string N_str;
	N_str = in(N_str);
	N = stoi(checkNumber(N_str));
	cout << "����� ��������� � ������ M = ";
	string M_str;
	M_str = in(M_str);
	M = stoi(checkNumber(M_str));
	cout << "Pn = ";
	string Pn_str;
	Pn_str = in(Pn_str);
	Pn = stoi(checkNumber(Pn_str));
	cout << "Kr = ";
	string Kr_str;
	Kr_str = in(Kr_str);
	Kr = stoi(checkNumber(Kr_str));
	cout << "������� ���������� ������ ��� ������ T_stop = ";
	string T_stop_str;
	T_stop_str = in(T_stop_str);
	T_stop = stoi(checkNumber(T_stop_str));

	cout.width(8);
	cout << "T" << " |";
	cout.width(8);
	cout << "��1" << " |";
	cout.width(8);
	cout << "��2" << " |";
	cout.width(8);
	cout << "��3" << " |";
	cout << endl;

	for (int T = 0; T < T_stop; T++) {
		cout.width(8);
		cout << T << " |";
		int K, P;
		for (int numb = 0; numb < N; numb++) {
			if (numb == N_work) { cout.width(8); cout << "Mem " << mem; }
			else {
				//��������� � ��������
				K = (rand() % 100 + 1);
				//cout << K;
				if (K < Kr) {
					cout.width(10);
					cout << "Reg  ";
				}
				else {
					P = (rand() % 100 + 1);
					//��������� � ���������������� ����� ������
					if (P < Pn) mem = numb;
					//��������� � ������� ����� ������
					else
						do {
							mem = rand() % 3;
						} while (mem = numb);
						//��������� ����
						if (T >= T_free) {
							T_free = -1;
							N_work = -1;
						}
						//���� ��������
						if (T_free < 0) {
							T_free = T + M;
							N_work = numb;
							cout.width(8);
							cout << "Mem " << mem;
						}
						else
							//���� �� ������������� ����
							if (numb != N_work) { cout.width(8); cout << "Wait " << mem; }
							//else { cout.width(8); cout << "Mem " << mem; }
				}
			}
		}
		cout << endl;
	}

	return 0;
}