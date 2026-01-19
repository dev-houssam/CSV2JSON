/*
Simple tool : Speedest
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char head_1[64];
    char head_2[64];
    char head_3[64];
    
} Head;

typedef struct {
    char triplet_1[30];
    char triplet_2[30];
    char triplet_3[30];
} Couple;

typedef struct {
    Head entete;
    int count;
    Couple * data;
} Concession;

#define BUF_SIZE 65536
int count_lines(FILE* file)
{
    char buf[BUF_SIZE];
    int counter = 0;
    for(;;)
    {
        size_t res = fread(buf, 1, BUF_SIZE, file);
        if (ferror(file))
            return -1;

        int i;
        for(i = 0; i < res; i++)
            if (buf[i] == '\n')
                counter++;

        if (feof(file))
            break;
    }
    return counter;
}

int getNumberOfInfo(const char * title){
    
    FILE* ptr = fopen(title, "r");
    if (ptr == NULL) {
        printf("no such file.");
        return 0;
    }
    
    
    int cpt = count_lines(ptr);
    return cpt;
}

// Driver Code
int main(int argc, const char argv[])
{
    FILE* ptr = fopen("abc.txt", "r");
    if (ptr == NULL) {
        printf("no such file.");
        return 0;
    }
    Concession con;
    memset(con.entete.head_1, 0, sizeof(con.entete.head_1));
    memset(con.entete.head_2, 0, sizeof(con.entete.head_2));
    memset(con.entete.head_3, 0, sizeof(con.entete.head_3));
    con.count = getNumberOfInfo("abc.txt");
    printf("Lines : %d\n", con.count);

    
    con.data = (Couple *) malloc(sizeof(Couple) * con.count);
    if(con.data == NULL) return -1;

    char buf[100];
    char buf2[100];
    memset(buf, 0, sizeof(buf));
    memset(buf2, 0, sizeof(buf2));
    long compteur = 0;
    while (fscanf(ptr, "%s", buf) == 1){
            switch(compteur){
                case 0:
                    strcat(con.entete.head_1, buf);
                    break;
                case 1:
                    strcat(con.entete.head_2, buf);
                    break;
                case 2:
                    strcat(con.entete.head_3, buf);
                    break;
            }
            
        compteur++;
        if(compteur == 3){
            break;
        }
        
    }
    printf("head: %s::[%s::%s]\n", con.entete.head_1, con.entete.head_2, con.entete.head_3);
    printf("\n[\n");
    compteur = 0;
    //----
    do{
        int cpt = 0;
        //Parcours
        while (fscanf(ptr, "%s", buf) == 1){ 
            switch(cpt){
                case 0:
                    strcpy(con.data[compteur].triplet_1, buf);
                    //printf("[1]=>%s\n", con.data[compteur].triplet_1);
                    break;
                case 1:
                    strcpy(con.data[compteur].triplet_2, buf);
                    //printf("[2]=>%s\n", con.data[compteur].triplet_2);
                    break;
                case 2:
                    strcpy(con.data[compteur].triplet_3, buf);
                    //printf("[3]=>%s\n", con.data[compteur].triplet_3);
                    break;
            }
            cpt++;
            if(cpt == 3) break; 
        }
        printf("\t{ id:%d, %s:%s, %s:%s, %s:%s },\n", compteur, 
            con.entete.head_1,  con.data[compteur].triplet_1, 
            con.entete.head_2,  con.data[compteur].triplet_2, 
            con.entete.head_3,  con.data[compteur].triplet_3);

        buf[0] = 0;
        compteur++;
        
        if(compteur == con.count){
            compteur=0;
            break;
        }
    }while (1);
    printf("]\n");
    return 0;
}
