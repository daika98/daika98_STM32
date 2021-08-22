#include "char_user.h"

void str_empty(char str[]){
	int i = 0;
	while (str[i]) {
		str[i] = '\0';
		i++;
	}
}

int length_str(char str[]) {
	int i = 0;
	while (str[i]) {
		i++;
	}
	return i;
}

void catenate_str (char str1[], char str2[]) {
	int i = 0;
	int length = length_str(str1);
	
	while (str2[i]) {
		str1[length + i] = str2[i];
		i++;
	}
}

void int2char(int number, char str[])
{
	int length = 0;
	int a = number;
	int i = 0;
	int b[10];
	
	if (a == 0) {
		length = 1;
		b[0] = 0;
	}
 	
	while ( a > 0 ) {
		length++;
		b[i] = a % 10;
		a /= 10;
		i++;
	}
	for (i = 0; i < length; i++){
			str[i] = b[length - i - 1]  + 0x30;
	}
	}
