#include<iostream>
#include<algorithm>
using namespace std;
struct node {
	int value;
	int times;
	node* father;
	node* left;
	node* right;
};
node* root = NULL;
int sign = 0;
void insert(node* root, int value) {
	if (value > root->value) {
		if (root->right == NULL) {
			node* newnode = new node;
			newnode->left = NULL;
			newnode->right = NULL;
			newnode->value = value;
			newnode->times = 1;
			newnode->father = root;
			root->right = newnode;
		}
		else {
			insert(root->right, value);
		}
	}
	else if (value < root->value) {
		if (root->left == NULL) {
			node* newnode = new node;
			newnode->left = NULL;
			newnode->right = NULL;
			newnode->value = value;
			newnode->times = 1;
			newnode->father = root;
			root->left = newnode;
		}
		else {
			insert(root->left, value);
		}
	}
	else if (value == root->value) {
		root->times = root->times + 1;
	}
}
void printnode(node* root) {
	if (root == NULL) {
		return;
	}
	else {
		cout << root->value << " ";
		printnode(root->left);
		printnode(root->right);
	}
}
void findnode(node* root, int value) {//找到节点并删除
	if (root == NULL) {
		return;
	}
	else {
		if (root->value == value) {
			if (root->times > 1) {
				root->times = root->times - 1;
			}
			else {
				if ((root->right == NULL) && (root->left == NULL)) {//无子节点
					if (root->father == NULL) {
						sign = 1;
					}
					else {
						if ((root->father->left != NULL) && (root->father->right != NULL)) {
							if (root->father->right->value == value) {
								root->father->right = NULL;
							}
							else {
								root->father->left = NULL;
							}
						}
						else {
							if (root->father->left != NULL) {
								root->father->left = NULL;
							}
							else {
								root->father->right = NULL;
							}
						}
					}
				}
				else if ((root->right != NULL) && (root->left != NULL)) {//有两个子节点
					node* cur = root->right;
					while (cur->left != NULL) {
						cur = cur->left;
					}
					int t = cur->value;
					cur->value = root->value;
					root->value = t;
					int g = cur->times;
					cur->times = g;
					root->times = g;
					findnode(cur, cur->value);
				}
				else {//有一个子节点
					int flag = 0;
					if (root->right != NULL) {
						flag = 1;//right
					}
					else {
						flag = 0;//left
					}
					if (root->father != NULL) {
						if ((root->father->left != NULL) && (root->father->right != NULL)) {
							if (root->father->left->value == value) {
								if (flag == 1) {
									root->father->left = root->right;
									root->right->father = root->father;
								}
								else {
									root->father->left = root->left;
									root->left->father = root->father;
								}
							}
							else {
								if (flag == 1) {
									root->father->right = root->right;
									root->right->father = root->father;
								}
								else {
									root->father->right = root->left;
									root->left->father = root->father;
								}
							}
						}
						else {
							if (root->father->left != NULL) {
								if (flag == 1) {
									root->father->left = root->right;
									root->right->father = root->father;
								}
								else {
									root->father->left = root->left;
									root->left->father = root->father;
								}
							}
							else {
								if (flag == 1) {
									root->father->right = root->right;
									root->right->father = root->father;
								}
								else {
									root->father->right = root->left;
									root->left->father = root->father;
								}
							}
						}
					}
					else {
						sign = 2;
					}
				}
			}
		}
		else if (root->value > value) {
			findnode(root->left, value);
		}
		else if (root->value < value) {
			findnode(root->right, value);
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int M;
	cin >> M;
	while (M--) {
		int op;
		cin >> op;
		sign = 0;
		if (op == 0) {
			printnode(root);
			cout << endl;
		}
		else if (op == 1) {
			//insert
			int value;
			cin >> value;
			if (root == NULL) {
				node* newnode = new node;
				newnode->father = NULL;
				newnode->left = NULL;
				newnode->right = NULL;
				newnode->times = 1;
				newnode->value = value;
				root = newnode;
			}
			else {
				insert(root, value);
			}
		}
		else if (op == 2) {
			//delete
			int value;
			cin >> value;
			findnode(root, value);
			if (sign == 1) {//此时无根节点
				root = NULL;
			}
			else if (sign == 2) {//此时根节点更新
				if (root->left != NULL) {
					root = root->left;
					root->father = NULL;
				}
				else if (root->right != NULL) {
					root = root->right;
					root->father = NULL;
				}
			}
			sign = 0;
		}
	}
	return 0;
}
