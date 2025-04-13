/* 5. Liste simple
Se considera lista simplu inlantuita realizata la seminar.
1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru.Daca lista
are mai putine noduri decat index - ul dat, nu se realizeaza stergerea.
2. Implementati o functie care sa insereze elementele in cadrul listei simplu inlantuite astfel
incat acestea a fie sortate crescator dupa un camp la alegerea voastra.
3. Implementati o functie care salveaza intr - un vector toate obiectele care indeplinesc o
conditie stabilita de voi.Realizati deep copy, astfel incat elementele din vector sa fie
diferentiate de cele din lista.Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti
pentru cate elemente veti aloca spatiu.
4. Implementati o functie care primeste lista si doua pozitii.In cadrul functiei trebuie sa
interschimbati elementele de pe cele doua pozitii din lista primita. */

#include <stdio.h>
#include <stdlib.h>

typedef struct Nod {
    int id;
    int valoare;
    struct Nod* next;
} Nod;

Nod* creareNod(int id, int valoare) {
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    nod->id = id;
    nod->valoare = valoare;
    nod->next = NULL;
    return nod;
}

void Sortat(Nod** head, int id, int valoare) {
    Nod* nou = creareNod(id, valoare);
    if (*head == NULL || (*head)->valoare > valoare) {
        nou->next = *head;
        *head = nou;
        return;
    }
    Nod* curent = *head;
    while (curent->next != NULL && curent->next->valoare <= valoare) {
        curent = curent->next;
    }
    nou->next = curent->next;
    curent->next = nou;
}

void StergerePoz(Nod** head, int pozitie) {
    if (*head == NULL || pozitie < 0) return;
    Nod* temp = *head;
    if (pozitie == 0) {
        *head = temp->next;
        free(temp);
        return;
    }
    for (int i = 0; temp != NULL && i < pozitie - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) return;
    Nod* deSters = temp->next;
    temp->next = deSters->next;
    free(deSters);
}

void AfisList(Nod* head) {
    while (head != NULL) {
        printf("[id: %d, val: %d] -> ", head->id, head->valoare);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Nod* lista = NULL;
    Sortat(&lista, 1, 40);
    Sortat(&lista, 2, 60);
    Sortat(&lista, 3, 20);
    Sortat(&lista, 4, 90);
    Sortat(&lista, 5, 10);
    printf("lista dupa inserari sortate: \n");
    AfisList(lista);
    StergerePoz(&lista, 2);
    printf("lista dupa stergerea de pe pozitia 2: \n");
    AfisList(lista);
    while (lista != NULL) {
        Nod* temp = lista;
        lista = lista->next;
        free(temp);
    }
    return 0;
}
