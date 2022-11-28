#include <iostream>
using namespace std;
struct node {
    char col;                                    //不同颜色 
    long long id = -1;                           //节点序号 
    node *right = NULL;                   //右节点 
}root;

long long num, num1, num2;
char op, opp;

void insert(node *tem, long long x, char pp)
{
    if (x > tem->id){
    	tem = tem->right;
    	insert(tem, x, pp);
	}
	else if (x == tem->id){
		node *dot = new node;
		tem->right = dot;
		dot->id = x + 1;
		dot->col = tem->col;
		tem->col = pp;
		dot->right = NULL;
	}
}

void del(node *tem, long long x){
	char limit;
	if (x > tem->id){
    	tem = tem->right;
    	del(tem, x);
	}
	else if (x == tem->id){
		if (tem->right == NULL){
			tem->col = limit;
		}
		else if (tem->right != NULL){
			if (((tem->right)->right) == NULL){
				(tem->col) = ((tem->right)->col);
				tem->right = NULL;
				return;
			}
			tem->col = ((tem->right)->col);
			tem = tem->right;
			x++;
			del(tem, x);
		} 
	}
}

char getcol(node *tem, long long x){
	if (x > tem->id){
		tem = tem->right;
		return getcol(tem, x);
	}
	else if (x == tem->id){
		return tem->col;
	}
}

void swapp(node *tem, long long x, char y){
	if (x > tem->id){
		tem = tem->right;
		swapp(tem, x, y);
	}
	else if (x == tem->id){
		tem->col = y;
	}
}

void show(node *tem){
	if (tem->right != NULL){
		cout << tem->col;
		tem = tem->right;
		show(tem);
	}
	else if (tem->right == NULL){
		cout << tem->col << endl;
	}
}

int main ()
{
	long long T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{	
		node *date = &root;
		cin >> op;
		if (op == 'A'){
			cin >> num >> opp;
			if(date->id == -1){
				date->col = opp;
				date->id = 0;
				date->right = NULL;
			}
			else {
			insert(date, num, opp);
			}
		}
		else if (op == 'D'){
			cin >> num;
			del(date, num);
		}
		else if (op == 'S'){
			cin >> num1 >> num2;
			if (num1 == num2){
				continue;
			}
			long long sma = min(num1, num2);
			long long lar = max(num1, num2);
			char qq = getcol(date, sma);
			char pp = getcol(date, lar);
			swapp(date, sma, pp);
			swapp(date, lar, qq);
		}
		else if (op == 'P'){
			show(date);
		}
	}
return 0;
}

