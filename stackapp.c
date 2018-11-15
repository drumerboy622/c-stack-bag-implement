/*	Author: Matthew Solbrack */
/*	Date: 10/15/2018 */
/*	File: stack.c: Stack application. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string
	pre: s is not null
*/
char nextChar(char* s)
{
	static int i = -1;
	char c;
	++i;
	c = *(s+i);
	if ( c == '\0' )
		return '\0';
	else
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string
	pre: s is not null
	post:
*/
int isBalanced(char* s)
{
    assert(s != NULL);
    DynArr *parenthesesStack = newDynArr(12);
	char check;

	do {
            check = nextChar(s);

            /* Add the character to the stack for the opening brackets */
            if (check == '(' || check == '{' || check == '[')
            {
                addDynArr(parenthesesStack, check);
            }

            /* check is the closing brackets are balanced with what is ontop of the stack */
            else if (check == ')' || check == '}' || check == ']')
            {
                if (topDynArr(parenthesesStack) == '(' && check == ')')
                {
                    popDynArr(parenthesesStack);
                }
                else if (topDynArr(parenthesesStack) == '{' && check == '}')
                {
                    popDynArr(parenthesesStack);
                }
                else if (topDynArr(parenthesesStack) == '[' && check == ']')
                {
                    popDynArr(parenthesesStack);
                }
            }
		} while (check != '\0');

    /* If the stack comes back empty it is balanced */
	if (sizeDynArr(parenthesesStack) == 0)
    {
        deleteDynArr(parenthesesStack);
        return 1;
    }
    /* If the stack is not empty it is unbalanced */
	else
    {
        deleteDynArr(parenthesesStack);
        return 0;
    }
}

int main(int argc, char* argv[]){

	char* s=argv[1];
	int res;

	printf("Assignment 2\n");
	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else
		printf("The string %s is not balanced\n",s);

	return 0;
}

