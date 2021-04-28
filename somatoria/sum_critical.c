#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void build_arr(FILE *inputFile, int thread_count, int* arr){
  int i = omp_get_thread_num();
  int scanReturn = 0;

  while (scanReturn != EOF)
  {
    scanReturn = fscanf(inputFile, "%d", &arr[i]);
    i+=thread_count;
  }
}

void somatoria(int vector[], int size, int thread_count, int* sum){
  for(int i = omp_get_thread_num(); i < size; i+=thread_count){
    *sum += vector[i];
  }
}

int main(int argc, char* agrv[]){
  int thread_count = strtol(agrv[1], NULL, 10);

  int size = 1073741824;
  int* arr = (int*)malloc(size * sizeof(int));

  FILE *inputFile;

  inputFile = fopen("vetor1.csv", "r");
  if (inputFile == NULL)
  {
    fprintf(stderr, "\n Erro ao abrir o arquivo \n");
    exit(1);
  }

  #pragma omp parallel num_threads(omp_get_max_threads())
  build_arr(inputFile, thread_count, arr);

  int res = 0;



  #pragma omp parallel num_threads(thread_count)
  {
    int sum = 0;
    somatoria(arr, size, thread_count, &sum);
    #pragma omp critical
    res += sum;
  }



  printf("Soma: %d \n", res);

  return 0;

}