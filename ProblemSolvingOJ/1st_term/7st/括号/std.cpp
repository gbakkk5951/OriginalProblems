#include <bits/stdc++.h>
using namespace std;
const int mxs = 1e5 + 10;
const int inf = 0x3f3f3f3f;
/* Used to distinguish our stack and STL stack container. */
namespace MyStack
{
    /* The upper limit of the number of elements in the stack. */
    const int MaxSize = 200000;

    struct stack
    {
        /* Data area in the stack is implemented in the form of an array. The current space is values[0 ~ top - 1]. If top = 0, the stack is empty. */
        int values[MaxSize];

        /*  The position of the top of the stack. */
        int top;

        /*
            initialization
             1,  Clear the data area in the stack.
             2， Assign top to 0.
        */
        void init()
        {
			top = 0;
        }

        /*
            Put x on the top of the stack.
            If the stack is full at this time (top == MaxSize), this operation is invalid, and return false.
            Otherwise, add x to the top of the stack and return true.
        */
        bool push(int x)
        {	
			if (top == MaxSize) return false;
			values[top++] = x;
			return true;
        }

        /*
            Pop the top element of the stack.
            If the stack is empty(top == 0), return -inf, which means the operation is invalid.
            Otherwise, clear the top element of the stack to 0 and update the top position.
        */
        int pop()
        {
			if (top == 0) return -inf;
			return values[--top];
        }

        /*
            Get the top element of the stack.
            If the stack is empty(top == 0), return -inf, which means this operation is illegal.
            Otherwise, return the top element of the stack.
        */
        int getTop()
        {
			if (top == 0) return -inf;
			return values[top - 1];
        }

        /*
            Returns the number of elements in the stack (return 'top').
        */
        int getNum()
        {
			return top;
        }
		int empty() {
			return top == 0;
		}
    };
}
char input[mxs];
char const * output[2] = {"no", "yes"};
int main()
{
	ios::sync_with_stdio(false);
    using MyStack::stack;
    stack s;
	int T;
	cin >> T;
	while (T--) {
		int flag = 1;
		s.init();
		cin >> input;
		for (int i = 0; input[i] && flag; ++i) {
			if (input[i] == '(') {
				s.push(0);
			} else {
				assert(input[i] == ')');
				flag &= s.pop() == 0;
			}
		}
		flag &= s.empty();
		cout << output[flag] << endl;
	}
    return 0;
}

