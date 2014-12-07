/**
* Program Name: cis27Spring2014JustinUnverrichtLab6Ex1
* Date:  4/20/2014
* Written By:  Justin Unverricht
*/

#include <stdio.h>
#include <stdlib.h>

struct FractionJustinU {
	int num;
	int denom;
};

typedef struct FractionJustinU Fraction;

// polynomial stuff below

struct ExpressionTerm {
	struct FractionJustinU data;
	char op; 
};

typedef struct ExpressionTerm ExT; 
typedef ExT* ExTPtr;

struct ExpressionListNode {
	ExT term;
	struct ExpressionListNode* next;

};

typedef struct ExpressionListNode ExprNode;
typedef struct ExpressionListNode* ExprNodeAddr;
typedef struct ExpressionListNode* ExprList;
typedef ExprList* ExprListAddr;

// Stacks
struct ExpressionNodeStack { 
	int size;
	ExprNodeAddr top;
	ExprNodeAddr* next;
}; 

typedef struct ExpressionNodeStack Stack;

// fraction funtions
Fraction* initFractionJustinU();
void simplifyFractionJustinU(Fraction*);
void printFractionJustinU(Fraction);
int gcd(int, int);

// term functions
ExprNodeAddr createExperNode(int);
void insertLastJustinU(ExprNodeAddr, ExprList*);
void displayExperNodeJustinU(ExprNodeAddr);
void createInfix(ExprList*);
void inFixToPostFix(ExprList*, ExprList*, Stack);
void deleteListJustinU(ExprList);
void removeFirstJustinU(ExprList*);
ExprNodeAddr evaluate(ExprList*, Stack);
ExprNodeAddr addFractionJustinU(ExprNodeAddr, ExprNodeAddr);
ExprNodeAddr subFractionJustinU(ExprNodeAddr, ExprNodeAddr);
ExprNodeAddr mulFractionJustinU(ExprNodeAddr, ExprNodeAddr);
ExprNodeAddr divFractionJustinU(ExprNodeAddr, ExprNodeAddr);
int getListLengthJustinU(ExprList*);
int checkForNumbers(ExprList*);

//stack functions
void push (ExprNodeAddr, Stack*);
ExprNodeAddr pop (Stack*);

// menus & misc
void menu();
void classInfo();


main() {
	classInfo();
	printf("\n");
	menu();

	return 0;
}

// fraction Functions
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

void printFractionJustinU(Fraction userFrac) {
	printf("%d",userFrac.num);
	printf("/");
	printf("%d", userFrac.denom);
	return;
}

// term functions

ExprNodeAddr createExperNode(int choice) {
	ExprNodeAddr newNode;
	ExT tmpPtr;
	int num, denom, goodSign;
	char sign;

	goodSign = 0;


	if (choice) {
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

		tmpPtr.data.num = num;
		tmpPtr.data.denom = denom;

		simplifyFractionJustinU(&tmpPtr.data);
		tmpPtr.op = '\0';
	}
	else {
		printf("Please choose your operator  + - * / ( ) only!  : ");
		scanf(" %c", &sign);

		do {
			switch (sign) {

			case '+':
				tmpPtr.op = sign;
				goodSign = 1;
				break;

			case '-' :
				tmpPtr.op = sign;
				goodSign = 1;
				break;

			case '*' :
				tmpPtr.op = sign;
				goodSign = 1;
				break;

			case '/' :
				tmpPtr.op = sign;
				goodSign = 1;
				break;

			case '(' :
				tmpPtr.op = sign;
				goodSign = 1;
				break;

			case ')' :
				tmpPtr.op = sign;
				goodSign = 1;
				break;

			default :
				printf("Please only choose + - / * ( ) all other signs are not acceptable\n");
				printf("Please choose your operator  + - * / ( ) only!  : ");
				scanf(" %c", &sign);
				break;
			} 
		} while (goodSign != 1);

		tmpPtr.data.num = 0;
		tmpPtr.data.denom = 0;
	}

	newNode = (struct ExpressionListNode*) malloc(sizeof(struct ExpressionListNode));

	newNode->term = tmpPtr;
	newNode->next = NULL;

	return newNode;
}

