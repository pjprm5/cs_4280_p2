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
  int lineCount = 0;
  
  char buffer[1024] = { 0 };
  char str[1024] = { 0 };
  char cleanStr[1024] = { 0 };
  char finalStr[1024] = { 0 };
 
  // Flags for comments
  int commentPresent = 0;
  int commentHead = 0;
  int commentTail = 0;
  int commentCleanse = 0;
  
  // Take input below and clear spaces
  while ((ch = getc(test)) != EOF)
  {
    if (ch != ' ' && ch != '\t' && ch != '\v' && ch != '\f' && ch != '\r')
    {
      if (ch == '\n')
      {
        lineCount++;
      }
      //printf("%c", ch);
      if (ch != '\n')
      {
        buffer[i] = ch;
        i++;
      }
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
  //printf("Comment Present: %d \n", commentPresent);
  //printf("Comment Head: %d \n", commentHead);
  //printf("Comment Tail: %d \n", commentTail);

  // Alert info about comments
  if ((commentPresent != 0) && (commentPresent % 2 != 0))
  {
    printf("ERROR: Comments are not correctly closed.\n");
    exit(-1);
  }
  else if ((commentPresent != 0) && (commentPresent % 2 == 0))
  {
    commentCleanse = 1;
    printf("Comments are correctly formatted.\n");

  }
  else if (commentPresent == 0)
  {
    printf("No comments found.\n");
  }

  commentPresent = 0;

  // Remove comments below
  if (commentCleanse == 1)
  {
    for (i = 0; i < strlen(str); i++)
    {
      if (str[i] != '$' && commentPresent == 0)
      {
        cleanStr[i] = str[i];
      }
      if (str[i] == '$' && str[i+1] == '$')
      {
        commentPresent++;
      }
      if ((commentPresent != 1) && (commentPresent % 2 == 0) && (str[i] != '$'))
      {
        cleanStr[i] = str[i];
      } 
    }
  }

  j = 0;
  //printf("CLEANED: %s\n", cleanStr);
  for (i = 0; i < strlen(str); i++)
  {
    //printf("%c", cleanStr[i]);
    if (cleanStr[i] != '\0')
    {
      finalStr[j] = cleanStr[i];
      j++;
    } 
  }
  
  if (commentCleanse != 1)
  {
    strcpy(finalStr, str);
  }
  printf("FINAL: %s\n", finalStr);
  printf("LINES: %d\n", lineCount);








  return 0;
}

