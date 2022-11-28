#include <bits/stdc++.h>
using namespace std;

bool isempty = true;

struct node{
	node *left, *right;
	node *father;
	int times;
	int value;
	node()
	{
		times = 1;
		left = NULL;
		right = NULL;
		father = NULL;
	}
};

void print(node *&root)
{
	printf("%d ", root->value);
    if (root->left != NULL)
	  print(root->left);
	if (root->right != NULL)
	  print(root->right);
}

void insert(node *&root, int num)
{
	if (num == root->value)
	  root->times++;
	else if (num < root->value)
	{
		if (root->left == NULL)
		{
			node *leftchild = new node;
			leftchild->value = num;
			leftchild->father = root;
			root->left = leftchild;
		}
		else
		  insert(root->left, num);
	}
	else if (num > root->value)
	{
		if (root->right == NULL)
		{
			node *rightchild = new node;
			rightchild->value = num;
			rightchild->father = root;
			root->right = rightchild;
		}
		else
		  insert(root->right, num);
	}
}

node *searchsuccessor(node *&root)
{
	node *cur = root->right;
	while(cur->left != NULL)
	  cur = cur->left;
	return cur;
}

void del(node *&root, int num)
{
	if (num == root->value)
	{
		if (root->times > 1)
		  root->times--;
		else
		{
			if (root->left == NULL && root->right == NULL)
			{
				if (root->father == NULL)
				{
					root->times = 0;
					root->value = 0;
					isempty = true;
			    }
				else
				{
					if (root->value < root->father->value)
					  root->father->left = NULL;
				    else
				      root->father->right = NULL;
				}
			}
			else if (root->left != NULL && root->right == NULL)
			{
				if (root->father == NULL)
				{
					root = root->left;
					root->father = NULL;
				}
				else
				{
					if (root->left->value < root->father->value)
					  root->father->left = root->left;
			        else
			          root->father->right = root->left;
				}
			}
			else if (root->left == NULL && root->right != NULL)
			{
				if (root->father == NULL)
				{
					root = root->right;
					root->father = NULL;
				}		  
				else
				{
					if (root->right->value < root->father->value)
			          root->father->left = root->right;
			        else
			          root->father->right = root->right;
				}
			}
			else
			{
				node *s = searchsuccessor(root);
				int temp;
				temp = s->value;
				s->value = root->value;
				root->value = temp;
				temp = s->times;
				s->times = root->times;
				root->times = temp;
				if (s->father == root)
				  root->right = NULL;
				else
				  del(s, s->value);
			}
		}
	}
	else if (num < root->value)
	{
		if (root->left != NULL)
		  del(root->left, num);
	}
	else if (num > root->value)
	{
		if (root->right != NULL)
		  del(root->right, num);
	}
}

int main()
{
	int m, ope, num;
	node *root = new node;
	cin >> m;
	while(m--)
	{
		cin >> ope;
		if (ope == 0)
		{
			if (!isempty)
			  print(root);
			printf("\n");
		}
		else if (ope == 1)
		{
			cin >> num;
			if (isempty)
			{
				root->value = num;
				root->times = 1;
				isempty = false;
			}
			else
			  insert(root, num);
		}
		else if (ope == 2)
		{
			cin >> num;
			if (!isempty)
			  del(root, num);
		}
	}
	return 0;
}
