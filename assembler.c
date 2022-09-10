/**************************************************************************************************/
/*********************************************Authorship*******************************************/
/**
  * Author: Mohamed M. A. Mordy

  * Started: August 31, 2020. 4:30 AM
    Finished: 

  * Aim: Design and implementation of an assembler for the HACK platform, translates from
         the HACK assemply language to the HACK machine language.

  * Notes: 1. This project is a part of the course "the elements of computing systems"
           2. This version(0.1) of the project is under major construction
		   3.
		   4.
 */	
/**************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"functions.h"

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Usage: assembler *.asm\n");
		exit(1);
	}
	check_input_file(argv[1]);
	list_g* green_code = green_code_loader(argv[1]);
	list_p* pure_code = pure_code_builder(green_code);
	drop_g(green_code);
	list_st* symbol_table = initialize_st();
	list_e* exact_code_mid = mid_exact_code(pure_code, symbol_table);
	drop_p(pure_code);
	list_e* exact_code = exact_code_builder(exact_code_mid, symbol_table);
	drop_e(exact_code_mid);
	drop_st(symbol_table);
	translater(exact_code);
	print_data(exact_code, argv[1]);
	drop_e(exact_code);
	printf("Done successfully\ncheck output\n");
	return 0;
}

