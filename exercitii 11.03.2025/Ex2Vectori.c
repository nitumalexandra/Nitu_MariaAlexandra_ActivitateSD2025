#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Animal {
    int cod;
    char* specie;
    int varsta;
    float* preturiM;
    int nrFeluri;
};

struct Animal citireAnimal() {
    struct Animal a;
    printf("Cod: ");
    scanf("%d", &a.cod);
    getchar();

    char buffer[100];
    printf("Specie: ");
    fgets(buffer, 100, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    a.specie = (char*)malloc(strlen(buffer) + 1);
    strcpy(a.specie, buffer);

    printf("Varsta: ");
    scanf("%d", &a.varsta);

    printf("Numar feluri mancare (fiecare fel va avea cate un pret): ");
    scanf("%d", &a.nrFeluri);

    a.preturiM = (float*)malloc(a.nrFeluri * sizeof(float));
    for (int i = 0; i < a.nrFeluri; i++) {
        printf("Pret %d: ", i + 1);
        scanf("%f", &a.preturiM[i]);
    }

    return a;
}

void afisAnimal(struct Animal a) {
    printf("Cod: %d , Specie: %s , Varsta: %d , Preturi: ", a.cod, a.specie, a.varsta);
    for (int i = 0; i < a.nrFeluri; i++) {
        printf("%.2f ", a.preturiM[i]);
    }
    printf("\n");
}

float mediaMancare(struct Animal a) {
    float suma = 0;
    for (int i = 0; i < a.nrFeluri; i++) {
        suma += a.preturiM[i];
    }
    return suma / a.nrFeluri;
}

void elibereazaAnimal(struct Animal* a) {
    free(a->specie);
    free(a->preturiM);
}

struct Animal copieAnimal(struct Animal src) {
    struct Animal copy;
    copy.cod = src.cod;
    copy.varsta = src.varsta;
    copy.nrFeluri = src.nrFeluri;

    copy.specie = (char*)malloc(strlen(src.specie) + 1);
    strcpy(copy.specie, src.specie);

    copy.preturiM = (float*)malloc(src.nrFeluri * sizeof(float));
    for (int i = 0; i < src.nrFeluri; i++) {
        copy.preturiM[i] = src.preturiM[i];
    }

    return copy;
}

struct Animal* filtrareVarsta(struct Animal* vector, int dim, int vMin, int* dimNoua) {
    *dimNoua = 0;
    struct Animal* rezultat = (struct Animal*)malloc(dim * sizeof(struct Animal));

    for (int i = 0; i < dim; i++) {
        if (vector[i].varsta >= vMin) {
            rezultat[*dimNoua] = copieAnimal(vector[i]);
            (*dimNoua)++;
        }
    }

    return rezultat;
}

struct Animal* filtrareMedia(struct Animal* vector, int dim, float prag, int* dimNoua) {
    *dimNoua = 0;
    struct Animal* rezultat = (struct Animal*)malloc(dim * sizeof(struct Animal));

    for (int i = 0; i < dim; i++) {
        if (mediaMancare(vector[i]) > prag) {
            rezultat[*dimNoua] = copieAnimal(vector[i]);
            (*dimNoua)++;
        }
    }

    return rezultat;
}

struct Animal* Vconcat(struct Animal* v1, int dim1, struct Animal* v2, int dim2, int* dimRez) {
    *dimRez = dim1 + dim2;
    struct Animal* rezultat = (struct Animal*)malloc(*dimRez * sizeof(struct Animal));

    for (int i = 0; i < dim1; i++) {
        rezultat[i] = copieAnimal(v1[i]);
    }
    for (int i = 0; i < dim2; i++) {
        rezultat[dim1 + i] = copieAnimal(v2[i]);
    }

    return rezultat;
}

void afisVector(struct Animal* vector, int dim, const char* label) {
    printf("\n %s \n", label);
    for (int i = 0; i < dim; i++) {
        afisAnimal(vector[i]);
    }
}

int main() {
    int n;
    printf("Introduceti numarul de animale\n");
    scanf("%d", &n);

    struct Animal* animale = (struct Animal*)malloc(n * sizeof(struct Animal));
    for (int i = 0; i < n; i++) {
        printf("\nAnimalul %d:\n", i + 1);
        animale[i] = citireAnimal();
    }

    afisVector(animale, n, "Vector initial");

    int dimV;
    struct Animal* vecVarsta = filtrareVarsta(animale, n, 5, &dimV);
    afisVector(vecVarsta, dimV, "Varsta >= 5");

    int dimM;
    struct Animal* vecMedia = filtrareMedia(animale, n, 15.0f, &dimM);
    afisVector(vecMedia, dimM, "Media > 15");

    int dimConcat;
    struct Animal* concatenat = Vconcat(vecVarsta, dimV, vecMedia, dimM, &dimConcat);
    afisVector(concatenat, dimConcat, "Vector concatenat");


    for (int i = 0; i < n; i++) elibereazaAnimal(&animale[i]);
    free(animale);

    for (int i = 0; i < dimV; i++) elibereazaAnimal(&vecVarsta[i]);
    free(vecVarsta);

    for (int i = 0; i < dimM; i++) elibereazaAnimal(&vecMedia[i]);
    free(vecMedia);

    for (int i = 0; i < dimConcat; i++) elibereazaAnimal(&concatenat[i]);
    free(concatenat);

    return 0;
}