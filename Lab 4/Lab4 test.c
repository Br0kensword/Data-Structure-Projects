/**
* Program Name: cis27Spring2014JustinULab4Ex1.c
* Date:  3/4/2014
* Written By:  Justin Unverricht
*/
#include <stdio.h>
#include <stdlib.h>

struct IntNode {
	int value;
	//Fraction value;
	struct IntNode* next;
};

struct Fraction {
	int num;
	int denom;
};

typedef struct IntNode* IntNodeAddr;
typedef struct IntNode* IntList;
typedef struct Fraction Fraction;


IntList createEmptyIntList(void);
IntNodeAddr createIntNode(int);
void insertFirstIntList(IntList*, IntNodeAddr);
IntNodeAddr removeFirstIntList(IntList*);
void printForwardIntList(IntList);
void printReverseIntList(IntList);
void appendIntList(IntNodeAddr, IntList*);
void appendNthNodeIntList(IntNodeAddr, IntList*, int);
void removeLastIntList(IntList*);
void swapIntNode(IntList*, IntNodeAddr, IntNodeAddr);
void classInfo();
int gcd(int, int);

int main() {
	IntList myList;
	//IntNodeAddr tmpPtr;
	
	//int i;
	int count = 0;
	int flag = 0;
	int userInt;
	char userChoice;

	myList = 0; 


	do {
		printf("Would you like to input a number? (y/n) : ");
		scanf(" %1c", &userChoice);
		flag = 2;
		printf("This is the value of userChoice : >>%c<<\n", userChoice);

		if (userChoice == 'y' && flag == 2) {
			printf("Input a number : ");
			scanf_s("%d", &userInt);

			insertFirstIntList(&myList, createIntNode(userInt));
			count++;
			userChoice = 'a';
		}
		else if (userChoice == 'n') {
			flag = 1;
		}
		else {
			printf("Invalid input please enter y or n\n");
			userChoice = 'a';
		}

	} while (flag != 1);

	//printForwardIntList(myList);
	
	printf("\n Pick a number you would like to add : ");
	scanf_s("%d", &userInt);
	appendIntList(createIntNode(userInt), &myList);
	count ++;
	
	printf("\n");

	printForwardIntList(myList);
	printf("\n Now printing in reverse\n");

	printReverseIntList(myList);

	printf("Deleting last position");
	removeLastIntList(&myList);

	printForwardIntList(myList);

	appendNthNodeIntList(createIntNode(31), &myList, 2);

	printForwardIntList(myList);

	printf("Printing out count : %d",count);

	free(myList);
	return 0;
}

void printForwardIntList(IntList myList) {
	IntNodeAddr tmpPtr;

	if (myList) {
		tmpPtr = myList;
		printf("\nThe list will start at : %d\n", tmpPtr->value);  //%p prints out a pointer

		while (tmpPtr) {
			printf("\n\n\tData : %d\n\tnext : %p\n", tmpPtr->value,
				tmpPtr->next);
			//printFractionJustinU(tmpPtr->value);
			printf("\n");
			tmpPtr = tmpPtr->next;
		}
	}
	else
		printf("\nIt is an empty list!\n");

	return;
}

void printReverseIntList(IntList myList) {
	IntNodeAddr tmpPtr;
	tmpPtr = myList;

	if (tmpPtr != NULL) {
		printReverseIntList(tmpPtr->next);
		printf("\n\n\tData : %d\n\tnext : %p\n", tmpPtr->value,tmpPtr->next);
		//printFractionJustinU(tmpPtr->value);
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
		free(tmpPtr->next);
		tmpPtr->next = NULL;
	}
	else {
		printf("There is nothing here to remove!");
	}

	return;
}

void insertFirstIntList(IntList* myListAddr, IntNodeAddr nodeAddr) {
	if (*myListAddr) {
		nodeAddr->next = *myListAddr;
	} 
	*myListAddr = nodeAddr;

	return;
}

/**
IntNodeAddr createIntNode(int a) {
	IntNodeAddr tmpPtr;

	tmpPtr = (IntNodeAddr) malloc(sizeof(struct IntNode));

	tmpPtr->value = a;
	tmpPtr->next = 0;

	return tmpPtr;
}

IntList createEmptyIntList() {
	return 0;
}
**/

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
	int i;
	IntNodeAddr tmpPtr;
	IntNodeAddr tmpPtr2;

	tmpPtr = *(headShot);
	if (place == 1 && tmpPtr == 0) {
		tmpPtr = target;
	}
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

void classInfo() {
	printf("\nCIS 27 - C Programming"\
		"\nLaney College "\
		"\nJustin Unverricht"\
		"\n"\
		"\nAssignment Informantion --"\
		"\n  Assignment Number:    Lab 04,"\
		"\n                        Coding Assignment -- Exercise #1"\
		"\n  Written by:           Justin Unverricht"\
		"\n  Submitted Date:       3/4/2014");

	return;
}