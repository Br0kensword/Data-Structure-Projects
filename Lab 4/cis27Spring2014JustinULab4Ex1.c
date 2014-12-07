/**
* Program Name: cis27Spring2014JustinULab4Ex1.c
* Date:  3/4/2014
* Written By:  Justin Unverricht
*/

#include <stdio.h>
#include <stdlib.h>

struct Fraction {
	int num;
	int denom;
};

struct IntNode {
	struct Fraction* value;
	struct IntNode* next;
};

typedef struct Fraction Fraction; 
typedef struct IntNode* IntNodeAddr;
typedef struct IntNode* IntList;

// Fraction functions
void simplifyFractionJustinU(Fraction*);
void printFractionJustinU(Fraction*);
int gcd(int, int);

// IntList functions
IntNodeAddr createIntNode();
IntNodeAddr removeFirstJustinU(IntList*);
void insertFirstJustinU(IntNodeAddr, IntList*);
void displayListJustinU(IntList);
void printListContentsJustinU(IntList*);
void insertLastJustinU(IntNodeAddr, IntList*);
void insertAtJustinU(IntNodeAddr, IntList*, int);
void removeLastJustinU(IntList*);
void removeAtJustinU(IntList*, int);
int getIntListLengthJustinU(IntList*);
int isEmptyJustinU(IntList*);

// Menu and Misc functions
void menu();
void insertMenu(IntList*);  
void removeMenu(IntList*);	
void classInfo();

int main() {
	classInfo();
	printf("\n");
	menu();

	return 0;
}

// Fraction Functions
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
	return ;
}

void printFractionJustinU(Fraction* userFrac) {
	printf("%d",userFrac->num);
	printf("/");
	printf("%d", userFrac->denom);
	return;
}

