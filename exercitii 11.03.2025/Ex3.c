#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

bool estePrim(int nr) {
    if (nr <= 1) {
        return false;
    }
    for (int i = 2; i * i <= nr; i++) {
        if (nr % i == 0) {
            return false;
        }
    }
    return true;
}


void prim(int nr) {
    printf("Factorii primi ai numarului %d sunt: ", nr);

    for (int i = 2; i <= nr; i++) {
        if (nr % i == 0 && estePrim(i)) {
            printf("%d ", i);
            while (nr % i == 0) {
                nr /= i;
            }
        }
    }

    printf("\n");
}

int main() {
    int nr;
    printf("Introduceti un numar: ");
    scanf("%d", &nr);
    prim(nr);

    return 0;
}
