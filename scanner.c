// Paul Passiglia
// cs_4280
// P1: The Scanner
// scanner.c


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "scanner.h"
#include "token.h"

// Prototype
int testScanner(FILE *fptr, int currentChar, int nextChar, struct token *t);


int scanner(FILE *test)
{
  int i = 0;
  int j;
  int ch;
  int lineCount = 0;
  
  // Stupid amount of buffers.
  char buffer[1024] = { 0 };
  char str[1024] = { 0 };
  char cleanStr[1024] = { 0 };
  char finalStr[1024] = { 0 };
 
  // Flags for comments
  int commentPresent = 0;
  int commentHead = 0;
  int commentTail = 0;
  int commentCleanse = 0;
  printf("\n");  
  // Take input below and clear spaces
  while ((ch = getc(test)) != EOF)
  {
    if (ch == '\n')
    {
      lineCount++;
    }
    //printf("%c", ch);

    buffer[i] = ch;
    i++;
  }
  printf("\n\n");

  strcpy(str, buffer);
  //printf("%s \n", str);
  //printf("String Length: %d \n", strlen(str));
  
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
  /*
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
  */
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
  // Clearing out NULLS
  for (i = 0; i < strlen(str); i++)
  {
    //printf("%c", cleanStr[i]);
    if (cleanStr[i] != '\0')
    {
      finalStr[j] = cleanStr[i];
      j++;
    } 
  }
  
  // No cleanse was done we copy into finalStr to prepare for stream
  if (commentCleanse != 1)
  {
    strcpy(finalStr, str);
  }
  //printf("FINAL: %s\n", finalStr);
  //printf("LINES: %d\n", lineCount);
  
  // Putting clean array into new file, so it can be read again
  FILE *fptr = fopen("cleanFile.fs", "w+");
  if (fptr != NULL)
  {
    fputs(finalStr, fptr);
  }
  fclose(fptr);
  
  fptr = fopen("cleanFile.fs", "r");
  
  // Finally start printing tokens with testScanner
  struct token t;   // Declare struct
  t.lineNumber = 0; // Initialize line numss

  int currentChar;
  int nextChar;
  do
  {
    currentChar = getc(fptr);
    nextChar = getc(fptr);
    testScanner(fptr, currentChar, nextChar, &t);
  }while (currentChar != EOF);
  

  return 0;
}

int testScanner(FILE *fptr, int currentChar, int nextChar, struct token *t)
{
  //printf("\nToken Printing Cycle Begins -----\n");
  //
  char key_id[9] = { 0 }; // Capture id tokens or keywords in here up to 8 chars
  
  int i;

  //printf("%c%c", currentChar, nextChar);
  int stateColumn;    // Holds column
  int state = 0;      // Holds Row
  int nextState = 0;
  int nextChar2;      // Placeholder for id loop
  int id_flag = 0;        // Flag if we get an id
  int num_flag = 0;    // Flag if we get a num
  
 
  // Checking for digits
  if (isdigit(currentChar))
  {
    ungetc(nextChar, fptr);
    num_flag = 1;
    key_id[0] = currentChar;
    for (i = 1; i < 8; i++)
    {
      nextChar2 = getc(fptr);
      if (isdigit(nextChar2))
      {
        key_id[i] = nextChar2;
      }
      else
      {
        ungetc(nextChar2, fptr);
        break;
      }
    } 
  }

  // Checking for identifiers and keywords
  if (islower(currentChar) || currentChar == '_')
  {
    ungetc(nextChar, fptr); // unget nextChar so we can get the true ID
    id_flag = 1;
    key_id[0] = currentChar;
    for (i = 1; i < 8; i++)
    {
      nextChar2 = getc(fptr);
      if (isalpha(nextChar2) || isdigit(nextChar2))
      {
        key_id[i] = nextChar2;
      }
      else
      {
        ungetc(nextChar2, fptr); // unget nextChar2 because not part of ID
        break;
      }
    }
   
  }
  
  if (id_flag == 1)
  {
    //printf("ID CAPTURED: %s\n", key_id);
  }

  if (num_flag == 1)
  {
    //printf("NUM CAPTURED: %s\n", key_id);
  }
  
  

  // Keep track of line numbers per token
  if (currentChar == '\n')
  {
    t->lineNumber++;
  }
 
  // Start grabbing column information
  stateColumn = findColumn(currentChar);
  state = fsaTable[state][stateColumn];
  //printf("currentChar: %c\n", currentChar);
  //printf("stateColumn currentChar: %d\n", stateColumn);
  //printf("state currentChar: %d\n", state);
  
  stateColumn = findColumn(nextChar);
  nextState = fsaTable[state][stateColumn];
  //printf("nextChar: %c\n", nextChar);
  //printf("stateColumn nextChar: %d\n", stateColumn);
  //printf("state nextChar: %d\n", nextState);
  

  
   
  // Print single operator tokens
  if (nextState == -1 && !(isspace(currentChar)) && state != 3 && id_flag != 1)
  {
    t->tokenValue = fsaTable[state][21];
    t->tokenInstance = returnString(t->tokenValue); 
    printf("Line: %d Value: op_tk Instance: %s \n", t->lineNumber, t->tokenInstance);
   
  }
  
  // Print double operator tokens
  if (nextState != -1 && nextState != -2 && !(isspace(currentChar)) && state != 3 && id_flag != 1)
  {
   
    t->tokenValue = fsaTable[state][stateColumn];
    t->tokenInstance = returnString(t->tokenValue); 
    printf("Line: %d Value: op_tk Instance: %s \n", t->lineNumber, t->tokenInstance);
  }
  
  // Print number tokens
  if (state == 3 && !(isspace(currentChar)) && num_flag == 1 && id_flag != 1)
  {
    t->tokenValue = fsaTable[4][21];
    //t->tokenInstance = key_id;
    printf("Line: %d Value: num_tk Instance: %s \n", t->lineNumber, key_id);
  }

  // Print id && keyword tokens
  if (id_flag == 1 && num_flag != 1)
  {
    //t->tokenValue = fsaTable[3][21];
    printf("Line: %d Value: id_tk Instance: %s \n", t->lineNumber, key_id);
  }
    
  if (t->tokenValue != 1005 && t->tokenValue != 1006 && t->tokenValue != 1007 && t->tokenValue != 1009)
  {
    //printf("Ungetting nextChar: %c\n", nextChar);
    ungetc(nextChar, fptr);
  }
   
} 


  










