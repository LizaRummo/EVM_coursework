#include <Windows.h>
#include <string>
#include <iostream>

using namespace std;

int N = 0;		//���-�� ������
int T = 0;		//������� ������
int T_stop = 0;		//��������� ���� ������
int Pn = 100;		//����������� ��������� � ��������������� ����� ������
int Kr = 100;		//����������� ��������� � ���������
int M;			//����� ������� � ������

struct States {
    //���������
    string pr_reg = "_/REG\\";      //������ � ���������
    string pr_wStart = "__[wM0";    //������ ��������
    string pr_wEnd = "----]_";      //����� ��������
    string pr_mStart = "___/M0";    //������ ������ � �������
    // ����
    string bus_none = "______";     //������
    string bus_mStart = "_/P0M0";   //������ ������ � �������

    string work = "------";         //�������
    string mEnd = "----\\_";        //����� ������ � �������
} st;

class Processor
{
	int N;			//����� ����������
	string* record;	//������ ���������

	//int Pn;			//����������� ��������� � ��������������� ����� ������
	//int Kr;			//����������� ��������� � ���������
	
public:
	Processor() : N(0), record(nullptr)/*, Pn(100), Kr(100)*/ {}
	Processor(int _N, string* _record/*, int _Pn, int _Kr*/) :N(_N), record(_record)/*, Pn(_Pn), Kr(_Kr) */{}
	Processor(int _N/*, int _Pn, int _Kr*/) :N(_N), record(nullptr)/*, Pn(_Pn), Kr(_Kr)*/ {}
	~Processor() {}

	//void to_register();
	void add_rec(int N_memory, string str);

	int getN() { return N; }
	//int getPn() { return Pn; }
	//int getKr() { return Kr; }
	string getRecord(int i) { return record[i]; }

	void setN(int _N) { N = _N; }
	//void setPn(int _Pn) { Pn = _Pn; }
	//void setKr(int _Kr) { Kr = _Kr; }
};

//void Processor::to_register() {
//	record[T] = st.pr_reg;
//	T++;
//}

void Processor::add_rec(int N_memory, string str) {
	string buf;
	buf = str;
	if (record == NULL) {
		record = new string[1];
	}
	else {
		string* temp = record;
		record = new string[T + 1];
		for (int i = 0; i < T; i++) {
			record[i] = temp[i];
		}
	}

	if (str == st.pr_mStart || str == st.pr_wStart) {
		buf[5] = N_memory + 48;
	}
	record[T] = buf;
}

class Bus
{
	//int T;			//������� ������
	int T_free;		//��������� ���� ��� ������� ��� ������ � �������
	//int M;			//����� ������� � ������
	int N_work;		//����������������� � ����� ���������

	//Processor* processors;
	string* record;	//������ ���������
public:
	Bus() : /*T(0),*/ T_free(NULL), record(nullptr)/*, M(1)*/, N_work(NULL){}
	Bus(/*int _T, */int _T_free, string* _record/*, int _M*/, int _N_work) :/*T(_T),*/ T_free(_T_free), record(_record)/*, M(_M)*/, N_work(_N_work) {}
	~Bus() {}

	//void to_memory(int N_processor, int N_memory);
	void add_rec(int N_processor, int N_memory, string str);

	//int getT() { return T; }
	int getTFree() { return T_free; }
	int getNWork() { return N_work; }
	string getRecord(int i) { return record[i]; }

	//void setT(int _T) { T = _T; }
	void setTFree(int _T_free) { T_free = _T_free; }
	void setNWork(int _N_work) { N_work = _N_work; }
};

//void Bus::to_memory(int N_processor, int N_memory)
//{
//	if (T_free == NULL) {
//		T_free = T + M;
//		string buf;
//		buf = st.bus_mStart;
//		buf[3] = N_processor;
//		buf[5] = N_memory;
//		record[T] = buf;
//
//		T++;
//	}
//}

