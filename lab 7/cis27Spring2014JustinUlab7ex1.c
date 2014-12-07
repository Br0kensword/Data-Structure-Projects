/**
* Program Name: cis27Spring2014JustinULab7Ex1.c
* Discussion: Trees
* Written by: Justin Unverricht

*/

#include <stdio.h>
#include <stdlib.h>

//Fractions
struct FractionJustinU {
	int num;
	int denom;
};

typedef struct FractionJustinU Fraction;

//Trees
struct Tree { 
	Fraction value;
	struct Tree* left;
	struct Tree* right;
	struct Tree* parent;
};

typedef struct Tree* TreeNode;
typedef struct Tree* TreeRoot;

// Stacks
struct TreeNodeStack { 
	int size;
	TreeNode top;
	TreeNode* next;
}; 

typedef struct TreeNodeStack Stack;

//Fraction Functions
void simplifyFractionJustinU(Fraction*);
void printFractionJustinU(Fraction);
int gcd(int, int);
int compareFrac(Fraction, Fraction);

// Tree functions
TreeNode createNode();
TreeNode findMinNode(TreeRoot);
void insert(TreeNode, TreeRoot*);
TreeNode find(Fraction, TreeRoot);
void removeNode(Fraction, TreeRoot*);
void removeUtil(TreeNode);
void preOrder(TreeRoot*, Stack);
void inOrder(TreeRoot*, Stack);
void postOrder(TreeRoot*, Stack, Stack);
void deleteTree(TreeRoot*);

// Stack Functions
void push (TreeNode, Stack*);
TreeNode pop (Stack*);

//Misc functions
void menu();
void classInfo();

int main() {
	classInfo();
	printf("\n");
	menu();
	return 0;
}
//Fraction Functions
int gcd(int arg1, int arg2) { // recursive gcd function
	if (arg1 % arg2 == 0) {
		return arg2; 
	}
	else {
		return gcd(arg2, arg1 % arg2);
	}
} 

