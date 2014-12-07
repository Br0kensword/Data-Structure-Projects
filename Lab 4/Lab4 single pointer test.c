/**
* Program Name: cis27Spring2014JustinULab4Ex1.c
* Date:  3/4/2014
* Written By:  Justin Unverricht
*/

/**
Need to create removeNthNode function, as well as finish insert and remove menus
Need to make logic to make sure people dont go out of bounds for selecting Nth node
Should also convert fraction input to the way it is wanted in the Lab
Need to rename the appendIntNode function to insertLast node or some shit
create isEmpty and getLength functions
**/

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
Fraction* initFractionJustinU();
void simplifyFractionJustinU(Fraction*);
void printFractionJustinU(Fraction*);
int gcd(int, int);

// IntList functions
IntNodeAddr createIntNode();
IntNodeAddr removeFirstIntList(IntList*);
void createEmptyIntList(IntList*);
void insertFirstIntList(IntNodeAddr, IntList*);
void printForwardIntList(IntList);
void printReverseIntList(IntList);
void appendIntList(IntNodeAddr, IntList*);
void appendNthNodeIntList(IntNodeAddr, IntList*, int);
void removeLastIntList(IntList*);
void removeNthNodeIntList(IntList*, int);
void swapIntNode(IntList*, IntNodeAddr, IntNodeAddr);
int getIntListLengthJustinU(IntList*);

// Menu and Misc functions
void menu();
void insertMenu(IntList*);
void removeMenu(IntList*);
void classInfo();


int main() {
	/**
	IntList myList;
	//IntNodeAddr tmpPtr;
	//Fraction* data = NULL;
	//int i;
	int count = 0;
	int flag = 0;
	//int userInt;
	char userChoice;

	myList = 0; 

	do {
	printf("Would you like to input a fraction? (y/n) : ");
	scanf(" %1c", &userChoice);
	flag = 2;
	printf("This is the value of userChoice : >>%c<<\n", userChoice);

	if (userChoice == 'y' && flag == 2) {
	printf("Input a Fraction \n");
	//data = initFractionJustinU();

	insertFirstIntList(createIntNode(), &myList);
	count++;
	//printFractionJustinU(data);
	userChoice = 'a';
	//free(data);
	}
	else if (userChoice == 'n') {
	flag = 1;
	}
	else {
	printf("Invalid input please enter y or n\n");
	userChoice = 'a';
	}

	} while (flag != 1);

	printForwardIntList(myList);
	//printf(" This is the current count of the Link List : %d", getIntListLengthJustinU(myList));
	printf("\n Pick a number you would like to add : \n");
	//scanf_s("%d", &userInt);
	appendIntList(createIntNode(), &myList);
	count ++;

	printf("\n");

	printForwardIntList(myList);
	printf("\n Now printing in reverse\n");

	printReverseIntList(myList);

	printf("Deleting last position");
	removeLastIntList(&myList);

	printForwardIntList(myList);

	appendNthNodeIntList(createIntNode(), &myList, 2);  //combine createIntNode with initFrac 

	printForwardIntList(myList);

	printf("Printing out count : %d",count);
	
	free(myList);
	**/
	menu();
	return 0;
}


// Fraction Functions
Fraction* initFractionJustinU() {
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

	return frPtr;
}

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

void printFractionJustinU(Fraction *userFrac) {
	printf("%d",userFrac->num);
	printf("/");
	printf("%d", userFrac->denom);
	return;
}

// IntList Functions
int getIntListLengthJustinU(IntList* myList) {
	IntNodeAddr tmpPtr;
	int count = 0;
	if (!myList)
		count = 0;
	else {
		tmpPtr = (*myList);
		while (tmpPtr) {
			count++;
			if (tmpPtr->next)
			tmpPtr = tmpPtr->next;
		}
	}
	return count;
}

void printForwardIntList(IntList myList) {
	IntNodeAddr tmpPtr;

	if (myList) {
		//tmpPtr = myList->next;
		tmpPtr = myList;

		printf("\nThe list will start at : ");  //%p prints out a pointer
		printFractionJustinU(tmpPtr->value);
		printf("\n");
		while (tmpPtr) {
			//printf("\n\n\tData : %p\n\tnext : %p\n", tmpPtr->value,
			//tmpPtr->next);
			printf("data : %p\n", tmpPtr->value);
			printFractionJustinU(tmpPtr->value);
			
			printf("\n");
			printf("pointer : %p\n", tmpPtr->next);
			tmpPtr = tmpPtr->next;
		}
	}
	else
		printf("\nEMPTY LIST ...!\n");

	return;
}

void printReverseIntList(IntList myList) {
	IntNodeAddr tmpPtr;
	tmpPtr = myList;

	if (tmpPtr != NULL) {
		printReverseIntList(tmpPtr->next);
		printFractionJustinU(tmpPtr->value);
		printf("\n");
	}

	return;
}

IntNodeAddr removeFirstIntList(IntList* myListAddr) {
	IntNodeAddr tmpPtr = 0;

	if (*myListAddr) {
		tmpPtr = *myListAddr;
		*myListAddr = tmpPtr->next;
	} 

	return tmpPtr;
}

void removeLastIntList(IntList* mylistAddr) {
	IntNodeAddr tmpPtr;
	tmpPtr = *mylistAddr;

	if (tmpPtr) {
		if (tmpPtr->next) {
			while (tmpPtr->next->next){
				tmpPtr = tmpPtr->next;
			}
		}
		free(tmpPtr->next->value);
		free(tmpPtr->next);
		tmpPtr->next = NULL;
	}
	else {
		printf("There is nothing here to remove!");
	}

	return;
}

