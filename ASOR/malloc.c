#include <stdlib.h>
#include <stdio.h>

void main(int args, char *argv[]) {
  char *a = malloc(sizeof(char)*10);
  printf("%li\n", sizeof(a));
  printf("%li\n", sizeof(*a));
  a = "cocacola";
  printf("%li\n", sizeof(a));
  printf("%li\n", sizeof(*a));
  printf("%li\n", sizeof(void*));
  printf("%s",a);
}