int compareFrac(Fraction fracA, Fraction fracB) { //compares the sizes of fractions to determin place in tree
	int result;

	if ((fracA.num * fracB.denom) < (fracB.num * fracA.denom))
		result = 0; //b is bigger
	else if ((fracA.num * fracB.denom) > (fracB.num * fracA.denom))
		result = 1; //a is bigger
	else // are the same
		result = 2;
	return result;
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

//Tree Functions
TreeNode createNode() {
	TreeNode newNode;
	Fraction tmpPtr;
	int num, denom;


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

	tmpPtr.num = num;
	tmpPtr.denom = denom;

	simplifyFractionJustinU(&tmpPtr);

	newNode = (struct Tree*) malloc(sizeof(struct Tree));

	newNode->value = tmpPtr;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;

	return newNode;
}

TreeNode findMin(TreeRoot userTree) {
	TreeNode temp;
	temp = userTree;
	while (temp->left) {
		temp = temp->left;
	}

	return temp;
}

TreeNode find(Fraction value, TreeRoot userTree) {
	TreeNode temp;
	int found;
	temp = userTree;
	found = 0;

	while (temp) {
		if (compareFrac(value, temp->value) == 2) {
			found = 1;
			break;
		}
		else if (compareFrac(value, temp->value) == 1) 
			temp = temp->right;
		else 
			temp = temp->left;
	}

	if (found == 1) 
		printf("Yes your value is in the tree\n");
	else {
		printf("Sorry that value is not in the tree\n");
		temp = NULL;
	}
	return temp;
}

void createBST(TreeRoot* userList) {
	int flag;
	char userChoice, nextTerm;

	printf("Lets create your Tree!\n\n");
	do {
		flag = 0;

		insert(createNode(), userList);

		printf("\nContinue inserting into tree? (choose y or n) : ");
		scanf(" %c" , &nextTerm);
		printf("\n");
		if (nextTerm == 'y' || nextTerm == 'Y')
			continue;
		else if (nextTerm == 'n' || nextTerm == 'N')
			flag = 1;
		else {
			printf("please choose only y or n\n");
			printf("\nContinue inserting into tree? (choose y or n) : ");
			scanf(" %c", &userChoice);
			if (userChoice == 'n' || userChoice == 'N')
				flag = 1;
		}

	} while (flag !=1);

	return;
}

void insert(TreeNode newNode, TreeRoot* tree) {
	TreeNode temp;
	int fracSize;

	if (*tree == NULL) {
		*tree = newNode; 
	}
	else {
		temp = *tree;

		while (temp != NULL){
			fracSize = compareFrac(newNode->value, temp->value);
			if (fracSize == 0) {
				if (temp->left) {
					temp = temp->left;
				}
				else {
					temp->left = newNode;
					newNode->parent = temp;
					break;
				}
			} 
			else if (fracSize == 1) {
				if (temp->right) {
					temp = temp->right;

				}
				else {
					temp->right = newNode;
					newNode->parent = temp;
					break;
				}
			}
			else {
				printf("\nDuplicate value found!\n");
				break;
			}
		}
	} 
	return;

}

void removeNode(Fraction value, TreeRoot* userTree) {
	TreeNode target, parent, min;

	target = find(value, *userTree);

	if (!target)
		printf("your value is not in the tree\n");
	else {
		if (target->parent) {
		if (!target->left && !target->right) { //target is leaf node
			parent = target->parent;
			target->value.denom = 0;
			if (parent->left->value.denom == 0)
				parent->left = NULL;
			else
				parent->right = NULL;
			free(target);
		}
		else if (!target->left || !target->right) { // one child
			parent = target->parent;
			target->value.denom = 0;
			if (parent->left->value.denom == 0){
				if(target->left)
					parent->left = target->left;
				else
					parent->left = target->right;
			}
			else
				if(target->left)
					parent->right = target->left;
				else
					parent->right = target->right;
			free(target);
		}	
		else if (target->left && target->right && target->parent != NULL) { //2 childs but not root
			parent = target->parent;
			target->value.denom = 0;
			if (parent->left->value.denom == 0){
				parent->left = target->right;
				target->right->left = target->left;
			}
			else {
				parent->right = target->right;
				target->right->left = target->left;
			}
			free(target);
		}
		}
		else { // target is root
			if (target->right) {
			min = target->right;
			while (min->left) {
				min = min->left;
			}
			min->left = target->left;
			*userTree = target->right;
			target->right->parent = NULL;
			free(target);
			if (!(*userTree)->right) 
				(*userTree)->right = NULL;
			}
			else {
				*userTree = target->left;
				free(target);
			}
		}
		
	}


	printf("Value Removed\n");
	return;
}

void preOrder(TreeRoot* userTree, Stack stack) {
	TreeNode temp;

	if (userTree) {
		push(*userTree, &stack);
		temp = stack.top;
		while(stack.size != 0) {
			printFractionJustinU(temp->value);
			printf(" ");

			if (temp->right)
				push(temp->right, &stack);
			if (temp->left)
				push(temp->left, &stack);

			free(temp);
			temp = pop(&stack);
		}
	}
	else {
		printf("Empty Tree!");
	}

	return;
}

void inOrder(TreeRoot* userTree, Stack stack) {
	TreeNode temp;
	temp = *userTree;

	while(stack.size != 0 || temp) {
		if (temp) {
			push(temp, &stack);
			temp = temp->left;
		}
		else {
			temp = pop(&stack);
			printFractionJustinU(temp->value);
			printf(" ");
			temp = temp->right;
		}
	}
	return;
}

void postOrder(TreeRoot* userTree, Stack stackA, Stack stackB) {
	TreeNode temp, visitedNode, burner;
	burner = NULL;
	temp = *userTree;
	push(temp, &stackA);

	while (stackA.size != 0) {
		visitedNode = pop(&stackA);
		push(visitedNode, &stackB);

		if (visitedNode->left)
			push(visitedNode->left, &stackA);
		if (visitedNode->right)
			push(visitedNode->right, &stackA);
	}

	while (stackB.size != 0) {
		burner = pop(&stackB);
		printFractionJustinU(burner->value);
		printf(" ");
		free(burner);
	}
	return;
}

void deleteTree(TreeRoot* userTree) {
	TreeNode target, parent, min;
	target = *userTree;
	
	while (*userTree) {
	if (!target->left && !target->right) { //target is leaf node
		if (target->parent) {
			parent = target->parent;
			target->value.denom = 0;
			if (parent->left->value.denom == 0) 
				parent->left = NULL;
			else
				parent->right = NULL;
			free(target);
		}
		else {
			free(target);
			*userTree = NULL;
		}
		}
	else {  //deleting right branch first then left
			if (target->right) { 
			min = target->right;
			while (min->left) {
				min = min->left;
			}
			min->left = target->left;
			*userTree = target->right;
			target->right->parent = NULL;
			free(target);
			}
			else {
				*userTree = target->left;
				if (!(*userTree)->left && !(*userTree)->right) 
					(*userTree)->parent = NULL;
				free(target);
			}
		}
	target = *userTree;
}
}

//Stack Functions
void push(TreeNode node, Stack* oppStack) {
	TreeNode tmpPtr;

	tmpPtr = (struct Tree*) malloc(sizeof(struct Tree));

	tmpPtr->value= node->value;
	tmpPtr->left = node->left;
	tmpPtr->right = node->right;
	tmpPtr->parent = NULL;

	if (oppStack->top) {
		tmpPtr->parent = oppStack->top; //changed this to parent from left
	}
	oppStack->top = tmpPtr;
	oppStack->size++; 
}

TreeNode pop (Stack* oppStack) {
	TreeNode temp, pop;
	pop = NULL;

	if (oppStack->size == 0) {
		printf("Empty Stack!\n");
	}
	else {
		pop = (struct Tree*) malloc(sizeof(struct Tree));
		pop->value = oppStack->top->value;
		pop->left = oppStack->top->left;
		pop->right = oppStack->top->right;
		pop->parent = oppStack->top->parent;

		temp = oppStack->top;
		if (temp)
			oppStack->top = temp->parent;
		free(temp);
		oppStack->size--;
	}
	return pop;
}

// Misc Functions
void menu() {
	TreeRoot spiritTree = NULL;
	Fraction searchValue;
	Stack mainStack, helperStack;
	int menuSelect, num, denom;
	char userChoice;

	mainStack.next = NULL;
	mainStack.top = NULL;
	mainStack.size = 0;

	helperStack.next = NULL;
	helperStack.top = NULL;
	helperStack.size = 0;

	do {
		printf("\n*******************************"\
			"\n*           MENU              *"\
			"\n* 1. Insert Value             *"\
			"\n* 2. Display Tree             *"\
			"\n* 3. Search Tree              *"\
			"\n* 4. Remove Node              *"\
			"\n* 5. Get & Display Smallest   *"\
			"\n* 6. Quit                     *"\
			"\n*******************************");
		printf("\n Enter Option : ");
		scanf_s("%d", &menuSelect);
		printf("\n");

		switch (menuSelect) {
		case 1:
			if (spiritTree == NULL) 
				createBST(&spiritTree);
			else {
				printf("\nCreate a new tree? Old tree will be chopped down(choose y or n) : ");
				scanf(" %c" , &userChoice);
				printf("\n");
				if (userChoice== 'y' || userChoice == 'Y') {
					deleteTree(&spiritTree);
					spiritTree = NULL;
					createBST(&spiritTree);
				}
				else if (userChoice == 'n' || userChoice == 'N') {
					printf("Inserting new value\n");
					createBST(&spiritTree);
				}
				else {
					printf("please choose only y or n\n");
					printf("\nContinue creating your expression? (choose y or n) : ");
					scanf(" %c", &userChoice);
					if (userChoice == 'n' || userChoice == 'N')
						createBST(&spiritTree);
				}
			}
			break;

		case 2:		
			if (spiritTree) {
			printf("Printing pre-order\n");
			preOrder(&spiritTree, mainStack);
			printf("\nPrinting in-order\n");
			inOrder(&spiritTree, mainStack);
			printf("\nPrinting post-order\n");
			postOrder(&spiritTree, mainStack, helperStack);
			}
			else {
				printf("Empty Tree!!\n");
			}
			printf("\n");
			break;

		case 3:
			if (spiritTree) {
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
				searchValue.num = num;
				searchValue.denom = denom;
				simplifyFractionJustinU(&searchValue);

				find(searchValue, spiritTree);
			}
			else {
				printf("Empty Tree!!\n");
			}
			printf("\n");
			break;

		case 4:
			if (spiritTree) {
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
				searchValue.num = num;
				searchValue.denom = denom;
				simplifyFractionJustinU(&searchValue);
				removeNode(searchValue, &spiritTree);
			}
			else {
				printf("Empty Tree!!\n");
			}
			printf("\n");
			break;

		case 5:
			if (spiritTree) {
				printf("finding smallest node\n");
				printFractionJustinU(findMin(spiritTree)->value);
			}
			else
				printf("Empty Tree\n");
			break;

		case 6:
			printf("I think that I shall never see\n"
    				"A billboard lovely as a tree.\n"
					"Indeed, unless the billboards fall,\n"
					"I'll never see a tree at all.\n"
					"      -- Joyce Kilmer\n\n");
			deleteTree(&spiritTree);
			spiritTree = NULL;
			break;

		default :
			printf("You should not be in this class!\n\n");
			break;
		}
	} while (menuSelect != 6);
}

void classInfo() {
	printf("\nCIS 27 - C Programming"\
		"\nLaney College "\
		"\nJustin Unverricht"\
		"\n"\
		"\nAssignment Informantion --"\
		"\n  Assignment Number:    Lab 07,"\
		"\n                        Coding Assignment -- Exercise #1"\
		"\n  Written by:           Justin Unverricht"\
		"\n  Submitted Date:       5/13/2014");

	return;
}

/* Output
	
CIS 27 - C Programming
Laney College
Justin Unverricht

Assignment Informantion --
  Assignment Number:    Lab 07,
                        Coding Assignment -- Exercise #1
  Written by:           Justin Unverricht
  Submitted Date:       5/13/2014

*******************************
*           MENU              *
* 1. Insert Value             *
* 2. Display Tree             *
* 3. Search Tree              *
* 4. Remove Node              *
* 5. Get & Display Smallest   *
* 6. Quit                     *
*******************************
 Enter Option : 1

Lets create your Tree!


Please choose your numerator : 50

Please choose your denominator : 1

Continue inserting into tree? (choose y or n) : y

Please choose your numerator : 25

Please choose your denominator : 1

Continue inserting into tree? (choose y or n) : y

Please choose your numerator : 75

Please choose your denominator : 1

Continue inserting into tree? (choose y or n) : y

Please choose your numerator : 10

Please choose your denominator : 1

Continue inserting into tree? (choose y or n) : y

Please choose your numerator : 45

Please choose your denominator : 1

Continue inserting into tree? (choose y or n) : y

Please choose your numerator : 65

Please choose your denominator : 1

Continue inserting into tree? (choose y or n) : y

Please choose your numerator : 90

Please choose your denominator : 1

Continue inserting into tree? (choose y or n) : y


Continue inserting into tree? (choose y or n) : y

Please choose your numerator : 35

Please choose your denominator : 1

Continue inserting into tree? (choose y or n) : y

Please choose your numerator : 55

Please choose your denominator : 1

Continue inserting into tree? (choose y or n) : y

Please choose your numerator : 80

Please choose your denominator : 1

Continue inserting into tree? (choose y or n) : y

Please choose your numerator : 95

Please choose your denominator : 1

Continue inserting into tree? (choose y or n) : n


*******************************
*           MENU              *
* 1. Insert Value             *
* 2. Display Tree             *
* 3. Search Tree              *
* 4. Remove Node              *
* 5. Get & Display Smallest   *
* 6. Quit                     *
*******************************
 Enter Option : 2

Printing pre-order
50/1 25/1 10/1 45/1 35/1 75/1 65/1 55/1 90/1 80/1 95/1
Printing in-order
10/1 25/1 35/1 45/1 50/1 55/1 65/1 75/1 80/1 90/1 95/1
Printing post-order
10/1 35/1 45/1 25/1 55/1 65/1 80/1 95/1 90/1 75/1 50/1

*******************************
*           MENU              *
* 1. Insert Value             *
* 2. Display Tree             *
* 3. Search Tree              *
* 4. Remove Node              *
* 5. Get & Display Smallest   *
* 6. Quit                     *
*******************************
 Enter Option : 5

finding smallest node
10/1

*******************************
*           MENU              *
* 1. Insert Value             *
* 2. Display Tree             *
* 3. Search Tree              *
* 4. Remove Node              *
* 5. Get & Display Smallest   *
* 6. Quit                     *
*******************************
 Enter Option : 3

Please choose your numerator : 101

Please choose your denominator : 1
Sorry that value is not in the tree

*******************************
*           MENU              *
* 1. Insert Value             *
* 2. Display Tree             *
* 3. Search Tree              *
* 4. Remove Node              *
* 5. Get & Display Smallest   *
* 6. Quit                     *
*******************************
 Enter Option : 3

Please choose your numerator : 50

Please choose your denominator : 1
Yes your value is in the tree

*******************************
*           MENU              *
* 1. Insert Value             *
* 2. Display Tree             *
* 3. Search Tree              *
* 4. Remove Node              *
* 5. Get & Display Smallest   *
* 6. Quit                     *
*******************************
 Enter Option : 4

Please choose your numerator : 75

Please choose your denominator : 1
Yes your value is in the tree
Value removed

*******************************
*           MENU              *
* 1. Insert Value             *
* 2. Display Tree             *
* 3. Search Tree              *
* 4. Remove Node              *
* 5. Get & Display Smallest   *
* 6. Quit                     *
*******************************
 Enter Option : 2

Printing pre-order
50/1 25/1 10/1 45/1 35/1 90/1 65/1 55/1 95/1
Printing in-order
10/1 25/1 35/1 45/1 50/1 55/1 65/1 90/1 95/1
Printing post-order
10/1 35/1 45/1 25/1 55/1 65/1 95/1 90/1 50/1

*******************************
*           MENU              *
* 1. Insert Value             *
* 2. Display Tree             *
* 3. Search Tree              *
* 4. Remove Node              *
* 5. Get & Display Smallest   *
* 6. Quit                     *
*******************************
 Enter Option : 6

I think that I shall never see
A billboard lovely as a tree.
Indeed, unless the billboards fall,
I'll never see a tree at all.
      -- Joyce Kilmer

*/