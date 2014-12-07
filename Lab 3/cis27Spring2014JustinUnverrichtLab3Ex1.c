/**
* Program Name: cis27Spring2014JustinULab3Ex1.c
* Date:  3/9/2014
* Written By:  Justin Unverricht
*/

#include <stdio.h>
#include <stdlib.h>

struct Fraction {
	int num;
	int denom;
};

typedef struct Fraction Fraction; 

// function prototypes    
Fraction* addFractionJustinU(Fraction*, Fraction*);
Fraction* subFractionJustinU(Fraction*, Fraction*);
Fraction* mulFractionJustinU(Fraction*, Fraction*);
Fraction* divFractionJustinU(Fraction*, Fraction*);
void initFractionJustinU(Fraction**);
void updateFractionJustinU(Fraction**);
void fracMenu(Fraction**, Fraction**);
void printFractionJustinU(Fraction*);
void printFractionJustinUInfo(Fraction*);
void menu();
void simplifyFractionJustinU(Fraction*);
void classInfo();
int gcd(int, int);


int main() {
	classInfo();
	printf("\n");
	menu();

	return 0;
}

// function definitions

void initFractionJustinU(Fraction **fracA) {
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

	if (denom < 0) {
		denom = -denom;
		num = -num; 
	}

	if (*fracA == NULL) {
		*fracA = (Fraction*) malloc(sizeof(struct Fraction));
	}
	(*fracA)->num = num;
	(*fracA)->denom = denom;

	simplifyFractionJustinU((*fracA));

	return;
}

Fraction* addFractionJustinU(Fraction *frac1, Fraction *frac2) {
	Fraction *frPtr = NULL;

	frPtr = (Fraction*) malloc(sizeof(struct Fraction));

	frPtr->num = (frac1->num * frac2->denom) + (frac2->num * frac1->denom);
	frPtr->denom = frac1->denom * frac2->denom;
	simplifyFractionJustinU(frPtr);
	return frPtr;
}

Fraction* subFractionJustinU(Fraction *frac1, Fraction *frac2) {
	Fraction *frPtr = NULL;

	frPtr = (Fraction*) malloc(sizeof(struct Fraction));

	frPtr->num = (frac1->num * frac2->denom) - (frac2->num * frac1->denom);
	frPtr->denom = frac1->denom * frac2->denom;
	simplifyFractionJustinU(frPtr);

	return frPtr;
}

Fraction* mulFractionJustinU(Fraction *frac1, Fraction *frac2) {
	Fraction *frPtr = NULL;

	frPtr = (Fraction*) malloc(sizeof(struct Fraction));

	frPtr->num = frac1->num * frac2->num;
	frPtr->denom = frac1->denom * frac2->denom;
	simplifyFractionJustinU(frPtr);

	return frPtr;
}

Fraction* divFractionJustinU(Fraction *frac1, Fraction *frac2) {
	Fraction *frPtr = NULL;

	frPtr = (Fraction*) malloc(sizeof(struct Fraction));

	if (frac2->num == 0) {
		printf("Undefined");
		frPtr->num = 1;
		frPtr->denom = 0;
	}
	else {
		frPtr->num = frac1->num * frac2->denom;
		frPtr->denom = frac1->denom * frac2->num;
		simplifyFractionJustinU(frPtr);
	}
	return frPtr;
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
	printf("%d", userFrac->num);
	printf("/");
	printf("%d", userFrac->denom);
	return;
}

void printFractionJustinUInfo(Fraction *userFrac) {
	printf("Address/Location : %p", userFrac);
	printf("\n");
	printf("Numerator : %d", userFrac->num);
	printf("\n");
	printf("Denominator : %d", userFrac->denom);
	return;
}

int gcd(int arg1, int arg2) { // recursive gcd function
	if (arg1 % arg2 == 0) 
		return arg2; 
	else 
		return gcd(arg2, arg1 % arg2);

} 

