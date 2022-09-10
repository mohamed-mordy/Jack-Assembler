#include"dict.h"
#include<string.h>

typedef struct{
	char assembly[20];
	char machine[10];
} translation;

char *get_dest(char *this, int that)
{
	translation arr[] = {
		{"null\0", "000\0"},
		{"M\0", "001\0"},
		{"D\0", "010\0"},
		{"MD\0", "011\0"},
		{"A\0", "100\0"},
		{"AM\0", "101\0"},
		{"AD\0", "110\0"},
		{"AMD\0", "111\0"}
	};
	for(int i = 0; i < 8; i++) {
		if(!strcmp(this, arr[i].assembly)) {
			strcpy(this, arr[i].machine);
			return this;
		}
	}
	printf("syntax error\ncheck line %d\n", that);
	exit(1);
}

char *get_comp(char *this, int that)
{
	translation arr[] = {
		{"0\0", "0101010\0"},
		{"1\0", "0111111\0"},
		{"-1\0", "0111010\0"},
		{"D\0", "0001100\0"},
		{"A\0", "0110000\0"},
		{"M\0", "1110000\0"},
		{"!D\0", "0001101\0"},
		{"!A\0", "0110011\0"},
		{"!M\0", "1110001\0"},
		{"A+1\0", "0110111\0"},
		{"-D\0", "0001111\0"},
		{"-A\0", "0110011\0"},
		{"-M\0", "1110011\0"},
		{"D+1\0", "0011111\0"},
		{"M+1\0", "1110111\0"},
		{"D-1\0", "0001110\0"},
		{"A-1\0", "0110010\0"},
		{"M-1\0", "1110010\0"},
		{"D+A\0", "0000010\0"},
		{"D+M\0", "1000010\0"},
		{"D-A\0", "0010011\0"},
		{"D-M\0", "1010011\0"},
		{"A-D\0", "0000111\0"},
		{"M-D\0", "1000111\0"},
		{"D&A\0", "0000000\0"},
		{"D&M\0", "1000000\0"},
		{"D|A\0", "0010101\0"},
		{"D|M\0", "1010101\0"}
	};
	for(int i = 0; i < 28; i++) {
		if(!strcmp(this, arr[i].assembly)) {
			strcpy(this, arr[i].machine);
			return this;
		}
	}
	printf("syntax error\ncheck line %d\n", that);
	exit(1);
}

char *get_jump(char *this, int that)
{
	translation arr[] ={
		{"null\0", "000\0"},
		{"JGT\0", "001\0"},
		{"JEQ\0", "010\0"},
		{"JGE\0", "011\0"},
		{"JLT\0", "100\0"},
		{"JNE\0", "101\0"},
		{"JLE\0", "110\0"},
		{"JMP\0", "111\0"}
	};
	for(int i = 0; i < 8; i++) {
		if(!strcmp(this, arr[i].assembly)) {
			strcpy(this, arr[i].machine);
			return this;
		}
	}
	printf("syntax error\ncheck line %d\n", that);
	exit(1);
}

