/**
 * @file polynomial.h
 * @Synopsis Header file for polynomial 
 * @author Xinguo Liu
 * @version Version 1.0
 * @date 2015-04-14
 */


/*! data type for the coefficients */
typedef int PCType;   

/*! utilities for input/output polynomial coefficients 
 *  from standard I/O */
PCType getPC();         /* read from standard input */
void   putPC(PCType c); /* write into standard output */

/**
 * @Synopsis The node for polynomial
 */
struct Poly_Node 
{
	PCType             coef; /*! the coefficient of a term */
	int                expo; /*! the exponential index */
	struct Poly_Node * next; /*! the pointer to the next term */
};
typedef struct Poly_Node PolyNode;

/**
 * @Synopsis A container for a polynomial
 */
typedef struct 
{
	PolyNode * head; /*! a pointer to the header */
} Polynomial;

void initPolynomial(Polynomial *poly);
void releasePolynomial(Polynomial *poly);
void freeNode(PolyNode **p);
void insertBeforeHead(PolyNode *n, Polynomial *poly);
void insertNodeByExpo(PolyNode *n, Polynomial *poly);
void appendAfterTail(PolyNode *n, Polynomial *poly);
void printPolynomial(Polynomial *p);
void readPolyNode(PolyNode *n);
Polynomial readPolynomial();
PolyNode * newNode();
Polynomial duplicate(Polynomial *poly);
PolyNode * findNodeByExpo(Polynomial *poly, int expo);
Polynomial addPolynomial(Polynomial *polyA, Polynomial *polyB);
Polynomial subPolynomial(Polynomial *polyA, Polynomial *polyB);
Polynomial mulPolynomial(Polynomial *polyA, Polynomial *polyB);

