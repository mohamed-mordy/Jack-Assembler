#include<stdio.h>
#include"ADT.h"

list_g* green_code_loader(const char* filename);
list_p* pure_code_builder(list_g* green_head);
void error(void);
void drop_g(list_g* head_g);
void drop_p(list_p* head_p);
void drop_e(list_e* head_e);
void drop_st(list_st* head_st);
list_st* initialize_st(void);
void add_2_st(pair this, list_st* head);
static void substring(char* dst, const char* src, int from , int to);
list_e* mid_exact_code(list_p* head_p, list_st* head_st);
_Bool search_st(char* this, list_st* head_st);
int get_value(char* this, list_st* head_st);
list_e* exact_code_builder(list_e* head, list_st* head_st);
void translater(list_e* head);

void check_input_file(const char* input_file);
void print_data(const list_e* head, const char* input_file);
/****************************************************************************************************/
/***********************************************testers**********************************************/
void print_green(const list_g* head);
void print_pure(const list_p* head);
void print_exact(const list_e* head);
void print_st(const list_st* head);

