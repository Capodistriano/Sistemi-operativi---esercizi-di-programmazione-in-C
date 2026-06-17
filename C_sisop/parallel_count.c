#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int n=argc-1;
    
    for(int i=1;i<=n;i++){
        pid_t pid=fork();
        
        if(pid==0){
            //child process
            char *filename=argv[i];
            FILE *fin=fopen(filename, "r");

            //conto le righe
            int count=0;
            char line[1024];
            while(fgets(line, sizeof(line), fin)!=NULL){
                count++;
            }
            fclose(fin);

            //crea nome file output: filename + ".count"
            char outname[1024];
            snprintf(outname, sizeof(outname), "%s.count", filename);

            //scrivo il conteggio nel file .count
            FILE *fout= fopen(outname, "w");
            fprintf("fout", "%d\n", count);
            fclose(fout);

            exit(0);
        }
        //Il padre continua il ciclo e crea il prossimo figlio
    }

    //Il padre attende tutti i figli
    for(int i=0;i<n;i++){
        wait(NULL);
    }

    printf("Tutti i figli hanno completato l'operazione.\n");
    return(0);

}