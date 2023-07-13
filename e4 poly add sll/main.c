#include <stdio.h>
#include "poly.h"

poly* obtain_poly(int n) {
    int e, i;
    float c;
    poly* p = create_poly();
    printf("Enter the polynomial.\n[poly %d] >>> ", n);
    do {
    	scanf("%fx^%d", &c, &e);
    	insert_ord(p, c, e);
	} while (e > 0);
    return p;
}

int main() {
    poly
        *p = obtain_poly(1),
        *q = obtain_poly(2),
        *r = add_poly(p, q);
    printf("Polynomial 1: ");
    display_poly(p);
    printf("\nPolynomial 2: ");
    display_poly(q);
    printf("\nResult: ");
    display_poly(r);
    printf("\n");
    return 0;
}
