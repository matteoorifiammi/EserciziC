///  \file   Esercizio2.c
///  \brief  Trasforma i caratteri minuscoli inseriti come argomento in caratteri maiuscoli
///  \date   11/11/2021

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 *  \fn     int main()
 *  \brief  Dopo aver inizializzato il processo figlio questo converte i caratteri inseriti da minuscolo a maiuscolo
 *  \param  int argc: L'array che contiene il numero di argomenti
 *  \param  char *argv: L’array che contiene i caratteri da convertire
 *  \return int: Il codice di terminazione del programma
 */

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("L'argomento è stato inserito in modo errato\n");
        exit(1);
    }
    else
    {
        int PID = fork();
        if (PID < 0)
        {
            printf("C'è stato un errore nella creazione del processo figlio\n");
            exit(2);
        }
        else if (PID == 0)
        {
            printf("Sono il figlio e inizio la conversione dei caratteri da minuscolo a maiuscolo\n");
            int dim = strlen(argv[1]);
            for (int i = 0; i < dim; i++)
                argv[1][i] = toupper(argv[1][i]);
            printf("Figlio: %s\n", argv[1]);
            printf("Sono il figlio ed ho terminato\n");
            exit(3);
        }
        else
        {
            wait(&PID);
            printf("Sono il padre e il mio processo figlio ha terminato la conversione\n");
        }
    }

    return 0;
}