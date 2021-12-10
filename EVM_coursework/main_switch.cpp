#include <Windows.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Queue.h"

#define N 3
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

Queue q_switch[N+1];

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	int mem = -1;
	int T = -1;			//������� ������
	int T_stop = -1;	//��������� ���� ������
	int Pn = 100;		//����������� ��������� � ��������������� ����� ������
	int Kr = 100;		//����������� ��������� � ���������
	int M;				//����� ������� � ������
	string str = "";

	cout << "���-�� ����������� � ������ ������ N = " << N << endl;
	cout << "����� ��������� � ������ M [2,5,10] = ";
	str = in(str); M = stoi(checkNumber(str));
	cout << "Pn [80, 60] = ";
	str = in(str); Pn = stoi(checkNumber(str));
	cout << "Kr [85, 75, 65] = ";
	str = in(str); Kr = stoi(checkNumber(str));
	cout << "������� ���������� ������ ��� ������ T_stop = ";
	str = in(str); T_stop = stoi(checkNumber(str));
	str.clear();

	cout << endl;
	cout.width(8);
	cout << "T |";
	cout.width(8);
	cout << "��1 |";
	cout.width(8);
	cout << "��2 |";
	cout.width(8);
	cout << "��3 |";
	cout << endl;
	for (int i = 0; i < 33; i++) { cout << "�"; }
	cout << endl;

	for (T = 1; T < T_stop + 1; T++) {
		str += to_string(T);
		str += " |";
		cout.width(8);
		cout << str;
		str.clear();
		cout << str;
		int K, P;
		for (int numb = 1; numb < N + 1; numb++) {
			if (((numb == q_switch[1].getFirst())&& (q_switch[1].find_mem(numb)!=0)) ||((numb == q_switch[2].getFirst())&& (q_switch[2].find_mem(numb)!=0)) ||((numb == q_switch[3].getFirst())&& (q_switch[3].find_mem(numb)!=0))) {
				str += "���";
				for (int i = 1; i < N + 1; i++) {
					if (numb == q_switch[i].getFirst()) { mem = i; break; }
				} 
				str += to_string(q_switch[mem].getMem());
				str += "  ";
				cout.width(8); cout << str; str.clear();
			}
			else
				if ((q_switch[1].find_proc(numb))||(q_switch[2].find_proc(numb))||(q_switch[3].find_proc(numb))) {
					str += "��";
					for (int i = 1; i < N + 1; i++) {
						if (q_switch[i].find_mem(numb) > 0) { mem = i; break; }
					}
					str += to_string(mem); str += "  ";
					cout.width(8); cout << str; str.clear();
				}
				else {
					K = (rand() % 100 + 1);
					if (K < Kr) {				//��������� � ��������

						str += "��  ";
						cout.width(8); cout << str; str.clear();
					}
					else {
						P = (rand() % 100 + 1);
						if (P < Pn) mem = numb;		//��������� � ���������������� ����� ������
						else {						//��������� � ������� ����� ������
							do {
								mem = (rand() % 3 + 1);
							} while (mem == numb);
						}
						if (q_switch[mem].isEmpty()) {	//��������� 
							for (int i = 0; i < M; i++) { q_switch[mem].push(numb, mem); }

							str += "���";
							str += to_string(q_switch[mem].find_mem(numb));
							//str += to_string(mem);
							str += "  ";
							cout.width(8); cout << str; str.clear();
						}
						else {

							for (int i = 0; i < M; i++) { q_switch[mem].push(numb, mem); }

							str += "��";
							str += to_string(q_switch[mem].find_mem(numb));
							//str += to_string(mem);
							str += "  ";
							cout.width(8); cout << str; str.clear();
						}
					}
				}
		}
		for (int i = 1; i < N + 1; i++) {
			if (!q_switch[i].isEmpty()) q_switch[i].pop();
		}
		cout << endl;
	}
	cout << endl;
	return 0;
}