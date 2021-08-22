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
str[0] = number / 10 + 0x30;
str[1] = number % 10 + 0x30;
}
