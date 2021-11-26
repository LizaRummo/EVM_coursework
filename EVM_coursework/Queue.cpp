#include "Queue.h"

void Queue::push(int _proc, int _mem) {

	Element* e = new Element;
	e->proc = _proc;
	e->mem = _mem;
	e->prev = NULL;
	if (size > 0) { e->prev = end; }
	end = e;
	this->size++;
}
void Queue::pop() {
	Element* e = end;
	if (this->size == 0) { cout << "none" << endl; }
	else {
		if (this->size == 1) { this->size--; delete end; }
		else {
			for (int i = 0; i < size - 2; i++) { e = e->prev; }
			delete e->prev;
			this->size--;
		}
	}
}
void Queue::clear() {
	Element* e = end;
	for (int i = 0; i < size; i++) {
		e = end;
		for (int j = 0; j < size - i - 1; j++) { e = e->prev; }
		delete e;
	}
	size = 0;
	end = NULL;
}
int Queue::find_proc(int find) {
	Element* e = end;
	for (int i = 0; i < size - 1; i++) {
		if (e->proc == find) return 1;
		else e = e->prev;
	}
	return 0;
}
int Queue::find_mem(int find) {
	Element* e = end;
	for (int i = 0; i < size /*- 1*/; i++) {
		if (e->proc == find) return e->mem;
		else e = e->prev;
	}
	return 0;
}