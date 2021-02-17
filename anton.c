#include <stdio.h>
#include <stdlib.h>

struct info 
{
    char fam [100];
    int nom;
    char kn [100];
    int day;
};

void print(char * text);


int main ()
{
    struct info ss[100];
    struct info buffer;
    int q = 0;
    int i = 0;
    int j,n,w;
    int a[100];
    printf ("Vvedem structuru");
    while (i==0)
    {
        printf ("\nFIO - ");
        fgets ((ss + q)->fam,100,stdin);
        printf ("\nNomer chitatelskogo bileta - ");
        scanf ("%d",&(ss + q)->nom);
        getchar ();
        printf ("\nNazvanie knigi - ");
        fgets ((ss + q)->kn,100,stdin);
        printf ("\nSrok vozvrata - ");
        scanf ("%d",&(ss + q)->day);
        printf ("\nProdolzhit' vvod? (0 - yes, 1 - no) - ");
        scanf ("%d", &a[q]);
        if (a[q] == 1) 
        {
            n = q+1;
            i = 1;
        }
        q++;
    }
    printf ("\nVvedennaya structura: ");
    printf ("\nFIO NOMER NAZVANIE SROK\n");
    for (i = 0; i < n; i++)
    {
        w = 0;
        while ((ss + q)->fam[w] != '\0')
        {
            printf ("%c",(ss + q)->fam[w]);
            w++;
        }
        w = 0;
        printf (" %d",(ss + i)->nom);
        while ((ss + q)->fam[w] != '\0')
        {
            printf ("%c",(ss + q)->fam[w]);
            w++;
        }
        printf (" %d dney\n",(ss + i)->day);
    }
    
}




void print(char * text){
    int i = 0; 
    while(text[i] != '\0'){
        putchar(text[i]);
        i++;
    }
    return;
}
