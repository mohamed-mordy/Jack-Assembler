#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include"functions.h"
#include"dict.h"

list_g* green_code_loader(const char* filename)
{
	FILE* fptr = fopen(filename, "r");

	if (fptr == NULL) {
		printf("error opening the file \n");
		exit(1);
	}

	list_g *head = malloc(sizeof(list_g));
	list_g *head_2_return = head;
	head->previous = NULL;
	int lineNumber = 1;
	while(1) {
		int m = 0;
		int i = 0;
		head -> line_no_green = lineNumber;
		while(1) {
			m = fscanf(fptr, "%c", &(head -> line[i]));
			if(m == EOF) {
				head -> line[i] = '\n';
				break;
			} 
			if((head -> line[i]) == '\n') 
				break;
			i++;
		}
		if(m == EOF)
			break;
		lineNumber++;
		head -> next = malloc(sizeof(list_g));
		list_g* tmp = head;
		head = head -> next;
		head -> previous = tmp;
	}
	head = head -> previous;
	free(head -> next);
	head -> next = NULL;
	fclose(fptr);
	return head_2_return;
}

list_p* pure_code_builder(list_g* green_head)
{
	if(green_head == NULL)
		error();
	list_p *pure_head = malloc(sizeof(list_p));
	pure_head->previous = NULL;
	list_p *pure_head_2_return = pure_head;
	int pure_line_number = 0;
	while(green_head != NULL) {
		int i = 0;
		int j = 0;
		char instruction[100];
		while(1) {
			if((green_head -> line[i]) == '\n') {
				instruction[j] = '\0';
				break;
			} else if(isspace(green_head -> line[i])) {
				i++;
				continue;
			} else if((green_head -> line[i] == '/') && (green_head -> line[i + 1] == '/')) {
				instruction[j] = '\0';
				break;
			} else {
				instruction[j] = green_head -> line[i];
				i++;
				j++;
			}
		}
		if(instruction[0] == '\0') {
			green_head = green_head -> next;
			continue;
		}
		strcpy(pure_head -> line, instruction);
		pure_head -> line_no_pure = pure_line_number;
		pure_line_number++;
		pure_head -> line_no_green = green_head -> line_no_green;
		green_head = green_head -> next;
		if(green_head == NULL)
			break;
		pure_head -> next = malloc(sizeof(list_p));
		list_p* tmp = pure_head;
		pure_head = pure_head -> next;
		pure_head -> previous = tmp;
	}
	pure_head -> next = NULL;
	if(pure_head -> line_no_pure == 0) {
		pure_head = pure_head -> previous;
		free(pure_head -> next);
		pure_head -> next = NULL;
	}
	return pure_head_2_return;
}

list_e *mid_exact_code(list_p *head_p, list_st *head_st)
{
	if(head_p == NULL || head_st == NULL) error();
	list_e* head_e = malloc(sizeof(list_e));
	list_e* head_e_2_return = head_e;
	head_e->previous = NULL;
	pair tmp_pair;
	int exact_code_line_number = 0;
	while(head_p != NULL) {
		if((head_p->line[0] == '(') && (head_p->line[strlen(head_p->line)-1] == ')')) {
			int i = strlen(head_p->line);
			substring(tmp_pair.symbol, head_p->line, 1, i-2);
			tmp_pair.value = exact_code_line_number;
			add_2_st(tmp_pair, head_st);
			head_p = head_p->next;
		} else {
			strcpy(head_e->line, head_p->line);
			head_e->line_no_green = head_p->line_no_green;
			head_e->line_no_exact = exact_code_line_number;
			exact_code_line_number++;
			head_p = head_p->next;
			head_e->next = malloc(sizeof(list_e));
			list_e* tmp = head_e;
			head_e = head_e->next;
			head_e->previous = tmp;
		}
	}

	if(head_e->line_no_exact == 0) {
		head_e = head_e->previous;
		free(head_e->next);
		head_e->next = NULL;
	}
	return head_e_2_return;
}

