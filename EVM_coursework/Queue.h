#pragma once
#include "Element.h"
#include <iostream>

using namespace std;

class Queue {
private:
	int size;			// кол-во элементов в очереди 
	Element* end;		// указатель на конец очереди

public:
	Queue() { size = 0; };	// конструктор, обнуляет начение size
	~Queue() { clear(); };	// деструктор
	void push(int, int);	// добавление элемента очереди
	void pop();				// извлечение элемента очереди
	void clear();			// очищение очереди
	int find_proc(int);
	int find_mem(int);
	int isEmpty() { if (size == 0) return 1; else return 0; }

	int getSize() { return this->size; };
	Element* getEnd() { return this->end; };
	int getFirst() {
		Element* e = end;
		int first;
		for (int i = 0; i < size - 1; i++) { e = e->prev; }
		if (e != NULL) { first = e->proc; return first; }
		else return 0;
	}
	int getMem() {
		Element* e = end;
		int _mem;
		for (int i = 0; i < size - 1; i++) { e = e->prev; }
		_mem = e->mem;
		return _mem;
	}
};