/**
* Program Name: cis27Spring2014JustinUnverrichtPolyQuiz 12.c
* Date:  3/18/2014
* Written By:  Justin Unverricht
*/

//finish out the rest of these functions
#include <stdio.h>
#include <stdlib.h>

struct FractionJustinU {
	int num;
	int denom;
};

typedef struct FractionJustinU Fraction;

// Polynomial Code below

struct PolyTJustinU { 
	int ex;
	struct FractionJustinU co;
	struct PolyTJustinU* next;
};

typedef struct PolyTJustinU PolyT;
typedef PolyT* PolyTermP;

struct PolyNodeJustinU {
	PolyT* polyDataP;
	struct PolyNodeJustinU* next;
};

typedef struct PolyNodeJustinU PTNode;
typedef PTNode* PTNodePtr;

// Term functions
PTNodePtr createPolyNodeJustinU();
void insertPolyNodeJustinU(PTNodePtr, PTNodePtr*);
PTNodePtr removeFirstJustinU(PTNodePtr*);
int getListLengthJustinU(PTNodePtr*);
void displayPolyNodeJustinU(PTNodePtr);
int getPolyOrder(PTNodePtr);


//Fraction stuff
Fraction* initFractionJustinU();
void simplifyFractionJustinU(Fraction);
void printFractionJustinU(Fraction);
int gcd(int, int);


main() {
	PTNodePtr termList = NULL;
	int i;
	printf("Inserting your first term\n\n");
	insertPolyNodeJustinU(createPolyNodeJustinU(), &termList);
	printf("\n\nSecond term \n");
	insertPolyNodeJustinU(createPolyNodeJustinU(), &termList);
	printf("\n\nThird term \n");
	insertPolyNodeJustinU(createPolyNodeJustinU(), &termList);
	printf("\n\n");
	printf("\n\nPrinting out your terms now : \n");
	displayPolyNodeJustinU(termList);

	for (i = 0; i < getListLengthJustinU(&termList); i++) {
		removeFirstJustinU(&termList);
	}
	free(termList);

	printf("\nHave Fun!!!\n");

	return 0;
}

// Fraction functions

int gcd(int arg1, int arg2) { // recursive gcd function
	if (arg1 % arg2 == 0) {
		return arg2; 
	}
	else {
		return gcd(arg2, arg1 % arg2);
	}
} 

void simplifyFractionJustinU(Fraction frac) { 
	int lcd = gcd(frac.num, frac.denom);

	frac.num = (frac.num / lcd);
	frac.denom = (frac.denom) / lcd;

	if (frac.denom < 0) {
		frac.num = -frac.num;
		frac.denom = -frac.denom;
	}
	return;
}

void printFractionJustinU(Fraction userFrac) {
	printf("%d",userFrac.num);
	printf("/");
	printf("%d", userFrac.denom);
	return;
}

// Term functions
PTNodePtr createPolyNodeJustinU() {
	PTNodePtr newNode;
	PolyTermP tmpPtr = NULL;
	Fraction frac;
	int num;
	int denom;
	int exponent;

	printf("Please choose your numerator : ");
	scanf("%d", &num);

	printf("\nPlease choose your denominator : ");
	scanf("%d", &denom);

	while (denom == 0) {
		printf("A black hole forms and eats your compiler, use something other than 0 \n");
		printf("\nPlease choose your denominator : ");
		scanf("%d", &denom);
	}

	if (denom < 0) {
		denom = -denom;
		num = -num; 
	}

	frac.num = num;
	frac.denom = denom;

	simplifyFractionJustinU(frac);

	printf("\nPlease choose your exponent : ");
	scanf("%d", &exponent);

	tmpPtr = (struct PolyTJustinU*) malloc(sizeof(struct PolyTJustinU));

	tmpPtr->co = frac;
	tmpPtr->ex = exponent;
	tmpPtr->next = NULL;

	newNode = (struct PolyNodeJustinU*) malloc(sizeof(struct PolyNodeJustinU));

	newNode->polyDataP = tmpPtr;
	newNode->next = NULL;

	return newNode;
}

void displayPolyNodeJustinU(PTNodePtr userNode) {
	PTNodePtr nodePtr;

	if (userNode) {
		nodePtr = userNode;

		printf("\nThe list will start at : "); 
		printFractionJustinU(nodePtr->polyDataP->co);
		printf("\n\n");
		while (nodePtr) {

			printf("coefficient : ");
			printFractionJustinU(nodePtr->polyDataP->co);

			printf("\n\n");

			printf("exponent : %d\n", nodePtr->polyDataP->ex);

			printf("\n");

			printf("pointer : %p\n", nodePtr->next);
			printf("\n");
			nodePtr = nodePtr->next;
		}
	}
	else
		printf("\nEMPTY LIST ...!\n");

	return;

}

void insertPolyNodeJustinU(PTNodePtr newTerm, PTNodePtr* userList) {
	PTNodePtr* nodePtr;

	if (newTerm->polyDataP->ex > getPolyOrder((*userList))) { // placing at front

	if (userList) {
		newTerm->next = (*userList);
	} 

	(*userList) = newTerm;
	}
	
	else { // placing at back
			nodePtr = userList;

	if (!nodePtr)   
		(*nodePtr) = newTerm;
	else {
		while ((*nodePtr)->next) {
			(*nodePtr) = (*nodePtr)->next;
		}

		(*nodePtr)->next = newTerm;
	}

	}

	return;
	}

int getPolyOrder(PTNodePtr userList) {
	PTNodePtr nodePtr;
	int highest;
	int flag = 0;

	if (userList) {
		nodePtr = userList;
		while (nodePtr) {

			if (flag == 0) {
				highest = nodePtr->polyDataP->ex;

				flag = 1;
			}
			
			if (nodePtr->polyDataP->ex > highest) {
				highest = nodePtr->polyDataP->ex;

			}

			nodePtr = nodePtr->next;
		}
		
	}

	else {
		highest = 0;
	}
	
	return highest;
}

int getListLengthJustinU(PTNodePtr* userList) {
	PTNodePtr tmpPtr;
	int count = 0;
	if ((*userList) == NULL)
		count = 0;
	else {
		tmpPtr = (*userList);
		do {
			count++;
			if (tmpPtr->next)
				tmpPtr = tmpPtr->next;
		} while (tmpPtr->next != NULL);
	}
	return count;
}

PTNodePtr removeFirstJustinU(PTNodePtr* userListAddr) {
	PTNodePtr tmpPtr = NULL;

	if (*userListAddr) {
		tmpPtr = *userListAddr;
		*userListAddr = tmpPtr->next;
		free(tmpPtr);
	} 

	return tmpPtr;
}


/** Output
Inserting your first term

Please choose your numerator : 3

Please choose your denominator : 4

Please choose your exponent : 1


Second term
Please choose your numerator : 5

Please choose your denominator : 12

Please choose your exponent : 0


Third term
Please choose your numerator : 1

Please choose your denominator : 1

Please choose your exponent : 2



Printing out your terms now :

The list will start at : 1/1

coefficient : 1/1

exponent : 2

pointer : 008E3C80

coefficient : 3/4

exponent : 1

pointer : 008E3CF8

coefficient : 5/12

exponent : 0

pointer : 00000000

Have Fun!!!

**/

