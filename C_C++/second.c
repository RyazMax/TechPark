// Автор Рязанов Максим АПО-13
/*
Условие:
Парсер арифметических выражений ("+ - * / ( ) ")
*/

#include <stdio.h>
#include <stdlib.h>

// Возвращает новый размер кучи, 0 - если выделение памяти не удалось
size_t addChar(char** line, const char val, size_t* trueSize, size_t* size)
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
	if (*trueSize == *size) {
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
	(*line)[(*trueSize)++] = val;
	return *size;
}


// Чтение строки из стандартного входа
size_t readLine(char **line)
{
	/*
	line - результирующая строка
	cur - текущий считанный символ
	size - размер кучи
	trueSize - используемый размер массива
	*/

	int cur = 0;
	size_t size=0, trueSize=0;
	while ((cur = getchar()) != EOF) {
		if (cur == '\n') {
			break;
		}

		if (addChar(line, cur, &trueSize, &size) == 0) {
			return 0;
		}
	}

	if (addChar(line, '\0', &trueSize, &size) == 0) {
		return 0;
	}
	
	return trueSize;
}

typedef struct Lexem {
    float value;
    enum type {
        DIG, // Цифра
        ADD, // Cложение
        SUB, // Вычитание
        MUL, // Умножение
        DIV, // Деление
        L_BRACE, // Левая скобка
        R_BRACE // Правая скобка
    } type;
} Lexem;

size_t addLexem(Lexem** destination, Lexem value, size_t *head, size_t *size)
{
    if (destination == NULL) {
        return 0;
    }

	// Расширение кучи
	if (*head == (*size-1)) {
			Lexem* tmp = (Lexem*)realloc(*destination, (2*(*size)+1)*sizeof(Lexem));
			if (tmp == NULL) {
                if (*destination != NULL) {
				    free(*destination);
                }
				return 0;
			}

			*size = 2*(*size)+1;
			*destination = tmp;
		}

	// Добавление элемента	
	(*destination)[++(*head)] = value;
	return *size;
}

Lexem* buildPostfix(Lexem *originArr, size_t size) 
{
    if (originArr == NULL) {
        return NULL;
    }

    // Результирующий массив
    size_t resArrHead = 0;
    size_t resArrSize = 1;
    Lexem* resArr = (Lexem*) malloc(resArrSize*sizeof(Lexem));
    if (resArr == NULL) {
        return NULL;
    }

    // Вспомогательный стек
    size_t subBuffHead = 0;
    size_t subBuffSize = 1;
    Lexem* subBuff = (Lexem*) malloc(subBuffSize*sizeof(Lexem));
    if (subBuff == NULL) {
        free(resArr);
        return NULL;
    }

    for (size_t i = 0; i<size; ++i) {
        if (originArr[i].type == DIG) {
            addLexem(&resArr, originArr[i], &resArrHead, resArrSize);
        }
        else if (subBuffHead == 0) {
            addLexem(&subBuff, originArr[i], &subBuffHead, &subBuffSize);
        } else {
            switch (originArr[i].type) {
                case SUB:
                case ADD:
                    // При попытке добавления сложения или вычитания
                    switch (subBuff[subBuffHead].type) {
                        case SUB:
                        case ADD:
                        сase DIV:
                        case MULL
                            addLexem(&resArr, subBuff[subBuffHead--],
                                &resArrHead, &resArrSize);
                            break;
                        case DIV:
                        case MUL:
                            a
                    }
            }
        }
    }

    return NULL;
}

int main()
{
    char *line = NULL;
    size_t lineLength = readline(line);
    printf("%s", line);
    return 0;
}