#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_EXP_LENGTH 64
#define INITIAL_RES_LENGTH 10

typedef enum
{
	PLUS = '+',
	MINUS = '-',
	MULT = '*',
	DIV = '/',
	OPEN_BRACKET = '(',
	CLOSE_BRACKET = ')'
} Sign;

void printError()
{
	printf("[error]");
}

int getPriority(char sign)
{
	if (sign == OPEN_BRACKET)
	{
		return 0;
	}
	else if (sign == PLUS || sign == MINUS)
	{
		return 1;
	}
	else 
	{
		return 2;
	}
}

int isDigit(char symbol)
{
	if (symbol - '0' >= 0 && symbol - '9' <= 0)
	{
		return 1;
	}
	return 0;
}

int isExpCorrect(char *exp, int len)
{

	int signCount = 0;
	int bracketCount = 0;

	for (int i = 0; i < len; i++)
	{
		if (exp[i] == PLUS || exp[i] == MINUS || exp[i] == MULT || exp[i] == DIV)
		{
			signCount++;

			// *1+2, 1+2+
			if (exp[i] != MINUS && i == 0 || i == len - 1)
			{
				return 0;
			}
		}
		else
		{
			signCount = 0;
		}

		//there are more than two signs together
		if (signCount > 1)
		{
			return 0;
		}
		if (exp[i] == OPEN_BRACKET)
		{
			bracketCount++;
			if (i > 0)
			{
				// 1(2+3)
				if (isDigit(exp[i - 1]))
				{
					return 0;
				}
				// *(1+2)
				if (i == 1 && exp[i - 1] != MINUS)
				{
					return 0;
				}
			}
			//(+1*2)
			if (!isDigit(exp[i + 1]) && exp[i + 1] != MINUS)
			{
				return 0;
			}
			
		}
		else if (exp[i] == CLOSE_BRACKET)
		{
			bracketCount--;
			// )1+2
			if (bracketCount < 0)
			{
				return 0;
			}
			if (i > 0)
			{
				// 1*(2+)
				if (!isDigit(exp[i - 1]))
				{
					return 0;
				}

				// (1+2)3*4+(5*6)(7+8)
				if (isDigit(exp[i + 1]) || exp[i + 1] == OPEN_BRACKET)
				{
					return 0;
				}
			}
		}


	}

	// nubmer of opening brackets is not equal to number of closing ones
	if (bracketCount != 0)
	{
		return 0;
	}

	return 1;
}

char* toPostfix(char* exp, int expLen)
{
	char* postfix = NULL;
	if (!(postfix = (char*)malloc((expLen + 1) * sizeof(char))))
	{
		return NULL;
	}

	char* operators = NULL;
	if (!(operators = (char*)malloc(expLen * sizeof(char))))
	{
		return NULL;
	}

	int postfixIndex = 0;
	int operatorsIndex = 0;
	for (int i = 0; i < expLen; i++)
	{
		char token = exp[i];
		if (isDigit(token))
		{
			postfix[postfixIndex++] = token;			
		}
		else
		{
			if (token == PLUS || token == MINUS || token == MULT || token == DIV)
			{
				postfix[postfixIndex++] = '|';
				while (operatorsIndex > 0 && getPriority(operators[operatorsIndex - 1]) >= getPriority(token))
				{
					postfix[postfixIndex++] = operators[--operatorsIndex];
				}
				operators[operatorsIndex++] = token;
			}
			else if (token == OPEN_BRACKET)
			{
				operators[operatorsIndex++] = token;
			}
			else if (token == CLOSE_BRACKET)
			{
				while (operatorsIndex > 0 && operators[operatorsIndex - 1] != OPEN_BRACKET)
				{
					postfix[postfixIndex++] = operators[--operatorsIndex];
				}
				operatorsIndex--;
			}
		}
	}

	for (int i = operatorsIndex - 1; i >= 0; i--)
	{
		postfix[postfixIndex++] = operators[i];
	}
	postfix[postfixIndex] = '\0';

	free(operators);
	return postfix;
}

char* evalPostfix(char* postfix)
{
	/*
	char* res = NULL;
	if (!(res = (char*)malloc(INITIAL_RES_LENGTH * sizeof(char))))
	{
		return NULL;
	}
	int resIndex = 0;
	for (int i = 0; postfix[i] != '\0'; i++)
	{
		if (isDigit(postfix[i]))
		{
			res[operandsIndex++] = postfix[i];
		}
		else
		{
			rcalculate(res[--operandsIndex], res[--operandsIndex], postfix[i]);
		}
	}


	return res;
	*/
	return NULL;
}

char* eval(char *exp, int expLen)
{
	char* postfix = toPostfix(exp, expLen);
	if (!postfix)
	{
		return NULL;
	}
	printf("%s", postfix);
	char* res = evalPostfix(postfix);

	return res;
}

int main()
{
	char *exp = NULL;
	int maxExpLen = INITIAL_EXP_LENGTH;
	
	if (!(exp = (char*)malloc(maxExpLen * sizeof(char))))
	{
		printError();
		return 0;
	}

	int expLen = 0;
	char symbol = 0;

	while (scanf("%c", &symbol) != EOF)
	{
		if (symbol == ' ' || symbol == '\n')
		{
			continue;
		}
		// -1+2, (-2+3)
		if (symbol == '-' && (expLen == 0 || exp[expLen - 1] == '('))
		{
			exp[expLen++] = '0';
		}
		exp[expLen++] = symbol;
		if (expLen == maxExpLen)
		{
			if (!(exp = (char*)realloc(exp, expLen * 2 * sizeof(char))))
			{
				printError();
				return 0;
			}
			maxExpLen *= 2;
		}
		printf("%c",symbol);
	}

	if (!isExpCorrect(exp, expLen))
	{
		printError();
		return 0;
	}

	char *res = eval(exp, expLen);
	if (!res)
	{
		printError();
		return 0;
	}
	//printf("%s", exp);
	/*
	for (int i = 0; i < expLen; i++)
	{
		printf("%d\n", exp[i]);
	}
	*/

	free(res);
	free(exp);
	return 0;
}