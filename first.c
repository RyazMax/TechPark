// Автор Рязанов Максим АПО-13
/* 
 * Определение и вывод простых множителей натурального числа.
 * Чтение числа происходит из стандартного входа.
 * При некорректных данных выводится [error].
 */

#include <stdio.h>
#include <stdlib.h>


// Флаги состояния при чтении числа
#define IN_DIG 1 // Внутри числа
#define BEFORE_DIG -1 // Не дошли до числа 
#define AFTER_DIG 0 // Вышли из числа


typedef unsigned long long ull_t;
const ull_t PREV_MAX_VAL = (ull_t)1e+18; // Максимальное допустимое круглое значение
const ull_t MAX_VAL = (((ull_t)1)<<63)-1; // Максимальное допустимое значение


// Добавление значения в конец массива типа сhar
// Возвращает новый размер кучи, 0 - если выделение памяти не удалось
size_t add_char(char** line, const char val, size_t* true_size, size_t* size)
{
	/*
	line - изменяемый массив
	val - добавляемое значение
	true_size - используемый размер массива
	size - размер кучи
	*/

	if (line == NULL) {
		return 0;
	}

	// Расширение кучи
	if (*true_size == *size) {
			char* tmp = (char*)realloc(*line, (2*(*size)+1)*sizeof(char));
			if (tmp == NULL) {
				if (*line != NULL) {
					free(*line);
				}
				return 0;
			}

			*size = 2*(*size)+1;
			*line = tmp;
		}

	// Добавление элемента	
	(*line)[(*true_size)++] = val;
	return *size;
}


// Добавление значения в конец массива типа unsigned long long
// Возвращает новый размер кучи, 0 - если выделение памяти не удалось
size_t add_ull(ull_t** line, const ull_t val, size_t* true_size, size_t* size)
{
	/*
	line - изменяемый массив
	val - добавляемое значение
	true_size - используемый размер массиваs
	size - размер кучи
	*/

	if (line == NULL) {
		return 0;
	}

	//Расширение кучи
	if (*true_size == *size) {
			ull_t* tmp = (ull_t*)realloc(*line, (2*(*size)+1)*sizeof(ull_t));
			if (tmp == NULL) {
				if (*line != NULL) {
					free(*line);
				}
				return 0;
			}

			*size = 2*(*size)+1;
			*line = tmp;
		}

	// Добавление нового элемента
	(*line)[(*true_size)++] = val;
	return *size;
}


// Чтение строки из стандартного входа
size_t readline(char **line)
{
	/*
	line - результирующая строка
	cur - текущий считанный символ
	size - размер кучи
	true_size - используемый размер массива
	*/

	int cur = 0;
	size_t size=0, true_size=0;
	while ((cur = getchar()) != EOF) {
		if (cur == '\n') {
			break;
		}

		if (add_char(line, cur, &true_size, &size) == 0) {
			return 0;
		}
	}

	if (add_char(line, '\0', &true_size, &size) == 0) {
		return 0;
	}
	
	return true_size;
}


// Преобразование строки в натуральное число не более 2^63 -1
// Возвращает 0, если входные данные не корректны.
ull_t get_digit(char* line, size_t line_length)
{
	/*
	line - исходная строка
	res - результирующее число
	state - положение относительно цифровых символов в строке
	*/

	ull_t res = 0;
	char state = BEFORE_DIG;
	for (size_t i=0; i<line_length-1; ++i)	{
		if (line[i] >= '0' && line[i] <='9' && state != AFTER_DIG) { 
			if (res > (ull_t)PREV_MAX_VAL) {
				free(line);
				return 0;
			}

			res = res*10 + line[i]-'0';
			state = IN_DIG;
		} else if (line[i] == ' ' || line[i] == '\n')	{
			if (state == IN_DIG) {
				state = AFTER_DIG;
			}
		}
		// Если есть нецифровые символы или второе число
		else {
			free(line);
			return 0;
		}

		// Проверка переполнения
		if (res > MAX_VAL) {
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
	/*
	num - исходное число
	size - размер кучи
	true_size - используемый размер массива
	res - результирующий массив из множителей
	div - текущий делитель
	*/

	size_t size=0, true_size=0;
	ull_t* res = NULL;
	
	if (add_ull(&res, 1, &true_size, &size)==0)	{
		return NULL;
	}
	
	ull_t div = 2;
	while (num != 1 && div*div <= num) {
		if (num % div) {
				++div;
		} else {
			if (add_ull(&res, div, &true_size, &size)==0) {
				return NULL;
			}
			num /= div;
		}
	} 
	
	if (num != 1) {
		if (add_ull(&res, num, &true_size, &size)==0) {
			return NULL;
		}
	}
	
	if (add_ull(&res, 0, &true_size, &size)==0)	{
		return NULL;
	}
	
	return res;
}


int main()
{
	/*
	line - входная строка
	tmp - рабочая переменная
	number - исходное число
	result - массив множителей
	*/

	char* line = NULL;
	size_t line_length = readline(&line);
	if (line_length == 0) {
		printf("[error]");
		return 0;
	}

	ull_t number;
	number = get_digit(line, line_length);
	
	if (number == 0) {
		printf("[error]");
		return 0;
	}
	
	ull_t* result = factor(number);
	if (result == NULL)	{
		printf("[error]");
		return 0;
	}

	for (size_t i = 0; result[i]; ++i)	{
		printf("%lli ", result[i]);
	}	

	free(result);	
	return 0;
}
