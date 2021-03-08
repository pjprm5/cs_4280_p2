// Paul Passiglia
// cs_4280
// P1: The Scanner
// token.h


#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

int fsaTable[22][22] = {
  /*
   -3 : Partial token
   -2 : Incorrect start
   -1 : Incorrect next
   
   1000: EOF
   1001: Keyword 
   1002: Identifier
   1003: Number

   1004: =
   1005: =>
   1006: =<
   1007: ==
   1008: :
   1009: :=
   1010: +
   1011: -
   1012: *
   1013: /
   1014: %
   1015: .
   1016: (
   1017: )
   1018: ,
   1019: {
   1020: }
   1021: ;
   1022: [
   1023: ]
   1024: ws
  */                                   //Valid Operators
  //                        = => =< == : := + - * / % . ( ) , { } ; [ ]

  //_  a     1     =     >     <     :  +  -  *   /   %   .   (   )   ,   {   }   ;   [   ]   ws            State
  { 1, 2,    3,    4,    5,    6,    7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22  }, //     0
  {-1, 1002, 1002,-1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2  }, // -   1
  {-1, 2,    3,   -1,   -1,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1002}, // a   2
  {-1,-1,    3,   -1,   -1,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1003}, // 1   3 
  {-1,-1,    -1,  1007, 1005, 1006, -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1004}, // =   4
  {-1,-1,    -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2  }, // >   5
  {-1,-1,    -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2  }, // <    fix
  {-1,-1,    -1,  1009, -1,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1008}, // :    fix
  {-1,-1,    -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1010}, // +    fix
  {-1,-1,    -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1011}, // -    fix
  {-1,-1,    -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1012}, // *    fix
  {-1,-1,    -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1013}, // /    fix
  {-1,-1,    -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1014}, // %    fix
  {-1,-1,    -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1015}, // .    fix
  {-1, -1,   -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1016}, // (    fix
  {-1, -1,   -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1017}, // )    fix
  {-1, -1,   -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1018}, // ,    fix
  {-1, -1,   -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1019}, // {    fix
  {-1, -1,   -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1020}, // }    fix
  {-1, -1,   -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1021}, // ;    fix
  {-1, -1,   -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1022}, // [    fix
  {-1, -1,   -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1023}, // ]    fix
  {-1, -1,   -1,  -1,   -2,   -1,   -1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1024}, // ws   fix



char* keyWordArray[14] = {
  "begin",
  "end",
  "loop",
  "whole",
  "void",
  "exit",
  "getter",
  "outter",
  "main",
  "if",
  "then",
  "assign",
  "data",
  "proc"
};

struct token {
  int lineNumber;
  char tokenType;
  int tokenValue;
  char tokenInstance;
}


#endif
