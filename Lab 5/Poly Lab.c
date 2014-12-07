/**
* Program Name: Polynomial Quiz 1.1.c
* Date:  3/18/2014
* Written By:  Justin Unverricht
*/

//Creat add and mul functions and add char to terms
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
	char sign;
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
void addPolysJustinU(PTNodePtr, PTNodePtr, PTNodePtr*);
void addPolyNodeJustinU(PTNodePtr, PTNodePtr);
void insertPolyNodeJustinU(PTNodePtr, PTNodePtr*);
void removePolyNodeJustinU(PTNode*, int ex);
void getPolyOrderJustinU(PTNodePtr);
void displayPolyNodeJustinU(PTNodePtr);
void searchPolyNodeJustinU(PTNodePtr, PTNodePtr*);
void updatePolyNodeJustinU(PTNodePtr, PTNodePtr);
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
void creatingMenu(PTNodePtr*, PTNodePtr*);
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

Fraction addFractionJustinU(Fraction frac1, Fraction frac2) {
	Fraction frac;

	frac.num = (frac1.num * frac2.denom) + (frac2.num * frac1.denom);
	frac.denom = frac1.denom * frac2.denom;
	simplifyFractionJustinU(frac);
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
	PolyTermP tmpPtr = NULL;
	Fraction frac;
	int num, denom, exponent, flag;
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

	simplifyFractionJustinU(frac);

	printf("\nPlease choose your exponent : ");
	scanf("%d", &exponent);

	tmpPtr = (struct PolyTJustinU*) malloc(sizeof(struct PolyTJustinU));
	/**
		do {
			printf("\nChoose a sign(+ -), type # to end your polynomial : ");
		scanf(" %c", &sign);
		flag = 2;

		if (sign == '+' && flag == 2) {
			tmpPtr->sign = sign;
			flag = 1;
		}

		else if (sign == '-' && flag == 2) {
			tmpPtr->sign = sign;
			flag = 1;
		}

		else if (sign == '#' && flag == 2) {
			tmpPtr->sign = sign;
			flag = 1;
		}
		else {
			printf("That is not an acceptable value, remember to type # to end your polynomial\n");
		}
	} while (flag != 1);
	**/
	tmpPtr->co = frac;
	tmpPtr->ex = exponent;
	tmpPtr->next = NULL;

	newNode = (struct PolyNodeJustinU*) malloc(sizeof(struct PolyNodeJustinU));

	newNode->polyDataP = tmpPtr;
	newNode->next = NULL;

	return newNode;
}

void addPolysJustinU(PTNodePtr left, PTNodePtr right, PTNodePtr* result) {
	PTNodePtr tmpPtr, tmpPtr2;
	tmpPtr = left;
	tmpPtr2 = tmpPtr->next;

	while (tmpPtr) {
		insertPolyNodeJustinU(tmpPtr, result);
		tmpPtr = tmpPtr2;
	}
	/**
	while (tmpPtr2) {
		insertPolyNodeJustinU(tmpPtr2, &result);
		tmpPtr2 = tmpPtr2->next;
	}
	**/

	return;
}

void updatePolyNodeJustinU(PTNodePtr newTerm, PTNodePtr oldTerm) {
	oldTerm->polyDataP->co.num = (oldTerm->polyDataP->co.num * newTerm->polyDataP->co.denom)
			+ (newTerm->polyDataP->co.num * oldTerm->polyDataP->co.denom);

	oldTerm->polyDataP->co.denom = oldTerm->polyDataP->co.denom * newTerm->polyDataP->co.denom;
	simplifyFractionJustinU(oldTerm->polyDataP->co);
}

