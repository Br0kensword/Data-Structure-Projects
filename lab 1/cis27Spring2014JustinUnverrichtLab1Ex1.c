/**
* Project Name : cis27spring2014JustinUproject1
* Date : 1/29/2014
* Written by : Justin Unverricht
**/

#include <stdio.h> 
#include <stdlib.h>

//Function Definitions
int getSecondLargestJustinU(int*, int);
void Menu();
void classInfo();

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
			"\n*                  MENU 01                 *"\
			"\n* 1. Calling getSecondLargestEvenJustinU() *"\
			"\n* 2. Quit                                  *"\
			"\n********************************************");
		printf("\n Enter Option : ");
		scanf_s("%d", &menuSelect);

		switch (menuSelect) {
		case 1:
			do {
				printf("Enter how many elements you would like in your array :  ");
				scanf_s("%d",&numberOfInt);
				printf("\n");

				if(numberOfInt <= 0)
					printf("Please enter a value larger than 0 \n");
			} while(numberOfInt <= 0);

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
			printf("Have fun.....\n");
			break;

		default:
			printf("You should not be in this class!");
			break;
		}

	} while(menuSelect != 2);

}

int getSecondLargestJustinU(int* userAry, int size) {
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

	return 0;
}

void classInfo() {
	printf("\nCIS 27 - C Programming"\
		"\nLaney College "\
		"\nJustin Unverricht"\
		"\n"\
		"\nAssignment Informantion --"\
		"\n  Assignment Number:    Lab 01,"\
		"\n                        Coding Assignment -- Exercise #1"\
		"\n  Written by:           Justin Unverricht"\
		"\n  Submitted Date:       2/6/2014");
}


//Output
/**

CIS 27 - C Programming
Laney College
Justin Unverricht

Assignment Informantion --
  Assignment Number:    Lab 01,
                        Coding Assignment -- Exercise #1
  Written by:           Justin Unverricht
  Submitted Date:       2/6/2014

********************************************
*                  MENU 01                 *
* 1. Calling getSecondLargestEvenJustinU() *
* 2. Quit                                  *
********************************************
 Enter Option : 7
You should not be in this class!
********************************************
*                  MENU 01                 *
* 1. Calling getSecondLargestEvenJustinU() *
* 2. Quit                                  *
********************************************
 Enter Option : -7
You should not be in this class!
********************************************
*                  MENU 01                 *
* 1. Calling getSecondLargestEvenJustinU() *
* 2. Quit                                  *
********************************************
 Enter Option : 1
Enter how many elements you would like in your array :  4

Enter the numbers that you want for your array :
123
456
-7890
12

Calling getSecondLargestEvenJustinU() --
For the array with the elements shown below

123 456 -7890 12
The second largest even number is : 12
********************************************
*                  MENU 01                 *
* 1. Calling getSecondLargestEvenJustinU() *
* 2. Quit                                  *
********************************************
 Enter Option : 9
You should not be in this class!
********************************************
*                  MENU 01                 *
* 1. Calling getSecondLargestEvenJustinU() *
* 2. Quit                                  *
********************************************
 Enter Option : 1
Enter how many elements you would like in your array :  2

Enter the numbers that you want for your array :
9
9

Calling getSecondLargestEvenJustinU() --
For the array with the elements shown below

9 9

The second largest even number is :   -1999999999


********************************************
*                  MENU 01                 *
* 1. Calling getSecondLargestEvenJustinU() *
* 2. Quit                                  *
********************************************
 Enter Option : 1
Enter how many elements you would like in your array :  7

Enter the numbers that you want for your array :
123
24
4561
-789
241
1
-3

Calling getSecondLargestEvenJustinU() --
For the array with the elements shown below

123 24 4561 -789 241 1 -3
The second largest even number is : -1999999999

********************************************
*                  MENU 01                 *
* 1. Calling getSecondLargestEvenJustinU() *
* 2. Quit                                  *
********************************************
 Enter Option : 2
Have fun.....
**/