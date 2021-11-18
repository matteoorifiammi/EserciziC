#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
 
int main (int argc, char *argv[]) {
  int primoFiglio, secondoFiglio, g, h , padre;
  padre = getpid();
  primoFiglio = 0; 
  secondoFiglio = 0; 
  g = 0; 
  h = 0;
  printf("1) Io sono il padre ed ho pid: %i \n", getpid());
  primoFiglio = fork();
  if (getpid() != padre)
    printf("2) Sono la prima fork con pid: %i \n", getpid());
  if (primoFiglio != 0) {
    secondoFiglio = fork();
    if (getpid() != padre)
      printf("3) Sono la seconda fork con pid : %i \n", getpid());
  } 
  if (primoFiglio == 0 || secondoFiglio == 0) {   
    g = fork();
    printf("4) Sono la terza fork con pid: %i \n", getpid());
    if (g != 0) {
      h = fork();
      printf("5) Sono la quarta fork con pid: %i \n", getpid());
    } 
	if (g != 0 && h != 0) {
      waitpid(g, 0, 0);
      waitpid(h, 0, 0);
    }
  } 
  else { // processo P
    waitpid(secondoFiglio,0,0);
    printf("6) Ha terminato il secondo figlio: %i \n", secondoFiglio );
    waitpid(primoFiglio,0,0);
    printf("7) Ha terminato il primo figlio: %i \n", primoFiglio );
  }  
 return 0;
} 