/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

// Assignment 2
// a) create a new function print_number b) insert function is_prime from assignment 1
// c) create a new body for the function "print_primes" from 2 to n by calling functions print_number & is_prime

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6
int numbersInRow = 0;

void print_number (int n) {
  // Should have one integer parameter value
  // representing the number that should be printed.
  // If the function is called several times in a row,
  // the output should be printed in several columns
  // The number of columns is defined by the define COLUMNS.
  // The function should not return any value.
  printf ("%10d", n);
  numbersInRow++;
  if (numbersInRow % COLUMNS == 0) {
    printf ("\n");
  }
}

int is_prime(int n){
  int i; 
  for (i=2; i <=n/2; i++) {
      if (n%i == 0)
      return 0;
  }
  return 1;
}

void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
  int i;
  for (i=2; i < n; i++) {
    if (is_prime (i)) {
      print_number (i);
    }
  }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
