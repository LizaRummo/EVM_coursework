#include <Windows.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define N 3

using namespace std;

struct Element {
	int proc;				// процессор
	int mem;				// память
	Element* prev;		// указатель на предыдущий элемент
};

class Queue {
private:
	int size;			// кол-во элементов в очереди 
	Element* end;		// указатель на конец очереди

public:
	Queue() { size = 0; };	// конструктор, обнуляет начение size
	~Queue() { clear(); };	// деструктор
	void push(int, int);
	void pop();
	void clear();
	int find_proc(int);
	int find_mem(int);
	int isEmpty() { if (size == 0) return 1; else return 0; }

	int getSize() { return this->size; };
	Element* getEnd() { return this->end; };
	int getFirst() {
		Element* e = end;		// установка указателя e на конец очереди end
		int first;
		for (int i = 0; i < size - 1; i++) {	// если в очереди больше 1 элемента
			e = e->prev;						// переменной е передается значение предыдущего указателя, движение по очереди
		}
		if (e != NULL) { first = e->proc; return first; }
		else return -1;
	}
	int getMem() {
		Element* e = end;		// установка указателя e на конец очереди end
		int _mem;
		for (int i = 0; i < size - 1; i++) {	// если в очереди больше 1 элемента
			e = e->prev;						// переменной е передается значение предыдущего указателя, движение по очереди
		}
		_mem = e->mem;
		return _mem;
	}
};

//Добавление элемента очереди программой (с передачей аргумента)
void Queue::push(int _proc, int _mem) {

	Element* e = new Element;	// объявление указателя для нового элементa типа Element
	e->proc = _proc;
	e->mem = _mem;				// в память по указателю кладем новое значение
	e->prev = NULL;				// записывается нулевой указатель
	if (size > 0) {
		e->prev = end;			// последний элемент очереди становится предпослдним, тк у нас появился новый элемент, который стал последним
	}
	end = e;					// указатель на конец очереди начинает указывать на элемент е, тк он теперь последний
	this->size++;				// увеличение размера очереди
}

// Извлечение элемента очереди
void Queue::pop() {
	Element* e = end;		// установка указателя e на конец очереди end
	//int a;					// создание переменной
	if (this->size == 0) {	// если нет элементов в очереди
		cout << "none" << endl;
	}
	else {
		if (this->size == 1) {	// если один элемент
			//a = end->proc;			// передача значения конца очереди в переменную
			this->size--;		// уменьшение размера очереди
			delete end;			// удаление указателя на конец очереди
			//cout << proc /*<< endl << "none" << endl*/;
		}
		else {
			for (int i = 0; i < size - 2; i++) {	// если в очереди больше 1 элемента
				e = e->prev;						// переменной е передается значение предыдущего указателя, движение по очереди
			}
			//a = e->prev->proc;			// в значение а записывается значение головы
			delete e->prev;			// удаление головы
			this->size--;			// уменьшение размера очереди
			//cout << proc << endl;;
		}
	}
}

// Очищение очереди
void Queue::clear() {			// просмотр элементов с хвоста до головы, удаление элементов от головы по порядку	
	Element* e = end;			// установка указателя на конец очереди
	for (int i = 0; i < size; i++) {	//очередь не пустая
		e = end;				// указатель на конец очереди
		for (int j = 0; j < size - i - 1; j++) {
			e = e->prev;		// просмотр элементов с конца очереди до начала
		}
		delete e;				// удаление элемента очереди
	}
	size = 0;
	end = NULL;
}

int Queue::find_proc(int find) {
	Element* e = end;		// установка указателя e на конец очереди end
	for (int i = 0; i < size - 1; i++) {	// если в очереди больше 1 элемента
		if (e->proc == find) 
			return 1;
		else
			e = e->prev;						// переменной е передается значение предыдущего указателя, движение по очереди
	}
	return 0;
}

int Queue::find_mem(int find) {
	Element* e = end;		// установка указателя e на конец очереди end
	for (int i = 0; i < size - 1; i++) {	// если в очереди больше 1 элемента
		if (e->proc == find) return e->mem;
		else
			e = e->prev;						// переменной е передается значение предыдущего указателя, движение по очереди
	}
	return -1;
}

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
	//int N_work = -1;
	int mem = -1;
	int T = -1;		//счётчик тактов
	int T_stop = -1;		//последний такт работы
	int T_free = -1;
	int Pn = 100;		//вероятность обращения к соответсвующему блоку памяти
	int Kr = 100;		//вероятность обращения к регистрам
	int M;			//время доступа к памяти
	string str = "";
	//int buf = -1;

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
	for (int i = 0; i < 33; i++) {
		cout << "—";
	}
	cout << endl;

	for (T = 1; T < T_stop+1; T++) {
		str += to_string(T);
		str += " |";
		cout.width(8);
		cout << str;
		str.clear();
		cout << str;
		//cout << T << " |";
		int K, P;
		if (T >= T_free) 
			T_free = -1;
		for (int numb = 1; numb < N+1; numb++) {
			if (numb == /*N_work*/ q_bus.getFirst() /*&& T_free <0*/) {
				str += "ПАМ";
				str += to_string(q_bus.getMem());
				str += "  ";
				cout.width(8); 
				cout << str;
				str.clear();
				//cout.width(8); cout << "ПАМ " << q_bus.getMem();
				//q_bus.pop();
			}
			else
				if (q_bus.find_proc(numb)) { 
					str += "ОЖ";
					str += to_string(q_bus.find_mem(numb));
					str += "  ";
					cout.width(8);
					cout << str;
					str.clear();
				}
				else
				{
					//обращение к регистру
					
					K = (rand() % 100 + 1);
					//cout << K;
					if (K < Kr) {
						str += "РГ  ";
						cout.width(8); 
						cout << str;
						str.clear();
						//cout << "РГ  ";
					}
					else {
						
						P = (rand() % 100 + 1);
						//обращение к соответствующему блоку памяти
						if (P < Pn) mem = numb;
						//обращение к другому блоку памяти
						else {
							//srand(time(NULL));
							do {
								//srand(time(NULL));
								mem = (rand() % 3 + 1);
							} while (mem == numb);
						}
						//занятость шины
						if (q_bus.isEmpty() && (T_free < 0 || T >= T_free)) {
							//N_work = numb;
							T_free = T + M;
							for (int i = 0; i < M; i++) {
								q_bus.push(numb, mem);
							}
							str += "ПАМ";
							str += to_string(q_bus.find_mem(numb));
							str += "  ";
							cout.width(8); 
							cout << str;
							str.clear();
							//cout << "ПАМ " << q_bus.find_mem(numb);
							//q_bus.pop();
						}
						else {
							
							for (int i = 0; i < M; i++) {
								q_bus.push(numb, mem);
							}
							str += "ОЖ";
							str += to_string(q_bus.find_mem(numb));
							str += "  ";
							cout.width(8); 
							cout << str;
							str.clear();
							//cout << "ОЖ " << q_bus.find_mem(numb);
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