#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_EXP_LENGTH 64
#define INITIAL_NUMBERS_LENGTH 10
#define INITIAL_NUMBER_LENGTH 10

#define _CRT_SECURE_NO_WARNINGS

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

int getDigit(char digit)
{
	return digit - '0';
}

char toChar(int digit)
{
	return '0' + digit;
}

char* sum(char *firstOperand, int firstOperandLen, char *secondOperand, int secondOperandLen)
{
	char* res = NULL;
	int maxLen = 0;
	int minLen = 0;
	char *maxOperand = NULL;
	char *minOperand = NULL;
	if (firstOperandLen > secondOperandLen)
	{
		maxLen = firstOperandLen;
		maxOperand = firstOperand;
		minOperand = secondOperand;
		minLen = secondOperandLen;
	}
	else
	{
		maxLen = secondOperandLen;
		minOperand = firstOperand;
		maxOperand = secondOperand;
		minLen = firstOperandLen;
	}

	if (!(res = (char*)malloc((maxLen + 2) * sizeof(char))))
	{
		return NULL;
	}
	int remain = 0;
	for (int i = 0; i < minLen; i++)
	{
		int addition = getDigit(firstOperand[i]) + getDigit(secondOperand[i]) + remain;
		if (addition > 9)
		{
			remain = 1;
			addition -= 10;
		}
		else
		{
			remain = 0;
		}
		res[i] = toChar(addition);
	}
	for (int i = minLen; i < maxLen; i++)
	{
		int addition = getDigit(maxOperand[i]) + remain;
		if (addition > 9)
		{
			remain = 1;
			addition -= 10;
		}
		else
		{
			remain = 0;
		}
		res[i] = toChar(addition);
	}
	if (remain)
	{
		res[maxLen++] = '1';
	}
	res[maxLen] = '\0';
	return res;
}

char* minus(char *firstOperand, int firstOperandLen, char *secondOperand, int secondOperandLen)
{
	return NULL;
}

char* mult(char *firstOperand, int firstOperandLen, char *secondOperand, int secondOperandLen)
{
	return NULL;
}
char* div(char *firstOperand, int firstOperandLen, char *secondOperand, int secondOperandLen)
{
	return NULL;
}

int calcLastTwoOperands(char **operandsIndex, int currentOperandIndex, char sign)
{
	char *firstOperand = operandsIndex[currentOperandIndex - 1];
	char *secondOperand = operandsIndex[currentOperandIndex];
	int firstOperandLen = strlen(firstOperand);
	int secondOperandLen = strlen(secondOperand);
	
	char *result = NULL;
	char *(*eval)(char *, int, char *, int);
	switch (sign)
	{
	case PLUS:
		eval = sum;
		break;
	case MINUS:
		eval = minus;
		break;
	case MULT:
		eval = mult;
	case DIV:
		eval = div;
		break;
	default:
		return 0;
	}
	result = eval(firstOperand, firstOperandLen, secondOperand, secondOperandLen);
	
	if (!result)
	{
		return 0;
	}

	free(operandsIndex[currentOperandIndex]);
	free(operandsIndex[currentOperandIndex - 1]);
	operandsIndex[currentOperandIndex - 1] = result;

	return 1;

}

char* evalPostfix(char *postfix)
{
	char **operandsIndex = NULL;
	int currentOperandIndex = 0;
	if (!(operandsIndex = (char**)malloc(INITIAL_NUMBERS_LENGTH * sizeof(char*))))
	{
		return NULL;
	}
	if (!(operandsIndex[0] = (char*)malloc(INITIAL_NUMBER_LENGTH * sizeof(char))))
	{
		return NULL;
	}

	int operandLen = 0;
	int maxOperandLen = INITIAL_NUMBER_LENGTH;
	for (int i = 0; postfix[i] != '\0'; i++)
	{
		if (postfix[i] == '|')
		{
			
			operandsIndex[currentOperandIndex][operandLen] = '\0';
			currentOperandIndex++;
			if (!(operandsIndex[currentOperandIndex] = (char*)malloc(INITIAL_NUMBER_LENGTH * sizeof(char))))
			{
				return NULL;
			}
			maxOperandLen = INITIAL_NUMBER_LENGTH;
			operandLen = 0;
			
		}
		else if (isDigit(postfix[i]))
		{
			
			operandsIndex[currentOperandIndex][operandLen++] = postfix[i];
			if (operandLen == maxOperandLen)
			{
				if (!(operandsIndex[currentOperandIndex] = (char*)realloc(operandsIndex[currentOperandIndex], maxOperandLen * 2 * sizeof(char))))
				{
					return NULL;
				}
				maxOperandLen *= 2;
			}
			operandsIndex[currentOperandIndex][operandLen + 1] = '\0';

		}
		else if (postfix[i] == MINUS || postfix[i] == PLUS || postfix[i] == MULT || postfix[i] == DIV)
		{
			int currentIndex = 0;
			if (currentOperandIndex == 1)
			{
				currentIndex = currentOperandIndex;
			}
			else
			{
				currentIndex = currentOperandIndex - 1;
			}
			if (!calcLastTwoOperands(operandsIndex, currentIndex, postfix[i]))
			{
				return NULL;
			}
			currentOperandIndex--;

		}
	}

	
	
	/*
	char *res = NULL;
	if (!(res = (char*)malloc((strlen(operandsIndex[0]) + 1) * sizeof(char))))
	{
		return NULL;
	}
	strncpy(res, operandsIndex[0], strlen(operandsIndex[0]));
	printf(" j ");
	free(operandsIndex[0]);
	return res;
	*/
	return operandsIndex[0];
}


char* eval(char *exp, int expLen)
{
	char* postfix = toPostfix(exp, expLen);
	if (!postfix)
	{
		return NULL;
	}
	
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
	printf("result = %s end", res);
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
