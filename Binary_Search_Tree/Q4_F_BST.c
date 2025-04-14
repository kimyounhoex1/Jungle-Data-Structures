//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS1(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

// You may use the following functions or you may write your own
void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS1(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
/** GTP 수도코드
1. 스택에 루트를 넣고, 이전 방문 노드를 null로 초기화한다.

2. 스택이 비어있을 때까지 반복:
    a. 현재 노드는 스택의 top이다.
    
    b. 이전 노드가 없거나 현재 노드의 자식이었던 경우 (하향 중):
        - 왼쪽 자식이 있으면 왼쪽으로 이동 (스택에 push)
        - 없으면 오른쪽 자식이 있으면 오른쪽으로 이동 (스택에 push)
        - 둘 다 없으면 현재 노드 처리 (출력 or 저장) 후 pop

    c. 이전 노드가 현재의 왼쪽 자식인 경우:
        - 오른쪽 자식이 있으면 오른쪽으로 이동 (스택에 push)
        - 없으면 현재 노드 처리 후 pop

    d. 이전 노드가 현재의 오른쪽 자식인 경우:
        - 현재 노드 처리 후 pop

    e. 이전 노드를 현재 노드로 갱신
 */
void postOrderIterativeS1(BSTNode *root)
{
	if(root == NULL)
		return;

	Stack *stk = malloc(sizeof(Stack));
	BSTNode *prev = NULL;
	
	push(stk, root);

	while(stk->top != NULL){
		BSTNode *curr = peek(stk);
		if(prev == NULL || prev->left == curr || prev->right == curr){
			if(curr->left != NULL){
				push(stk, curr->left);
			}
			else if(curr->right != NULL){
				push(stk, curr->right);
			}
			else {
				printf("%d ", curr->item);
				pop(stk);
			}
		} else if (curr->left == prev){
			if (curr->right != NULL){
				push(stk, curr->right);
			}
			else {
				printf("%d ", curr->item);
				pop(stk);
			}
		} else if (curr->right == prev){
			printf("%d ", curr->item);
			pop(stk);
		}

		prev = curr;
	}

	free(stk);
	free(BSTNode);
}
	
	 /* add your code here */

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
