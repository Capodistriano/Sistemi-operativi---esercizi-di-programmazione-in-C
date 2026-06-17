int presente(uid_t uid, int *lista, int L){
    int i;
    for(i=0;i<L;i++){
        if(lista[i]==uid)
         return 1;
    }
    return 0;

}

int main(int argc, char *argv[]){
    //apertura del file binario
    FILE *fp=fopen("/etc/numbers.bin", "rb");

    int L;

    //legge il numero di UID
    fread(&L, sizeof(int),1 ,fp);

    //alloca il vettore
    int *lista=malloc(L*sizeof(int));

    //legge i L interi
    fread(lista, sizeof(int), L, fp);
    fclose(fp);

    //apre la directory passat da riga di comando
    DIR *dir=opendir(argv[1]);

    struct dirent *entry;

    while((entry = readdir(dir)) != NULL){
        char path[1024];

        // costrusico il path completo
        sprintf(path, " %s/%s", argv[1], entry -> d_name);

        struct stat st;

        stat(path , &st);

        // controlla se è un file regolare
        if(S_ISREG(st.st_mode)){
            // controlla se l'UID è nella lista
            if(presente(st.st_uid, lista, L)){
                printf("File: %s UID: %d\n", entry->d_name, (int)st.st_uid);
            }
        }


    }
    
    closedir(dir);
    free(lista);
    return 0;
}