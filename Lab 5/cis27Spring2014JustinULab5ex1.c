/**
* Program Name: Polynomial Quiz 1.1.c
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



//PolyT* createTerm(); rolled this function into createPolyNodeJustinU()
//PolyT createTerm01(struct Fraction coe, int ex);
//PTNodePtr createPolyNodeJustinUKnown(PTNode);
PTNodePtr createPolyNodeJustinU();
PTNodePtr getPolyTerm(PTNodePtr);
void addPolyNodeJustinU(PTNodePtr, PTNodePtr);
void insertPolyNodeJustinU(PTNodePtr, PTNodePtr*);
void removePolyNodeJustinU(PTNode*, int ex);
void getPolyOrderJustinU(PTNodePtr);
void displayPolyNodeJustinU(PTNodePtr);
void searchPolyNodeJustinU(PTNodePtr, PTNodePtr*);
//void sortPolyNodeJustinU(PTNodePtr*);
PTNodePtr removeFirstJustinU(PTNodePtr*);
int getListLengthJustinU(PTNodePtr*);
void printListContents(PTNodePtr);


//Fraction stuff
Fraction* initFractionJustinU();
void simplifyFractionJustinU(Fraction);
void printFractionJustinU(Fraction);
int gcd(int, int);


// menu functions
void menu();
/**
struct PolyNodeYourName { 
PolyTermAdrYourName* dataPtr; 
struct PolyNodeYourName* next;
};

typedef struct PolyNodeYourName* PolyNodeAdrYourName;

typedef struct PolyNodeYourName* PolyListYourName;

typedef PolyListYourName* PolyListAdrYourName;
**/

