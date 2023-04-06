#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void delay()
{
    int c,d;
    for (c = 1; c <= 32767; c++)
        for (d = 1; d <= 32767; d++)
            {}
}
int nr_cuv()
{
    srand(time(NULL));
    int nrr=rand()%331;
    return nrr;
}
int meniu()
{
    system("cls");
    int alg;
    printf("1.Incepe joc\n");
    printf("2.Clasament\n");
    printf("3.Inchide\n");
    printf("Alegeti o optiune\n");
    scanf("%d",&alg);
    if(alg<=0||alg>3){printf("Optiunea gresita. Alegeti din nou.\n");delay();meniu();}
    else{
        if(alg==1){joc();}
        else if(alg==2){clasament();}
        else{return 0;}
    }
}
int meniu_in_joc()
{
    system("cls");
    int alg;
    printf("1.Incepe alt joc\n");
    printf("2.Clasament\n");
    printf("3.Meniu\n");
    printf("Alegeti o optiune\n");
    scanf("%d",&alg);
    if(alg<=0||alg>3){printf("Optiunea gresita. Alegeti din nou.\n");delay();meniu();}
    else{
        if(alg==1){joc();}
        else if(alg==2){clasament();}
        else if(alg==3){meniu();}
    }
}
void joc()
{
    system("cls");
    FILE *c=fopen("listacuv.txt","r");;
    char cuv[40],x[40],litera;
    int n,i=0,l=0,nrg=5,ok;
    n=nr_cuv();
    while(fscanf(c,"%s",x)!=EOF)
    {
        i++;
        if(i==n)
        {
            strcpy(cuv,x);
            break;
        }
    }
    fclose(c);
    l=strlen(cuv);
    int a[60];
    for(i=0;i<l;i++)
    {
        if(cuv[i]==cuv[0]||cuv[i]==cuv[l-1]){a[i]=1;}
        else{a[i]=0;}
    }
    printf("Cuvantul este: ");
    printf("\n");
    while(nrg>0)
    {
        system("cls");
        desen(nrg);
        afisare_cuv(cuv,l,a);
        printf("\nLitera: ");
        scanf(" %c",&litera);
        ok=0;
        for(i=0;i<l;i++)
        {
            if(litera==cuv[i]){a[i]=1;ok=ok+1;}
        }
        if(ok==0){nrg=nrg-1;}
        if(nrg==0)
        {printf("Nu ati ghicit cuvantul\n");
        printf("Cuvantul era: %s\n",cuv);
        sf_joc(0);
        break;}
        if(ghicit(a,l)==1)
        {printf("Ati ghicit cuvantul\n");
        printf("Cuvantul era: %s\n",cuv);
        sf_joc(l);
        break;}
    }
}
void desen(int x)
{
    if(x==5)
    {
        printf(" ___________\n");
        printf(" |         }\n");
        printf(" |         \n");
        printf("_|______________\n");
    }
    else if(x==4)
    {
        printf(" ___________\n");
        printf(" |         }\n");
        printf(" |         0 \n");
        printf("_|______________\n");
    }
    else if(x==3)
    {
        printf(" ___________\n");
        printf(" |         }\n");
        printf(" |       \\ 0 \n");
        printf("_|______________\n");
    }
    else if(x==2)
    {
        printf(" ___________\n");
        printf(" |         }\n");
        printf(" |       \\ 0 /\n");
        printf("_|______________\n");
    }
    else if(x==1)
    {
        printf(" ___________\n");
        printf(" |         }\n");
        printf(" |       \\ 0 /\n");
        printf(" |         |\n");
        printf(" |        /  \n");
        printf("_|______________\n");
    }
    else
    {
        printf(" ___________\n");
        printf(" |         }\n");
        printf(" |       \\ 0 /\n");
        printf(" |         |\n");
        printf(" |        / \\ \n");
        printf("_|______________\n");
    }
}
int ghicit(int a[60],int l)
{
    int i,k=0;
    for(i=0;i<l;i++)
    {
        if(a[i]==1){k++;}
    }
    if(k==l){return 1;}
    else{return 0;}
}
void afisare_cuv(char x[60],int l,int a[60])
{
    int i;
    for(i=0;i<l;i++)
    {
        if(x[i]==x[0]||x[i]==x[l-1]||a[i]==1)
        {
            printf("%c",x[i]);
        }
        else
        {
            printf("_");
        }
    }
}
void sf_joc(int l)
{
    char x[20],y[20];
    printf("Introduceti-va numele: ");
    scanf("%s",&x);
    strcpy(y,x);
    strcat(y,".txt");
    FILE *f1=fopen(y,"r");
    if(f1==NULL)
    {
        fclose(f1);
        f1=fopen(y,"w");
        fprintf(f1,"1 %d",l);
        mod_cls(0,x,l);
        fclose(f1);
        delay();
        meniu_in_joc();
    }
    else
    {
        mod_cls(1,x,l);
        int joc,scor,i=1;
        while(fscanf(f1,"%d %d",&joc,&scor)!=EOF)
        {
            i++;
        }
        fclose(f1);
        f1=fopen(y,"a");
        fprintf(f1,"%d %d",i,l);
        fprintf(f1,"\n");
        fclose(f1);
        delay();
        meniu_in_joc();
    }
}
void mod_cls(int ok,char x[20],int l)
{
    FILE *cl=fopen("clasament.txt","r");
    char nume[50][30],n[30];
    int scor[50],s,i=0,k;
    while(fscanf(cl,"%s %d",n,&s)!=EOF)
    {
        strcpy(nume[i],n);
        scor[i]=s;
        i++;
    }
    fclose(cl);
    if(ok==1) //daca jucatorul e deja in cls
    {
        for(k=0;k<i;k++)
        {
            if(strcmp(nume[k],x)==0)
            {
                scor[k]=scor[k]+l;
                break;
            }
        }
    }
    else
    {
        strcpy(nume[i],x);
        scor[i]=l;
        i++;
    }
    int p,aux;
    char t[50];
    for(k=i-1;k>=0;k--)
    {
        for(p=k-1;p>=1;p--)
        {
            if(scor[k]>scor[p])
            {
                aux=scor[k];
                scor[k]=scor[p];
                scor[p]=aux;
                strcpy(t,nume[k]);
                strcpy(nume[k],nume[p]);
                strcpy(nume[p],t);
            }
        }
    }
    FILE *f2=fopen("clsv2.txt","w");
    for(k=0;k<i-1;k++)
    {
        fprintf(f2,"%s ",nume[k]);
        fprintf(f2,"%d\n",scor[k]);
    }
    fprintf(f2,"%s ",nume[i-1]);
    fprintf(f2,"%d",scor[i-1]);
    fclose(f2);
    remove("clasament.txt");
    rename("clsv2.txt","clasament.txt");
}
int meniu_cls()
{
    int alg;
    printf("1.Vezi istoric jucator\n");
    printf("2.Meniu\n");
    printf("Alegeti o optiune\n");
    scanf("%d",&alg);
    if(alg<=0||alg>2){printf("Optiunea gresita. Alegeti din nou.\n");delay();meniu();}
    else{
        if(alg==1){istoric();}
        else if(alg==2){meniu();}
    }
}
void istoric()
{
    printf("\n");
    printf("Istoricul carui jucator vreti sa-l vedeti? ");
    char n[40];
    scanf("%s",&n);
    strcat(n,".txt");
    system("cls");
    FILE *f=fopen(n,"r");
    if(f==NULL)
    {
        printf("Nu exista istoric pentru acest jucator");
        printf("\n");
        meniu_cls();
    }
    else
    {
        int scor,joc;
        while(fscanf(f,"%d %d",&joc,&scor)!=EOF)
        {
            printf("%d - %d puncte\n",joc,scor);
        }
        fclose(f);
        meniu_cls();
    }
}
void clasament()
{
    system("cls");
    FILE *cl=fopen("clasament.txt","r");
    if(cl==NULL)
    {
        printf("Momentan nu exista clasament\n");
        delay();
        meniu();
    }
    else
    {
        char nume[30];
        int scor,l=1;
        while(fscanf(cl,"%s %d",nume,&scor)!=EOF)
        {
            printf("%d.%s - %dpx\n",l,nume,scor);
            l=l+1;
        }
        fclose(cl);
        meniu_cls();
    }
}
int main()
{
    meniu();
    return 0;
}
