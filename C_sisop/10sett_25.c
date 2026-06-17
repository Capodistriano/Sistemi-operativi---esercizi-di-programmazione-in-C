#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_PATH 256
#define MAX_CMD 512
#define MAX_STRING 10000

int main(int argc, char * argv[]){

    FILE *fp_lista;
    FILE *fp_file;

    char path[MAX_PATH];

    int A;
    int B;

    char risultato[MAX_STRING];
    risultato[0]= '\0';

    fp_lista= fopen(argv[1], "r");
    while(fscanf(fp_lista, "%s %d %d", path, &A, &B)==3){
        fp_file=fopen(path, "r");
        fseek(fp_file, A, SEEK_SET);
        
        for(int i=A; i<=B;i++){
            char c;
            
            if(fread(&c, sizeof(char),1,fp_file)==1){
                int len=strlen(risultato);
                
                risultato[len]=c;
                risultato[len+1]='\0';
            }
        }
        fclose(fp_file);
    }

    fclose(fp_lista);

    char comando[MAX_CMD];
    gets(comando);
    if(strcmp(comando, "V")==0){
        printf("%s\n", risultato);
    }else if(comando[0]== 'F'){
        char outpath[MAX_PATH];
        sscanf(comando, "F %s", outpath);

        FILE *out= fopen(outpath, "w");
        fprintf(out, "%s", risultato);
        fclose(out);
    }

    return 0;


}