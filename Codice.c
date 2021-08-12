#include <stdio.h>
#include <stdlib.h>

#define LUNG_RIGO 4000
#define MAX_NUM 4294967295
struct grafo{
    int grafo;
    unsigned int cammino;};
typedef struct grafo Grafo;


unsigned int nNodi, k, numeroGrafo=0, numerografi=0;

Grafo* AggiungiGrafo(Grafo* lista);
void TopK(Grafo* lista);
Grafo Dijkstra(unsigned int matrice[nNodi][nNodi]);


unsigned int Left(unsigned int i);
unsigned int Right(unsigned int i);
Grafo* Max_Heapify(Grafo* A, unsigned int i);
Grafo* Build_Max_Heap(Grafo* lista);
int main() {
   char riga[LUNG_RIGO];
   nNodi=0;
   k=0;
   int i;
   if(fgets(riga, LUNG_RIGO, stdin)){};
   for(i=0; riga[i]!=' '; i++)
       nNodi=nNodi*10+(riga[i]-48);
   for(i++; riga[i]!='\n'; i++)
       k=k*10+(riga[i]-48);

   Grafo *lista = malloc(sizeof(Grafo[k]));
   for(int i=0; i<k; i++)
   {
       lista[i].cammino = MAX_NUM;
       lista[i].grafo=-1;
   }
    do{
        if(fgets(riga, LUNG_RIGO, stdin)) { ;
            switch (riga[0]) {
                case 'A':
                    numerografi++;
                    AggiungiGrafo(lista);
                    break;
                case 'T':
                    TopK(lista);
                    break;
            }
        }
        else
            return 0;
   }while(1);
}

Grafo* AggiungiGrafo(Grafo* lista) {
    char riga[LUNG_RIGO];
    Grafo nuovoElem;

    unsigned int matrice[nNodi][nNodi];
    for (int i = 0; i < nNodi; i++) {
        int l = -1;
        if (fgets(riga, LUNG_RIGO, stdin)) {};
        for (int j = 0; j < nNodi; j++) {
            unsigned int num;
            num = 0;
            for (l++; riga[l] != ',' && riga[l] != '\n' && riga[l] != '\0'; l++)
                num = num * 10 + (riga[l] - 48);
            if (num == 0)
                num = MAX_NUM;
            matrice[i][j] = num;
        }
    }

    nuovoElem = Dijkstra(matrice);
    if(k >= numerografi)
    {
        lista[numerografi-1].grafo=nuovoElem.grafo;
        lista[numerografi-1].cammino=nuovoElem.cammino;
        if(k == numerografi)
            return Build_Max_Heap(lista);
        return lista;
    }
    if (nuovoElem.cammino >= lista[0].cammino)
        return lista;
    lista[0].cammino=nuovoElem.cammino;
    lista[0].grafo=nuovoElem.grafo;
    return Max_Heapify(lista, 0);
}

//uso 4294967295 come se fosse infinito
Grafo Dijkstra(unsigned int matrice[nNodi][nNodi])
{
    int NonVisitati[nNodi];   //array di nodi NON visitati, in posizione 5 avrò nodo 5, se l'ho già visitato ci metto -1
    unsigned int distanze[nNodi];
    for(int i=0; i<nNodi; i++)
    {
        NonVisitati[i]=i;
        distanze[i]=matrice[0][i];   //qui sto facendo la ricerca x il primo nodo
    }
    NonVisitati[0]=-1;
    distanze[0]=0;  //la distanza di 0 da 0 è sempre 0
    for(int i=1; i<nNodi; i++)
    {
        unsigned int distMinore=MAX_NUM;  //indica la minore tra quelle nella lista delle distanze
        int nodoAttuale = 0;

        //qui sto scegliendo su quale nodo applicare l'algoritmo (sara' poi j)
        for(int j=1; j<nNodi; j++) {
            //qui controllo di non averlo già visitato
            int visitato = 0; //booleano, se 0 non ho visitato
            //if(k<20)
            if(NonVisitati[j] == -1)
                 visitato=1;
                //qui trovo il nodo da fare
            if (distMinore > distanze[j] && visitato == 0) {
                distMinore = distanze[j];
                nodoAttuale = j;
            }
        }

        unsigned int distNodo = distanze[nodoAttuale];
        NonVisitati[nodoAttuale] = -1;
        //qui calcolo le distanze e vedo se sono minori
        for(int j=0; j<nNodi; j++)
        {
            unsigned long long somma;
            if(matrice[nodoAttuale][j] == MAX_NUM)
                somma = MAX_NUM;
            else
                somma = distNodo + matrice[nodoAttuale][j];
            if(somma < distanze[j])
                distanze[j] = somma;
        }
    }

    unsigned long long totaleDistanze = 0;
    for(int i=0; i< nNodi; i++) {
        if(distanze[i] == MAX_NUM)
            distanze[i]=0;
        totaleDistanze += distanze[i];
    }
    Grafo grafo;
    grafo.cammino=totaleDistanze;
    grafo.grafo=numeroGrafo;
    numeroGrafo++;
    return grafo;
}

void TopK(Grafo *lista)
{
    for(int i=0; i<k && i<numerografi; i++) {
        /*fputs((char*)lista[i].grafo, stdout);
        fputs(" ", stdout);*/                           //consigli per parsare da int a stringa?
        if(i==k-1 || i==numerografi-1)
            printf("%d", lista[i].grafo);
        else
            printf("%d ", lista[i].grafo);
    }
    fputs("\n", stdout);
}

Grafo* Build_Max_Heap(Grafo* lista)
{
    Grafo* ritorno = malloc(sizeof(Grafo[k]));
    for(unsigned int i=k/2; i>0; i--)
        ritorno=Max_Heapify(lista, i);
    return ritorno;
}

Grafo* Max_Heapify(Grafo* A, unsigned int i)
{
    unsigned int max;
    unsigned int l=Left(i);
    unsigned int r=Right(i);
    if(l<=k && A[l].cammino>A[i].cammino)
        max=l;
    else
        max=i;
    if(r<=k && A[r].cammino>A[max].cammino)
        max=r;
    if(max!=i){
        Grafo grafo;
        grafo.grafo=A[i].grafo;
        grafo.cammino=A[i].cammino;

        A[i].grafo=A[max].grafo;
        A[i].cammino=A[max].cammino;

        A[max].grafo=grafo.grafo;
        A[max].cammino=grafo.cammino;

        Max_Heapify(A, max);
    }
    return A;
}


unsigned int Left(unsigned int i)
{
    return 2*i;
}
unsigned int Right(unsigned int i)
{
    return 2*i+1;
}