void menu() {
	Fraction* fracA = NULL;
	Fraction* fracB = NULL;
	Fraction* fracC = NULL;
	int menuSelect;
	int fractionInit = 0;

	do {
		printf("\n*******************************"\
			"\n*           MENU              *"\
			"\n* 1. Creating/Updating        *"\
			"\n* 2. Adding                   *"\
			"\n* 3. Subtracting              *"\
			"\n* 4. Multiplying              *"\
			"\n* 5. Dividing                 *"\
			"\n* 6. Displaying               *"\
			"\n* 7. Quit                     *"\
			"\n*******************************");
		printf("\n Enter Option : ");
		scanf_s("%d", &menuSelect);
		printf("\n");

		switch (menuSelect) {
		case 1:
			fracMenu(&fracA, &fracB);
			if (fracA != NULL && fracB != NULL)
				fractionInit = 1;

			break;

		case 2:
			if (fractionInit == 1) {
				if (fracC) 
					free(fracC);
				printFractionJustinU(fracA);
				printf(" + ");
				printFractionJustinU(fracB);
				printf(" = ");
				fracC = addFractionJustinU(fracA, fracB);
				printFractionJustinU(fracC);
			}
			else 
				printf("Not allowed yet - No proper data \n");
			break;

		case 3:
			if (fractionInit == 1) {
				if (fracC) 
					free(fracC);
				printFractionJustinU(fracA);
				printf(" - ");
				printFractionJustinU(fracB);
				printf(" = ");
				fracC = subFractionJustinU(fracA, fracB);
				printFractionJustinU(fracC);
			}
			else 
				printf("Not allowed yet - No proper data \n");

			break;

		case 4:
			if (fractionInit == 1) {
				if (fracC) 
					free(fracC);
				printFractionJustinU(fracA);
				printf(" * ");
				printFractionJustinU(fracB);
				printf(" = ");
				fracC = mulFractionJustinU(fracA, fracB);
				printFractionJustinU(fracC);
			}
			else 
				printf("Not allowed yet - No proper data \n");
			break;

		case 5:
			if (fractionInit == 1) {
				if (fracC) 
					free(fracC);
				printFractionJustinU(fracA);
				printf(" / ");
				printFractionJustinU(fracB);
				printf(" = ");
				fracC = divFractionJustinU(fracA, fracB);
				if (fracC->denom != 0)
					printFractionJustinU(fracC);
			}
			else 
				printf("Not allowed yet - No proper data \n");
			break;

		case 6:
			printf("The values of your fractions are : \n\n");

			if (fracA == NULL && fracB == NULL) {
				printf("Left Operand :\n");
				printf("Address/Location : NULL\n");

				printf("Right Operand :\n");
				printf("Address/Location : NULL\n");
				printf("\n");
			}

			else if (fracB == NULL) {
				printf("Left Operand :\n");
				printFractionJustinUInfo(fracA);
				printf("\n\n");

				printf("Right Operand :\n");
				printf("Address/Location : NULL\n");
				printf("\n");
			}

			else if (fracA == NULL) {
				printf("Left Operand :\n");
				printf("Address/Location : NULL\n");
				printf("\n\n");

				printf("Right Operand :\n");
				printFractionJustinUInfo(fracB);
				printf("\n");
			}

			else {
				printf("Left Operand :\n");
				printFractionJustinUInfo(fracA);
				printf("\n\n");

				printf("Right Operand :\n");
				printFractionJustinUInfo(fracB);
				printf("\n");
			}
			break;

		case 7:
			printf("Feel SOOOOO Great!\n");
			free(fracA);
			free(fracB);
			free(fracC);
			break;

		default:
			printf("You should not be in this class!\n");
			break;
		}

	} while (menuSelect != 7);
}

