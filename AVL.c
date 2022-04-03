/*
Alexander Boyev 314393158
Genady Yolgin 321983413
*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	int height;
	int balance_factor;
	struct node *left;
	struct node *right;
}node;

typedef struct queue {
	node* key;
	struct queue *next;
}queue;

node* Load_AVL(node*);									//1
node* Insert_new_node(node*, int);						//2
node* Delete_node(node*, int);							//3
void Print_Levelorder(node*, int);						//4
void Print_Preorder(node*);								//5
void Print_Inorder(node*);								//6
void Print_Postorder(node*);							//7
node* AVL_Search_Key(node*, int);						//8
node* Print_Tree_Minimum(node*);						//9
node* Print_Tree_Maximum(node*);						//10
node* Print_Tree_Successor_by_Key(node*, node*);		//11
node* Convert_to_preorder_doubly_link_list(node*);		//12
void  Print_Balance_Factors(node*);						//13
void exit_clean(node*);									//14
queue* Enqueue(queue*, node*);							//enqueue lvl order print help
node* Dequeue(queue*);									//dequeue lvl order print help
node* link(int);										//allocate new node
void printmenu();										//print menu
void cleanqueue(queue*);								//clean queue
void CleanDLL(node*);									//clean Doubly linked list
node* parent(node*, node*);								//parent function
node* findrotation(node*);								//help rotation	
void Print_InorderNoArrow(node*);						//print inorder without ->
node* Rotate_Right_Right(node*);						//R->RR	
node* Rotate_Right_Left(node*);							//R->RL
node* Rotate_Left_Left(node*);							//R->LL
node* Rotate_Left_Right(node*);							//R->LR
int intlength(int);										//digits


int main() {

	int element = 0;
	node *root = NULL;
	int num = 0;
	int count = 0;
	int indicator = 0;
	node* mini, *maxi, *search, *find, *succesor;

	printf("\nWelcome!\n");

	while (num != 14) {

		printmenu();
		scanf("%d", &num);
		getchar();

		if (indicator == 1) {
			if (num != 1 && num != 14) {
				printf("\nAVL is not valid anymore!\n");
				printf("Press 1 to reload or 14 to exit: \n");
			}

			while (num != 1 && num != 14) {
				scanf("%d", &num);
				getchar();
				if (num != 1 && num != 14)
					printf("Wrong input, try again: \n");

			}
			if (num == 1) {
				indicator = 0;
				CleanDLL(root);
				root = NULL;
			}
			else {
				indicator = 1;
			}
		}

		switch (num) {
		case 1:
			if (root == NULL) {
				root = Load_AVL(root);
			}
			else {
				exit_clean(root);
				root = NULL;
				root = Load_AVL(root);
			}
			count = 11;
			num = 0;
			break;
		case 2:
			printf("\nEnter an element that you wish to insert: \n\n");
			scanf("%d", &element);
			getchar();
			root = Insert_new_node(root, element);
			count += 1;
			num = 0;
			break;
		case 3:
			if (root == NULL) {
				printf("The tree is empty,please load the tree.\n");
			}
			else {
				printf("\nEnter an element that you wish to delete: \n\n");
				scanf("%d", &element);
				getchar();
				node* temp = AVL_Search_Key(root, element);
				if (temp == NULL) {
					printf("\nThis element doesn't exist.\n");
				}
				else {
					root = Delete_node(root, element);
					count -= 1;
				}
			}
			num = 0;
			break;
		case 4:
			if (root == NULL) {
				printf("\nThe tree is empty,please load the tree.\n");
			}
			else {
				printf("\nprinting levelorder:\n\n");
				Print_Levelorder(root, count);
				printf("\n");
			}
			num = 0;
			break;
		case 5:
			if (root == NULL) {
				printf("The tree is empty,please load the tree.\n");
			}
			else {
				printf("\nprinting Preorder:\n\n");
				Print_Preorder(root);
				printf("\n");
			}
			num = 0;
			break;
		case 6:
			if (root == NULL) {
				printf("The tree is empty,please load the tree.\n");
			}
			else {
				printf("\nprinting Inorder: \n\n");
				Print_Inorder(root);
				printf("\n");
			}
			num = 0;
			break;
		case 7:

			if (root == NULL) {
				printf("The tree is empty,please load the tree.\n");
			}
			else {
				printf("\nprinting Postorder: \n\n");
				Print_Postorder(root);
				printf("\n");
			}
			num = 0;
			break;
		case 8:
			if (root == NULL) {
				printf("The tree is empty,please load the tree.\n");
			}
			else {
				printf("\nEnter a key that you wish to search: \n\n");
				scanf("%d", &element);
				getchar();
				search = AVL_Search_Key(root, element);
				if (search != NULL)
					printf("\nTrue\n");
				else
					printf("\nFalse\n");
				printf("\n");
			}
			num = 0;
			break;
		case 9:
			if (root == NULL) {
				printf("The tree is empty,please load the tree.\n");
			}
			else {
				mini = Print_Tree_Minimum(root);
				printf("\nThe minimum key is: %d\n", mini->key);
			}
			num = 0;
			break;
		case 10:
			if (root == NULL) {
				printf("The tree is empty,please load the tree.\n");
			}
			else {
				maxi = Print_Tree_Maximum(root);
				printf("\nThe maximum key is: %d\n", maxi->key);
			}
			num = 0;
			break;
		case 11:
			if (root == NULL) {
				printf("The tree is empty,please load the tree.\n");
			}
			else {
				printf("\nEnter tree successor key: \n\n");
				scanf("%d", &element);
				getchar();
				find = AVL_Search_Key(root, element);
				succesor = Print_Tree_Successor_by_Key(root, find);
				if (succesor == NULL) {
					printf("\nTree successor doesnt exist!\n");
				}
				else {
					printf("\nThe succuessor of %d is %d.\n", element, succesor->key);
				}
			}
			num = 0;
			break;
		case 12:
			indicator = 1;
			if (root == NULL) {
				printf("\nThe tree is empty,please load the tree.\n");
			}
			else {

				root = Convert_to_preorder_doubly_link_list(root);

				node* temp = root;
				node *next = temp->right;
				printf("\nTesting doubly linked list: \n");
				printf("next is the 2nd key in the doubly linked list!\n");
				printf("1st key is: next->left %d \n", next->left->key);
				printf("2nd key is: %d \n", next->key);
				printf("3rd key is: next->right %d \n", next->right->key);
				printf("\n");
				printf("The whole doubly linked list is: \n\n");
				while (temp != NULL) {
					printf("%d<->", temp->key);
					temp = temp->right;
				}
				printf("\n");
			}
			num = 0;
			break;

		case 13:
			printf("printing balance factors: \n");
			printf("\n");
			Print_InorderNoArrow(root);
			printf("\n");
			Print_Balance_Factors(root);
			printf("\n");
			num = 0;
			break;
		case 14:
			if (indicator == 1) {
				CleanDLL(root);
			}
			else {
				exit_clean(root);
			}
			printf("\nGoodbye!\n");
			break;
		default:
			printf("\nInvalid input, try again!\n");
			num = 0;
		}
	}

	return 0;
}

void CleanDLL(node* root) {
	if (root != NULL) {
		CleanDLL(root->right);
		free(root);
		root = NULL;
	}
}

node* link(int add) {
	node *temp = (node*)malloc(sizeof(node));
	temp->key = add;
	temp->left = NULL;
	temp->right = NULL;
	temp->height = 0;
	temp->balance_factor = 0;
	return temp;
}

void printmenu() {

	printf("\npress 1 for Load AVL.\n");
	printf("press 2 for Insert new node.\n");
	printf("press 3 for Delete node.\n");
	printf("press 4 for Print Levelorder.\n");
	printf("press 5 for Print Preorder.\n");
	printf("press 6 for Print Inorder.\n");
	printf("press 7 for Print Postorder.\n");
	printf("press 8 for AVL - Search Key.\n");
	printf("press 9 for Print Tree - Minimum.\n");
	printf("press 10 for Print Tree - Maximum.\n");
	printf("press 11 for Print Tree - Successor by Key.\n");
	printf("press 12 for Convert to preorder doubly link list.\n");
	printf("press 13 for Print Balance factors. \n");
	printf("press 14 for Exit.\n\n");
}

node* Load_AVL(node* root) {

	printf("\nThe tree is loaded!\n");

	root = Insert_new_node(root, 11);
	root = Insert_new_node(root, 19);
	root = Insert_new_node(root, 43);
	root = Insert_new_node(root, 49);
	root = Insert_new_node(root, 31);
	root = Insert_new_node(root, 17);
	root = Insert_new_node(root, 6);
	root = Insert_new_node(root, 8);
	root = Insert_new_node(root, 10);
	root = Insert_new_node(root, 4);
	root = Insert_new_node(root, 5);

	return root;
}

node* Insert_new_node(node* nodeindi, int add) {

	if (nodeindi == NULL) {
		return link(add);
	}
	if (add < nodeindi->key) {

		nodeindi->left = Insert_new_node(nodeindi->left, add);

		int left = 0, right = 0;
		if (nodeindi->left != NULL) {
			left = nodeindi->left->height + 1;

		}
		if (nodeindi->right != NULL) {
			right = nodeindi->right->height + 1;
		}
		if (left >= right) {
			nodeindi->height = left;
		}
		else {
			nodeindi->height = right;
		}
		nodeindi->balance_factor = left - right;
		if (nodeindi->balance_factor >= 2 || nodeindi->balance_factor <= -2) {
			nodeindi = findrotation(nodeindi);
		}


	}
	else if (add > nodeindi->key) {

		nodeindi->right = Insert_new_node(nodeindi->right, add);
		int left = 0, right = 0;
		if (nodeindi->left != NULL) {
			left = nodeindi->left->height + 1;
		}
		if (nodeindi->right != NULL) {
			right = nodeindi->right->height + 1;
		}
		if (left >= right) {
			nodeindi->height = left;
		}
		else {
			nodeindi->height = right;
		}
		nodeindi->balance_factor = left - right;
		if (nodeindi->balance_factor >= 2 || nodeindi->balance_factor <= -2) {
			nodeindi = findrotation(nodeindi);
		}
	}
	return nodeindi;
}

node* Delete_node(node* root, int del) {
	int left = 0, right = 0;
	if (root == NULL) {
		return NULL;
	}
	if (del < root->key) {
		root->left = Delete_node(root->left, del);

		if (root->right != NULL) {
			right = root->right->height + 1;
		}
		if (root->left != NULL) {
			left = root->left->height + 1;
		}
		if (root->left == NULL && root->right == NULL) {
			root->height = 0;
			root->balance_factor = 0;
		}
		else {
			if (left == right) {
				root->balance_factor = 0;
				root->height = left;
			}
			else if (left > right) {
				root->height = left;
				root->balance_factor = left - right;
			}
			else if (left < right) {
				root->height = right;
				root->balance_factor = left - right;
			}

		}

		if (root->balance_factor >= 2 || root->balance_factor <= -2) {
			root = findrotation(root);
		}

	}
	else if (del > root->key) {
		root->right = Delete_node(root->right, del);
		if (root->right != NULL) {
			right = root->right->height + 1;
		}
		if (root->left != NULL) {
			left = root->left->height + 1;
		}
		if (root->left == NULL && root->right == NULL) {
			root->height = 0;
			root->balance_factor = 0;
		}
		else {
			if (left == right) {
				root->balance_factor = 0;
				root->height = left;
			}
			else if (left > right) {
				root->height = left;
				root->balance_factor = left - right;
			}
			else if (left < right) {
				root->height = right;
				root->balance_factor = left - right;
			}
		}

		if (root->balance_factor >= 2 || root->balance_factor <= -2) {
			root = findrotation(root);
		}
	}
	else {
		if (root->left == NULL && root->right == NULL) {
			free(root);
			root = NULL;
		}

		else if (root->left == NULL) {
			node *temp = root;
			root = root->right;
			free(temp);
		}

		else if (root->right == NULL) {
			node *temp = root;
			root = root->left;
			free(temp);
		}

		else {
			node *temp = Print_Tree_Minimum(root->right);
			root->key = temp->key;
			root->right = Delete_node(root->right, temp->key);
		}
	}
	return root;
}

void Print_Levelorder(node* root, int size) {

	queue* enter = NULL;
	queue* temp = enter;
	node* t = root;


	while (size>0) {

		printf("%d-->", t->key);
		if (t->left != NULL)
			temp = Enqueue(temp, t->left);
		if (t->right != NULL)
			temp = Enqueue(temp, t->right);

		if (temp != NULL) {
			t = Dequeue(temp);
			temp = temp->next;
		}

		size -= 1;
	}

	cleanqueue(enter);
}

int intlength(int value) {
	int len = !value;
	while (value) {
		len++;
		value /= 10;
	}
	if (value < 0) {
		len -= 1;
	}
	return len;
}

void Print_Balance_Factors(node* root) {
	int number = 0;
	int i = 1;
	if (root != NULL) {

		Print_Balance_Factors(root->left);
		number = intlength(root->key);
		if (root->balance_factor < 0) {
			i++;
		}
		for (i; i < number; i++) {
			printf(" ");
		}
		printf("%d  ", root->balance_factor);
		Print_Balance_Factors(root->right);
	}

}

void Print_Preorder(node* root) {

	if (root != NULL) {

		printf("%d-->", root->key);
		Print_Preorder(root->left);
		Print_Preorder(root->right);
	}
}

void Print_InorderNoArrow(node* root) {

	if (root != NULL) {

		Print_InorderNoArrow(root->left);
		printf("%d  ", root->key);
		Print_InorderNoArrow(root->right);

	}
}

void Print_Inorder(node* root) {

	if (root != NULL) {

		Print_Inorder(root->left);
		printf("%d-->", root->key);
		Print_Inorder(root->right);

	}
}

void Print_Postorder(node* root) {

	if (root != NULL) {

		Print_Postorder(root->left);
		Print_Postorder(root->right);
		printf("%d-->", root->key);

	}
}

node* AVL_Search_Key(node* root, int key) {

	node* temp = root;
	while (temp != NULL) {
		if (temp->key == key)
			return temp;
		else if (key > temp->key)
			temp = temp->right;
		else
			temp = temp->left;
	}
	return temp = NULL;
}

node* Print_Tree_Minimum(node* root) {
	node* temp = root;
	while (temp->left != NULL) {
		temp = temp->left;
	}
	return  temp;
}

node* Print_Tree_Maximum(node* root) {
	node* temp = root;
	while (temp->right != NULL) {
		temp = temp->right;
	}
	return temp;
}

node* Print_Tree_Successor_by_Key(node* root, node* groot) {
	node* dad = NULL;
	if ((root == NULL) || (root->left == NULL && root->right == NULL)) {
		return dad;
	}
	else if (groot->right != NULL) {
		return Print_Tree_Minimum(groot->right);
	}
	else if (groot == Print_Tree_Maximum(root)) {
		return dad;
	}
	dad = parent(root, groot);
	if (dad->right != NULL) {
		while ((dad != NULL) && (dad->right->key == groot->key)) {
			groot = dad;
			dad = parent(root, groot);
		}
	}
	return dad;
}

node* parent(node* root, node* son) {
	node* dad = NULL;
	if (root->key == son->key) {
		return dad;
	}
	dad = root;
	while (dad->right != NULL || dad->left != NULL) {
		if (dad->right != NULL)
			if (dad->right->key != son->key) {
				if (son->key > dad->key)
					dad = dad->right;
			}
			else break;


			if (dad->left != NULL)
				if (dad->left->key != son->key) {
					if (son->key < dad->key)
						dad = dad->left;
				}
				else break;
	}
	return dad;
}

node* Convert_to_preorder_doubly_link_list(node* root) {

	node *temp = root;
	node *prev = temp;
	node *max = NULL;
	if (temp->left != NULL) {
		max = temp->left;
		while (max->right != NULL) {
			max = max->right;
		}
		max->right = temp->right;
		temp->right = temp->left;
		temp->left = NULL;
	}
	temp = temp->right;
	while (temp != NULL) {
		if (temp->left == NULL) {
			temp->left = prev;
			temp = temp->right;
			prev = prev->right;
		}
		else {
			max = temp->left;
			while (max->right != NULL) {
				max = max->right;
			}
			max->right = temp->right;
			temp->right = temp->left;
			temp->left = prev;
			temp = temp->right;
			prev = prev->right;
		}
	}
	return root;
}

void exit_clean(node* root) {

	if (root != NULL) {
		exit_clean(root->left);
		exit_clean(root->right);
		free(root);
		root = NULL;
	}
}

void cleanqueue(queue* enter) {
	queue* temp = enter;
	while (temp != NULL) {
		temp = enter;
		enter = enter->next;
		free(temp);
	}
}

queue* Enqueue(queue* enter, node* add) {
	queue* head = enter;

	if (enter == NULL) {
		enter = (queue*)malloc(sizeof(queue));
		enter->key = add;
		enter->next = NULL;
	}
	else {
		while (head->next != NULL) {
			head = head->next;
		}
		head->next = (queue*)malloc(sizeof(queue));
		head->next->key = add;
		head->next->next = NULL;
	}
	return enter;
}

node* Dequeue(queue *enter) {
	node* temp = enter->key;
	return temp;
}

node* findrotation(node* cookie) {
	int left = 0, right = 0;
	while (!(cookie->balance_factor <= 1 && cookie->balance_factor >= -1)) {

		if (cookie->left != NULL) {
			left = cookie->left->height;
		}
		if (cookie->right != NULL) {
			right = cookie->right->height;
		}
		if (right > left) {
			if (cookie->right->right != NULL) {
				cookie = Rotate_Right_Right(cookie);
			}
			else {
				cookie = Rotate_Right_Left(cookie);
			}
		}
		else {
			if (cookie->left->left != NULL) {
				cookie = Rotate_Left_Left(cookie);
			}
			else {
				cookie = Rotate_Left_Right(cookie);
			}
		}
	}
	return cookie;
}

node* Rotate_Right_Right(node* twix) {
	int left = 0, right = 0;
	node *temp = NULL;
	node* result = twix->right;
	if (twix->right->left != NULL) {
		temp = twix->right->left;
	}
	twix->right->left = twix;
	twix->right = temp;
	if (twix->left != NULL) {
		left = twix->left->height + 1;
	}
	if (temp != NULL) {
		right = temp->height + 1;
	}
	twix->height = left >= right ? left : right;
	twix->balance_factor = left - right;
	result->height = result->left->height >= result->right->height ? result->left->height + 1 : result->right->height + 1;
	result->balance_factor = result->left->height - result->right->height;
	return result;
}

node* Rotate_Right_Left(node* twix) {
	node* temp = twix->right;
	twix->right = temp->left;
	twix->right->right = temp;
	temp->left = NULL;
	twix->right->height = 1;
	twix->right->balance_factor = 1;
	twix->right->right->height = 0;
	twix->right->right->balance_factor = 0;
	return twix;
}

node* Rotate_Left_Left(node* twix) {
	int left = 0, right = 0;
	node* temp = NULL;
	node* result = twix->left;
	if (twix->left->right != NULL) {
		temp = twix->left->right;

	}
	twix->left->right = twix;
	twix->left = temp;
	if (twix->right != NULL) {
		right = twix->right->height + 1;
	}
	if (temp != NULL) {
		left = temp->height + 1;
	}
	twix->height = left >= right ? left : right;
	twix->balance_factor = left - right;
	result->height = result->left->height >= result->right->height ? result->left->height + 1 : result->right->height + 1;
	result->balance_factor = result->left->height - result->right->height;
	return result;
}

node* Rotate_Left_Right(node* twix) {
	node * temp = twix->left;
	twix->left = temp->right;
	twix->left->left = temp;
	temp->right = NULL;
	twix->left->height = 1;
	twix->left->balance_factor = 1;
	twix->left->left->height = 0;
	twix->left->left->balance_factor = 0;
	return twix;
}