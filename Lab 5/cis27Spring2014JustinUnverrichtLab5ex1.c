/**
* Program Name: cis27Spring2014JustinUnverrichtLab5Ex1
* Date:  4/7/2014
* Written By:  Justin Unverricht
*/

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
};

typedef struct PolyTJustinU PolyT;
typedef PolyT* PolyTermP;

struct PolyNodeJustinU {
	struct PolyTJustinU polyDataP;
	struct PolyNodeJustinU* next;
};

typedef struct PolyNodeJustinU PTNode;
typedef PTNode* PTNodePtr;

PTNodePtr createPolyNodeJustinU();
PTNodePtr createPolyTermJustinU(PTNodePtr);
PTNodePtr getPolyTerm(PTNodePtr);
PTNodePtr removeFirstJustinU(PTNodePtr*);
int getListLengthJustinU(PTNodePtr*);
PTNodePtr* addPolynomialJustinU(PTNodePtr, PTNodePtr);
PTNodePtr* multiplyPolynomialJustinU(PTNodePtr, PTNodePtr);
void addPolyNodeJustinU(PTNodePtr, PTNodePtr);
void insertPolyNodeJustinU(PTNodePtr, PTNodePtr*);
void removePolyNodeJustinU(PTNode*, int ex);
void getPolyOrderJustinU(PTNodePtr);
void displayPolyNodeJustinU(PTNodePtr);
void searchPolyNodeJustinU(PTNodePtr, PTNodePtr*);
void updatePolyNodeJustinU(PTNodePtr, PTNodePtr);
void deleteListJustinU(PTNodePtr);
void printListContents(PTNodePtr);
void removeZeros(PTNodePtr*);

//Fraction stuff
Fraction* initFractionJustinU();
void simplifyFractionJustinU(Fraction*);
void printFractionJustinU(Fraction);
int gcd(int, int);

// menu functions
void menu();
void creatingMenu(PTNodePtr*, PTNodePtr*);
void deletingMenu(PTNodePtr*, PTNodePtr*, PTNodePtr*);
void classInfo();