list_e *exact_code_builder(list_e *head, list_st *head_st)
{
	list_e *head_e = malloc(sizeof(list_e));
	list_e *head_e_2_return = head_e;
	pair tmp_pair;
	int mem_count = 16;
	while(head != NULL) {
		if((head->line[0] == '@')&&(isalpha(head->line[1]))) {
			int i = strlen(head->line);
			char buffer[50];
			substring(buffer, head->line, 1, i-1);
			strcpy(tmp_pair.symbol, buffer);
			if(search_st(tmp_pair.symbol, head_st)) {
				tmp_pair.value = get_value(tmp_pair.symbol, head_st);
				head_e->line_no_green = head->line_no_green;
				head_e->line_no_exact = head->line_no_exact;
				sprintf(head_e->line, "@%d",tmp_pair.value);
				head = head->next;
				head_e->next = malloc(sizeof(list_e));
				list_e* tmp = head_e;
				head_e = head_e->next;
				head_e->previous = tmp;
			} else {
				tmp_pair.value = mem_count;
				mem_count++;
				add_2_st(tmp_pair, head_st);
				head_e->line_no_green = head->line_no_green;
				head_e->line_no_exact = head->line_no_exact;
				sprintf(head_e->line, "@%d",tmp_pair.value);
				head = head->next;
				head_e->next = malloc(sizeof(list_e));
				list_e* tmp = head_e;
				head_e = head_e->next;
				head_e->previous = tmp;
			}
		} else {
			strcpy(head_e->line, head->line);
			head_e->line_no_green = head->line_no_green;
			head_e->line_no_exact = head->line_no_exact;
			head = head->next;
			head_e->next = malloc(sizeof(list_e));
			list_e* tmp = head_e;
			head_e = head_e->next;
			head_e->previous = tmp;
		}
	}
	while((head_e->line_no_exact) == 0 || (head_e->line_no_green) == 0) {
		head_e = head_e->previous;
		free(head_e->next);
		head_e->next = NULL;
	}

	return head_e_2_return;
}

void error(void)
{
	printf("undefined error\n");
	exit(1);
}

void drop_g(list_g *head_g)
{
	if(head_g == NULL)
		error();
	while(head_g != NULL) {
		list_g *tmp = head_g->next;
		free(head_g);
		head_g = tmp;
	}
}

void drop_p(list_p *head_p)
{
	if(head_p == NULL)
		error();
	while(head_p != NULL) {
		list_p *tmp = head_p->next;
		free(head_p);
		head_p = tmp;
	}
}

void drop_e(list_e *head_e)
{
	if(head_e == NULL)
		error();
	while(head_e != NULL) {
		list_e *tmp = head_e->next;
		free(head_e);
		head_e = tmp;
	}
}

void drop_st(list_st* head_st)
{
	if(head_st == NULL)
		error();
	while(head_st != NULL) {
		list_st* tmp = head_st -> next;
		free(head_st);
		head_st = tmp;
	}
}

static void substring(char* dst, const char* src, int from , int to)
{
	int j = 0;
	for(int i = from; i <= to; i++) {
		dst[j] = src[i];
		j++;
	}
	dst[j] = '\0';
}

list_st *initialize_st(void)
{
	list_st *head_st = malloc(sizeof(list_st));
	list_st *head_st_2_return = head_st;
	head_st->previous = NULL;
	list_st *tmp;
	for(int i = 0; i <= 9; i++) {
		sprintf(head_st -> record.symbol, "R%c", i + 48);
		head_st -> record.value = i;
		head_st -> next = malloc(sizeof(list_st));
		tmp = head_st;
		head_st = head_st -> next;
		head_st -> previous = tmp;
	}
	int j = 0;
	for(int i = 10; i <= 15; i++) {
		sprintf(head_st -> record.symbol, "R%c%c", 1 + 48, j + 48);
		head_st -> record.value = i;
		head_st -> next = malloc(sizeof(list_st));
		tmp = head_st;
		head_st = head_st -> next;
		head_st -> previous = tmp;
		j++;
	}

	strcpy(head_st->record.symbol, "SCREEN");
	head_st->record.value = 16384;
	head_st->next = malloc(sizeof(list_st));
	tmp = head_st;
	head_st = head_st->next;
	head_st->previous = tmp;

	strcpy(head_st->record.symbol, "KBD");
	head_st->record.value = 24576;
	head_st->next = malloc(sizeof(list_st));
	tmp = head_st;
	head_st = head_st->next;
	head_st->previous = tmp;

	strcpy(head_st->record.symbol, "SP");
	head_st->record.value = 0;
	head_st->next = malloc(sizeof(list_st));
	tmp = head_st;
	head_st = head_st->next;
	head_st->previous = tmp;

	strcpy(head_st->record.symbol, "LCL");
	head_st->record.value = 1;
	head_st->next = malloc(sizeof(list_st));
	tmp = head_st;
	head_st = head_st->next;
	head_st->previous = tmp;

	strcpy(head_st->record.symbol, "ARG");
	head_st->record.value = 2;
	head_st->next = malloc(sizeof(list_st));
	tmp = head_st;
	head_st = head_st->next;
	head_st->previous = tmp;

	strcpy(head_st->record.symbol, "THIS");
	head_st->record.value = 3;
	head_st->next = malloc(sizeof(list_st));
	tmp = head_st;
	head_st = head_st->next;
	head_st->previous = tmp;

	strcpy(head_st->record.symbol, "THAT");
	head_st->record.value = 4;
	head_st->next = NULL;
	return head_st_2_return;
}

