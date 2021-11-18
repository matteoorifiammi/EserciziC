#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define ROW_LENGTH 40

int contatoreRighe(FILE *fp, char filename[])
{
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("C'è stato un problema nell'apertura del file\n");
        exit(4);
    }
    int numeroRighe = 0;
    char c;
    while (!feof(fp))
    {
        c = fgetc(fp);
        if (c == '\n')
            numeroRighe++;
    }
    if (c == EOF && numeroRighe != 0)
        numeroRighe++;
    fclose(fp);
    return numeroRighe;
}

int main(int argc, char *argv[])
{
    int pidFiglio1, pidFiglio2, pidFiglio3, status;
    pidFiglio1 = fork();
    if (pidFiglio1 == 0)
    {
        FILE *fp;
        if ((fp = fopen("fileOutput.txt", "w+")) == NULL)
        {
            printf("Sono il figlio numero 1, c'è stato un problema nell'apertura del file\n");
        }
        else
        {
            int righe = contaRighe(fp, "fileOutput.txt");
            char rows[ROW_LENGTH * righe];
            for (int i = 0; !feof(fp); i++)
            {
                rows[i] = fgetc(fp);
            }
            char row[] = "Sono il figlio numero 1\n";
            strcat(rows, row);
            fprintf(fp, "%s", rows);
        }
        fclose(fp);
        sleep(6);
        exit(1);
    }
    else if (pidFiglio1 > 0)
    {
        pidFiglio2 = fork();
        if (pidFiglio2 == 0)
        {
            FILE *fp;
            if ((fp = fopen("fileOutput.txt", "w+")) == NULL)
            {
                printf("Sono il figlio numero 2, c'è stato un problema nell'apertura del file\n");
            }
            else
            {
                int righe = ContaRighe(fp, "fileOutput.txt");
                char rows[ROW_LENGTH * righe];
                for (int i = 0; !feof(fp); i++)
                {
                    rows[i] = fgetc(fp);
                }
                char row[] = "Sono il figlio numero 2\n";
                strcat(rows, row);
                fprintf(fp, "%s", rows);
            }
            fclose(fp);
            sleep(4);
            exit(2);
        }
        else if (pidFiglio2 > 0)
        {
            pidFiglio3 = fork();
            if (pidFiglio3 == 0)
            {
                FILE *fp;
                if ((fp = fopen("fileOutput.txt", "w+")) == NULL)
                {
                    printf("Sono il figlio numero 3, c'è stato un problema nell'apertura del file\n");
                }
                else
                {
                    int righe = ContaRighe(fp, "fileOutput.txt");
                    char rows[ROW_LENGTH * righe];
                    for (int i = 0; !feof(fp); i++)
                    {
                        rows[i] = fgetc(fp);
                    }
                    char row[] = "Sono il figlio numero 3\n";
                    strcat(rows, row);
                    fprintf(fp, "%s", rows);
                }
                fclose(fp);
                exit(3);
            }
            else if (pidFiglio2 > 0)
            {
                printf("Sono il padre è sto aspettando che il figlio più lento termini\n");
                waitpid(pidFiglio1, &status, 0);
                printf("Tutti i figli hanno terminato, ora leggo il file\n");
                FILE *fp;
                if ((fp = fopen("fileOutput.txt", "r")) == NULL)
                {
                    printf("Sono il padre, c'è stato un problema nell'apertura del file\n");
                }
                else
                {
                    char row[ROW_LENGTH];
                    while (fgets(row, sizeof(row), fp) != NULL)
                    {
                        puts(row);
                    }
                    printf("Questo è quello che i miei figli hanno scritto\n");
                }
                fclose(fp);
            }
        }
    }
    return 0;
}