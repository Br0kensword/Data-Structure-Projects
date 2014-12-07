/**
* Project Name : cis27spring2014JustinUnverrichtLab2Ex1
* Date : 2/13/2014
* Written by : Justin Unverricht
**/

#include <stdio.h> 
#include <stdlib.h>

//Function Definitions
void getSecondLargestJustinU(int*, int);
void Menu();
void classInfo();
void displayIntOccuranceJustinU(int*, int);

int main() {
	classInfo();
	printf("\n");
	Menu();

	return 0;
}

void Menu() {
	int menuSelect;
	int numberOfInt;
	int* iPtr;
	int i;

	do {
		printf("\n********************************************"\
			"\n*                  MENU                    *"\
			"\n* 1. Calling getSecondLargestEvenJustinU() *"\
			"\n* 2. Calling displayIntOccuranceJustinU()  *"\
			"\n* 3. Quit                                  *"\
			"\n********************************************");
		printf("\n Enter Option : ");
		scanf_s("%d", &menuSelect);

		switch (menuSelect) {
		case 1:
			do {
				printf("How many elements would you like in your array?(integers only) :  ");
				scanf_s("%d",&numberOfInt);
				printf("\n");

				if (numberOfInt <= 0)
					printf("Please enter a value larger than 0 \n");
			} while (numberOfInt <= 0);

			iPtr = (int*) malloc(numberOfInt * sizeof(int));  

			printf("Enter the numbers that you want for your array : \n");

			for (i = 0; i < numberOfInt; i++) {
				scanf_s("%d",(iPtr + i));
			}

			printf("\n");

			printf("Calling getSecondLargestEvenJustinU() -- \n");
			printf("For the array with the elements shown below \n");

			printf("\n");

			for (i = 0; i < numberOfInt; i++) {  
				printf("%d ",*(iPtr + i));
			}

			printf("\n");

			getSecondLargestJustinU(iPtr, numberOfInt);
			printf("\n");

			free(iPtr);
			break;

		case 2:
			do {
				printf("How many elements would you like in your array?(integers only) :  ");
				scanf_s("%d",&numberOfInt);
				printf("\n");

				if (numberOfInt <= 0)
					printf("Please enter a value larger than 0 \n");
			} while (numberOfInt <= 0);

			iPtr = (int*) malloc(numberOfInt * sizeof(int));  

			printf("Enter the numbers that you want for your array : \n");

			for (i = 0; i < numberOfInt; i++) {
				scanf_s("%d",(iPtr + i));
			}

			printf("\n");
			printf("Calling displayIntOccuranceJustinU() \n");
			printf("For the array with the elements shown below \n\n");

			for (i = 0; i < numberOfInt; i++) {  
				printf("%d ",*(iPtr + i));
			}

			printf("\n\n");
			displayIntOccuranceJustinU(iPtr, numberOfInt);
			free(iPtr);
			break;

		case 3:
			printf("Have fun.....\n");
			break;

		default:
			printf("You should not be in this class!");
			break;
		}

	} while (menuSelect != 3);

}

void getSecondLargestJustinU(int* userAry, int size) {
	int largest;
	int secondLargest = -1999999999 ;
	int count = 0;
	int i;

	for (i=0; i < size; i++) {
		if (count == 0){
			if (*(userAry + i) % 2 == 0) {
				largest = *(userAry + i);
				count++;
			}
		}
		else {
			if ((*(userAry + i) % 2 == 0 && *(userAry + i) != largest )) { 
				if (*(userAry + i) > largest) {
					secondLargest = largest;
					largest = *(userAry + i);
					count++;
				}
				else {
					secondLargest = *(userAry + i);
					count++;
				}
			} 
		}
	}

	if (count <= 0) {
		printf("\nThe second largest even number is :   %d", secondLargest);
	}
	else {
		printf("The second largest even number is : %d", secondLargest);
	}

	return;
}

void displayIntOccuranceJustinU(int *userAry, int size) {
	int *copyAry;
	int intOccurance = 0;
	int i, j;
	int temp;

	copyAry = (int*) malloc(size * sizeof(int));

	for (i = 0; i < size; i++) { 
		*(copyAry + i) = *(userAry + i);
	}

	for (i = 0; i < size; i++)	{  // bubble sorting copyAry
		for (j = 0; j < size-1; j++) {
			if (*(copyAry + j) > *(copyAry + (j+1)))	{
				temp = *(copyAry + (j+1));
				*(copyAry + (j+1)) = *(copyAry + j);
				*(copyAry + j) = temp;
			}
		}
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (*(copyAry + i) == *(copyAry + j)) 
				intOccurance++;	
		}

		if (*(copyAry + i) != *(copyAry + (i + 1))) {
			printf("%d", *(copyAry + i));
			printf(" occurs ");
			printf("%d", intOccurance);
			printf(" time(s)\n");	
		}

		intOccurance = 0;
	}

	free(copyAry);
}

void classInfo() {
	printf("\nCIS 27 - C Programming"\
		"\nLaney College "\
		"\nJustin Unverricht"\
		"\n"\
		"\nAssignment Informantion --"\
		"\n  Assignment Number:    Lab 02,"\
		"\n                        Coding Assignment -- Exercise #1"\
		"\n  Written by:           Justin Unverricht"\
		"\n  Submitted Date:       2/18/2014");
	return;
}

/**   Output

CIS 27 - C Programming
Laney College
Justin Unverricht

Assignment Informantion --
Assignment Number:    Lab 02,
Coding Assignment -- Exercise #1
Written by:           Justin Unverricht
Submitted Date:       2/18/2014

********************************************
*                  MENU                    *
* 1. Calling getSecondLargestEvenJustinU() *
* 2. Calling displayIntOccuranceJustinU()  *
* 3. Quit                                  *
********************************************
Enter Option : 7
You should not be in this class!
********************************************
*                  MENU                    *
* 1. Calling getSecondLargestEvenJustinU() *
* 2. Calling displayIntOccuranceJustinU()  *
* 3. Quit                                  *
********************************************
Enter Option : 2
How many elements would you like in your array?(integers only) :  7

Enter the numbers that you want for your array :
1
-2
24
-2
198
8
24

Calling displayIntOccuranceJustinU()
For the array with the elements shown below

1 -2 24 -2 198 8 24

-2 occurs 2 time(s)
1 occurs 1 time(s)
8 occurs 1 time(s)
24 occurs 2 time(s)
198 occurs 1 time(s)

********************************************
*                  MENU                    *
* 1. Calling getSecondLargestEvenJustinU() *
* 2. Calling displayIntOccuranceJustinU()  *
* 3. Quit                                  *
********************************************
Enter Option : 2
How many elements would you like in your array?(integers only) :  9

Enter the numbers that you want for your array :
-9
9
12
3
3
3
12
7
-10

Calling displayIntOccuranceJustinU()
For the array with the elements shown below

-9 9 12 3 3 3 12 7 -10

-10 occurs 1 time(s)
-9 occurs 1 time(s)
3 occurs 3 time(s)
7 occurs 1 time(s)
9 occurs 1 time(s)
12 occurs 2 time(s)

********************************************
*                  MENU                    *
* 1. Calling getSecondLargestEvenJustinU() *
* 2. Calling displayIntOccuranceJustinU()  *
* 3. Quit                                  *
********************************************
Enter Option : 3
Have fun.....
**/