void add_2_st(pair this, list_st *head)
{
	list_st *tmp1 = head->next;
	head->next = malloc(sizeof(list_st));
	list_st *tmp2 = head->next;
	tmp2->next = tmp1;
	tmp2->previous = head;
	tmp2->record = this;
	tmp1->previous = tmp2;
}

_Bool search_st(char *this, list_st *head_st)
{
	if(head_st == NULL)
		error();
	while(head_st != NULL) {
		if(!strcmp(this, head_st->record.symbol)) {
			return true;
		}
		head_st = head_st -> next;
	}
	return false;
}

int get_value(char *this, list_st *head_st)
{
	if(head_st == NULL)
		error();
	while(head_st != NULL) {
		if(!strcmp(this, head_st->record.symbol)) {
			return head_st->record.value;
		}
		head_st = head_st -> next;
	}
}

void translater(list_e *head)
{
	if(head == NULL)
		error();
	while(head != NULL) {
		if(head->line[0] == '@') {
			int len = strlen(head->line);
			char val[20];
			substring(val, head->line, 1, len - 1);
			int num = atoi(val);
			val[16] = '\0';
			int j = 15;
			for(int i = 0; i < 16; i++) {
				val[j] = (char) (num%2 + 48);
				num /=2;
				j--;
			}
			strcpy(head->line, val);
		} else {

			int len = strlen(head->line);
			char dest[10]; char comp[10]; char jump[10];
			int equal = 0; int scolon = 0;
			for(int i = 0; i < len; i++) {
				if(head->line[i] == '=')
					equal = i;
				if(head->line[i] == ';')
					scolon = i;
			}
			if(equal == 0 && scolon != 0) {
				substring(comp, head->line, 0, scolon -1);
				substring(jump, head->line, scolon + 1, len - 1);
				strcpy(dest, "null");
			} else if(equal != 0 && scolon == 0) {
				substring(dest, head->line, 0, equal - 1);
				substring(comp, head->line, equal + 1, len - 1);
				strcpy(jump, "null");
			} else if(equal != 0 && scolon != 0) {
				substring(dest, head->line, 0, equal - 1);
				substring(comp, head->line, equal + 1, scolon - 1);
				substring(jump, head->line, scolon + 1, len - 1);
			} else {
				printf("syntax error\ncheck line: %d\n", head->line_no_green);
				exit(1);
			}
			get_comp(comp, head->line_no_green);
			get_dest(dest, head->line_no_green);
			get_jump(jump, head->line_no_green);
			sprintf(head->line,"111%s%s%s", comp, dest, jump);
		}
		head = head->next;
	}
}

void print_data(const list_e* head, const char* input_file)
{
	char file_name[20];
	substring(file_name, input_file, 0, strlen(input_file) - 5);
	sprintf(file_name, "%s.hack", file_name);
	FILE *output_file_ptr = fopen(file_name, "w");
	while(head != NULL) {
		fprintf(output_file_ptr, "%s\n", head->line);
		head = head->next;
	}

	fclose(output_file_ptr);
}

void check_input_file(const char *input_file)
{
	char buffer[5];
	int len = strlen(input_file);
	substring(buffer, input_file, len - 4, len - 1);
	if(strcmp(buffer, ".asm")) {
		printf("provide a valid input file\"*.asm\"\n");
		exit(1);
	}
}

/****************************************************************************************************/
/***********************************************testers**********************************************/

void print_green(const list_g *head)
{
	while(head != NULL) {
		int i = 0;
		printf("%d ", head->line_no_green);
		while(1) {
			printf("%c", head->line[i]);
			if((head->line[i]) == '\n') break;
			i++;
		}
		head = head->next;
	}
}

void print_pure(const list_p* head)
{
	while(head != NULL) {
		printf("%d", head -> line_no_green);
		printf("\t");
		printf("%d", head -> line_no_pure);
		printf("\t");
		printf("%s", head -> line);
		printf("\n");
		head = head -> next;
	}
}

void print_exact(const list_e *head)
{
	while(head != NULL) {
		printf("%d", head->line_no_green);
		printf("\t");
		printf("%d", head->line_no_exact);
		printf("\t");
		printf("%s", head->line);
		printf("\n");
		head = head -> next;
	}
}

void print_st(const list_st *head)
{
	while(head != NULL) {
		printf("%s\t%d\n", head->record.symbol, head->record.value);
		head = head->next;
	}
}

