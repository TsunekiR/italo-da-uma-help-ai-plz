#include <stdio.h>
#include <stdlib.h>

int main(){
  FILE *inputFile;

  inputFile = fopen("vetor1.csv","w+");
  for(int i = 0; i < 1073741824; i++){
    fputs("1\n", inputFile);
  }

  return 0;
}