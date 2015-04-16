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

int main()
{
	Polynomial p1, p2, presult;
	char op[MaxLine];
	p1 = readPolynomial();
	printPolynomial(&p1);
	p2 = readPolynomial();
	printPolynomial(&p2);
	while ( 1 )
	{
		scanf("%s", op);
		if( strcmp(op, "add")==0 )
			presult = addPolynomial(&p1,&p2);
		else if( strcmp(op, "sub")==0 )
			presult = subPolynomial(&p1,&p2);
		else if( strcmp(op, "mul")==0 )
			presult = mulPolynomial(&p1,&p2);
		else if( strcmp(op, "end")==0 )
			break;
		else 
		{
			printf("unknown operator: %s\n", op);
			break;
		}
		printPolynomial(&presult);
		releasePolynomial(&p1);
		releasePolynomial(&p2);
		releasePolynomial(&presult);
	}

	return 0; 
}

