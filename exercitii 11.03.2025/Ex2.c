/*1. Structura si functii
Se consideră prima literă din numele vostru, și prima literă din prenumele vostru.
Sa se construiască un articol care să conțină cele două litere.
Articolul trebuie să aibă logica. Articolul trebuie sa fie un substantiv. Articolul trebuie sa aibă
cel puțin trei atribute, si cel puțin unul să fie alocat dinamic.
Realizati o functie cu ajutorul careia sa cititi de la tastatura un articol de tipul construit de
voi. Funcția returnează obiectul citit.
Realizati o functie care calculeaza ceva pentru un obiect de tipul implementat de voi. (o
medie sau o suma, un maxim, un minim...sau orice altceva)
Realizati o functie care modifica pentru un obiect primit ca parametru, un anumit camp.
noua valoare este primita ca parametru.
Realizați o funcție care afișează un obiect de tipul creat. Afișarea se face la console, și sunt
afișate toate informațiile.

numele: nitu maria - NM - atribut folosit animale
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Animal {
    int cod;
    char* specie;
    int varsta;
    float* preturiMancare;
    int nrFeluri;
};


struct Animal citesteAnimal() {
    struct Animal a;
    printf("Introduceti codul animalului(ex:4215): ");
    scanf("%d", &a.cod);
    getchar();

    char buffer[100];
    printf("Introduceti specia animalului(ex:pisica): ");
    fgets(buffer, 100, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    a.specie = (char*)malloc(strlen(buffer) + 1);
    strcpy(a.specie, buffer);


    printf("Introduceti varsta animalului: ");
    scanf("%d", &a.varsta);


    printf("Introduceti numarul de feluri de mancare(fiecare fel de mancare va avea pret): ");
    scanf("%d", &a.nrFeluri);


    a.preturiMancare = (float*)malloc(a.nrFeluri * sizeof(float));
    for (int i = 0; i < a.nrFeluri; i++) {
        printf("Pretul felului de mancare %d: ", i + 1);
        scanf("%f", &a.preturiMancare[i]);
    }

    return a;
}


float calculeazaMediaMancare(struct Animal a) {
    float suma = 0;
    for (int i = 0; i < a.nrFeluri; i++) {
        suma += a.preturiMancare[i];
    }

    if (a.nrFeluri > 0) {
        return suma / a.nrFeluri;
    }
    else {
        return 0;
    }
}


void modificaSpecie(struct Animal* a, const char* specieNoua) {
    free(a->specie);
    a->specie = (char*)malloc(strlen(specieNoua) + 1);
    strcpy(a->specie, specieNoua);
}


void afiseazaAnimal(struct Animal a) {
    printf("Animal {\n");
    printf("Cod: %d\n", a.cod);
    printf("Specie: %s\n", a.specie);
    printf("Varsta: %d\n", a.varsta);
    printf("Preturi mancare: ");
    for (int i = 0; i < a.nrFeluri; i++) {
        printf("%.2f ", a.preturiMancare[i]);
    }
    printf("\n}\n");
}


void elibereazaAnimal(struct Animal* a) {
    free(a->specie);
    free(a->preturiMancare);
}


int main() {
    struct Animal animal = citesteAnimal();
    afiseazaAnimal(animal);

    float media = calculeazaMediaMancare(animal);
    printf("Media preturilor la mancare: %.2f\n", media);

    modificaSpecie(&animal,"Papagal (specie modificata)");
    printf("Dupa modificare:\n");
    afiseazaAnimal(animal);

    elibereazaAnimal(&animal);
    return 0;
}

