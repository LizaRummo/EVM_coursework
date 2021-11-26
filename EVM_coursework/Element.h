#pragma once

struct Element {
	int proc;				// процессор
	int mem;				// память
	Element* prev;		// указатель на предыдущий элемент
};