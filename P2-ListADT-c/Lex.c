//-----------------------------------------------------------------------------
// Lex.c
// Kevin Duong
// keduong
// 1-27-17
// Sorts given in file using List ADT into out file in lex order.
// Used FileIO.c as framework
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

   int count=0;
   int i, j;
   FILE *in, *out;
   char line[MAX_LEN];
 

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   /* read each line of input file, then count and print tokens */
   while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;
   }
   
   /* return to start */
   rewind(in);
   
   /* create string array and loop through */
   char strarry[count-1][MAX_LEN];
   int lines = -1;
   while(fgets(line,MAX_LEN,in) != NULL){
      strcpy(strarry[++lines], line);
   }
   
   /* make list and sort */
   List L = newList();
   char* element;
   append(L,0);
   for(i=1; i<count; ++i){
      element = strarry[i];
      j = i-1;
      moveFront(L);
      while(j>=0 && strcmp(element, strarry[get(L)])<=0){
         --j;
         moveNext(L);
      }
   if(index(L)>=0) 
      insertBefore(L,i);
   else
      append(L,i);  
   }   
   
   /* Return to front and print*/
   moveBack(L);
   while(index(L)>=0){
      fprintf(out, "%s", strarry[get(L)]);
      movePrev(L);
   }
   
   /* close files and free list*/
   fclose(in);
   fclose(out);
   freeList(&L);
   
   return(0);
}