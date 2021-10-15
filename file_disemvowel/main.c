#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUF_SIZE 1024

bool is_vowel(char c) {
  char *vowels = "aeiouAEIOU";

  for(int i = 0; i < strlen(vowels); i++){
    if(c == vowels[i]){
      return 1;
    }
  }

  return 0;
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
  int position = 0;
  
  for(int i = 0; i < num_chars; i++) {
    out_buf[position] = in_buf[i];
    position++;	
  }

  return position;  
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
  char c = fgetc(inputFile);
  
  while(c != EOF) {
    if(!is_vowel(c)){
      fputc(c, outputFile);
    }
    c = fgetc(inputFile);
  }
}

int main(int argc, char *argv[]) {
  FILE *inputFile = stdin;
  FILE *outputFile = stdout;

  if(argc == 2) {
    inputFile = fopen(argv[1], "r");
  }
  if(argc == 3) {
    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");
  }
    
  disemvowel(inputFile, outputFile);
  fclose(inputFile);
  fclose(outputFile);
	
  return 0;
}

