#include<stdio.h>

int main(){
    int n=0,s=0,e;
    FILE *f;
    char nome[100];
    f=fopen("persone.txt","r");
    if(f==NULL){
        printf("Impossibile aprire persone.txt\n");
        return 1;
    }

    while(fscanf(f,"%s %d\n", nome,&e)!=EOF){
        n++;
        s+=e;
    }
    printf("La media è %f\n", (float)s/n);
    return 0;
}