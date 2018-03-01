#define _POSIX_C_SOURCE 


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define IN_DIG 1
#define BEFORE_DIG -1
#define AFTER_DIG 0


typedef unsigned long long ull_t;
const ull_t PREV_MAX_VAL = (ull_t)1e+18;


ull_t get_digit()
{
	char* line = NULL;
	size_t size = 0;
	ssize_t buff = 0;
	buff = getline(&line, &size, stdin); 

	if (line == NULL)
	{
		return 0;
	}
	
	if (buff == -1)
	{
		free(line);
		return 0;
	}

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
			if (res < (ull_t)PREV_MAX_VAL)
				res = res*10 + *i-'0';
			else
			{
				free(line);
				return 0;
			}
			state = IN_DIG;
		}
		else if (*i == ' ' || *i == '\n')
		{
			if (state == IN_DIG)
			state = AFTER_DIG;
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


ull_t* factor(ull_t num)
{
	ull_t* tmp = NULL;
	ull_t* res = (ull_t*)malloc(sizeof(ull_t));
	if (!res)
		return NULL;
	res[0] = 1;

	ull_t div = 2;
	size_t cnt = 1;
	while (num != 1 && div*div <= num)
	{
		if (num % div)
			++div;
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
	else
	{
		res = tmp;
		if (num != 1)
			res[cnt++] = num;
		res[cnt] = 0;
	}

	return res;
}


int main()
{
	ull_t a;
	a = get_digit();
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
		printf("%lli ",result[i]);
		
	free(result);	
	return 0;
}

