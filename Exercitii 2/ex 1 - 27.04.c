/*Se doreste gestiunea cladirilor din Bucuresti in funtie de anul construirii. Acest lucru va ajuta
la stabilire riscului seismic al acestora.
1. Sa se creeze o tabela de dispersie pentru stocarea cladirilor din Bucuresti (structura
Cladire contine ce atribute vreti voi dar va contine obligatoriu anul construirii si un id unic).
campul folosit pentru clusterizare este anul construirii cladirii.
2. Implementati o functie care afiseaza cladirile dintr-un cluster (construite intr-un an primit
ca parametru).
3. Implementati o functie care sterge o cladire pentru care se primeste id-ul si anul
construirii.
4. Implementati o functie care sterge o cladire pentru care se primeste doar id-ul cladirii.
5. Observatii diferenta dintre functia implementata la 4 si functia de la 5.
6. Implementati o functie care salveaza intr-un vector toate cladirile dintr-un an primit ca
parametru. Realizati deep copy, astfel incat elementele din vector sa fie diferentiate de cele
din tabela de dispersie. Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti pentru
cate elemente veti aloca spatiu.
7. Implementati o functie care modifica anul construirii unei cladiri identificate prin ID.
Functia primeste ca parametri: id-ul cladirii, vechiul an de constructie si noul an de
constructie. Aveti grija se modifica valoarea atributului folosit pentru clusterizare. */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Cladire {
    int id;
    int an;
    char* nume;
};

struct Nod {
    struct Cladire cladire;
    struct Nod* next;
};

struct Nod** creareTabela(int dimensiune) {
    struct Nod** tabela = (struct Nod**)malloc(dimensiune * sizeof(struct Nod*));
    for (int i = 0; i < dimensiune; i++) tabela[i] = NULL;
    return tabela;
}

void inserare(struct Nod** tabela, int dimensiune, struct Cladire c) {
    int poz = c.an % dimensiune;
    struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
    nou->cladire.id = c.id;
    nou->cladire.an = c.an;
    nou->cladire.nume = (char*)malloc(strlen(c.nume) + 1);
    strcpy(nou->cladire.nume, c.nume);
    nou->next = tabela[poz];
    tabela[poz] = nou;
}

void afisareCluster(struct Nod** tabela, int dimensiune, int an) {
    int poz = an % dimensiune;
    struct Nod* p = tabela[poz];
    while (p) {
        if (p->cladire.an == an)
            printf("ID:%d An:%d Nume:%s\n", p->cladire.id, p->cladire.an, p->cladire.nume);
        p = p->next;
    }
}

void stergereIdAn(struct Nod** tabela, int dimensiune, int id, int an) {
    int poz = an % dimensiune;
    struct Nod* p = tabela[poz], * ant = NULL;
    while (p && (p->cladire.id != id || p->cladire.an != an)) {
        ant = p;
        p = p->next;
    }
    if (p) {
        if (ant) ant->next = p->next;
        else tabela[poz] = p->next;
        free(p->cladire.nume);
        free(p);
    }
}

void stergereId(struct Nod** tabela, int dimensiune, int id) {
    for (int i = 0; i < dimensiune; i++) {
        struct Nod* p = tabela[i], * ant = NULL;
        while (p) {
            if (p->cladire.id == id) {
                if (ant) ant->next = p->next;
                else tabela[i] = p->next;
                free(p->cladire.nume);
                free(p);
                return;
            }
            ant = p;
            p = p->next;
        }
    }
}

struct Cladire* cladiriDinAn(struct Nod** tabela, int dimensiune, int an, int* nr) {
    int poz = an % dimensiune;
    struct Nod* p = tabela[poz];
    *nr = 0;
    struct Nod* q = p;
    while (q) { if (q->cladire.an == an) (*nr)++; q = q->next; }
    struct Cladire* v = (struct Cladire*)malloc((*nr) * sizeof(struct Cladire));
    int k = 0;
    while (p) {
        if (p->cladire.an == an) {
            v[k].id = p->cladire.id;
            v[k].an = p->cladire.an;
            v[k].nume = (char*)malloc(strlen(p->cladire.nume) + 1);
            strcpy(v[k].nume, p->cladire.nume);
            k++;
        }
        p = p->next;
    }
    return v;
}

void modificaAn(struct Nod** tabela, int dimensiune, int id, int anVechi, int anNou) {
    int poz = anVechi % dimensiune;
    struct Nod* p = tabela[poz], * ant = NULL;
    while (p && (p->cladire.id != id || p->cladire.an != anVechi)) {
        ant = p;
        p = p->next;
    }
    if (p) {
        struct Cladire cNou = p->cladire;
        cNou.an = anNou;
        if (ant) ant->next = p->next;
        else tabela[poz] = p->next;
        free(p);
        inserare(tabela, dimensiune, cNou);
    }
}

int main() {
    int dim = 10;
    struct Nod** tabela = creareTabela(dim);
    inserare(tabela, dim, (struct Cladire) { 1, 1990, "Bloc A" });
    inserare(tabela, dim, (struct Cladire) { 2, 1977, "Bloc B" });
    inserare(tabela, dim, (struct Cladire) { 3, 1990, "Bloc C" });
    afisareCluster(tabela, dim, 1990);
    int nr;
    struct Cladire* v = cladiriDinAn(tabela, dim, 1990, &nr);
    for (int i = 0; i < nr; i++) printf("Copiat: %s\n", v[i].nume);
    stergereIdAn(tabela, dim, 3, 1990);
    stergereId(tabela, dim, 2);
    modificaAn(tabela, dim, 1, 1990, 2000);
    free(v);
    return 0;
}
