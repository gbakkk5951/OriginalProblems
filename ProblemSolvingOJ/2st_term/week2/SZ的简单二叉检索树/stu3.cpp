#include<iostream>

using namespace std;
struct dot
{
	dot* left = NULL, * right = NULL, * father = NULL;
	int value;
	int exc = 0;
};
dot a[1000005];
int t;
int op, root = 1000004, tar, step = 1;
bool flag = true;
void findpos(int n, dot* cur)
{
	if (a[n].exc == 0)
	{
		if (root == 1000004)
		{
			root = n;
			a[n].value = n;
			a[n].left = NULL;
			a[n].right = NULL;
			a[n].exc++;
		}
		else
		{
			if (n > cur->value)
			{
				if (cur->right == NULL)
				{
					cur->right = &a[n];
					a[n].value = n;
					a[n].father = cur;
					a[n].exc++;
					return;
				}
				else findpos(n, cur->right);
			}
			else if (n < cur->value)
			{
				if (cur->left == NULL)
				{
					cur->left = &a[n];
					a[n].value = n;
					a[n].father = cur;
					a[n].exc++;
					return;
				}
				else findpos(n, cur->left);
			}
		}
	}
	else
	{
		a[n].exc++;
		return;
	}
}

void out(dot* d)
{
	if (d == NULL)return;
	if (d->exc >= 1)
	cout << d->value << " ";
	out(d->left );
	out(d->right);
}
int main()
{
	cin >> t;
	if (t == 0)return 0;
	while (flag)
	{
		cin >> op;
		if (op == 0)cout << endl, step++;
		else if (op == 1)
		{
			cin >> tar;
			flag = false;
			step++;
			root = tar;
			a[tar].value = tar;
			a[tar].left = NULL;
			a[tar].right = NULL;
			a[tar].exc++;
		}
		else if (op == 2)cin >> tar, step++;
	}
	for (int i = step; i <= t; i++)
	{
		cin >> op;
		if (op == 0)
		{
			out(&a[root]);
			cout << endl;
		}
		else if (op == 1)
		{
			cin >> tar;
			findpos(tar, &a[root]);
		}
		else if (op == 2)
		{
			cin >> tar;
			if (a[tar].exc >= 2)
			{
				a[tar].exc--;
			}
			else if (a[tar].exc == 1)
			{
				if (a[tar].left == NULL && a[tar].right == NULL)
				{
					a[tar].exc--;
					if (tar == root)root = 1000004;
					else
					{
						if (&a[tar] == a[tar].father->left)
						{
							a[tar].father->left = NULL;
						}
						else
						{
							a[tar].father->right = NULL;
						}
					}
				}
				else if (a[tar].left == NULL && a[tar].right != NULL)
				{
					
					if (tar == root)
					{
						root = a[tar].right->value;
						a[tar].exc--;
						a[root].father = NULL;
					}
					else
					{
						a[tar].exc--;
						if (&a[tar] == a[tar].father->left)
						{
							a[tar].father->left = a[tar].right;
							a[tar].right->father = a[tar].father;
						}
						else
						{
							a[tar].father->right = a[tar].right;
							a[tar].right->father = a[tar].father;
						}
					}
				}
				else if (a[tar].left != NULL && a[tar].right == NULL)
				{

					if (root == tar)
					{
						root = a[tar].left->value;
						a[tar].exc--;
						a[root].father = NULL;
					}
					else 
					{
						a[tar].exc--;
						if (&a[tar] == a[tar].father->left)
						{
							a[tar].father->left = a[tar].left;
							a[tar].left->father = a[tar].father;
						}
						else
						{
							a[tar].father->right = a[tar].left;
							a[tar].left->father = a[tar].father;
						}
					}
				}
				else if (a[tar].left != NULL && a[tar].right != NULL)
				{

					dot* node=a[tar].right;
					while (node->left != NULL)node = node->left;
					if (tar == root) 
					{
						if (node != a[tar].right)
						{
							if (node = node->father->left)node->father->left = NULL;
							else node->father->right = NULL;
							root = node->value;
							node->father = NULL;
							node->left = a[tar].left;
							node->right = a[tar].right;
							a[tar].left->father = node;
							a[tar].right->father = node;
						}
						else 
						{
							root = node->value;
							node->father = NULL;
							node->left = a[tar].left;
							a[tar].left->father = node;
						}
						a[tar].exc--;
					}
					else
					{
						if (node != a[tar].right)
						{
							if (node->father->left = node)node->father->left = NULL;
							else node->father->right = NULL;
							node->father = a[tar].father;
							node->left = a[tar].left;
							node->right = a[tar].right;
							a[tar].left->father = node;
							a[tar].right->father = node;
							if (&a[tar] == a[tar].father->left)
							{
								a[tar].father->left = node;
							}
							else
							{
								a[tar].father->right = node;
							}
							if (node->father->left = node)node->father->left = NULL;
							else node->father->right = NULL;
						}
						else
						{
							node->father = a[tar].father;
							node->left = a[tar].left;
							a[tar].left->father = node;
							if (&a[tar] == a[tar].father->left)
							{
								a[tar].father->left = node;
							}
							else
							{
								a[tar].father->right = node;
							}
						}
						a[tar].exc--;
					}
				}
				a[tar].left = NULL;
				a[tar].right = NULL;
				a[tar].father = NULL;
				a[tar].exc = 0;
			}
		}
	}
	return 0;
}
