#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LINE_SIZE 64
#define LINE_LENGTH 128

void printError()
{
	printf("[error]");
}

char** removeExtraSpaces(char** lines, int size, int lineLength)
{
	
	for (int i = 0; i < size; i++)
	{
		int space = 0;
		char *buffer = NULL;

		if (!(buffer = (char*)malloc(lineLength * sizeof(char))))
		{
			printError();
			return NULL;
		}

		for (int sourceIndex = 0, destIndex = 0; (buffer[destIndex] = lines[i][sourceIndex]) != '\0'; sourceIndex++)
		{
			if (buffer[destIndex] == ' ')
			{
				if (space)
				{
					continue;
				}
				space = 1;
			}
			else
			{
				space = 0;
			}
			destIndex++;
		}
		free(lines[i]);
		lines[i] = buffer;
	}

	return lines;
}

int main()
{
	char symbol;
	char **lines = NULL;
	int linesCount = 0;
	int currentMaxLineCount = ARRAY_LINE_SIZE;
	int currentMaxLineLength = LINE_LENGTH;
	
	if (!(lines = (char**)malloc(currentMaxLineCount * sizeof(char*))))
	{
		printError();
		return 0;
	}
	
	int lineLength = 0;
	if (!(lines[0] = (char*)malloc(currentMaxLineLength * sizeof(char))))
	{
		printError();
		return 0;
	}
	while (scanf("%c", &symbol) != EOF)
	{
		
		if (linesCount == 0)
		{
			linesCount++;
		}
		//новая строка
		if (symbol == '\n')
		{			
			lines[linesCount - 1][lineLength] = '\0';
			lineLength = 0;
			if (!(lines[linesCount] = (char*)malloc(currentMaxLineLength * sizeof(char))))
			{
				printError();
				return 0;
			}
			linesCount++;
			if (linesCount >= currentMaxLineCount)
			{
				
				if (!(lines = (char**)realloc(lines, currentMaxLineCount * 2 * sizeof(char*))))
				{
					printError();
					return 0;
				}
				currentMaxLineCount *= 2;
			}
			continue;
		}

		//запись символа в массив
		lines[linesCount - 1][lineLength++] = symbol;
		
		//массив полон
		if (lineLength == currentMaxLineLength)
		{
			if (!(lines[linesCount - 1] = (char*)realloc(lines[linesCount - 1], currentMaxLineLength * 2 * sizeof(char))))
			{
				
				printError();
				return 0;
			}
			currentMaxLineLength *= 2;
		}	
	}
	if (linesCount > 0)
	{
		lines[linesCount - 1][lineLength] = '\0';
	}
	
	//удаление лишних пробелов
	if((lines = removeExtraSpaces(lines, linesCount, currentMaxLineLength)) == NULL)
	{
		printError();
		return 0;
	}
	
	//вывод обработанных строк
	for (int i = 0; i < linesCount; i++)
	{
		printf("%s\n", lines[i]);
	}

	//освобождение памяти
	free(lines[0]);
	for (int i = 1; i < linesCount; i++)
	{
		free(lines[i]);
	}
	free(lines);
	
	return 0;
}