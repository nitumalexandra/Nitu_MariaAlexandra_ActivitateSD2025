// pentru a analiza temperaturile inregistrate pe parcursul unei saptamani, un meteorolog creeaza un vector alcatuit din 7 elemente, fiecare element reprezentand cate o zi din saptamana. Se cere:
// 1. formarea si citirea vectorului
// 2. temperatura medie a saptamanii 
// 3. afisarea celei mai ridicate si scazute temperaturi si mentionarea zilei respective

#include <stdio.h>
#include <stdlib.h> 

int main() {

    const int z = 7; // numarul maxim de zile
    float* temp = (float*)malloc(z * sizeof(*temp)); // alocam memorie

    float maxT, minT;
    int maxZi = 1, minZi = 1;
    float suma = 0;

    printf("introduceti temperaturile pentru fiecare zi: \n");

    for (int i = 0; i < z; i++) {  
        printf("ziua %d: ", i + 1);
        scanf_s ("%f", &temp[i]);
    }

    maxT = minT = temp[0];

    for (int i = 0; i < z; i++) { 
        suma += temp[i];

        if (temp[i] > maxT) {
            maxT = temp[i];
            maxZi = i + 1; 
        }

        if (temp[i] < minT) {
            minT = temp[i];
            minZi = i + 1;
        }
    }

    free(temp);

    printf("temperatura medie a saptamanii: %.2f \n", suma / z);
    printf("temperatura cea mai ridicata a fost %.2f in ziua %d \n", maxT, maxZi);
    printf("temperatura cea mai scazuta a fost %.2f in ziua %d \n", minT, minZi);

    return 0;
}
