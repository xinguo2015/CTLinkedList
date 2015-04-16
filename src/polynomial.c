/**
 * @file polynomial.c
 * @Synopsis Imaplementation of a linked list node
 * @author Xinguo Liu
 * @version Version 1.0
 * @date 2015-04-14
 */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "polynomial.h"


/**
 * @Synopsis alloc a node for the polynomial.
 *
 * @Returns a pointer to the node 
 */
PolyNode * newNode()
{
	PolyNode * p = (PolyNode*)malloc(sizeof(PolyNode));
	if( ! p ) 
	{
		fprintf(stderr,"Failed to alloc memory for PolyNode\n");
		return NULL;
	}
	/* do some initialization */
	p->coef = 0;
	p->expo = 0;
	p->next = NULL;
	return p;
}


/**
 * @Synopsis free the memory of a node
 *
 * @Param    p - the address of the pointer to the node
 */
void freeNode(PolyNode **p)
{
	if( !p || !*p ) 
		return;
	free(*p);
	*p = NULL; /* clear the reference to the release memory */
}

/**
 * @Synopsis initialize a polynomial.
 *
 * @Param    poly is the input polynomial for initialization
 */
void initPolynomial(Polynomial *poly)
{
	poly->head = NULL;
}

/**
 * @Synopsis Release all nodes of a polynomial
 *
 * @Param    poly is the input polynomial
 */
void releasePolynomial(Polynomial *poly)
{
	PolyNode * p = poly->head;
	while( p )
	{
		PolyNode * n = p;
		p = p->next; /* move to the next node */
		free(n); /* free the memory of 'n' */
	}
	/* update the polynomial's list */
	poly->head = NULL;
}

/**
 * @Synopsis insert a node to the head of a list
 *
 * @Param    n    - the node to insert
 * @Param    poly - the polynomial list
 */
void insertBeforeHead(PolyNode *n, Polynomial *poly)
{
	if( poly->head==NULL ) /* an empty polynomial */
	{
		poly->head = n;
		n->next = NULL;
	}
	else
	{
		n->next = poly->head; 
		poly->head = n;  /* update the head pointer */
	}
}

/**
 * @Synopsis get a pointer to the tail node
 *
 * @Param    poly - the input  polynomial
 *
 * @Returns  a pointer to the tail node
 */
PolyNode * getTail(Polynomial *poly)
{
	PolyNode * p;
	for( p=poly->head; p; p=p->next )
		if( p->next==NULL )
			break;
	return p;
}

/**
 * @Synopsis Print a polynomial
 *
 * @Param    poly - the input polynomial for printing
 */
void printPolynomial(Polynomial *poly)
{
	PolyNode *p;
	for( p=poly->head; p; p=p->next ) 
		printf("%d %d", p->coef, p->expo);
	/* print the ending flags */
	printf("0 -1\n");
}

void readPolyNode(PolyNode *n) 
{
	scanf("%d%d", &n->coef, &n->expo);
	printf("coef=%d coef=%d ", n->coef, n->expo);
}

int isZeroNode(PolyNode *n)
{
	return (n->coef==0);
}

Polynomial readPolynomial() 
{
	Polynomial poly;
	initPolynomial(&poly);
	while ( 1 ) {
		PolyNode n, *p;
		readPolyNode(&n);
		if( isZeroNode(&n) ) /* zero node indicates the "end" */
			break;
		p = newNode();
		*p = n;
		insertNodeByExpo(p, &poly);
	}
	return poly;
}

/**
 * @Synopsis append a node after the tail node
 *
 * @Param    n    - the node to append
 * @Param    poly - the polynomial list
 */
void appendAfterTail(PolyNode *n, Polynomial *poly)
{
	PolyNode *t = getTail(poly);
	if( t==NULL ) /* an empty polynomial */
		poly->head = n; 
	else
		t->next = n; /* append to the tail */
	n->next = NULL;
}

/**
 * @Synopsis insert a node into the polynomial.
 *           This insertion maintains the nodes in order of
 *           increasing exponential index.
 *
 * @Param    n    - the node to insert
 * @Param    poly - the polynomial pointer
 */
