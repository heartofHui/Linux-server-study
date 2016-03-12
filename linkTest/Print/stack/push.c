/*************************************************************************
    > File Name: push.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年02月22日 15:56:04
 ************************************************************************/
extern char stack[512];
extern int top;
void push(char c)
{
	stack[++top];
}

