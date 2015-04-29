/**
 * @file test.c
 * @Synopsis A testing program for polynomial
 * @author Xinguo Liu
 * @version Version 1.0
 * @date 2015-04-14
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "polynomial.h"

#define MaxLine 1024

int main(int argc, char * argv[])
{
	FILE * fp = NULL;
	Polynomial p1, p2, p[3];
	if( argc<2 ) {
		printf("Usage: <polynomial file name>\n");
		return 0;
	}
	printf("Opening file %s...", argv[1]);
	if( (fp = fopen(argv[1], "rt"))==NULL ) {
		printf("Failed");
		return 0;
	}
	printf("\n");
	/* read polynomial */
	p1 = readPolynomial(fp); 
	printPolynomial(&p1);
	p2 = readPolynomial(fp); 
	printPolynomial(&p2);
	p[0] = addPolynomial(&p1,&p2);
	p[1] = subPolynomial(&p1,&p2); 
	p[2] = mulPolynomial(&p1,&p2); 
	printPolynomial(p+0); releasePolynomial(p+0);
	printPolynomial(p+1); releasePolynomial(p+1);
	printPolynomial(p+2); releasePolynomial(p+2);
	releasePolynomial(&p1);
	releasePolynomial(&p2);
	return 0; 
}