main() {
	//PTNodePtr termList = NULL;
	menu();
	/**
	insertPolyNodeJustinU(createPolyNodeJustinU(), &termList);
	printf("\n");
	displayPolyNodeJustinU(termList);
	printf("\n");
	insertPolyNodeJustinU(createPolyNodeJustinU(), &termList);
	printf("\n");
	displayPolyNodeJustinU(termList);
	printf("\nHave Fun!!!\n");
	**/

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

// Polynomial functions

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

	printf("Please choose your exponent : ");
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
	PTNodePtr tmpPtr, prevNode;
	int count; 

	if ((*userList)) {
		count = 0;
		tmpPtr = (*userList);
		prevNode = (*userList);

		while (tmpPtr && newTerm->polyDataP->ex <= tmpPtr->polyDataP->ex) {
			count++;
			prevNode = tmpPtr;
			tmpPtr = tmpPtr->next;
		}

		if (count == 0 && newTerm->polyDataP->ex <= tmpPtr->polyDataP->ex) {
			(*userList)->next = newTerm;
		}
		else {
			if (!tmpPtr) {
				prevNode->next = newTerm;
			}
			else {
				newTerm->next = tmpPtr;
				prevNode->next = newTerm;
			}
		}

	}
	else {
		newTerm->next = (*userList);
		(*userList) = newTerm;
	}

	return;
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
	return count + 1;
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

void getPolyOrderJustinU(PTNodePtr userList) {
	PTNodePtr nodePtr;
	Fraction highestFrac;
	int highest;
	int flag = 0;

	if (userList) {
		nodePtr = userList;

		printf("\nThe list will start at : "); 
		printFractionJustinU(nodePtr->polyDataP->co);
		printf("\n\n");
		while (nodePtr) {

			printf("coefficient : ");
			printFractionJustinU(nodePtr->polyDataP->co);

			printf("\n\n");

			printf("exponent : %d\n", nodePtr->polyDataP->ex);

			printf("\n");

			if (flag == 0) {
				highest = nodePtr->polyDataP->ex;
				highestFrac = ((*nodePtr).polyDataP->co);
				flag = 1;
			}

			if (nodePtr->polyDataP->ex > highest) {
				highest = nodePtr->polyDataP->ex;
				highestFrac = ((*nodePtr).polyDataP->co);
			}

			nodePtr = nodePtr->next;
		}

		printf("\nThe highest order term is : ");
		printFractionJustinU(highestFrac);
		printf("\n");
	}
	else
		printf("\nEMPTY LIST ...!\n");
}

void searchPolyNodeJustinU(PTNodePtr searchNode, PTNodePtr* userList) {

	if (userList) {
		printf("\nSearching list for your node : "); 

		while ((*userList)) {

			(*userList) = (*userList)->next;
		}
	}
	else
		printf("\nEMPTY LIST ...!\n");


}

void printListContents(PTNodePtr userNode) {
	PTNodePtr nodePtr;
	int position = 0;
	nodePtr = userNode;

	while (nodePtr) {
		printf("%d : ", position+1);
		printFractionJustinU((*nodePtr).polyDataP->co);
		printf("^%d ", (*nodePtr).polyDataP->ex); 
		printf("  ");
		nodePtr = nodePtr->next;
		position++;
	}
	return;
}

void addPolyNodeJustinU(PTNodePtr node1, PTNodePtr node2) {
	PTNodePtr newNode;
	PolyTermP tmpPtr = NULL;


	tmpPtr = (struct PolyTJustinU*) malloc(sizeof(struct PolyTJustinU));

	if (node1->polyDataP->ex == node2->polyDataP->ex) {
		tmpPtr->co.num = (node1->polyDataP->co.num * node2->polyDataP->co.denom)
			+ (node2->polyDataP->co.num * node1->polyDataP->co.denom);

		tmpPtr->co.denom = node1->polyDataP->co.denom * node2->polyDataP->co.denom;
		simplifyFractionJustinU(tmpPtr->co);

		newNode = (struct PolyNodeJustinU*) malloc(sizeof(struct PolyNodeJustinU));

		newNode->polyDataP = tmpPtr;
		newNode->next = NULL;

		displayPolyNodeJustinU(newNode);
		free((*newNode).polyDataP);
		free(newNode);

	}
	else {
		printf("( ");
		printFractionJustinU(node1->polyDataP->co);
		printf("^%d ", node1->polyDataP->ex);
		printf("+ ");
		printFractionJustinU(node2->polyDataP->co);
		printf("^%d ", node2->polyDataP->ex);
		printf(" ) \n");
	}

	return;
}

PTNodePtr getPolyTerm(PTNodePtr userList) {
	int i;
	int position;
	PTNodePtr nodePtr;

	printListContents(userList);
	printf("\n\nPlease select a term : ");
	scanf("%d", &position);

	while (position < 0 || (position - 1) > getListLengthJustinU(&userList)) {
		printf("The value you selected is out of bounds, please choose again : ");
		scanf("%d", &position);
	}

	printf("\n\n");
	nodePtr = userList;
	for (i = 0; i < (position-1); i++) {
		nodePtr = nodePtr->next;
	}

	return nodePtr;
}

//menu functions

void menu() {
	PTNodePtr userList = NULL;
	int menuSelect;
	int i;

	do {
		printf("\n*******************************"\
			"\n*           MENU              *"\
			"\n* 1. Display current list     *"\
			"\n* 2. Inserting                *"\
			"\n* 3. Get Order                *"\
			"\n* 4. Add                      *"\
			"\n* 5. Quit                     *"\
			"\n*******************************");
		printf("\n Enter Option : ");
		scanf_s("%d", &menuSelect);
		printf("\n");

		switch (menuSelect) {
		case 1:
			if (!userList)
				printf("EMPTY LIST...\n\n\n");
			else
				displayPolyNodeJustinU(userList);

			break;

		case 2:
			printf("Lets put a term in here shall we?\n");
			insertPolyNodeJustinU(createPolyNodeJustinU(), &userList);
			//sortPolyNodeJustinU(&userList);
			printf("\n");
			break;

		case 3:
			if (!userList) {
				printf("EMPTY LIST...\n");
			}
			else {
				getPolyOrderJustinU(userList);
			}
			break;

		case 4:
			if (!userList) {
				printf("EMPTY LIST...\n");
			}
			else if (getListLengthJustinU(&userList) > 1) { 
				printf("\nSelect terms to add ");
				addPolyNodeJustinU(getPolyTerm(userList), getPolyTerm(userList));
			}
			else {
				printf("Please create at least 1 more term to perform addition\n");
			}
			break;

		case 5:
			printf("Thank you Apu!\n");
			break;

		default:
			printf("You should not be in this class!\n");
			break;
		}

	} while (menuSelect != 5);
	for (i = 0; i < getListLengthJustinU(&userList); i++) {
		removeFirstJustinU(&userList);
	}
	free(userList);
}