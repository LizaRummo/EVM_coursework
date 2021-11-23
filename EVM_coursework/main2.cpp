#include <Windows.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define N 3

using namespace std;

struct Element {
	int proc;				// ���������
	int mem;				// ������
	Element* prev;		// ��������� �� ���������� �������
};

class Queue {
private:
	int size;			// ���-�� ��������� � ������� 
	Element* end;		// ��������� �� ����� �������

public:
	Queue() { size = 0; };	// �����������, �������� ������� size
	~Queue() { clear(); };	// ����������
	void push(int, int);
	void pop();
	void clear();
	int find_proc(int);
	int find_mem(int);
	int isEmpty() { if (size == 0) return 1; else return 0; }

	int getSize() { return this->size; };
	Element* getEnd() { return this->end; };
	int getFirst() {
		Element* e = end;		// ��������� ��������� e �� ����� ������� end
		int first;
		for (int i = 0; i < size - 1; i++) {	// ���� � ������� ������ 1 ��������
			e = e->prev;						// ���������� � ���������� �������� ����������� ���������, �������� �� �������
		}
		if (e != NULL) { first = e->proc; return first; }
		else return -1;
	}
	int getMem() {
		Element* e = end;		// ��������� ��������� e �� ����� ������� end
		int _mem;
		for (int i = 0; i < size - 1; i++) {	// ���� � ������� ������ 1 ��������
			e = e->prev;						// ���������� � ���������� �������� ����������� ���������, �������� �� �������
		}
		_mem = e->mem;
		return _mem;
	}
};

//���������� �������� ������� ���������� (� ��������� ���������)
void Queue::push(int _proc, int _mem) {

	Element* e = new Element;	// ���������� ��������� ��� ������ �������a ���� Element
	e->proc = _proc;
	e->mem = _mem;				// � ������ �� ��������� ������ ����� ��������
	e->prev = NULL;				// ������������ ������� ���������
	if (size > 0) {
		e->prev = end;			// ��������� ������� ������� ���������� ������������, �� � ��� �������� ����� �������, ������� ���� ���������
	}
	end = e;					// ��������� �� ����� ������� �������� ��������� �� ������� �, �� �� ������ ���������
	this->size++;				// ���������� ������� �������
}

// ���������� �������� �������
void Queue::pop() {
	Element* e = end;		// ��������� ��������� e �� ����� ������� end
	//int a;					// �������� ����������
	if (this->size == 0) {	// ���� ��� ��������� � �������
		cout << "none" << endl;
	}
	else {
		if (this->size == 1) {	// ���� ���� �������
			//a = end->proc;			// �������� �������� ����� ������� � ����������
			this->size--;		// ���������� ������� �������
			delete end;			// �������� ��������� �� ����� �������
			//cout << proc /*<< endl << "none" << endl*/;
		}
		else {
			for (int i = 0; i < size - 2; i++) {	// ���� � ������� ������ 1 ��������
				e = e->prev;						// ���������� � ���������� �������� ����������� ���������, �������� �� �������
			}
			//a = e->prev->proc;			// � �������� � ������������ �������� ������
			delete e->prev;			// �������� ������
			this->size--;			// ���������� ������� �������
			//cout << proc << endl;;
		}
	}
}

// �������� �������
void Queue::clear() {			// �������� ��������� � ������ �� ������, �������� ��������� �� ������ �� �������	
	Element* e = end;			// ��������� ��������� �� ����� �������
	for (int i = 0; i < size; i++) {	//������� �� ������
		e = end;				// ��������� �� ����� �������
		for (int j = 0; j < size - i - 1; j++) {
			e = e->prev;		// �������� ��������� � ����� ������� �� ������
		}
		delete e;				// �������� �������� �������
	}
	size = 0;
	end = NULL;
}

int Queue::find_proc(int find) {
	Element* e = end;		// ��������� ��������� e �� ����� ������� end
	for (int i = 0; i < size - 1; i++) {	// ���� � ������� ������ 1 ��������
		if (e->proc == find) 
			return 1;
		else
			e = e->prev;						// ���������� � ���������� �������� ����������� ���������, �������� �� �������
	}
	return 0;
}

int Queue::find_mem(int find) {
	Element* e = end;		// ��������� ��������� e �� ����� ������� end
	for (int i = 0; i < size - 1; i++) {	// ���� � ������� ������ 1 ��������
		if (e->proc == find) return e->mem;
		else
			e = e->prev;						// ���������� � ���������� �������� ����������� ���������, �������� �� �������
	}
	return -1;
}

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
	//int N_work = -1;
	int mem = -1;
	int T = 0;		//������� ������
	int T_stop = 0;		//��������� ���� ������
	int T_free = -1;
	int Pn = 100;		//����������� ��������� � ��������������� ����� ������
	int Kr = 100;		//����������� ��������� � ���������
	int M;			//����� ������� � ������
	cout << "���-�� ����������� � ������ ������ N = " << N << endl;
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
		if (T >= T_free) 
			T_free = -1;
		for (int numb = 0; numb < N; numb++) {
			if (numb == /*N_work*/ q_bus.getFirst() /*&& T_free <0*/) {
				cout.width(8); cout << "Mem " << q_bus.getMem();
				//q_bus.pop();
			}
			else
				if (q_bus.find_proc(numb)) { cout.width(8); cout << "Wait " << q_bus.find_mem(numb); }
				else
				{
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
						else {
							//srand(time(NULL));
							do {
								//srand(time(NULL));
								mem = rand() % 3;
							} while (mem == numb);
						}
						//��������� ����
						if (q_bus.isEmpty() && (T_free < 0 || T >= T_free)) {
							//N_work = numb;
							T_free = T + M;
							for (int i = 0; i < M; i++) {
								q_bus.push(numb, mem);
							}
							cout.width(8);
							cout << "Mem " << q_bus.find_mem(numb);
							//q_bus.pop();
						}
						else {
							
							for (int i = 0; i < M; i++) {
								q_bus.push(numb, mem);
							}
							cout.width(8);
							cout << "Wait " << q_bus.find_mem(numb);
						}
						//else { cout.width(8); cout << "Mem " << mem; }
					}
				}
			
		}
		if (!q_bus.isEmpty())
			q_bus.pop();
		cout << endl;
	}

	return 0;
}