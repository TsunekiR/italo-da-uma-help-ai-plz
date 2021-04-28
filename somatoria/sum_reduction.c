#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
// #include<sys/time.h>

void build_arr(FILE *inputFile, int thread_count, int* arr){
  int i = omp_get_thread_num();
  int scanReturn = 0;
}

int somatoria(int arr[], int size, int thread_count){
  int sum = 0;
  for(int i = omp_get_thread_num(); i < size; i+=thread_count){
    sum += arr[i];
  }
  return sum;
}

int main(int argc, char* agrv[]){
  int thread_count = strtol(agrv[1], NULL, 10);
  double start, end, time;
  // struct timeval tv;

  int size = 1073741824;
  int* arr = (int*)malloc(size * sizeof(int));

  FILE *inputFile;

  inputFile = fopen("vetor1.csv", "r");
  if (inputFile == NULL)
  {
    fprintf(stderr, "\n Erro ao abrir o arquivo \n");
    exit(1);
  }

  #pragma omp parallel num_threads(thread_count)
  build_arr(inputFile, thread_count, arr);

  int res = 0;

  // gettimeofday(&tv, NULL);
  // start = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;

  #pragma omp parallel num_threads(thread_count) reduction(+ : res)
    res += somatoria(arr, 1073741824, thread_count);

  // gettimeofday(&tv, NULL);
  // end = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
  // time = end - start;


  printf("Soma: %d \n", res);

  return 0;

}