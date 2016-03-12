/*************************************************************************
    > File Name: pop.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年02月22日 15:57:10
 ************************************************************************/
extern char stack[512];
extern int top;
char pop()
{
	return stack[top--];
}