// IntList Functions
int getIntListLengthJustinU(IntList* userList) {
	IntNodeAddr tmpPtr;
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

int isEmptyJustinU(IntList* userList) {
	if ((*userList) == NULL)
		return 0;
	else
		return 1;
}

void displayListJustinU(IntList userList) {
	IntNodeAddr tmpPtr;

	if (userList) {

		tmpPtr = userList;

		printf("\nThe list will start at : ");  
		printFractionJustinU(tmpPtr->value);
		printf("\n\n");
		while (tmpPtr) {
			printf("data : ");
			printFractionJustinU(tmpPtr->value);

			printf("\n");
			printf("pointer : %p\n", tmpPtr->next);
			printf("\n");
			tmpPtr = tmpPtr->next;
		}
	}
	else
		printf("\nEMPTY LIST ...!\n");

	return;

}

void printListContentsJustinU(IntList* userList) {
	IntNodeAddr tmpPtr;
	int position = 0;
	tmpPtr = (*userList);

	while (tmpPtr) {
		printf("%d : ", position+1);
		printFractionJustinU(tmpPtr->value);
		printf("  ");
		tmpPtr = tmpPtr->next;
		position++;
	}
	return;
}

IntNodeAddr removeFirstJustinU(IntList* userListAddr) {
	IntNodeAddr tmpPtr = NULL;

	if (*userListAddr) {
		tmpPtr = *userListAddr;
		*userListAddr = tmpPtr->next;
		free(tmpPtr);
	} 

	return tmpPtr;
}

void removeLastJustinU(IntList* userList) {
	IntNodeAddr tmpPtr;
	tmpPtr = *userList;

	if (tmpPtr) {
		if (tmpPtr->next) {
			while (tmpPtr->next->next){
				tmpPtr = tmpPtr->next;
			}
		
		free(tmpPtr->next->value);
		free(tmpPtr->next);
		tmpPtr->next = NULL;
		}
		else {
			tmpPtr = *userList;
			*userList = tmpPtr->next;
			free(tmpPtr);
		}
	}
	else {
		printf("There is nothing here to remove!");
	}

	return;
}

void insertFirstJustinU(IntNodeAddr newNode, IntList* userList) {
	if (userList) {
		newNode->next = (*userList);
	} 

	*userList = newNode;
	return;
}

IntNodeAddr createIntNode() {
	IntNodeAddr tmpPtr;
	Fraction* frPtr = NULL;
	int num;
	int denom;

	printf("Please choose your numerator : ");
	scanf_s("%d", &num);

	printf("\nPlease choose your denominator : ");
	scanf_s("%d", &denom);

	while (denom == 0) {
		printf("A black hole forms and eats your compiler, use something other than 0 \n");
		printf("\nPlease choose your denominator : ");
		scanf_s("%d", &denom);
	}

	frPtr = (Fraction*) malloc(sizeof(struct Fraction));

	if (denom < 0) {
		denom = -denom;
		num = -num; 
	}

	frPtr->num = num;
	frPtr->denom = denom;

	simplifyFractionJustinU(frPtr);

	tmpPtr = (IntNodeAddr) malloc(sizeof(struct IntNode));

	tmpPtr->value = frPtr;
	tmpPtr->next = NULL;

	return tmpPtr;
}

void insertLastJustinU(IntNodeAddr newNode, IntList* userList) {  
	// sets temp to address of IntList and checks for empty node.
	IntNodeAddr tmpPtr;

	tmpPtr = *(userList);

	if (tmpPtr == 0)   
		*userList = newNode;
	else {
		while (tmpPtr->next) {
			tmpPtr = tmpPtr->next;
		}

		tmpPtr->next = newNode;
	}
	return;
}

void insertAtJustinU(IntNodeAddr newNode, IntList* userList, int place) {
	int i;
	IntNodeAddr tmpPtr;
	IntNodeAddr tmpPtr2;

	if (!(*userList)) {
		printf("EMPTY LIST creating new list for your new node.\n");
		*userList = newNode;
	}
	else {
		tmpPtr = newNode;
		tmpPtr2 = *(userList);
		for (i = 0; i < (place-1); i++) {
			tmpPtr2 = tmpPtr2->next;
		}
		tmpPtr->next = tmpPtr2->next;
		tmpPtr2->next = tmpPtr;
	}

	return;
}

void removeAtJustinU(IntList* userList, int place) {
	int i;
	IntNodeAddr tmpPtr;
	IntNodeAddr tmpPtr2;

	if ((*userList)) {
		tmpPtr = (*(userList));
		for (i = 0; i < (place-1); i++) {
			tmpPtr = tmpPtr->next;
		}
		if (!tmpPtr->next){ //Checking if there is only 1 node in list
		tmpPtr = *userList;
		*userList = tmpPtr->next;
		}
		else if (tmpPtr->next->next) { // saves pointer to node after node to be deleted
			tmpPtr2 = tmpPtr->next->next;
			free(tmpPtr->next->value);
			free(tmpPtr->next);
			tmpPtr->next = tmpPtr2;
		}
		else {
			free(tmpPtr->next->value);
			free(tmpPtr->next);
			tmpPtr->next = NULL;
		}
	}
	else {
		printf("There is nothing here to remove!");
	}

}
// Menu and Misc functions

void menu() {
	IntList userList = NULL;
	int menuSelect;
	int i;

	do {
		printf("\n*******************************"\
			"\n*           MENU              *"\
			"\n* 1. Display current list     *"\
			"\n* 2. Inserting                *"\
			"\n* 3. Removing                 *"\
			"\n* 4. Quit                     *"\
			"\n*******************************");
		printf("\n Enter Option : ");
		scanf_s("%d", &menuSelect);
		printf("\n");

		switch (menuSelect) {
		case 1:
			if (userList == NULL)
				printf("EMPTY LIST...\n\n\n");
			else
				displayListJustinU(userList);

			break;

		case 2:
			insertMenu(&userList);
			break;

		case 3:
			removeMenu(&userList);
			break;

		case 4:
			printf("I feel great with linked lists and fractions!\n");
			break;

		default:
			printf("You should not be in this class!\n");
			break;
		}

	} while (menuSelect != 4);
	for (i = 0; i < getIntListLengthJustinU(&userList); i++) {
		removeFirstJustinU(&userList);
	}
	free(userList);
}

void insertMenu(IntList* userList) {	
	int menuSelect;
	int nodePosition;

	do {
		printf("\n***********************"\
			"\n*   INSERTING  MENU   *"\
			"\n* 1. As first node    *"\
			"\n* 2. After n-th node  *"\
			"\n* 3. As last node     *"\
			"\n* 4. Displaying       *"\
			"\n* 5. Quit             *"\
			"\n***********************");
		printf("\n Enter Option : ");
		scanf_s("%d", &menuSelect);
		printf("\n");

		switch (menuSelect) {
		case 1:
			if (isEmptyJustinU(userList) == 0)
				(*userList) = NULL;

			printf("Adding new node to the first position of list\n\n");
			insertFirstJustinU(createIntNode(), userList);
			break;

		case 2:
			if (!(*userList))
				(*userList) = NULL;

			printListContentsJustinU(userList);
			printf("\n");
			if ((*userList) == NULL) {
				printf("Please select 0 to create your list : ");
				scanf("%d", &nodePosition);
			}
			else {
				printf("Please choose which position after which you would like to add your node : \n");
				scanf("%d", &nodePosition);
			}
			while (nodePosition < 0 || (nodePosition - 1) > getIntListLengthJustinU(userList)) {
				printf("The value you selected is out of bounds for your list, please choose again : ");
				scanf("%d", &nodePosition);
			}

			insertAtJustinU(createIntNode(), userList, nodePosition);

			break;

		case 3:
			if (!(*userList))
				(*userList) = NULL;
			insertLastJustinU(createIntNode(), userList);
			break;

		case 4:
			if (userList == NULL)
				printf("EMPTY LIST...\n");
			else
				displayListJustinU((*userList));
			break;

		case 5:
			printf("Returning to Main Menu\n");
			break;

		default:
			printf("You should not be in this class!\n");
			break;
		}

	} while (menuSelect != 5);

	return;
}

void removeMenu(IntList* userList) {
	int menuSelect;
	int nodePosition;
	
	do {
		printf("\n***********************"\
			"\n*   REMOVING  MENU    *"\
			"\n* 1. First node       *"\
			"\n* 2. N-th node        *"\
			"\n* 3. Last node        *"\
			"\n* 4. Displaying       *"\
			"\n* 5. Quit             *"\
			"\n***********************");
		printf("\n Enter Option : ");
		scanf_s("%d", &menuSelect);
		printf("\n");

		switch (menuSelect) {
		case 1:
			if (!(*userList))
				printf("This is an empty list");
			else {
				printf("Removing first node in list\n");
				removeFirstJustinU(userList);
			}
			break;

		case 2:
			if (!(*userList))
				printf("This is an empty list");
			else {
				printListContentsJustinU(userList);
				printf("\n");
				printf("Please choose which node you would like to delete : ");
				scanf("%d", &nodePosition);

				while (nodePosition < 0 || (nodePosition - 1) > getIntListLengthJustinU(userList)) {
					printf("The value you selected is out of bounds for your list, please choose again : ");
					scanf("%d", &nodePosition);
				}
				removeAtJustinU(userList, (nodePosition - 1));
			}

			break;

		case 3:
			if (!(*userList))
				printf("This is an empty list");
			else {
				printf("Removing last node in list\n");
				removeLastJustinU(userList);
			}
			break;

		case 4:
			if (userList == NULL)
				printf("EMPTY LIST...\n");
			else
				displayListJustinU((*userList));
			break;

		case 5:
			printf("Returning to Main Menu\n");
			break;

		default:
			printf("You should not be in this class!\n");
			break;
		}

	} while (menuSelect != 5);

	return;

}

void classInfo() {
	printf("\nCIS 27 - C Programming"\
		"\nLaney College "\
		"\nJustin Unverricht"\
		"\n"\
		"\nAssignment Informantion --"\
		"\n  Assignment Number:    Lab 04,"\
		"\n                        Coding Assignment -- Exercise #1"\
		"\n  Written by:           Justin Unverricht"\
		"\n  Submitted Date:       3/18/2014");

	return;
}

/** Output   //Following Mr Nguyen's instructions I have only used 2 fractions so as to save paper.

CIS 27 - C Programming
Laney College
Justin Unverricht

Assignment Informantion --
  Assignment Number:    Lab 04,
                        Coding Assignment -- Exercise #1
  Written by:           Justin Unverricht
  Submitted Date:       3/18/2014

*******************************
*           MENU              *
* 1. Display current list     *
* 2. Inserting                *
* 3. Removing                 *
* 4. Quit                     *
*******************************
 Enter Option : 5

You should not be in this class!

*******************************
*           MENU              *
* 1. Display current list     *
* 2. Inserting                *
* 3. Removing                 *
* 4. Quit                     *
*******************************
 Enter Option : 1

EMPTY LIST...




*******************************
*           MENU              *
* 1. Display current list     *
* 2. Inserting                *
* 3. Removing                 *
* 4. Quit                     *
*******************************
 Enter Option : 2


***********************
*   INSERTING  MENU   *
* 1. As first node    *
* 2. After n-th node  *
* 3. As last node     *
* 4. Displaying       *
* 5. Quit             *
***********************
 Enter Option : 1

Adding new node to the first position of list

Please choose your numerator : 3

Please choose your denominator : 4

***********************
*   INSERTING  MENU   *
* 1. As first node    *
* 2. After n-th node  *
* 3. As last node     *
* 4. Displaying       *
* 5. Quit             *
***********************
 Enter Option : 2

1 : 3/4
Please choose which position after which you would like to add your node : 1
Please choose your numerator : 5

Please choose your denominator : 12

***********************
*   INSERTING  MENU   *
* 1. As first node    *
* 2. After n-th node  *
* 3. As last node     *
* 4. Displaying       *
* 5. Quit             *
***********************
 Enter Option : 4


The list will start at : 3/4

data : 3/4
pointer : 005352B8

data : 5/12
pointer : 00000000

***********************
*   INSERTING  MENU   *
* 1. As first node    *
* 2. After n-th node  *
* 3. As last node     *
* 4. Displaying       *
* 5. Quit             *
***********************
 Enter Option : 5

Returning to Main Menu

*******************************
*           MENU              *
* 1. Display current list     *
* 2. Inserting                *
* 3. Removing                 *
* 4. Quit                     *
*******************************
 Enter Option : 3


***********************
*   REMOVING  MENU    *
* 1. First node       *
* 2. N-th node        *
* 3. Last node        *
* 4. Displaying       *
* 5. Quit             *
***********************
 Enter Option : 1

Removing first node in list

***********************
*   REMOVING  MENU    *
* 1. First node       *
* 2. N-th node        *
* 3. Last node        *
* 4. Displaying       *
* 5. Quit             *
***********************
 Enter Option : 2

1 : 5/12
Please choose which node you would like to delete : 1

***********************
*   REMOVING  MENU    *
* 1. First node       *
* 2. N-th node        *
* 3. Last node        *
* 4. Displaying       *
* 5. Quit             *
***********************
 Enter Option : 4


EMPTY LIST ...!

***********************
*   REMOVING  MENU    *
* 1. First node       *
* 2. N-th node        *
* 3. Last node        *
* 4. Displaying       *
* 5. Quit             *
***********************
 Enter Option : 5

Returning to Main Menu

*******************************
*           MENU              *
* 1. Display current list     *
* 2. Inserting                *
* 3. Removing                 *
* 4. Quit                     *
*******************************
 Enter Option : 4

I feel great with linked lists and fractions!
**/