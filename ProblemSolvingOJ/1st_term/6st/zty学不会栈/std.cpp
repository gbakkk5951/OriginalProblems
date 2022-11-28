/* Please do not introduce '#include <bits/stdc++.h>', otherwise if the namespace 'std' is declared, the definition will conflict with '#include <stack>'. */
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

/* We default the absolute value of the elements in the stack will not exceed 10^9, so in the main function, we use the return value -inf to mark the failure of this operation. */
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
    };
}

int main()
{
    /* Declare to use the namespace MyStack, otherwise we cannot introduce the struct we defined under MyStack. */
    using namespace MyStack;

    stack st;
    int n, m;
    scanf("%d", &n);
    st.init();
    for (int i = 0; i < n; i++)
    {
        int opt, x;
        scanf("%d", &opt);
        if (opt == 1)
        {
            scanf("%d", &x);
            bool status = st.push(x);
            if (status == false)
            {
                printf("The stack is full.\n");
            }
            else
            {
                printf("push OK.\n");
            }
        }

        else if (opt == 2)
        {
            x = st.pop();
            if (x == -inf)
            {
                printf("The stack is empty.\n");
            }
            else
            {
                printf("POP.\n");
            }
        }

        else if (opt == 3)
        {
            x = st.getTop();
            if (x == -inf)
            {
                printf("The stack is empty.\n");
            }
            else
            {
                printf("%d\n", x);
            }
        }

        else if (opt == 4)
        {
            x = st.getNum();
            printf("%d\n", x);
        }
    }
    return 0;
}
