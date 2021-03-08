// Paul Passiglia
// cs_4280
// 3/6/2021
// P1: The Scanner


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"

//#include "token.h"


int main(int argc, char* argv[])
{
  char input_buffer[1024] = { 0 };
  int i = 0;
  int flag1 = 0;
  int flag2 = 0;


  //fprintf(stderr, "main.c begins..\n");
  //printf("argc = %d \n", argc);

  // Parse invocations below ----------------------------------------------

  // ./main --- Check if there was a file redirection using isatty
  if (argc < 2 && (isatty(0)))
  {
    flag1 = 1;
    printf("Reading from stdin.\n");
    printf("Type a string out to be tested and then press CNTRL + D when finished.\n");
    scanner(stdin);

  }
  
  // ./main < list.sp2020 --- File redirection was used. ------------------
  if (argc < 2 && !(isatty(0)))
  {
    flag1 = 1;
    printf("File was redirected to stdin. \n");
    scanner(stdin);
   
  }
  
  // ./main list.sp2020 --- File will be read. -----------------------------
  if (argc == 2)
  {
    printf("File specified to read: %s \n", argv[1]);
    FILE *fptr;
    if ((fptr = fopen(argv[1], "r")) == NULL)
    {
      fprintf(stderr, "Error! File will not open. \n");
      return -1;
    }
    flag2 = 1;
    scanner(fptr);
  }

  

 
  return 0;
}
