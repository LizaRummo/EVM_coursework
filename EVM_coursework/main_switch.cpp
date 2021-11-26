#include <Windows.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Queue.h"

#define N 3
using namespace std;

//struct States {
//	//���������
//	string pr_reg = "_/ �� \\_";      //������ � ���������
//	string pr_wait = "_[���0]_";    //������ ��������
//	string pr_memory = "_/���0\\_";    //������ ������ � �������
//	// ����������
//	string sw_none = "________";     //������
//	string sw_memory = "_/�0�0\\_";   //������ ������ � �������
//} st;
//struct Element {
//	int proc;				// ���������
//	int mem;				// ������
//	Element* prev;		// ��������� �� ���������� �������
//};
//class Queue {
//private:
//	int size;			// ���-�� ��������� � ������� 
//	Element* end;		// ��������� �� ����� �������
//
//public:
//	Queue() { size = 0; };	// �����������, �������� ������� size
//	~Queue() { clear(); };	// ����������
//	void push(int, int);	// ���������� �������� �������
//	void pop();				// ���������� �������� �������
//	void clear();			// �������� �������
//	int find_proc(int);
//	int find_mem(int);
//	int isEmpty() { if (size == 0) return 1; else return 0; }
//
//	int getSize() { return this->size; };
//	Element* getEnd() { return this->end; };
//	int getFirst() {
//		Element* e = end;						
//		int first;
//		for (int i = 0; i < size - 1; i++) { e = e->prev; }
//		if (e != NULL) { first = e->proc; return first; }
//		else return 0;
//	}
//	int getMem() {
//		Element* e = end;		
//		int _mem;
//		for (int i = 0; i < size - 1; i++) { e = e->prev; }
//		_mem = e->mem;
//		return _mem;
//	}
//};
//
//void Queue::push(int _proc, int _mem) {
//
//	Element* e = new Element;	
//	e->proc = _proc;
//	e->mem = _mem;				
//	e->prev = NULL;				
//	if (size > 0) { e->prev = end; }
//	end = e;					
//	this->size++;				
//}
//void Queue::pop() {
//	Element* e = end;		
//	if (this->size == 0) { cout << "none" << endl; }
//	else {
//		if (this->size == 1) { this->size--; delete end; }
//		else {
//			for (int i = 0; i < size - 2; i++) { e = e->prev; }
//			delete e->prev;			
//			this->size--;			
//		}
//	}
//}
//void Queue::clear() {				
//	Element* e = end;				
//	for (int i = 0; i < size; i++) {	
//		e = end;					
//		for (int j = 0; j < size - i - 1; j++) { e = e->prev; }
//		delete e;					
//	}
//	size = 0;
//	end = NULL;
//}
//int Queue::find_proc(int find) {
//	Element* e = end;						
//	for (int i = 0; i < size - 1; i++) {
//		if (e->proc == find) return 1;
//		else e = e->prev;
//	}
//	return 0;
//}
//int Queue::find_mem(int find) {
//	Element* e = end;						
//	for (int i = 0; i < size /*- 1*/; i++) {	
//		if (e->proc == find) return e->mem;
//		else e = e->prev;					
//	}
//	return 0;
//}

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