void Bus::add_rec(int N_processor, int N_memory, string str)
{
	string buf;
	buf = str;
	if (record == NULL) {
		record = new string[1];
	}
	else {
		string* temp = record;
		record = new string[T + 1];
		for (int i = 0; i < T; i++) {
			record[i] = temp[i];
		}
	}

	if (str == st.bus_mStart) {
		buf[3] = N_processor + 48;
		//buf[3] = 'X';
		buf[5] = N_memory + 48;
		//buf[5] = 'Y';
		
	}
	record[T] = buf;
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
int selection(int first, int last) {
	int input;
	string buf;
	while (true) {
		try
		{
			buf = in(buf);
			buf = checkNumber(buf);
			input = stoi(buf);
			//cin >> input;
			if (!(cin.fail() || input < first || input > last))
				return input;
			else throw "������ ������������� ����� ����";
		}
		catch (const char*) {
			cin.clear();
			cerr << "������ ������������� ����� ����. ���������� ����" << endl << "> ";
		}
		//cin.ignore(32767, '\n');
	}
	return input;
}

Processor* processors;
Bus bus;

void to_memory(int N_processor, int N_memory) {
	//������ ���������
	if (bus.getTFree() == NULL) {
		bus.setNWork(N_processor);
		bus.setTFree(T + M);
		bus.add_rec(N_processor, N_memory, st.bus_mStart);
		processors[N_processor].add_rec(N_memory, st.pr_mStart);
		T++;
	}
	//��������� �� ����� ������
	else
		if (T < bus.getTFree()) {
			//���� �� ����������
			if (N_processor == bus.getNWork()) {
				//��������� ���� ���������
				if ((T + 1) == bus.getTFree()) {
					bus.setTFree(NULL);
					bus.setNWork(NULL);
					bus.add_rec(N_processor, N_memory, st.mEnd);
					processors[N_processor].add_rec(N_memory, st.mEnd);
				}
				else {
					bus.add_rec(N_processor, N_memory, st.work);
					processors[N_processor].add_rec(N_memory, st.work);
				}
				T++;
			}
			//������� ����������
			else {
				//bus.add_rec(j, j, st.work);
				/*if (processors[N_processor].getRecord(T - 1) != st.work)
					processors[N_processor].add_rec(N_memory, st.work);
				else*/ processors[N_processor].add_rec(N_memory, st.pr_wStart);
				T++;
			}
		}
}
void output() {
	cout.width(8);
	cout << "T |";
	for (int i = 0; i < T; i++) {
		cout.width(8);
		cout << i << "  |";
	}
	cout.width(8);
	cout << "|" << endl;
	for (int i = 0; i < N; i++) {
		cout.width(8);
		cout << "��" << i << " |";
		for (int j = 0; j < T; j++) {
			cout.width(8);
			cout << processors[i].getRecord(j);
		}
		cout.width(8);
		cout << "|" << endl;
	}
	cout.width(8);
	cout << "���� |";
	for (int i = 0; i < T; i++) {
		cout.width(8);
		cout << bus.getRecord(i);
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
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
	//menu();

	Processor* pr_ptr = new Processor[N];
	processors = pr_ptr;

	for (int i = 0; i < N; i++) {
		Processor pr;
		pr.setN(i);
		processors[i] = pr;
	}

	cout << "������� ���������� ������ ��� ������ T_stop = ";
	string T_stop_str;
	T_stop_str = in(T_stop_str);
	T_stop = stoi(checkNumber(T_stop_str));
	
	//�� ������� i ��������� ������?
	for (int i = 0; i < T_stop; i++) {
		int K, P;
			for (int j = 0; j < N; j++) {
				//��������� � ��������
				K = (rand() % 100 + 1);
				if (K <= Kr) {
					processors[j].add_rec(0, st.pr_reg);
					T++;
				}
				else
					//��������� � ���������������� ����� ������
					P = (rand() % 100 + 1);
					if (P < Pn) {
						to_memory(j, j);

						//if (bus.getTFree() == NULL) {
						//	bus.setNWork(j);
						//	bus.setTFree(T + M);
						//	bus.add_rec(j, j, st.bus_mStart);
						//	processors[j]->add_rec(j, st.pr_mStart);
						//	T++;
						//} 
						////��������� �� ����� ������
						//else
						//	if (T < bus.getTFree()) {
						//		//���� �� ����������
						//		if (j == bus.getNWork()) {
						//			//��������� ���� ���������
						//			if (T + 1 == bus.getTFree()) {
						//				bus.setTFree(NULL);
						//				bus.setNWork(NULL);
						//				bus.add_rec(j, j, st.mEnd);
						//				processors[j]->add_rec(j, st.mEnd);
						//			}
						//			else {
						//				bus.add_rec(j, j, st.work);
						//				processors[j]->add_rec(j, st.work);
						//			}
						//			T++;
						//		}
						//		//������� ����������
						//		else {
						//			//bus.add_rec(j, j, st.work);
						//			if (processors[j]->getRecord(T - 1) != st.work)
						//				processors[j]->add_rec(j, st.work);
						//			else processors[j]->add_rec(j, st.pr_wStart);
						//			T++;
						//		}
						//	}
					}
					//��������� � ������� ����� ������
					else {
						int random=0;
						do {
							random = rand() % 3;
						} while (random = j);
						to_memory(j, random);
					}
			}	
			output();
	}
	
	return 0;
}


