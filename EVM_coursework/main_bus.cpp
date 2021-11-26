#include <Windows.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Queue.h"

#define N 3
using namespace std;

struct States {
	//���������
	string pr_reg = "__/���\\_";      //������ � ���������
	string pr_wait = "_[���0]_";    //������ ��������
	string pr_memory = "_/���0\\_";    //������ ������ � �������
	// ����
	string bus_none = "________";     //������
	string bus_memory = "_/�0�0\\_";   //������ ������ � �������
} st;

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

Queue q_bus;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	int mem = -1;
	int T = -1;			//������� ������
	int T_stop = -1;	//��������� ���� ������
	int T_free = -1;
	int Pn = 100;		//����������� ��������� � ��������������� ����� ������
	int Kr = 100;		//����������� ��������� � ���������
	int M;				//����� ������� � ������
	string str = "";

	cout << "���-�� ����������� � ������ ������ N = " << N << endl;
	cout << "����� ��������� � ������ M = ";
	str = in(str);
	M = stoi(checkNumber(str));
	cout << "Pn = ";
	str = in(str);
	Pn = stoi(checkNumber(str));
	cout << "Kr = ";
	str = in(str);
	Kr = stoi(checkNumber(str));
	cout << "������� ���������� ������ ��� ������ T_stop = ";
	str = in(str);
	T_stop = stoi(checkNumber(str));
	str.clear();

	string status [5][100];
	status[0][0] = "T";
	status[1][0] = "��1";
	status[2][0] = "��2";
	status[3][0] = "��3";
	status[4][0] = "����";

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
	for (int i = 0; i < 33; i++) {cout << "�";}
	cout << endl;

	for (T = 1; T < T_stop+1; T++) {

		status[0][T] = to_string(T);

		str += to_string(T);
		str += " |";
		cout.width(8);
		cout << str;
		str.clear();
		cout << str;
		int K, P;
		if (T >= T_free) T_free = -1;
		for (int numb = 1; numb < N+1; numb++) {
			if (numb == q_bus.getFirst()) {

				str = st.pr_memory;
				str[5] = q_bus.getMem() + 48;
				status[numb][T] = str;
				str.clear();

				str += "���";
				str += to_string(q_bus.getMem());
				str += "  ";
				cout.width(8); cout << str; str.clear();

				str = st.bus_memory;
				str[3] = numb + 48;
				str[5] = q_bus.getMem() + 48;
				status[4][T] = str;
				str.clear();
			}
			else
				if (q_bus.find_proc(numb)) { 

					str = st.pr_wait;
					str[5] = q_bus.find_mem(numb) + 48;
					status[numb][T] = str;
					str.clear();

					str += "��";
					str += to_string(q_bus.find_mem(numb));
					str += "  ";
					cout.width(8); cout << str; str.clear();
				}
				else {					
					K = (rand() % 100 + 1);
					if (K < Kr) {				//��������� � ��������

						status[numb][T] = st.pr_reg;
						str.clear();

						str += "��  ";
						cout.width(8); cout << str; str.clear();
					}
					else {
						P = (rand() % 100 + 1);
						if (P < Pn) mem = numb;		//��������� � ���������������� ����� ������
						else {						//��������� � ������� ����� ������
							do { mem = (rand() % 3 + 1);
							} while (mem == numb);
						}
						if (q_bus.isEmpty() && (T_free < 0 || T >= T_free)) {	//��������� ����
							T_free = T + M;
							for (int i = 0; i < M; i++) { q_bus.push(numb, mem); }

							str = st.pr_memory;
							str[5] = q_bus.find_mem(numb) + 48;
							status[numb][T] = str;
							str.clear();

							str = st.bus_memory;
							str[3] = numb + 48;
							str[5] = q_bus.find_mem(numb) + 48;
							status[4][T] = str;
							str.clear();

							str += "���";
							str += to_string(q_bus.find_mem(numb));
							str += "  ";
							cout.width(8); cout << str; str.clear();
						}
						else {
							for (int i = 0; i < M; i++) { q_bus.push(numb, mem); }

							str = st.pr_wait;
							str[5] = q_bus.find_mem(numb) + 48;
							status[numb][T] = str;
							str.clear();

							str += "��";
							str += to_string(q_bus.find_mem(numb));
							str += "  ";
							cout.width(8); cout << str; str.clear();
						}
					}
				}
		}
		if (!q_bus.isEmpty()) q_bus.pop();
		if (status[4][T].empty()) {
			status[4][T] = st.bus_none;
			str.clear();
		}
		cout << endl;
	}
	cout << endl << endl;

	//����� � ���� ���������

	cout << "<- ��������� ���� ->" << endl << endl;

	cout.width(8);
	cout << status[0][0] << " | ";
	for (int j = 1; j < T; j++) { cout.width(7); cout << status[0][j]<<"|"; }
	cout << endl;

	for (int j = 1; j < ((T - 1) * 8) + 11; j++) { cout << "�"; }
	cout << endl << endl;

	for (int i = 1; i < 5; i++) {
		cout.width(8);
		cout << status[i][0] << " | ";
		for (int j = 1; j < T; j++) {cout.width(8);	cout << status[i][j];}
		cout << endl << endl;
	}
	return 0;
}