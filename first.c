//#define _GNU_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/* 
 * Определение простых множителей натурального числа.
 * Чтение числа происходит из стандартного входа.
 * При некорректных данных выводится [error].
 */


// Флаги состояния при чтении числа
#define IN_DIG 1 // Внутри числа
#define BEFORE_DIG -1 // Не дошли до числа 
#define AFTER_DIG 0 // Вышли из числа


typedef unsigned long long ull_t;
const ull_t PREV_MAX_VAL = (ull_t)1e+18;


size_t add_val(char** line, const char val, size_t* true_size, size_t* size)
{
	if (*true_size == *size)
		{
			char* tmp = (char*)realloc(*line,(2*(*size)+1)*sizeof(char));
			if (tmp == NULL)
			{
				free(*line);
				return 0;
			}

			*size = 2*(*size)+1;
			*line = tmp;
		}
	(*line)[(*true_size)++] = val;
	return *size;

}

// Чтение строки из стандартного входа
size_t readline(char **line)
{
	int cur = 0;
	size_t size=0, true_size=0;
	while ((cur = getchar()) != EOF)
	{
		if (cur == '\n')
		{
			break;
		}
		if (add_val(line, cur, &true_size, &size) == 0)
		{
			return 0;
		}
	}

	if (add_val(line, '\0', &true_size, &size) == 0)
	{
		return 0;
	}
	
	return true_size;
}

// Преобразование строки в натуральное число не более 2^63 -1
// Возвращает 0, если входные данные не корректны.
ull_t get_digit(char* line)
{
	ull_t res = 0;
	char state = BEFORE_DIG;
	for (char* i=line; *i; ++i)
	{
		if (res > LLONG_MAX)
		{
			free(line);
			return 0;
		}

		if (*i >= '0' && *i <='9' && state)
		{ 
			if (res > (ull_t)PREV_MAX_VAL)
			{
				free(line);
				return 0;
			}

			res = res*10 + *i-'0';
			state = IN_DIG;
		}
		else if (*i == ' ' || *i == '\n')
		{
			if (state == IN_DIG)
			{
				state = AFTER_DIG;
			}
		}
		else
		{
			free(line);
			return 0;
		}
	}

	free(line);

	return res;
}


// Создание массива простых множителей числа.
// Возвращает NULL, если создание не удалось.
ull_t* factor(ull_t num)
{
	ull_t* tmp = NULL;
	ull_t* res = (ull_t*)malloc(sizeof(ull_t));
	
	if (!res)
	{
		return NULL;
	}
	res[0] = 1;

	ull_t div = 2;
	size_t cnt = 1;
	while (num != 1 && div*div <= num)
	{
		if (num % div)
		{
				++div;
		}
		else
		{
			tmp = realloc(res, (++cnt)*sizeof(ull_t));
			if (!tmp)
			{
				free(res);
				return NULL;
			}

			res = tmp;
			res[cnt-1] = div;
			num /= div;
		}
	} 

	tmp = realloc(res, (cnt+2)*sizeof(ull_t));
	if (!tmp)
	{
		free(res);
		return NULL;
	}
	
	res = tmp;
	if (num != 1)
	{
		res[cnt++] = num;
	}
	res[cnt] = 0;
	
	return res;
}


int main()
{
	char* line = NULL;
	size_t buf = readline(&line);
	if (buf == 0)
	{
		printf("[error]");
		return 0;
	}

	ull_t a;
	a = get_digit(line);
	ull_t* result = NULL;
	
	if (!a)
	{
		printf("[error]");
		return 0;
	}
	
	result = factor(a);
	if (!result)
	{
		printf("[error]");
		return 0;
	}

	for (int i = 0; result[i]; ++i)
	{
		printf("%lli ", result[i]);
	}	
	free(result);	
	return 0;
}
