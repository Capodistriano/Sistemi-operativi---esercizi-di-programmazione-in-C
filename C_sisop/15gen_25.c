#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){

    FILE *fp;

    int A, B;

    int maxA=0;
    int maxB=-1;

    char c;

    fp= fopen(argv[1], "r");
    
    while(1){
        printf("Inserisci A e B: ");
        scanf("%d %d", &A, &B);

        if(B>maxB){
            maxB=B;
            maxA=A;
        }

        if(B==0)
         break;
        
        fseek(fp, A, SEEK_SET);
        for(int i=0; i<B && (c= fgetc(fp)) != EOF; i++)
         putchar(c);
        
        printf("\n");
        fseek(fp, 0, SEEK_SET);


    }
    printf("Coppia con B massimo: (%d, %d)\n", maxA, maxB);
    fclose(fp);

    return 0;

}