main() {
	classInfo();
	printf("\n");
	menu();

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

void simplifyFractionJustinU(Fraction* frac) { 
	int lcd = gcd(frac->num, frac->denom);

	frac->num = (frac->num / lcd);
	frac->denom = (frac->denom) / lcd;

	if (frac->denom < 0) {
		frac->num = -frac->num;
		frac->denom = -frac->denom;
	}
	return;
}

Fraction addFractionJustinU(Fraction frac1, Fraction frac2) {
	Fraction frac;

	frac.num = (frac1.num * frac2.denom) + (frac2.num * frac1.denom);
	frac.denom = frac1.denom * frac2.denom;
	simplifyFractionJustinU(&frac);
	return frac;
}

void printFractionJustinU(Fraction userFrac) {
	printf("%d",userFrac.num);
	printf("/");
	printf("%d", userFrac.denom);
	return;
}

// Polynomial functions

PTNodePtr createPolyNodeJustinU() { // this is a large function but it cuts down on overhead for
	// creating multiple nodes in a row
	PTNodePtr newNode;
	PolyT tmpPtr;
	Fraction frac;
	int num, denom, exponent;
	//char sign;

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

	simplifyFractionJustinU(&frac);

	printf("\nPlease choose your exponent : ");
	scanf("%d", &exponent);

	tmpPtr.co = frac;
	tmpPtr.ex = exponent;

	newNode = (struct PolyNodeJustinU*) malloc(sizeof(struct PolyNodeJustinU));

	newNode->polyDataP = tmpPtr;
	newNode->next = NULL;

	return newNode;
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

PTNodePtr removeFirstJustinU(PTNodePtr* userPolyLddr) {
	PTNodePtr tmpPtr = NULL;

	if (*userPolyLddr) {
		tmpPtr = *userPolyLddr;
		*userPolyLddr = tmpPtr->next;
		free(tmpPtr);
	} 

	return tmpPtr;
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

PTNodePtr* addPolynomialJustinU(PTNodePtr left, PTNodePtr right) {
	PTNodePtr tmpPtr, tmpPtr2;
	PTNodePtr* result;

	tmpPtr = left;
	result = (PTNodePtr*)malloc(sizeof(struct PolyTJustinU));
	*result = NULL;

	while (tmpPtr) {
		tmpPtr2 = (struct PolyNodeJustinU*) malloc(sizeof(struct PolyNodeJustinU));
		tmpPtr2->polyDataP.co = tmpPtr->polyDataP.co;
		tmpPtr2->polyDataP.ex = tmpPtr->polyDataP.ex;
		tmpPtr2->next = NULL;

		printf("calling insert()\n");
		insertPolyNodeJustinU(tmpPtr2, result);
		tmpPtr = tmpPtr->next;
	}

	tmpPtr = right;
	tmpPtr2 = NULL;

	while (tmpPtr) {
		tmpPtr2 = (struct PolyNodeJustinU*) malloc(sizeof(struct PolyNodeJustinU));
		tmpPtr2->polyDataP.co = tmpPtr->polyDataP.co;
		tmpPtr2->polyDataP.ex = tmpPtr->polyDataP.ex;
		tmpPtr2->next = NULL;

		printf("calling insert()\n");
		insertPolyNodeJustinU(tmpPtr2, result);
		tmpPtr = tmpPtr->next;
	}


	return result;
}

PTNodePtr* multiplyPolynomialJustinU(PTNodePtr left, PTNodePtr right) {
	PTNodePtr leftNode, rightNode, tmpPtr;
	PTNodePtr* result;

	result = (PTNodePtr*)malloc(sizeof(struct PolyTJustinU));
	*result = NULL;
	leftNode = left;

	while (leftNode) {
		rightNode = right;
		while (rightNode) {
			tmpPtr = (struct PolyNodeJustinU*) malloc(sizeof(struct PolyNodeJustinU));
			tmpPtr->polyDataP.co.num = leftNode->polyDataP.co.num * rightNode->polyDataP.co.num;
			tmpPtr->polyDataP.co.denom = leftNode->polyDataP.co.denom * rightNode->polyDataP.co.denom;
			tmpPtr->polyDataP.ex = leftNode->polyDataP.ex + rightNode->polyDataP.ex;
			tmpPtr->next = NULL;

			printf("calling insert()\n");
			insertPolyNodeJustinU(tmpPtr, result);
			rightNode = rightNode->next;
		}
		leftNode = leftNode->next;
	}

	return result;
}

void updatePolyNodeJustinU(PTNodePtr newTerm, PTNodePtr oldTerm) {
	printf("calling update()\n");
	(*oldTerm).polyDataP.co.num = ((*oldTerm).polyDataP.co.num * (*newTerm).polyDataP.co.denom)
		+ ((*newTerm).polyDataP.co.num * (*oldTerm).polyDataP.co.denom);

	(*oldTerm).polyDataP.co.denom = (*oldTerm).polyDataP.co.denom * (*newTerm).polyDataP.co.denom;
	simplifyFractionJustinU(&(*oldTerm).polyDataP.co);
}

void displayPolyNodeJustinU(PTNodePtr userNode) { //might do this with a temp so I can fiddle with the values
	PTNodePtr nodePtr;
	int subtraction;
	subtraction = 0;

	if (userNode) {
		nodePtr = userNode;
		simplifyFractionJustinU(&(*nodePtr).polyDataP.co);
		while (nodePtr) {
			if (subtraction == 0) {
				printFractionJustinU((*nodePtr).polyDataP.co);
			}
			else {
				printf("%d",-(*nodePtr).polyDataP.co.num);
				printf("/");
				printf("%d", (*nodePtr).polyDataP.co.denom);
				subtraction = 0;
			}
			if ((*nodePtr).polyDataP.ex > 0)
				printf("x^%d", (*nodePtr).polyDataP.ex);
			if (nodePtr->next){
				if (nodePtr->next->polyDataP.co.num < 0) {
					printf(" - ");
					subtraction = 1;
				}
				else
					printf(" + ");
			}
			nodePtr = nodePtr->next;
		}
		printf("\n");
	}

	else
		printf("\nEMPTY LIST ...!\n");

	return;

}

void insertPolyNodeJustinU(PTNodePtr newTerm, PTNodePtr* userList) {
	PTNodePtr tmpPtr, prevNode;
	int count, updated;
	updated = 0;

	if ((*userList)) {
		count = 0;
		tmpPtr = (*userList);
		prevNode = (*userList);

		while (tmpPtr && (*newTerm).polyDataP.ex <= (*tmpPtr).polyDataP.ex) {  
			count+= 1;
			prevNode = tmpPtr;
			tmpPtr = tmpPtr->next;
		}

		if ((*newTerm).polyDataP.ex == (*prevNode).polyDataP.ex) {
			updatePolyNodeJustinU(newTerm, prevNode);
			prevNode->next = tmpPtr;
			free(newTerm);
			updated = 1;
		}

		if (count == 1 && (*newTerm).polyDataP.ex < (*prevNode).polyDataP.ex) { 
			if (updated == 0)
				(*userList)->next = newTerm;
		}



		if (count == 0){
			newTerm->next = (*userList);
			(*userList) = newTerm;
		}
		else {
			if (!tmpPtr && updated == 0) {
				prevNode->next = newTerm;
			}
			if (tmpPtr && updated == 0) {
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

void getPolyOrderJustinU(PTNodePtr userList) {
	PTNodePtr nodePtr;
	Fraction highestFrac;
	int highest;
	int flag = 0;

	if (userList) {
		nodePtr = userList;

		printf("\nThe list will start at : "); 
		printFractionJustinU((*nodePtr).polyDataP.co);
		printf("\n\n");
		while (nodePtr) {

			printf("coefficient : ");
			printFractionJustinU((*nodePtr).polyDataP.co);

			printf("\n\n");

			printf("exponent : %d\n", (*nodePtr).polyDataP.ex);

			printf("\n");

			if (flag == 0) {
				highest = (*nodePtr).polyDataP.ex;
				highestFrac = ((*nodePtr).polyDataP.co);
				flag = 1;
			}

			if ((*nodePtr).polyDataP.ex > highest) {
				highest = (*nodePtr).polyDataP.ex;
				highestFrac = ((*nodePtr).polyDataP.co);
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
		printFractionJustinU((*nodePtr).polyDataP.co);
		printf("^%d ", (*nodePtr).polyDataP.ex); 
		printf("  ");
		nodePtr = nodePtr->next;
		position++;
	}
	return;
}

void addPolyNodeJustinU(PTNodePtr node1, PTNodePtr node2) {
	PTNodePtr newNode;
	PolyT tmpPtr;

	if ((*node1).polyDataP.ex == (*node2).polyDataP.ex) {
		tmpPtr.co.num = ((*node1).polyDataP.co.num * (*node2).polyDataP.co.denom)
			+ ((*node2).polyDataP.co.num * (*node1).polyDataP.co.denom);

		tmpPtr.co.denom = (*node1).polyDataP.co.denom * (*node2).polyDataP.co.denom;
		simplifyFractionJustinU(&tmpPtr.co);

		newNode = (struct PolyNodeJustinU*) malloc(sizeof(struct PolyNodeJustinU));

		newNode->polyDataP = tmpPtr;
		newNode->next = NULL;

		displayPolyNodeJustinU(newNode);
		free(newNode);

	}
	else {
		printf("( ");
		printFractionJustinU((*node1).polyDataP.co);
		printf("^%d ", (*node1).polyDataP.ex);
		printf("+ ");
		printFractionJustinU((*node2).polyDataP.co);
		printf("^%d ", (*node2).polyDataP.ex);
		printf(" ) \n");
	}

	return;
}

void deleteListJustinU(PTNodePtr userList) {
	int listLen, i;

	listLen = getListLengthJustinU(&userList);

	for (i = 0; i < listLen; i++) {
		removeFirstJustinU(&userList);
	}

	free(userList);

	return;
}

void removeZeros(PTNodePtr* userList) {
	PTNodePtr tmpPtr, prevNode;
	int listLen, count;

	count = 0;
	listLen = getListLengthJustinU(userList);
	tmpPtr = *userList;
	prevNode = *userList;

	while (tmpPtr) {
		if ((*tmpPtr).polyDataP.co.num == 0 && count == 0) {
			removeFirstJustinU(userList);
			tmpPtr = *userList;
		}

		if ((*tmpPtr).polyDataP.co.num == 0 && count == listLen) {
			prevNode->next = tmpPtr->next;
			free(tmpPtr);
		}

		if ((*tmpPtr).polyDataP.co.num == 0 && count < listLen) {
			prevNode->next = tmpPtr->next;
			free(tmpPtr);
		}

		prevNode = tmpPtr;
		tmpPtr = tmpPtr->next;
		count++;
	}

	return;
}

//menu functions

void menu() {
	PTNodePtr userPolyL, userPolyR;
	PTNodePtr* resultPoly;
	int menuSelect, created;

	created = 0;
	userPolyL = NULL;
	userPolyR = NULL;
	resultPoly = NULL;
	

	do {
		printf("\n*******************************"\
			"\n*           MENU              *"\
			"\n* 1. Creating Polynomials     *"\
			"\n* 2. Adding Polynomials       *"\
			"\n* 3. Multiplying Polynomials  *"\
			"\n* 4. Displaying Polynomials   *"\
			"\n* 5. Clearing Polynomials     *"\
			"\n* 6. Quit                     *"\
			"\n*******************************");
		printf("\n Enter Option : ");
		scanf_s("%d", &menuSelect);
		printf("\n");

		switch (menuSelect) {
		case 1:
			creatingMenu(&userPolyL, &userPolyR);
			break;

		case 2:		
			if (!userPolyL || !userPolyR) {
				printf("Please create both left and right terms for this operation Tom!\n");
			}

			else {
				if (resultPoly) {
					deleteListJustinU((*resultPoly));
				}
				printf("Adding like polynomials and presorting into new list\n");
				resultPoly = addPolynomialJustinU(userPolyL, userPolyR);
				printf("removing any zero terms from list\n");
				removeZeros(resultPoly);
				created = 1;
			}
			break;

		case 3:
			if (!userPolyL || !userPolyR) {
				printf("Please create both left and right terms for this operation Tom!\n");
			}

			else {
				if (resultPoly) {
					deleteListJustinU((*resultPoly));
				}
			}
			printf("Multiplying Polynomials and presorting into a new list\n");
			resultPoly = multiplyPolynomialJustinU(userPolyL, userPolyR);
			printf("removing any zero terms from list\n");
			removeZeros(resultPoly);
			created = 1;
			break;

		case 4:
			if (!userPolyL || !userPolyR)
				created = 0;

			if (!userPolyL) {
				printf("Left Poly Pointer : 0\n");
			}
			else{
				printf("Left Poly Pointer : %p", userPolyL);
				printf("\n");
				displayPolyNodeJustinU(userPolyL);
			}

			if (!userPolyR) {
				printf("Right Poly Pointer : 0\n");
			}
			else{
				printf("Right Poly Pointer : %p", userPolyR);
				printf("\n");
				displayPolyNodeJustinU(userPolyR);
			}

			if (created == 0) {
				printf("Resulting Poly Pointer : 0\n");
			}
			else{
				printf("Resulting Poly Pointer : %p", resultPoly);
				printf("\n");
				displayPolyNodeJustinU((*resultPoly));
			}
			break;

		case 5:
			deletingMenu(&userPolyL, &userPolyR, resultPoly);
			break;

		case 6:
			printf("Having Fun!\n\n");
			break;
		
		}
	} while (menuSelect != 6);

	if (userPolyL) 
		deleteListJustinU(userPolyL);

	if (userPolyR) 
		deleteListJustinU(userPolyR);

	if (resultPoly) {
		deleteListJustinU((*resultPoly));
	}
}

void creatingMenu(PTNodePtr* left, PTNodePtr* right) {
	int menuSelect, flag;
	char userChoice;

	do {
		printf("\n*******************************"\
			"\n*  Creating/Updating          *"\
			"\n* 1. Left Operand             *"\
			"\n* 2. Right Operand            *"\
			"\n* 3. Both Operands            *"\
			"\n* 4. Return                   *"\
			"\n*******************************");
		printf("\n Enter Option : ");
		scanf_s("%d", &menuSelect);
		printf("\n");

		switch (menuSelect) {
		case 1:
			if(left){
				deleteListJustinU((*left));
				(*left) = NULL;
			}

			printf("Choose values for your left operand\n\n");

			printf("Lets create your first term\n\n");
			do {
				flag = 0;
				printf("Calling insertPolyNodeJustinU()\n");
				printf("Calling createPolyNodeJustinU()\n\n");
				insertPolyNodeJustinU(createPolyNodeJustinU(), left);
				printf("create another term? (y or n): ");
				scanf(" %c", &userChoice);

				if (userChoice == 'y' || userChoice == 'Y') 
					printf("\n");
				else if (userChoice == 'n' || userChoice == 'N')
					flag = 1;
				else
					printf("please choose only y or n\n");
					printf("create another term? (y or n): ");
					scanf(" %c", &userChoice);
					if (userChoice == 'n' || userChoice == 'N')
					flag = 1;

			} while (flag !=1);
			printf("\n");

			break;

		case 2:
			if(right){
				deleteListJustinU((*right));
				(*right) = NULL;
			}

			printf("\nLets create your second term\n");
			do {
				flag = 0;
				printf("Calling insertPolyNodeJustinU()\n");
				printf("Calling createPolyNodeJustinU()\n");
				insertPolyNodeJustinU(createPolyNodeJustinU(), right);
				printf("create another term? (y or n): ");
				scanf(" %c", &userChoice);

				if (userChoice == 'y' || userChoice == 'Y') 
					continue;
				else if (userChoice == 'n' || userChoice == 'N')
					flag = 1;
				else
					printf("please choose only y or n\n");
					printf("create another term? (y or n): ");
					scanf(" %c", &userChoice);
					if (userChoice == 'n' || userChoice == 'N')
					flag = 1;

			} while (flag !=1);
			break;

		case 3:
			if(left){
				deleteListJustinU((*left));
				(*left) = NULL;
			}

			if(right){
				deleteListJustinU((*right));
				(*right) = NULL;
			}

			printf("Lets create your first term\n\n");
			do {
				flag = 0;
				printf("Calling insertPolyNodeJustinU()\n");
				printf("Calling createPolyNodeJustinU()\n\n");
				insertPolyNodeJustinU(createPolyNodeJustinU(), left);
				printf("create another term? (y or n): ");
				scanf(" %c", &userChoice);

				if (userChoice == 'y' || userChoice == 'Y') 
					printf("\n");
				else if (userChoice == 'n' || userChoice == 'N')
					flag = 1;
				else
					printf("please choose only y or n\n");
					printf("create another term? (y or n): ");
					scanf(" %c", &userChoice);
					if (userChoice == 'n' || userChoice == 'N')
					flag = 1;

			} while (flag !=1);
			printf("\n");

			flag = 2;

			printf("\nLets create your second term\n");
			do {
				flag = 0;
				printf("Calling insertPolyNodeJustinU()\n");
				printf("Calling createPolyNodeJustinU()\n");
				insertPolyNodeJustinU(createPolyNodeJustinU(), right);
				printf("create another term? (y or n): ");
				scanf(" %c", &userChoice);

				if (userChoice == 'y' || userChoice == 'Y') 
					continue;
				else if (userChoice == 'n' || userChoice == 'N')
					flag = 1;
				else
					printf("please choose only y or n\n");
					printf("create another term? (y or n): ");
					scanf(" %c", &userChoice);
					if (userChoice == 'n' || userChoice == 'N')
					flag = 1;

			} while (flag !=1);
			break;

		case 4:
			printf("Returning to Main Menu \n");
			break;

		default:
			printf("You should not be in this class!\n");
			break;
		}

	} while (menuSelect != 4);

	return; 
}

void deletingMenu(PTNodePtr* left, PTNodePtr* right, PTNodePtr* result) {
	int menuSelect;

	do {
		printf("\n*******************************"\
			"\n*  Creating/Updating          *"\
			"\n* 1. Left Operand             *"\
			"\n* 2. Right Operand            *"\
			"\n* 3. Both Operands            *"\
			"\n* 4. Return                   *"\
			"\n*******************************");
		printf("\n Enter Option : ");
		scanf_s("%d", &menuSelect);
		printf("\n");

		switch (menuSelect) {
		case 1:
			if(left){
				deleteListJustinU((*left));
				deleteListJustinU((*result));
				(*left) = NULL;
				(*result) = NULL;
				printf("Deleting\n");
			}
			else {
				printf("Empty List\n");
			}
			break;

		case 2:
			if(right){
				deleteListJustinU((*right));
				deleteListJustinU((*result));
				(*right) = NULL;
				(*result) = NULL;
				printf("Deleting\n");
			}
			else {
				printf("Empty List\n");
			}
			break;

		case 3:
			if(left){
				deleteListJustinU((*left));
				deleteListJustinU((*result));
				(*left) = NULL;
				(*result) = NULL;
				printf("Deleting\n");
			}
			else {
				printf("Empty List\n");
			}

			if(right){
				deleteListJustinU((*right));
				deleteListJustinU((*result));
				(*right) = NULL;
				(*result) = NULL;
				printf("Deleting\n");
			}
			else {
				printf("Empty List\n");
			}
			break;

		case 4:
			printf("Returning to Main Menu \n");
			break;

		default:
			printf("You should not be in this class!\n");
			break;
		}

	} while (menuSelect != 4);

	return; 
}

void classInfo() {
	printf("\nCIS 27 - C Programming"\
		"\nLaney College "\
		"\nJustin Unverricht"\
		"\n"\
		"\nAssignment Informantion --"\
		"\n  Assignment Number:    Lab 05,"\
		"\n                        Coding Assignment -- Exercise #1"\
		"\n  Written by:           Justin Unverricht"\
		"\n  Submitted Date:       4/7/2014");

	return;
}

/** Outpput

CIS 27 - C Programming
Laney College
Justin Unverricht

Assignment Informantion --
  Assignment Number:    Lab 05,
                        Coding Assignment -- Exercise #1
  Written by:           Justin Unverricht
  Submitted Date:       4/7/2014

*******************************
*           MENU              *
* 1. Creating Polynomials     *
* 2. Adding Polynomials       *
* 3. Multiplying Polynomials  *
* 4. Displaying Polynomials   *
* 5. Clearing Polynomials     *
* 6. Quit                     *
*******************************
 Enter Option : 7

 
*******************************
*           MENU              *
* 1. Creating Polynomials     *
* 2. Adding Polynomials       *
* 3. Multiplying Polynomials  *
* 4. Displaying Polynomials   *
* 5. Clearing Polynomials     *
* 6. Quit                     *
*******************************
 Enter Option : 4

Left Poly Pointer : 0
Right Poly Pointer : 0
Resulting Poly Pointer : 0


*******************************
*           MENU              *
* 1. Creating Polynomials     *
* 2. Adding Polynomials       *
* 3. Multiplying Polynomials  *
* 4. Displaying Polynomials   *
* 5. Clearing Polynomials     *
* 6. Quit                     *
*******************************
 Enter Option : 1


*******************************
*  Creating/Updating          *
* 1. Left Operand             *
* 2. Right Operand            *
* 3. Both Operands            *
* 4. Return                   *
*******************************
 Enter Option : 3

Lets create your first term

Calling insertPolyNodeJustinU()
Calling createPolyNodeJustinU()

Please choose your numerator : 1

Please choose your denominator : 1

Please choose your exponent : 2
create another term? (y or n): y

Calling insertPolyNodeJustinU()
Calling createPolyNodeJustinU()

Please choose your numerator : 3

Please choose your denominator : 4

Please choose your exponent : 1
create another term? (y or n): y

Calling insertPolyNodeJustinU()
Calling createPolyNodeJustinU()

Please choose your numerator : 5

Please choose your denominator : 12

Please choose your exponent : 0
create another term? (y or n): n


Lets create your second term
Calling insertPolyNodeJustinU()
Calling createPolyNodeJustinU()
Please choose your numerator : 1

Please choose your denominator : 1

Please choose your exponent : 4
create another term? (y or n): y
Calling insertPolyNodeJustinU()
Calling createPolyNodeJustinU()
Please choose your numerator : -3

Please choose your denominator : 7

Please choose your exponent : 2
create another term? (y or n): y
Calling insertPolyNodeJustinU()
Calling createPolyNodeJustinU()
Please choose your numerator : 4

Please choose your denominator : 9

Please choose your exponent : 1
create another term? (y or n): y
Calling insertPolyNodeJustinU()
Calling createPolyNodeJustinU()
Please choose your numerator : 2

Please choose your denominator : 11

Please choose your exponent : 0
create another term? (y or n): n


*******************************
*  Creating/Updating          *
* 1. Left Operand             *
* 2. Right Operand            *
* 3. Both Operands            *
* 4. Return                   *
*******************************
 Enter Option : 4

Returning to Main Menu


*******************************
*           MENU              *
* 1. Creating Polynomials     *
* 2. Adding Polynomials       *
* 3. Multiplying Polynomials  *
* 4. Displaying Polynomials   *
* 5. Clearing Polynomials     *
* 6. Quit                     *
*******************************
 Enter Option : 4

Left Poly Pointer : 003F4D68
1/1x^2 + 3/4x^1 + 5/12
Right Poly Pointer : 003F4E28
1/1x^4 - 3/7x^2 + 4/9x^1 + 2/11
Resulting Poly Pointer : 0


*******************************
*           MENU              *
* 1. Creating Polynomials     *
* 2. Adding Polynomials       *
* 3. Multiplying Polynomials  *
* 4. Displaying Polynomials   *
* 5. Clearing Polynomials     *
* 6. Quit                     *
*******************************
 Enter Option : 2

Adding like polynomials and presorting into new list
calling insert()
calling insert()
calling insert()
calling insert()
calling insert()
calling insert()
calling insert()
removing any zero terms from list


*******************************
*           MENU              *
* 1. Creating Polynomials     *
* 2. Adding Polynomials       *
* 3. Multiplying Polynomials  *
* 4. Displaying Polynomials   *
* 5. Clearing Polynomials     *
* 6. Quit                     *
*******************************
 Enter Option : 4

Left Poly Pointer : 003D4D68
1/1x^2 + 3/4x^1 + 5/12
Right Poly Pointer : 003D4E28
1/1x^4 - 3/7x^2 + 4/9x^1 + 2/11
Resulting Poly Pointer : 003D4F28
1/1x^4 + 4/7x^2 + 43/36x^1 + 79/132


*******************************
*           MENU              *
* 1. Creating Polynomials     *
* 2. Adding Polynomials       *
* 3. Multiplying Polynomials  *
* 4. Displaying Polynomials   *
* 5. Clearing Polynomials     *
* 6. Quit                     *
*******************************
 Enter Option : 3

Multiplying Polynomials and presorting into a new list
calling insert()
calling insert()
calling insert()
calling insert()
calling insert()
calling insert()
calling insert()
calling insert()
calling insert()
calling insert()
calling insert()
calling insert()
removing any zero terms from list

*******************************
*           MENU              *
* 1. Creating Polynomials     *
* 2. Adding Polynomials       *
* 3. Multiplying Polynomials  *
* 4. Displaying Polynomials   *
* 5. Clearing Polynomials     *
* 6. Quit                     *
*******************************
 Enter Option : 4

Left Poly Pointer : 005D4D68
1/1x^2 + 3/4x^1 + 5/12
Right Poly Pointer : 005D4E28
1/1x^4 - 3/7x^2 + 4/9x^1 + 2/11
Resulting Poly Pointer : 005D4F28
1/1x^6 + 3/4x^5 - 1/84x^4 + 31/252x^3 + 311/924x^2 + 191/594x^1 + 5/66

*******************************
*           MENU              *
* 1. Creating Polynomials     *
* 2. Adding Polynomials       *
* 3. Multiplying Polynomials  *
* 4. Displaying Polynomials   *
* 5. Clearing Polynomials     *
* 6. Quit                     *
*******************************
 Enter Option : 5


*******************************
*  Creating/Updating          *
* 1. Left Operand             *
* 2. Right Operand            *
* 3. Both Operands            *
* 4. Return                   *
*******************************
 Enter Option : 1
 Deleting

*******************************
*  Creating/Updating          *
* 1. Left Operand             *
* 2. Right Operand            *
* 3. Both Operands            *
* 4. Return                   *
*******************************
 Enter Option : 4

Returning to Main Menu


*******************************
*           MENU              *
* 1. Creating Polynomials     *
* 2. Adding Polynomials       *
* 3. Multiplying Polynomials  *
* 4. Displaying Polynomials   *
* 5. Clearing Polynomials     *
* 6. Quit                     *
*******************************
 Enter Option : 4

Left Poly Pointer : 0
Right Poly Pointer : 00864E28
1/1x^4 - 3/7x^2 + 4/9x^1 + 2/11
Resulting Poly Pointer : 0

*******************************
*           MENU              *
* 1. Creating Polynomials     *
* 2. Adding Polynomials       *
* 3. Multiplying Polynomials  *
* 4. Displaying Polynomials   *
* 5. Clearing Polynomials     *
* 6. Quit                     *
*******************************
 Enter Option : 5


*******************************
*  Creating/Updating          *
* 1. Left Operand             *
* 2. Right Operand            *
* 3. Both Operands            *
* 4. Return                   *
*******************************
 Enter Option : 2
 Deleting

*******************************
*  Creating/Updating          *
* 1. Left Operand             *
* 2. Right Operand            *
* 3. Both Operands            *
* 4. Return                   *
*******************************
 Enter Option : 4

Returning to Main Menu


*******************************
*           MENU              *
* 1. Creating Polynomials     *
* 2. Adding Polynomials       *
* 3. Multiplying Polynomials  *
* 4. Displaying Polynomials   *
* 5. Clearing Polynomials     *
* 6. Quit                     *
*******************************
 Enter Option : 4

Left Poly Pointer : 0
Right Poly Pointer : 0
Resulting Poly Pointer : 0

*******************************
*           MENU              *
* 1. Creating Polynomials     *
* 2. Adding Polynomials       *
* 3. Multiplying Polynomials  *
* 4. Displaying Polynomials   *
* 5. Clearing Polynomials     *
* 6. Quit                     *
*******************************
 Enter Option : 6
Having Fun!
**/