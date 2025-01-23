

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef struct El {
    short int points[7];
    struct El * next[7];
} Nodo;
typedef Nodo * Tree;

typedef struct {
    int pos, punti;
} Move;

Tree create(int d) {
    if(d == 0)
        return NULL;
    Tree t = malloc(sizeof(Nodo));
    for(int i=0; i<7; i++) {
        t->points[i] = 0;
        t->next[i] = create(d-1);
    }
    return t;
}
void inizializzaTabella(char m[6][7]) {
    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
            m[i][j] = ' ';
}
void StampaTabella(char m[6][7]) {
    for(int i=0; i<6; i++) {
        printf("|");
        for(int j =0; j<7; j++)
            printf("%c|", m[i][j]);
        printf("\n");
    }
    printf("---------------\n");
}
int checkOrizzontale(char m[6][7]) {
    int i,j;
    for(i = 0; i<6; i++)
        for(j=0; j<4; j++) {
            if(m[i][j] == 'X' && m[i][j+1] == 'X' && m[i][j+2] == 'X' && m[i][j+3] == 'X')
                return 1;
            if(m[i][j] == 'O' && m[i][j+1] == 'O' && m[i][j+2] == 'O' && m[i][j+3] == 'O')
                return 2;
        }
    return 0;
}
int checkVerticale(char m[6][7]) {
    for(int i = 0; i<3; i++)
        for(int j=0; j<4; j++) {
            if(m[i][j] == 'X' && m[i+1][j] == 'X' && m[i+2][j] == 'X' && m[i+3][j] == 'X')
                return 1;
            if(m[i][j] == 'O' && m[i+1][j] == 'O' && m[i+2][j] == 'O' && m[i+3][j] == 'O')
                return 2;
        }
    return 0;
}
int checkDiagPrin(char m[6][7]) {
    for(int i=0; i<3; i++)
        for(int j=0; j<4; j++) {
            if(m[i][j] == 'X' && m[i+1][j+1] == 'X' && m[i+2][j+2] == 'X' && m[i+3][j+3] == 'X')
                return 1;
            if(m[i][j] == 'O' && m[i+1][j+1] == 'O' && m[i+2][j+2] == 'O' && m[i+3][j+3] == 'O')
                return 2;
        }
    return 0;
}
int checkDiagSec(char m[6][7]) {
    for(int i = 3; i<6; i++)
        for(int j=0; j<4; j++) {
            if(m[i][j] == 'X' && m[i-1][j+1] == 'X' && m[i-2][j+2] == 'X' && m[i-3][j+3] == 'X')
                return 1;
            if(m[i][j] == 'O' && m[i-1][j+1] == 'O' && m[i-2][j+2] == 'O' && m[i-3][j+3] == 'O')
                return 2;
        }
    return 0;
}
int check(char m[6][7]) {
    if(checkOrizzontale(m) >= 1)
        return checkOrizzontale(m);
    if(checkVerticale(m) >= 1)
        return checkVerticale(m);
    if(checkDiagPrin(m) >= 1)
        return checkDiagPrin(m);
    if(checkDiagSec(m) >= 1)
        return checkDiagSec(m);
    return 0;
}
int countOriz(char k[6][7], char b) {
    short int n=0, count=0, i, j, l;
    for(i=0; i<6; i++)
        for(j=0; j<4; j++) {
            for(l=0; l<4; l++)
                if(k[i][j+l] == b)
                    count++;
                else if(k[i][j+l] != ' ') {
                    count = 0;
                    break;
                }
            if(count == 2)
                n++;
            else if(count == 3)
                n += 10;
            else if(count == 4)
                n+= 1000;
            count = 0;
        }
    return n;
}
int countVert(char k[6][7], char b) {
    short int n=0, count = 0, i, j, l;
    for(i =3; i<6; i++)
        for(j=0; j<7; j++){
            for(l=0; l<4; l++)
                if(k[i-l][j] == b)
                    count++;
                else if(k[i-l][j] != ' ') {
                    count = 0;
                    break;
                }
            if(count == 2)
                n++;
            else if(count == 3)
                n += 10;
            else if(count == 4)
                n+= 1000;
            count = 0;
        }
    return n;
}
int countDiagPrinc(char k[6][7], char b) {
    short int n=0, count = 0, i, j, l;
    for(i=3; i<6; i++)
        for(j=0; j<4; j++) {
            for(l=0; l<4; l++)
                if(k[i-l][j+l] == b)
                    count++;
                else if(k[i-l][j+l] != ' ') {
                    count = 0;
                    break;
                }
            if(count == 2)
                n++;
            else if(count == 3)
                n += 10;
            else if(count == 4)
                n+= 1000;
            count = 0;
        }
    return n;
}
int countDiagSec(char k[6][7], char b) {
    short int n=0, count = 0, i, j, l;
    for(i=0; i<3; i++)
        for(j=0; j<4; j++) {
            for(l =0; l<4; l++)
                if(k[i+l][j+l] == b)
                    count++;
                else if(k[i+l][j+l] != ' ') {
                    count = 0;
                    break;
                }
            if(count == 2)
                n++;
            else if(count == 3)
                n += 10;
            else if(count == 4)
                n+= 1000;
            count = 0;
        }
    return n;
}
int count(char k[6][7], int d) {
    int n=0;
    n += countOriz(k, 'O');
    n += countVert(k, 'O');
    n += countDiagPrinc(k, 'O');
    n += countDiagSec(k, 'O');
    n -= countOriz(k, 'X');
    n -= countVert(k, 'X');
    n -= countDiagPrinc(k, 'X');
    n -= countDiagSec(k, 'X');
    if(d%2 == 0)
        n = -n;
    return n;
}
void mossa(char m[6][7], int *flag) {
    int i,j;
    do{
        do{
            printf("Inserisci la colonna della mossa: ");
            scanf("%d", &j);
        } while(j<1 && j>7);
        for(i=5; i>=0; i--)
            if(m[i][j-1] == ' ')
                break;
    } while(i== -1);
    *flag = 2;
    m[i][j-1] = 'X';
}
int checkTabella(char m[6][7]) {
    for(int i =0; i<6; i++)
        for(int j=0; j<7; j++)
            if(m[i][j] == ' ')
                return 1;
    return 0;
}
int max(short int v[7]) {
    int ind = 0;
    for(int i=1; i<7; i++)
        if(v[ind] < v[i])
            ind = i;
    return ind;
}
Move findBestMove(Tree t) {
    Move z;
    if(t->next[0] == NULL) {
        z.pos = max(t->points);
        z.punti = t->points[z.pos];
        return z;
    }
    for(int i=0; i<7; i++)
        if(t->points[i] >= 899) {
            z.pos = max(t->points);
            z.punti = t->points[z.pos];
            return z;
        }
    Move v[7];
    short int l[7] = {0};
    for(int i=0; i<7; i++) {
        if(t->points[i] == -25000)
            l[i] = -30000;
        else {
            v[i] = findBestMove(t->next[i]);
            l[i] = t->points[i] * 1.2 - v[i].punti;
        }
    }
    z.pos = max(l);
    z.punti = v[z.pos].punti;
    return z;
}
int inserisciii(int pos, char m[6][7], int d) {
    int i=5;
    while(i>=0) {
        if(m[i][pos] == ' ')
            break;
        i--;
    }
    if(i==-1)
        return -1;
    if(d%2==0)
        m[i][pos] = 'X';
    else
        m[i][pos] = 'O';
    return 0;
}
void togli(int pos, char m[6][7]) {
    int i;
    for(i=0; i<6; i++)
        if(m[i][pos] != ' ')
            break;
    m[i][pos] = ' ';
}
void inserisciValori(Tree t, char m[6][7], int d) {
    if(t->next[0] == NULL) {
        for(int i = 0; i<7; i++) {
            int k = inserisciii(i, m,d);
            if(k!=-1) {
                t->points[i] = count(m, d);
                togli(i, m);
            }
            else
                t->points[i] = -25000;
        }
        return;
    }
    for(int i=0; i<7; i++) {
        int a = inserisciii(i, m, d);
        if(a==-1)
            t->points[i] = -25000;
        else{
            if(check(m) == 0)
                inserisciValori(t->next[i], m, d-1);
            t->points[i] = count(m, d);
            togli(i, m);
        }
    }
}
void MossaAI(char m[6][7], Tree t, int *flag) {
    *flag = 1;
    int i, d=8;
    inserisciValori(t, m, d);
    Move mossa = findBestMove(t);
    for(i=5; i>=0; i--)
        if(m[i][mossa.pos] == ' ')
            break;
    m[i][mossa.pos] = 'O';
}
void game(char m[6][7]) {
    int flag = 2;
    Tree t = create(8);
    do {
        if(checkTabella(m) == 0) {
            printf("Pareggio");
            return;
        }
        if(flag == 1)
            mossa(m, &flag);
        else
            MossaAI(m, t, &flag);
        StampaTabella(m);
    } while(check(m) == 0);
    if(check(m) == 1)
        printf("Hai vinto giocatore 1\n");
    else
        printf("Hai vinto giocatore 2\n");
}

int main(void){
    char m[6][7];
    inizializzaTabella(m);
    StampaTabella(m);
    game(m);
    return 0;
}