void fracMenu(Fraction** fracA, Fraction** fracB) {
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

void classInfo() {
	printf("\nCIS 27 - C Programming"\
		"\nLaney College "\
		"\nJustin Unverricht"\
		"\n"\
		"\nAssignment Informantion --"\
		"\n  Assignment Number:    Lab 03,"\
		"\n                        Coding Assignment -- Exercise #1"\
		"\n  Written by:           Justin Unverricht"\
		"\n  Submitted Date:       3/11/2014");

	return;
}

/** Output

CIS 27 - C Programming
Laney College
Justin Unverricht

Assignment Informantion --
Assignment Number:    Lab 03,
Coding Assignment -- Exercise #1
Written by:           Justin Unverricht
Submitted Date:       3/11/2014


*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 9

You should not be in this class!

*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 2

Not allowed yet - No proper data

*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 3

Not allowed yet - No proper data

*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 6

The values of your fractions are :

Left Operand :
Address/Location : NULL
Right Operand :
Address/Location : NULL


*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 1


*******************************
*  MENU : Creating/Updating  *
* 1. Left Operand             *
* 2. Right Operand            *
* 3. Both Operand             *
* 4. Display Current Operands *
* 5. Return                   *
*******************************
Enter Option : 1

Choose values for your fraction

Please choose your numerator : 3

Please choose your denominator : 4

Address/Location : 004D52C0
Numerator : 3
Denominator : 4
*******************************
*  MENU : Creating/Updating  *
* 1. Left Operand             *
* 2. Right Operand            *
* 3. Both Operand             *
* 4. Display Current Operands *
* 5. Return                   *
*******************************
Enter Option : 4

Left Operand :
Address/Location : 004D52C0
Numerator : 3
Denominator : 4

Right Operand :
Address/Location : NULL


*******************************
*  MENU : Creating/Updating  *
* 1. Left Operand             *
* 2. Right Operand            *
* 3. Both Operand             *
* 4. Display Current Operands *
* 5. Return                   *
*******************************
Enter Option : 5

Returning to Main Menu


*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 2

Not allowed yet - No proper data

*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 6

The values of your fractions are :

Left Operand :
Address/Location : 004D52C0
Numerator : 3
Denominator : 4

Right Operand :
Address/Location : NULL


*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 1


*******************************
*  MENU : Creating/Updating  *
* 1. Left Operand             *
* 2. Right Operand            *
* 3. Both Operand             *
* 4. Display Current Operands *
* 5. Return                   *
*******************************
Enter Option : 2

Choose values for your fraction

Please choose your numerator : 5

Please choose your denominator : 12

Address/Location : 004D52F8
Numerator : 5
Denominator : 12

*******************************
*  MENU : Creating/Updating  *
* 1. Left Operand             *
* 2. Right Operand            *
* 3. Both Operand             *
* 4. Display Current Operands *
* 5. Return                   *
*******************************
Enter Option : 4

Left Operand :
Address/Location : 004D52C0
Numerator : 3
Denominator : 4

Right Operand :
Address/Location : 004D52F8
Numerator : 5
Denominator : 12

*******************************
*  MENU : Creating/Updating  *
* 1. Left Operand             *
* 2. Right Operand            *
* 3. Both Operand             *
* 4. Display Current Operands *
* 5. Return                   *
*******************************
Enter Option : 5

Returning to Main Menu


*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 2

3/4 + 5/12 = 7/6
*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 3

3/4 - 5/12 = 1/3
*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 4

3/4 * 5/12 = 5/16
*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 5

3/4 / 5/12 = 9/5
*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 6

The values of your fractions are :

Left Operand :
Address/Location : 004152C0
Numerator : 3
Denominator : 4

Right Operand :
Address/Location : 004152F8
Numerator : 5
Denominator : 12


*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 1


*******************************
*  MENU : Creating/Updating  *
* 1. Left Operand             *
* 2. Right Operand            *
* 3. Both Operand             *
* 4. Display Current Operands *
* 5. Return                   *
*******************************
Enter Option : 3

Choose values for your left operand

Please choose your numerator : 2

Please choose your denominator : 11

Choose values for your right operand

Please choose your numerator : 5

Please choose your denominator : 101

Address/Location : 004152C0
Numerator : 2
Denominator : 11
Address/Location : 004152F8
Numerator : 5
Denominator : 101

*******************************
*  MENU : Creating/Updating  *
* 1. Left Operand             *
* 2. Right Operand            *
* 3. Both Operand             *
* 4. Display Current Operands *
* 5. Return                   *
*******************************
Enter Option : 5

Returning to Main Menu


*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 2

2/11 + 5/101 = 257/1111
*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 3

2/11 - 5/101 = 147/1111
*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 4

2/11 * 5/101 = 10/1111
*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 5

2/11 / 5/101 = 202/55
*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 6

The values of your fractions are :

Left Operand :
Address/Location : 004152C0
Numerator : 2
Denominator : 11

Right Operand :
Address/Location : 004152F8
Numerator : 5
Denominator : 101

*******************************
*           MENU              *
* 1. Creating/Updating        *
* 2. Adding                   *
* 3. Subtracting              *
* 4. Multiplying              *
* 5. Dividing                 *
* 6. Displaying               *
* 7. Quit                     *
*******************************
Enter Option : 7

Feel SOOOOO Great!
**/