void insertNodeByExpo(PolyNode *n, Polynomial *poly)
{
	PolyNode *pp = NULL, *p = poly->head;
	/*! skip node smaller than node 'n', yielding a poiter 'p'
	 *  of the first node that is greater than node 'n' */
	while( p && p->expo < n->expo )
	{	
		pp = p;      /* track the previous node for insertion */
		p = p->next; /* proceed to the next node */
	}
	if ( pp==NULL ) /* implies no node is smaller than node 'n' */
		insertBeforeHead(n, poly);
	else
	{
		/*! insert after node 'pp' and before 'p', such that
		 *             pp ---> n ---> p       */
		n->next = p;
		pp->next = n;
	}
}

/**
 * @Synopsis duplicate a polynomial.
 *           all nodes are duplicated and linked
 *
 * @Param    poly - the input polynomial
 *
 * @Returns  the duplicated copy
 */
Polynomial duplicate(Polynomial *poly)
{
	Polynomial dup; /* the copy */
	PolyNode *p, *n;

	/*! initialize a empty polynomial */
	dup.head = NULL;
	/*! start duplicating the polynomial node by node */
	for( p= poly->head; p!=NULL; p=p->next )
	{
		n = newNode();      /* new node */
		if( ! n ) exit(-1); /* no node is available */
		*n = *p;            /* copy the content */
		appendAfterTail(n, &dup);
	}
	return dup;
}

void negativePolynomial(Polynomial *poly)
{
	PolyNode * p = poly->head;
	for( ; p!=NULL; p=p->next )
		p->coef = - p->coef;
}

PolyNode * findNodeByExpo(Polynomial *poly, int expo)
{
	PolyNode *p = poly->head;
	while ( p && p->expo!=expo )
		p = p->next;
	return p;
}

void removeZeroNode(Polynomial *poly)
{
	PolyNode *p = poly->head, *pp = NULL;
	while( p!=NULL ) {
		if( p->coef!=0 ) {
			pp = p;
			p = p->next;
			continue;
		}
		if( pp )
			pp->next = p->next;
		else
			poly->head = p->next;
		freeNode(&p);
		p = pp->next;
	}
}

/**
 * @Synopsis a += b
 *
 * @Param    a the input and output polynomial
 * @Param    b the other input polynomial
 */
void catPolynomial(Polynomial *polyA, Polynomial *polyB) 
{
	PolyNode *p, *n; 
	for( p=polyB->head; p!=NULL; p=p->next ) {
		n = findNodeByExpo(polyA,p->expo);
		if( n ) /* found a term with the same exponential */
			n->coef += p->coef;
		else {
			n = newNode();        /* alloc a new node */
			*n = *p;              /* copy the node content */
			insertNodeByExpo(n, polyA); /* insert into the sum in order */
		}
	}
	removeZeroNode(polyA);
}

/**
 * @Synopsis Polynomial addition: a+b
 *
 * @Param    a polynomial to add
 * @Param    b polynomial to add
 *
 * @Returns  the sum of the polynomials
 */

Polynomial addPolynomial(Polynomial *polyA, Polynomial *polyB) 
{
	Polynomial sum = duplicate(polyA);
	catPolynomial(&sum, polyB);
	return sum;
}

		
Polynomial subPolynomial(Polynomial *polyA, Polynomial *polyB) 
{
	Polynomial dif = duplicate(polyB);
	negativePolynomial( &dif );
	catPolynomial(&dif, polyA);
	return dif;
}

Polynomial mulPolynomial(Polynomial *polyA, Polynomial *polyB) 
{
	Polynomial prod;
	PolyNode *a, *b, *n;

	initPolynomial(&prod); /* make zero */
	/* for each pair of combination */
	for( a=polyA->head; a; a=a->next ) {
		for( b=polyB->head; b; b=b->next ) {
			int e = a->expo + b->expo;
			n = findNodeByExpo(&prod, e);
			if( n )
				n->coef += a->coef*b->coef;
			else {
				n = newNode();
				n->expo = e;
				n->coef = a->expo + b->expo;
				insertNodeByExpo(n, &prod);
			}
		}
	}
	removeZeroNode(&prod);
	return prod;
}

