#include <stdio.h>
#include <stdlib.h>

void read_file(const char *filename, int ***matrix, int *n)
{
  FILE *file = fopen(filename, "r");
  if (!file)
  {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  fscanf(file, "%d", n);
  int discard;
  fscanf(file, "%d", &discard);

  *matrix = (int **)malloc(*n * sizeof(int *));

  for (int i = 0; i < *n; i++) // 
  {
    (*matrix)[i] = (int *)malloc(*n * sizeof(int));
    for (int j = 0; j < *n; j++)
    {
      fscanf(file, "%d", &(*matrix)[i][j]);
    }
  }
  fclose(file);
}

void rotate(int **matrix, int n)
{
  int **done = (int **)malloc(n * sizeof(int *));

  for (int i = 0; i < n; i++)
  {
    done[i] = (int *)malloc(n * sizeof(int));
  }

  // rotate matrix
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      done[j][n - 1 - i] = matrix[i][j];
    }
  }

  // print matrix
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%d ", done[i][j]);
    }
    printf("\n");
  }

  // free memory
  for (int i = 0; i < n; i++)
  {
    free(done[i]);
  }
  free(done);
}

//free original matrix

void free_matrix(int **matrix, int n){
    for(int i = 0; i < n; i++){
      free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    fprintf(stderr, "./second {text file}\n");
    exit(1);
  }

  int **matrix;
  int n;

  //read file first
  read_file(argv[1], &matrix, &n); 

  //then rotate it
  rotate(matrix, n); 
  
  //then free the original matrix
  free_matrix(matrix, n); 

  return EXIT_SUCCESS;
}