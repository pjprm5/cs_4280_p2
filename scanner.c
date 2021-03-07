// Paul Passiglia
// cs_4280
// P1: The Scanner
// scanner.c


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "scanner.h"

int scanner(FILE *test)
{
  int i = 0;
  int j;
  int ch;
  //FILE fptr;

  char buffer[300] = { 0 };
  char str[300] = { 0 };
  
  int commentPresent = 0;
  int commentHead = 0;
  int commentTail = 0;
  
   
   
  //printf("scanner.c begins...\n");
  while ((ch = getc(test)) != '@' /*(ch = getc(test)) != EOF*/)
  {
    if (isspace(ch) == 0 && (ch != '@') && (ch != '\n'))
    {
      printf("%c", ch);
      buffer[i] = ch;
      fflush(stdout);
      i++;
    }

  }
  strcpy(str, buffer);
  printf("%s \n", str);
  printf("String Length: %d \n", strlen(str));
  
  // Searching for comments
  for (i = 0; i < strlen(str); i++)
  {
    if ((str[i] == '$') && (str[i+1] == '$'))
    {
      commentPresent++;
      commentHead++;
      //printf("Searching for tail end of comment $$ \n");
      for (j = i+2; j < strlen(str); j++)
      {
        if ((str[j] == '$') && (str[j+1] == '$'))
        {
          commentTail++;
          //printf("Tail end of comment found! \n");
          break;
        }
        
      }
    }
  }
  printf("Comment Present: %d \n", commentPresent);
  printf("Comment Head: %d \n", commentHead);
  printf("Comment Tail: %d \n", commentTail);

  if ((commentPresent != 0) && (commentPresent % 2 != 0))
  {
    printf("ERROR: Comments are not correctly closed.\n");
    exit(-1);
  }
  else if ((commentPresent != 0) && (commentPresent % 2 == 0))
  {
    printf("Comments are correctly formatted.\n");
  }
  else if (commentPresent == 0)
  {
    printf("No comments found.\n");
  }



  return 0;
}