//Queue q_bus;
Queue q_switch[N+1];

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
	str = in(str); M = stoi(checkNumber(str));
	cout << "Pn = ";
	str = in(str); Pn = stoi(checkNumber(str));
	cout << "Kr = ";
	str = in(str); Kr = stoi(checkNumber(str));
	cout << "������� ���������� ������ ��� ������ T_stop = ";
	str = in(str); T_stop = stoi(checkNumber(str));
	str.clear();

	//string status[N+2][100];
	//status[0][0] = "T";
	//status[1][0] = "��1";
	//status[2][0] = "��2";
	//status[3][0] = "��3";
	//status[4][0] = "����������";

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

		//status[0][T] = to_string(T);

		str += to_string(T);
		str += " |";
		cout.width(8);
		cout << str;
		str.clear();
		cout << str;
		int K, P;
		if (T >= T_free) T_free = -1;
		for (int numb = 1; numb < N + 1; numb++) {
			if (((numb == q_switch[1].getFirst())&& (q_switch[1].find_mem(numb)!=0)) ||((numb == q_switch[2].getFirst())&& (q_switch[2].find_mem(numb)!=0)) ||((numb == q_switch[3].getFirst())&& (q_switch[3].find_mem(numb)!=0))) {

				str += "���";

				for (int i = 1; i < N + 1; i++) {
					if (numb == q_switch[i].getFirst()) { mem = i; break; }
				} 
				str += to_string(q_switch[mem].getMem());

				//if ((numb == q_switch[1].getFirst()) /*&& (q_switch[1].find_mem(numb) != 0)*/) {
				//	//str += to_string(q_switch[1].find_mem(numb));
				//	str += to_string(q_switch[1].getMem());
				//	//str += to_string(q_switch[1].getFirst());
				//	//str += to_string(1); 
				//}
				//else {
				//	if ((numb == q_switch[2].getFirst()) /*&& (q_switch[2].find_mem(numb) != 0)*/) {
				//		//str += to_string(q_switch[2].find_mem(numb));
				//		str += to_string(q_switch[2].getMem());
				//		//str += to_string(q_switch[2].getFirst());
				//		//str += to_string(2);
				//	}
				//	else
				//		if ((numb == q_switch[3].getFirst()) /*&& (q_switch[3].find_mem(numb) != 0)*/) {
				//			//str += to_string(q_switch[3].find_mem(numb));
				//			str += to_string(q_switch[3].getMem());
				//			//str += to_string(q_switch[3].getFirst());
				//			//str += to_string(3);
				//		}
				//}

				str += "  ";
				cout.width(8); cout << str; str.clear();

				//str = st.pr_memory;
				//str[5] = q_switch[mem].getMem() + 48;
				//status[numb][T] = str;
				//str.clear();
				
				//str = st.sw_memory;
				//str[3] = numb + 48;
				//str[5] = q_bus.getMem() + 48;
				//status[4][T] = str;
				//str.clear();
			}
			else
				if ((q_switch[1].find_proc(numb))||(q_switch[2].find_proc(numb))||(q_switch[3].find_proc(numb))) {
					
					str += "��";

					for (int i = 1; i < N + 1; i++) {
						if (q_switch[i].find_mem(numb) > 0) { mem = i; break; }
					}
					str += to_string(mem);

					//if (q_switch[1].find_mem(numb) > 0) {
					//	str += to_string(1); }
					//else if (q_switch[2].find_mem(numb) > 0) {
					//	str += to_string(2); }
					//else if (q_switch[3].find_mem(numb) > 0) {
					//	str += to_string(3); }

					str += "  ";
					cout.width(8); cout << str; str.clear();

					//str = st.pr_wait;
					//str[5] = q_switch[mem].find_mem(numb) + 48;
					//status[numb][T] = str;
					//str.clear();

				}
				else {
					K = (rand() % 100 + 1);
					if (K < Kr) {				//��������� � ��������

						//status[numb][T] = st.pr_reg;
						//str.clear();

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
						if (q_switch[mem].isEmpty() /*&& (T_free < 0 || T >= T_free)*/) {	//��������� ����
							//T_free = T + M;
							for (int i = 0; i < M; i++) { q_switch[mem].push(numb, mem); }

							//str = st.pr_memory;
							//str[5] = q_switch[mem].find_mem(numb) + 48;
							//status[numb][T] = str;
							//str.clear();

							/*str = st.sw_memory;
							str[3] = numb + 48;
							str[5] = q_switch[mem].find_mem(numb) + 48;
							status[4][T] = str;
							str.clear();*/

							str += "���";
							str += to_string(q_switch[mem].find_mem(numb));
							//str += to_string(mem);
							str += "  ";
							cout.width(8); cout << str; str.clear();
						}
						else {

							for (int i = 0; i < M; i++) { q_switch[mem].push(numb, mem); }

							//str = st.pr_wait;
							//str[5] = q_switch[mem].find_mem(numb) + 48;
							//status[numb][T] = str;
							//str.clear();

							/*str = st.sw_memory;
							str[3] = numb + 48;
							str[5] = q_switch[mem].find_mem(numb) + 48;
							status[4][T] = str;
							str.clear();*/

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
		/*if (status[4][T].empty()) {
			status[4][T] = st.sw_none;
			str.clear();
		}*/
		cout << endl;
	}
	cout << endl << endl;
	/*cout << "<- ��������� ���� ->" << endl << endl;

	cout.width(11);
	cout << status[0][0] << " | ";
	for (int j = 1; j < T; j++) { cout.width(7); cout << status[0][j] << "|"; }
	cout << endl;

	for (int j = 1; j < ((T - 1) * 8) + 14; j++) { cout << "�"; }
	cout << endl << endl;

	for (int i = 1; i < 4; i++) {
		cout.width(11);
		cout << status[i][0] << " | ";
		for (int j = 1; j < T; j++) { cout.width(8);cout << status[i][j]; }
		cout << endl << endl;
	}*/
	return 0;
}