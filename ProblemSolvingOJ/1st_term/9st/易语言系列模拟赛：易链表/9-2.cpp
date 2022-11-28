
#include <iostream>
using namespace std;

const int maxC = 1000 + 5;
const int maxN = 500 + 5;
const int maxM = 5e5 + 5;
int id = 0, n = 0;

struct var {
	int id = 0;
	int val = 1;//±¸×¢
	var* prev = nullptr;
	var* next = nullptr;
};

struct node {
	int head = 0, tail = 0;
	bool empty() {
		return head == 0 ? true : false;
	}
	var list[maxC];
}all[maxN];

void init(int n);
void addH(int nid);
void addT(int nid);
var* findId(int id, int& nid);
void getId(int id);
void del(int id);
void changeVal(int id, int x);


int main() {
	cin >> n;
	init(n);
	int times = 0;
	cin >> times;
	for (int i = 0; i < times; i++) {
		int opt = -1, x = 0, y = 0;
		cin >> opt;
		if (opt == 1) {
			cin >> x;
			getId(x);
		}
		if (opt == 2) {
			cin >> x;
			del(x);
		}
		if (opt == 3) {
			cin >> x;
			addH(x);
		}
		if (opt == 4) {
			cin >> x;
			addT(x);
		}
		if (opt == 5) {
			cin >> x >> y;
			changeVal(x, y);
		}
	}
	return 0;
}

//ÎÒÖªµÀÓÃÕûÕûÈý¸ö¶ÀÁ¢µÄÓÖ³ôÓÖ³¤µÄº¯Êý£¬À´Íê³ÉÉú³ÉÔ­Á´±í£¬Í·²¿¡¢Î²²¿¼ÓÏîºÜº©£¬µ«ÊÇ¡­¡­
void init(int n) {
	for (int i = 0; i < n; i++) {
		int ci = 0;
		cin >> ci;
		for (int j = 0; j < ci; j++) {
			if (j == 0) {
				all[i].list[j] = { ++id, id, nullptr, nullptr };
			}
			else if (j > 0) {
				all[i].list[j] = { ++id, id };
				all[i].list[j].prev = &all[i].list[j - 1];
				all[i].list[j - 1].next = &all[i].list[j];
			}
			if (j == ci - 1) {
				all[i].list[j].next = nullptr;
			}
			all[i].tail++;
		}
	}
}


void addH(int nid) {
	var* ptrNew = &all[nid - 1].list[all[nid - 1].tail];
	var* ptrH = &all[nid - 1].list[all[nid - 1].head];
	if (all[nid - 1].empty())
		all[nid - 1].list[0] = { ++id, id, nullptr, nullptr };
	else {
		ptrNew->id = ++id, ptrNew->prev = nullptr, ptrNew->next = ptrH, ptrNew->val = id;
		ptrH -> prev = ptrNew;
	}
	all[nid - 1].tail++;
}


void addT(int nid) {
	var* ptrNew = &all[nid - 1].list[all[nid - 1].tail];
	var* ptrT = &all[nid - 1].list[all[nid - 1].tail - 1];
	if (all[nid - 1].empty())
		all[nid - 1].list[0] = { ++id, id, nullptr, nullptr };
	else {
		ptrT->next = ptrNew;
		ptrNew->prev = ptrT, ptrNew->next = nullptr, ptrNew->id = ++id, ptrNew->val = id;
	}
	all[nid - 1].tail++;
}

var* findId(int id, int& nid) {
	bool existence = false;
	for (int i = 0; i < n;) {
		int tailNum = all[i].tail - 1;
		var tailVar = all[i].list[tailNum];
		if (id > tailVar.id) {
			i++;
		}
		if (id <= tailVar.id) {
			var* ptr = &tailVar;
			while (id != ptr->id && ptr->prev != nullptr) {
				ptr = ptr->prev;
			}
			if (ptr->id != id)
				continue;
			else {
				existence = true;
				nid = i + 1;
				printf("nid = %d, i = %d\n", nid, i);
				return ptr;
			}
		}
	}
	if (!existence)
		return nullptr;
}


void getId(int id) {
	int useless = 0;
	var* ptr = findId(id, useless);
	if (ptr == nullptr) {
		cout << "NULL NULL NULL";
		return;
	} //<< (ptr->prev)->val << ptr->val
	else {
		if ((ptr->prev) == nullptr) {
			cout << "NULL" << ' ' << ptr->val << ' ';
		}
		else {
			//cout << 1001;
			int a = 1;
		}
		
//		cout  << "ptr " << ptr << endl;
		cout  << "before " << ptr->next << endl;
		if (ptr->next == nullptr) {
			cout << "NULL";
		}
		else {
			cout  << "BEfore " << ptr->next << endl;
		
			cout << (ptr->next)->val;
			cout << endl << "AFter " << ptr->next << endl;
		}
		cout << endl << "after " << ptr->next << endl;
	}
	cout << endl;
}

void del (int id) {
	int nid = 0;
	var* ptr = findId(id, nid);
	if (ptr != nullptr) {
		ptr->id = -1;
		var* pV = ptr->prev, * nV = ptr->next;
		bool prev = pV != nullptr;
		bool next = nV != nullptr;
		pV = nullptr, nV = nullptr;
		if (prev && next) {
			pV->next = nV;
			nV->prev = pV;
		}
		if (prev && !next)
			pV->next = nullptr;
		if (!prev && next)
			nV->prev = nullptr;
		all[nid - 1].tail--;
	}
}

void changeVal(int id, int x) {
	int nid = 0;
	var* ptr = findId(id, nid);
	if (ptr != nullptr) {
		ptr->val = x;
	}
}