void insertLastJustinU(ExprNodeAddr newNode, ExprList* userList) {  
	// sets temp to address of IntList and checks for empty node.
	ExprNodeAddr tmpPtr;

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

void displayExperNodeJustinU(ExprList userNode) { 
	ExprNodeAddr nodePtr;

	if (userNode) {
		nodePtr = userNode;
		while (nodePtr) {
			if ((*nodePtr).term.data.denom != 0) {
				printFractionJustinU((*nodePtr).term.data);
				printf(" ");
			}
			else {
				printf("%c",(*nodePtr).term.op);
				printf(" ");
			}

			nodePtr = nodePtr->next;
		}
		printf("\n");
	}

	else
		printf("\nEMPTY LIST ...!\n");

	return;
}

void createInfix(ExprList* userList) {
	int userChoice, flag;
	char nextTerm;

	printf("Lets create your Expression!\n\n");
	do {
		flag = 0;

		printf("Is your input a number or operand? (select 1 for number, 2 for opperand) : ");
		scanf(" %d", &userChoice);
		printf("\n");

		if (userChoice == 1) {
			insertLastJustinU(createExperNode(1), userList);
		}
		else {
			insertLastJustinU(createExperNode(0), userList);
		}

		printf("\nContinue creating your expression? (choose y or n) : ");
		scanf(" %c" , &nextTerm);
		printf("\n");
		if (nextTerm == 'y' || nextTerm == 'Y')
			continue;
		else if (nextTerm == 'n' || nextTerm == 'N')
			flag = 1;
		else {
			printf("please choose only y or n\n");
			printf("\nContinue creating your expression? (choose y or n) : ");
			scanf(" %c", &userChoice);
			if (userChoice == 'n' || userChoice == 'N')
				flag = 1;
		}

	} while (flag !=1);
	return;
}

void inFixToPostFix(ExprList* inFix, ExprList* postFix, Stack oppStack) {
	ExprNodeAddr temp, node, burner;
	temp = *inFix;

	while (temp) {
		if (temp->term.op == '\0') {
			node = (struct ExpressionListNode*) malloc(sizeof(struct ExpressionListNode));

			node->term = temp->term;
			node->next = NULL;
			insertLastJustinU(node, postFix);
			temp = temp->next;
		}
		else {
			if (oppStack.size == 0) {
				push(temp, &oppStack);
			}
			else if (temp->term.op == '(') {
				push(temp, &oppStack);
			}
			else if (oppStack.top->term.op == '(') {
				push(temp, &oppStack);
			}
			else if (temp->term.op == ')') {
				while (oppStack.top->term.op != '(') {
					insertLastJustinU(pop(&oppStack), postFix);
				}
				burner = pop(&oppStack);
				free(burner);
			}
			else {
				insertLastJustinU(pop(&oppStack), postFix);
				push(temp, &oppStack);
			}
			temp = temp->next;
		}
	}

	while (oppStack.size != 0) {
		insertLastJustinU(pop(&oppStack), postFix);
	}
	return;
}

void deleteListJustinU(ExprList userList) {
	int listLen, i;

	listLen = getListLengthJustinU(&userList);

	for (i = 0; i < listLen; i++) {
		removeFirstJustinU(&userList);
	}

	free(userList);

	return;
}

void removeFirstJustinU(ExprList* userNode) {
	ExprNodeAddr tmpPtr = NULL;

	if (userNode) {
		tmpPtr = *userNode;
		*userNode = tmpPtr->next;
		free(tmpPtr);
	} 

	return;
}

ExprNodeAddr evaluate(ExprList* postFix, Stack evalStack) {
	ExprNodeAddr temp, left, right;
	char opperator;
	int evaluated;
	temp = *postFix;

	while (temp) {
		if (temp->term.op == '\0') {
			push(temp, &evalStack);
			temp = temp->next;
		}
		else {
			opperator = temp->term.op;
			evaluated = 0;
			do {
				switch (opperator) {

				case '+':
					left = pop(&evalStack);
					right = pop(&evalStack);
					push(addFractionJustinU(left, right), &evalStack);
					free(left);
					free(right);
					evaluated = 1;
					break;

				case '-' :
					left = pop(&evalStack);
					right = pop(&evalStack);
					push(subFractionJustinU(left, right), &evalStack);
					free(left);
					free(right);
					evaluated = 1;
					break;

				case '*' :
					left = pop(&evalStack);
					right = pop(&evalStack);
					push(mulFractionJustinU(left, right), &evalStack);
					free(left);
					free(right);
					evaluated = 1;
					break;

				case '/' :
					left = pop(&evalStack);
					right = pop(&evalStack);
					push(divFractionJustinU(left, right), &evalStack);
					free(left);
					free(right);
					evaluated = 1;
					break;

				default :
					printf("Hail Hydra!\n");
					break;
				} 
			} while (evaluated != 1);
			temp = temp->next;
		}
	}
	return pop(&evalStack);
}

ExprNodeAddr addFractionJustinU(ExprNodeAddr left, ExprNodeAddr right) {
	ExprNodeAddr result;

	result = (struct ExpressionListNode*) malloc(sizeof(struct ExpressionListNode));
	result->term.op = '\0';

	result->term.data.num = (left->term.data.num * right->term.data.denom) +
		(right->term.data.num * left->term.data.denom);

	result->term.data.denom = left->term.data.denom * right->term.data.denom;
	simplifyFractionJustinU(&result->term.data);
	return result;
}

ExprNodeAddr subFractionJustinU(ExprNodeAddr left, ExprNodeAddr right) {
	ExprNodeAddr result;

	result = (struct ExpressionListNode*) malloc(sizeof(struct ExpressionListNode));
	result->term.op = '\0';

	result->term.data.num = (right->term.data.num * left->term.data.denom) -
		(left->term.data.num * right->term.data.denom);

	result->term.data.denom = left->term.data.denom * right->term.data.denom;
	simplifyFractionJustinU(&result->term.data);
	return result;
}

ExprNodeAddr mulFractionJustinU(ExprNodeAddr left, ExprNodeAddr right) {
	ExprNodeAddr result;

	result = (struct ExpressionListNode*) malloc(sizeof(struct ExpressionListNode));
	result->term.op = '\0';

	result->term.data.num = (left->term.data.num * right->term.data.num);
	result->term.data.denom = left->term.data.denom * right->term.data.denom;
	simplifyFractionJustinU(&result->term.data);
	return result;
}

ExprNodeAddr divFractionJustinU(ExprNodeAddr left, ExprNodeAddr right) {
	ExprNodeAddr result;

	result = (struct ExpressionListNode*) malloc(sizeof(struct ExpressionListNode));
	result->term.op = '\0';

	if (right->term.data.num == 0) {
		result->term.data.num = 0;
		result->term.data.denom = 0;
	}
	else {
		result->term.data.num = (right->term.data.num * left->term.data.denom);
		result->term.data.denom = (right->term.data.denom * left->term.data.num);
		simplifyFractionJustinU(&result->term.data);
	}
	return result;
}

int getListLengthJustinU(ExprList* userList) {
	ExprNodeAddr tmpPtr;
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

int checkForNumbers(ExprList* userList) {
	ExprNodeAddr tmpPtr;
	int count = 0;
	if ((*userList) == NULL)
		count = 0;
	else {
		tmpPtr = (*userList);
		if (tmpPtr->term.op == '\0') {
			count++;
			tmpPtr = tmpPtr->next;
		}
		else {
			tmpPtr = tmpPtr->next;
		}
	}
	return count;
}

// stack functions
void push(ExprNodeAddr node, Stack* oppStack) {
	ExprNodeAddr tmpPtr;

	tmpPtr = (struct ExpressionListNode*) malloc(sizeof(struct ExpressionListNode));

	tmpPtr->term = node->term;
	tmpPtr->next = NULL;

	if (oppStack->top) {
		tmpPtr->next = oppStack->top;
	}
	oppStack->top = tmpPtr;
	oppStack->size++; 
}

ExprNodeAddr pop (Stack* oppStack) {
	ExprNodeAddr temp, pop;
	pop = NULL;

	if (oppStack->size == 0) {
		printf("Empty Stack!\n");
	}
	else {
		pop = (struct ExpressionListNode*) malloc(sizeof(struct ExpressionListNode));
		pop->term = oppStack->top->term;
		pop->next = NULL;

		temp = oppStack->top;
		if (temp)
			oppStack->top = temp->next;
		free(temp);
		oppStack->size--;
	}
	return pop;
}

// menus & misc functions

void menu() {
	ExprList inFix, postFix;
	Stack oppStack;
	ExprNodeAddr result = NULL;
	int menuSelect, created;

	created = 0;
	inFix = NULL;
	postFix = NULL;
	oppStack.next = NULL;
	oppStack.top = NULL;
	oppStack.size = 0;

	do {
		printf("\n*******************************"\
			"\n*           MENU              *"\
			"\n* 1. Creating/Updating Infix  *"\
			"\n* 2. Converting to Postfix    *"\
			"\n* 3. Displaying Infix         *"\
			"\n* 4. Displaying PostFix       *"\
			"\n* 5. Evauluating Expression   *"\
			"\n* 6. Quit                     *"\
			"\n*******************************");
		printf("\n Enter Option : ");
		scanf_s("%d", &menuSelect);
		printf("\n");

		switch (menuSelect) {
		case 1:
			if (created == 0) {
				createInfix(&inFix);
				created = 1;
			}
			else {
				printf("Lets Create a new Infix expression shall we?\n\n");

				if (result)
					free(result);

				if (postFix) {
					deleteListJustinU(postFix);
					postFix = NULL;
				}

				deleteListJustinU(inFix);
				inFix = NULL;
				createInfix(&inFix);
			}
			break;

		case 2:		
			if (!inFix) {
				printf("Please create an Infix expression first or millions of 0's and 1's will starve tonight!\n");
			}
			else {
				if (postFix) {
					deleteListJustinU(postFix);
					postFix = NULL;
				}
				printf("Converting Infix to Postfix \n");
				inFixToPostFix(&inFix, &postFix, oppStack);
			}
			break;

		case 3:
			if (!inFix) {
				printf("Please create an Infix expression first, or the communists win.....\n");
			}
			else {
				displayExperNodeJustinU(inFix);
			}
			break;

		case 4:
			if (!postFix) {
				printf("Please convert a Infix expression to PostFix first! \n");
			}
			else {
				displayExperNodeJustinU(postFix);
			}
			break;

		case 5:
			if (!postFix) {
				printf("Please convert a Infix expression to PostFix first! Then the magic can happen.\n");
			}
			else {
				if (checkForNumbers(&postFix) == 0) {
					printf("I'm sorry but you dont have an expression with any numbers!\n");
				}
				else {
					result = evaluate(&postFix, oppStack);
					if (result->term.data.denom == 0) {
						printf("I'm sorry but your expression is is undefined, perhapse l'hopital can help you\n");
					}
					else {
						printf("The expression evaluates as : ");
						printf("%d/%d\n", result->term.data.num, result->term.data.denom);
						printf("\n");
					}
				}
			}
			break;

		case 6:
			printf("Having Fun!\n\n");
			break;

		default :
			printf("You should not be in this class!\n\n");
			break;

		}
	} while (menuSelect != 6);

	if (inFix) {
		deleteListJustinU(inFix);
		inFix = NULL;
	}

	if (postFix) {
		deleteListJustinU(postFix);
		postFix = NULL;
	}

	if (result) 
		free(result);

}

void classInfo() {
	printf("\nCIS 27 - C Programming"\
		"\nLaney College "\
		"\nJustin Unverricht"\
		"\n"\
		"\nAssignment Informantion --"\
		"\n  Assignment Number:    Lab 06,"\
		"\n                        Coding Assignment -- Exercise #1"\
		"\n  Written by:           Justin Unverricht"\
		"\n  Submitted Date:       4/29/2014");

	return;
}

// output

/*
CIS 27 - C Programming
Laney College
Justin Unverricht

Assignment Informantion --
  Assignment Number:    Lab 06,
                        Coding Assignment -- Exercise #1
  Written by:           Justin Unverricht
  Submitted Date:       4/29/2014

*******************************
*           MENU              *
* 1. Creating/Updating Infix  *
* 2. Converting to Postfix    *
* 3. Displaying Infix         *
* 4. Displaying PostFix       *
* 5. Evauluating Expression   *
* 6. Quit                     *
*******************************
Enter Option : 1

Lets create your Expression!

Is your input a number or operand? (select 1 for number, 2 for opperand) : 1

Please choose your numerator : 2

Please choose your denominator : 1

Continue creating your expression? (choose y or n) : y

Is your input a number or operand? (select 1 for number, 2 for opperand) : 2

Please choose your operator  + - * / ( ) only!  : +

Continue creating your expression? (choose y or n) : y

Is your input a number or operand? (select 1 for number, 2 for opperand) : 1

Please choose your numerator : 3

Please choose your denominator : 1

Continue creating your expression? (choose y or n) : y

Is your input a number or operand? (select 1 for number, 2 for opperand) : 2

Please choose your operator  + - * / ( ) only!  : -

Continue creating your expression? (choose y or n) : y

Is your input a number or operand? (select 1 for number, 2 for opperand) : 1

Please choose your numerator : 5

Please choose your denominator : 1

Continue creating your expression? (choose y or n) : n

*******************************
*           MENU              *
* 1. Creating/Updating Infix  *
* 2. Converting to Postfix    *
* 3. Displaying Infix         *
* 4. Displaying PostFix       *
* 5. Evauluating Expression   *
* 6. Quit                     *
*******************************
Enter Option : 3

2/1 + 3/1 - 5/1

*******************************
*           MENU              *
* 1. Creating/Updating Infix  *
* 2. Converting to Postfix    *
* 3. Displaying Infix         *
* 4. Displaying PostFix       *
* 5. Evauluating Expression   *
* 6. Quit                     *
*******************************
Enter Option : 2

Converting Infix to Postfix

*******************************
*           MENU              *
* 1. Creating/Updating Infix  *
* 2. Converting to Postfix    *
* 3. Displaying Infix         *
* 4. Displaying PostFix       *
* 5. Evauluating Expression   *
* 6. Quit                     *
*******************************
Enter Option : 4

2/1 3/1 + 5/1 -

*******************************
*           MENU              *
* 1. Creating/Updating Infix  *
* 2. Converting to Postfix    *
* 3. Displaying Infix         *
* 4. Displaying PostFix       *
* 5. Evauluating Expression   *
* 6. Quit                     *
*******************************
Enter Option : 5

The expression evaluates as : 0/1

*******************************
*           MENU              *
* 1. Creating/Updating Infix  *
* 2. Converting to Postfix    *
* 3. Displaying Infix         *
* 4. Displaying PostFix       *
* 5. Evauluating Expression   *
* 6. Quit                     *
*******************************
Enter Option : 7

You should not be in this class!

*******************************
*           MENU              *
* 1. Creating/Updating Infix  *
* 2. Converting to Postfix    *
* 3. Displaying Infix         *
* 4. Displaying PostFix       *
* 5. Evauluating Expression   *
* 6. Quit                     *
*******************************
Enter Option : 6

Having Fun!
*/