void displayPolyNodeJustinU(PTNodePtr userNode) {
	PTNodePtr nodePtr;

	if (userNode) {
		nodePtr = userNode;
		while (nodePtr) {
			printFractionJustinU(nodePtr->polyDataP->co);
			if (nodePtr->polyDataP->ex > 0)
				printf("x^%d", nodePtr->polyDataP->ex);
			printf(" ");
			if (nodePtr->polyDataP->sign != '#') // lets work on this part shall we?
				printf("%c", nodePtr->polyDataP->sign);
			printf(" ");
			nodePtr = nodePtr->next;
		
		}
		printf("\n");

		/**
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
		**/

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
			count+= 1;
			prevNode = tmpPtr;
			tmpPtr = tmpPtr->next;
		}

		if (count == 1 && newTerm->polyDataP->ex <= prevNode->polyDataP->ex) { 
			(*userList)->next = newTerm;
		}

		if (count == 0){
			newTerm->next = (*userList);
			(*userList) = newTerm;
		}
		else {
			if (!tmpPtr) {
				prevNode->next = newTerm;
			}
			if (tmpPtr) {
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

PTNodePtr removeFirstJustinU(PTNodePtr* userPolyLddr) {
	PTNodePtr tmpPtr = NULL;

	if (*userPolyLddr) {
		tmpPtr = *userPolyLddr;
		*userPolyLddr = tmpPtr->next;
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
	PTNodePtr userPolyL, userPolyR, resultPoly;
	int menuSelect, i, flag;
	char userChoice;
	userPolyL = NULL;
	userPolyR = NULL;
	resultPoly = NULL;


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
			if (!userPolyL)
				printf("EMPTY LIST...\n\n\n");
			else {
				displayPolyNodeJustinU(userPolyL);
				displayPolyNodeJustinU(userPolyR);
				displayPolyNodeJustinU(resultPoly);
			}
			break;

		case 2:
			printf("Lets create your first term\n\n");
			do {
				flag = 0;
				printf("Calling insertPolyNodeJustinU()\n");
				printf("Calling createPolyNodeJustinU()\n\n");
				insertPolyNodeJustinU(createPolyNodeJustinU(), &userPolyL);
				printf("create another term? (y or n): ");
				scanf(" %c", &userChoice);

				if (userChoice == 'y' || userChoice == 'Y') 
					printf("\n");
				else if (userChoice == 'n' || userChoice == 'N')
					flag = 1;
				else
					printf("please choose only y or n\n");

			} while (flag !=1);
			printf("\n");

			flag = 2;
			/**
			printf("\nLets create your second term\n");
						do {
				flag = 0;
				printf("Calling insertPolyNodeJustinU()\n");
				printf("Calling createPolyNodeJustinU()\n");
				insertPolyNodeJustinU(createPolyNodeJustinU(), &userPolyR);
				printf("create another term? (y or n): ");
				scanf(" %c", &userChoice);

				if (userChoice == 'y' || userChoice == 'Y') 
					continue;
				else if (userChoice == 'n' || userChoice == 'N')
					flag = 1;
				else
					printf("please choose only y or n\n");

			} while (flag !=1);
			**/
			break;
		
		case 3:
			if (!userPolyL) {
				printf("EMPTY LISTS...\n");
			}
			else {
				getPolyOrderJustinU(userPolyL);
			}
			break;

		case 4:
			if (!userPolyL) {
				printf("EMPTY LIST...\n");
			}
			else {
				addPolysJustinU(userPolyL, userPolyR, &resultPoly);
			}
			/**
			else if (getListLengthJustinU(&userPolyL) > 1) { 
				printf("\nSelect terms to add ");
				addPolyNodeJustinU(getPolyTerm(userPolyL), getPolyTerm(userPolyL));
			}
			else {
				printf("Please create at least 1 more term to perform addition\n");
			}
			**/
			break;

		case 5:
			printf("Thank you Apu!\n");
			break;

		default:
			printf("You should not be in this class!\n");
			break;
		}

	} while (menuSelect != 5);
	for (i = 0; i < getListLengthJustinU(&userPolyL); i++) {
		removeFirstJustinU(&userPolyL);
	}

	for (i = 0; i < getListLengthJustinU(&userPolyR); i++) {
		removeFirstJustinU(&userPolyR);
	}
	free(userPolyL);
	free(userPolyR);
}
/**
void creatingMenu (PTNodePtr* left, PTNodePtr right) {
int menuSelect;

do {
printf("\n*******************************"\
"\n*  MENU : Creating/Updating  *"\
"\n* 1. Left Operand             *"\
"\n* 2. Right Operand            *"\
"\n* 3. Both Operand             *"\
"\n* 4. Display Current Operands *"\
"\n* 5. Return                   *"\
"\n*******************************");
printf("\n Enter Option : ");
scanf_s("%d", &menuSelect);
printf("\n");

switch (menuSelect) {
case 1:
printf("Choose values for your fraction\n\n");
initFractionJustinU(fracA);
printf("\n");
printFractionJustinUInfo(*fracA);
break;

case 2:
printf("Choose values for your fraction\n\n");
initFractionJustinU(fracB);
printf("\n");
printFractionJustinUInfo(*fracB);
printf("\n");
break;

case 3:
printf("Choose values for your left operand\n\n");
initFractionJustinU(fracA);

printf("\n");

printf("Choose values for your right operand\n\n");
initFractionJustinU(fracB);

printf("\n");
printFractionJustinUInfo(*fracA);
printf("\n");
printFractionJustinUInfo(*fracB);
printf("\n");
break;

case 4:
if (*fracA == NULL && *fracB == NULL) {
printf("Left Operand :\n");
printf("Address/Location : NULL\n");

printf("Right Operand :\n");
printf("Address/Location : NULL\n");
printf("\n");
}

else if (*fracB == NULL) {
printf("Left Operand :\n");
printFractionJustinUInfo(*fracA);
printf("\n\n");

printf("Right Operand :\n");
printf("Address/Location : NULL\n");
printf("\n");
}

else if (*fracA == NULL) {
printf("Left Operand :\n");
printf("Address/Location : NULL\n");
printf("\n\n");

printf("Right Operand :\n");
printFractionJustinUInfo(*fracB);
printf("\n");
}

else {
printf("Left Operand :\n");
printFractionJustinUInfo(*fracA);
printf("\n\n");

printf("Right Operand :\n");
printFractionJustinUInfo(*fracB);
printf("\n");
}
break;

case 5:
printf("Returning to Main Menu \n");
break;

default:
printf("You should not be in this class!\n");
break;
}

} while (menuSelect != 5);

return; 
}
}
**/