void insertFirstIntList(IntNodeAddr newNode, IntList* myList) {
	
	if (myList) {
		newNode->next = (*myList);
	} 

	*myList = newNode;
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

void createEmptyIntList(IntList* myList) {
	(*myList) = NULL;
	return;
}

void appendIntList(IntNodeAddr target, IntList* headShot) {  // appending to a link-list
	// sets temp to address of IntList and checks for empty node, once found
	IntNodeAddr tmpPtr;

	tmpPtr = *(headShot);

	if (tmpPtr == 0)   
		*headShot = target;
	else {
		while (tmpPtr->next) {
			tmpPtr = tmpPtr->next;
		}

		tmpPtr->next = target;
	}
	return;
}

void appendNthNodeIntList(IntNodeAddr target, IntList* headShot, int place) {
	//int listRange = getIntListLengthJustinU(headShot);
	int i;
	IntNodeAddr tmpPtr;
	IntNodeAddr tmpPtr2;

	tmpPtr = *(headShot);
	if (!headShot) {
		printf("EMPTY LIST creating new list for your new node.\n");
		tmpPtr = target;
	}
	//create new list hreer instead
	else {
		tmpPtr = target;
		tmpPtr2 = *(headShot);
		for (i = 0; i < (place-1); i++) {
			tmpPtr2 = tmpPtr2->next;
		}
		tmpPtr->next = tmpPtr2->next;
		tmpPtr2->next = tmpPtr;
	}

	return;
}

void removeNthNodeIntList(IntList* myList, int place) {
	int i;
	IntNodeAddr tmpPtr;
	tmpPtr = *(myList);

	if (tmpPtr) {
		for (i = 0; i < (place-1); i++) {
			tmpPtr = tmpPtr->next;
		}
		tmpPtr->next = tmpPtr->next->next;
		free(tmpPtr->next->value);
		free(tmpPtr->next);
	}
	else {
		printf("There is nothing here to remove!");
	}

}
// Menu and Misc functions

void menu() {
	IntList myList = NULL;
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
			if (myList == NULL)
				printf("You have not created a list yet");
			else
				printForwardIntList(myList);
//				printReverseIntList((*myList));
			break;

		case 2:
			insertMenu(&myList);
			break;

		case 3:
			removeMenu(&myList);
			break;

		case 4:
			printf("I feel great with linked lists and fractions!\n");
			break;

		default:
			printf("You should not be in this class!\n");
			break;
		}

	} while (menuSelect != 4);
	for (i = 0; i < getIntListLengthJustinU(myList); i++) {
		removeFirstIntList(myList);
	}
	free(myList);
}

void insertMenu(IntList** userList) {	
	int menuSelect;
	int nodePosition;
	int i;
	
	do {
		printf("\n***********************"\
			"\n*   INSERTING  MENU   *"\
			"\n* 1. As first node    *"\
			"\n* 2. After n-th node  *"\
			"\n* 3. As last node     *"\
			"\n* 4. Quit             *"\
			"\n***********************");
		printf("\n Enter Option : ");
		scanf_s("%d", &menuSelect);
		printf("\n");

		switch (menuSelect) {
		case 1:
			if (!(*userList))
				createEmptyIntList(userList);
			
			printf("Adding new node to the first position of list\n");
			insertFirstIntList(createIntNode(), &userList);
			break;

		case 2:
			for (i = 0; i < getIntListLengthJustinU((*userList)); i++) {
				printf("%d : ", i);
			}
			printf("did it here");
			printf("\n");
			printf("Please choose which position you would like to add your node : ");
			scanf("%d", &nodePosition);

			while (nodePosition < 0 || nodePosition > getIntListLengthJustinU((*userList))) {
				printf("The position you selected is out of the bounds of your list, please choose again : ");
				scanf("%d", &nodePosition);
			}

			appendNthNodeIntList(createIntNode(), (*userList), nodePosition);
			break;

		case 3:
	
			appendIntList(createIntNode(), (*userList));
			break;

		case 4:
			printf("Returning to Main Menu\n");
			break;

		default:
			printf("You should not be in this class!\n");
			break;
		}

	} while (menuSelect != 4);

	return;
}

void removeMenu(IntList* userList) {
	int menuSelect;
	int nodePosition;
	int i;

	do {
		printf("\n***********************"\
			"\n*   REMOVING  MENU    *"\
			"\n* 1. First node       *"\
			"\n* 2. N-th node        *"\
			"\n* 3. Last node        *"\
			"\n* 4. Quit             *"\
			"\n***********************");
		printf("\n Enter Option : ");
		scanf_s("%d", &menuSelect);
		printf("\n");

		switch (menuSelect) {
		case 1:
			if (!(*userList))
				printf("You have not created a list yet");
			else {
			printf("Removing first node in list\n");
			removeFirstIntList((*userList));
			}
			break;

		case 2:
				if (!(*userList))
				printf("You have not created a list yet");
				else {
			for (i = 0; i < getIntListLengthJustinU((*userList)); i++) {
				printf("%d : ", i);
			}
			printf("\n");
			printf("Please choose which position you would like to add your node : ");
			scanf("%d", &nodePosition);

			while (nodePosition < 0 || nodePosition > getIntListLengthJustinU((*userList))) {
				printf("The position you selected is out of the bounds of your list, please choose again : ");
				scanf("%d", &nodePosition);
			}

			removeNthNodeIntList((*userList), nodePosition);
				}
			break;

		case 3:
				if (!(*userList))
				printf("You have not created a list yet");
				else {
			printf("Removing last node in list\n");
			removeLastIntList((*userList));
				}
			break;

		case 4:
			printf("Returning to Main Menu\n");
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
		"\n  Assignment Number:    Lab 04,"\
		"\n                        Coding Assignment -- Exercise #1"\
		"\n  Written by:           Justin Unverricht"\
		"\n  Submitted Date:       3/18/2014");

	return;
}
