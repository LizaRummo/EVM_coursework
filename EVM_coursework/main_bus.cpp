#include <Windows.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Queue.h"

#define N 3
using namespace std;

struct States {
	//процессор
	string pr_reg = "__/РЕГ\\_";      //работа с регистром
	string pr_wait = "_[ожП0]_";    //начало ожидания
	string pr_memory = "_/ПАМ0\\_";    //начало работы с памятью
	// шина
	string bus_none = "________";     //ничего
	string bus_memory = "_/П0П0\\_";   //начало работы с памятью
} st;
//struct Element {
//	int proc;				// процессор
//	int mem;				// память
//	Element* prev;		// указатель на предыдущий элемент
//};
//class Queue {
//private:
//	int size;			// кол-во элементов в очереди 
//	Element* end;		// указатель на конец очереди
//
//public:
//	Queue() { size = 0; };	// конструктор, обнуляет начение size
//	~Queue() { clear(); };	// деструктор
//	void push(int, int);	// добавление элемента очереди
//	void pop();				// извлечение элемента очереди
//	void clear();			// очищение очереди
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
//		else return -1;
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
//	//return -1;
//}

string in(string str) {
	do {
		getline(cin, str);
	} while (str.empty());
	return str;
}
//проверка для ввода чисел
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
	int T = -1;			//счётчик тактов
	int T_stop = -1;	//последний такт работы
	int T_free = -1;
	int Pn = 100;		//вероятность обращения к соответсвующему блоку памяти
	int Kr = 100;		//вероятность обращения к регистрам
	int M;				//время доступа к памяти
	string str = "";

	cout << "Кол-во процессоров и блоков памяти N = " << N << endl;
	cout << "Время обращения к памяти M = ";
	str = in(str);
	M = stoi(checkNumber(str));
	cout << "Pn = ";
	str = in(str);
	Pn = stoi(checkNumber(str));
	cout << "Kr = ";
	str = in(str);
	Kr = stoi(checkNumber(str));
	cout << "Задайте количество тактов для работы T_stop = ";
	str = in(str);
	T_stop = stoi(checkNumber(str));
	str.clear();

	string status [5][100];
	status[0][0] = "T";
	status[1][0] = "ПР1";
	status[2][0] = "ПР2";
	status[3][0] = "ПР3";
	status[4][0] = "ШИНА";

	cout << endl;
	cout.width(8);
	cout << "T |";
	cout.width(8);
	cout << "ПР1 |";
	cout.width(8);
	cout << "ПР2 |";
	cout.width(8);
	cout << "ПР3 |";
	cout << endl;
	for (int i = 0; i < 33; i++) {cout << "—";}
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

				str += "ПАМ";
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

					str += "ОЖ";
					str += to_string(q_bus.find_mem(numb));
					str += "  ";
					cout.width(8); cout << str; str.clear();
				}
				else {					
					K = (rand() % 100 + 1);
					if (K < Kr) {				//обращение к регистру

						status[numb][T] = st.pr_reg;
						str.clear();

						str += "РГ  ";
						cout.width(8); cout << str; str.clear();
					}
					else {
						P = (rand() % 100 + 1);
						if (P < Pn) mem = numb;		//обращение к соответствующему блоку памяти
						else {						//обращение к другому блоку памяти
							do { mem = (rand() % 3 + 1);
							} while (mem == numb);
						}
						if (q_bus.isEmpty() && (T_free < 0 || T >= T_free)) {	//занятость шины
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

							str += "ПАМ";
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

							str += "ОЖ";
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

	//вывод в виде диаграммы

	cout << "<- Растяните окно ->" << endl << endl;

	cout.width(8);
	cout << status[0][0] << " | ";
	for (int j = 1; j < T; j++) { cout.width(7); cout << status[0][j]<<"|"; }
	cout << endl;

	for (int j = 1; j < ((T - 1) * 8) + 11; j++) { cout << "—"; }
	cout << endl << endl;

	for (int i = 1; i < 5; i++) {
		cout.width(8);
		cout << status[i][0] << " | ";
		for (int j = 1; j < T; j++) {cout.width(8);	cout << status[i][j];}
		cout << endl << endl;
	}
	return 0;
}