/*Miklos Balazs
Grupa 30224*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Profiler.h"
#include <string.h>
typedef struct node
{
	int key;
	struct node *left;
	struct node *right;
	struct node *parent;
	int size;
}NodeT;
Profiler q("arbore");
void preorder(NodeT *root)
{
	if (root != NULL)
	{
		printf(" %d", root->key);
		preorder(root->left);
		preorder(root->right);
	}
}
void inorder(NodeT *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf(" %d", root->key);
		inorder(root->right);
	}
}
//O simplu inserare cu parent
NodeT *insert_tree(NodeT *tree, int key)
{
	
	if (tree == NULL)
	{
		tree=(NodeT*)malloc(sizeof(NodeT));
		tree->key = key;
		tree->left = NULL;
		tree->right = NULL;
		tree->parent = NULL;
		tree->size=1;
	}
	if (key < tree->key)
	{
		tree->left = insert_tree(tree->left, key);
		tree->left->parent = tree;
		tree->size++;
	}
	else if (key>tree->key)
	{
		tree->right = insert_tree(tree->right, key);
		tree->right->parent = tree;
		tree->size++;
	}
	return tree;

}
/*
void draw_tree(NodeT *tree,int level)
{
	int i;
	for (i = 0; i < level; i++)
		printf(" ");
	printf("\n");
	printf("%d,%d", tree->key, tree->size);
	if (tree->left != NULL)
		draw_tree(tree->left, level + 1);
	if (tree->right != NULL)
		draw_tree(tree->right, level + 1);
	
}
*/
NodeT* newNode(int data)
{
	NodeT* node = (NodeT*)malloc(sizeof(NodeT));

	node->key = data;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->size = 1;

	return node;
}/*
NodeT* buildTree(int *arr, int start, int end)
{
	if (start > end)
	{
		return NULL;
	}

	int mid = (start + end) / 2;

	NodeT* tree = newNode(arr[mid]);

	tree->left = buildTree(arr, start, mid - 1);
	

	tree->right = buildTree(arr, mid + 1, end);
	
	if (tree->left != NULL)
	{
		if (tree->right != NULL)
		{
			tree->size = tree->left->size + tree->right->size + 1;
		}
		else
		{
			tree->size = tree->left->size + 1;
		}
	}
	else
	{
		if (tree->right != NULL)
		{
			tree->size = tree->right->size + 1;
		}
	}

	return tree;
}
*/
//Functia ce insereaza un nod la arborein mod echilibrat
NodeT * insert_balanced(NodeT *tree, int keys[], int low,int high)
{
	
	if (high <low)
		return tree;
	int mid = (low + high) / 2;
	tree = insert_tree(tree, keys[mid]);
	
	if (tree->left != NULL)
	{
		if (tree->right != NULL)
		{
			tree->size = tree->left->size + tree->right->size + 1;
		}
		else
		{
			tree->size = tree->left->size + 1;
		}
	}
	else 
	{
		if (tree->right != NULL)
		{
			tree->size = tree->right->size + 1;
		}
	}
	insert_balanced(tree, keys, low, mid-1);
	insert_balanced(tree, keys, mid+1 , high);
}
//functia utila pentru desenarea arborelui
void draw_tree(NodeT *root, int space,int COUNT)
{
	if (root == NULL)
		return;
	space += COUNT;
	draw_tree(root->right, space,COUNT);
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%d,%d\n", root->key,root->size);

	draw_tree(root->left, space,COUNT);
}


//Functia care cauta nodul minim dintr-un arbore
NodeT *findMin(NodeT *root)
{
	if (root == NULL)
	{
		
		return 0;
	}
	else if (root->left == NULL)
	{
		return root;
	}
	findMin(root->left);
}
NodeT* search(NodeT* root, int key)
{
	if (root == NULL || root->key == key)
		return root;
	if (root->key < key)
		return search(root->right, key);
	return search(root->left, key);
}
/*
NodeT *findMax(NodeT *root)
{
	if (root == NULL)
	{
	
		return 0;
	}
	else if (root->right == NULL)
	{
		return root;
	}
	findMax(root->right);
}
NodeT * successor(NodeT *n)
{
	// step 1 of the above algorithm  
	if (n->right != NULL)
		return findMin(n->right);

	// step 2 of the above algorithm 
	struct node *p = n->parent;
	while (p != NULL && n == p->right)
	{
		n = p;
		p = p->parent;
	}
	return p;
}
NodeT *predecesor(NodeT *root)
{
	if (root->left != NULL)
	{
		return findMax(root->left);
	}
	NodeT *aux = root->parent;
	while (aux != NULL && root == aux->left)
	{
		root = aux;
		aux = aux->parent;
	}
	return aux;
}*/
//Functia care returneaza al ilea cea mai mica element cu nod
NodeT * OS_SELECT(NodeT *root, int i,Operation op)
{
	op.count();
	if (root == NULL)
		return root;
	if (i > root->size )
		return NULL;
	int r;
	if (root->left == NULL)
		r = 1;
	else
		r = root->left->size + 1;
	if (i == r)
		return root;
	else if (i < r)
		return OS_SELECT(root->left, i,op);
	else
		return OS_SELECT(root->right, i - r,op);


}
//Functia care scade dimensiunea nodului si tuturor parintelor
void scad_size(NodeT *root)
{
	NodeT *current = root;
	while (current->parent != NULL )
	{
		current->size--;
		current = current->parent;
	}

	
}
//Functia de stergere dupa cheie
NodeT* delNode(NodeT* root, int key,Operation op) {
	NodeT *p;
	op.count();
	if (root == NULL) return root;
	
	if (key < root->key)
		root->left = delNode(root->left, key,op);
	
	else if (key > root->key)
		root->right = delNode(root->right, key,op);

	else {
		
		if (root->left == NULL) {
			p = root->right;
			free(root);
			return p;
		}
		else if (root->right == NULL) {
			p = root->left;
			free(root);
			return p;
		}
		p = findMin(root->right);
		root->key = p->key;
		root->right = delNode(root->right, p->key,op);
	}
	//scad dimensiunea root
	scad_size(root);
	return root;
}

//Functia demo care arata corectitudinea algoritmului
void demo()
{
	NodeT *root = NULL;
	Operation op = q.createOperation("fff", 10);
	int keys[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 ,10,11};
	printf("Original:\n");
	root = insert_balanced(root, keys, 0, 10);
	draw_tree(root, 0, 10);
	printf("Gasirea elementelor cu OS_SELECT si dupa stergerea lor:\n");
	NodeT *neww,*p;
	for (int i= 5; i >0 ;i--)
	{
		p = OS_SELECT(root,rand()%i+1,op);
		if (p != NULL)
			root->size--;
			root=delNode(root, p->key,op);

	}
	draw_tree(root, 0, 10);

	



}
//Functia de perform care arata reultatele pentru dimensiuni mai mari
void perofrm()
{
	
	int v[10000];
	int n;
	NodeT *root = NULL;
	NodeT *p;
	for (n = 100; n <10000; n += 100)
	{
		Operation op = q.createOperation("total", n);
		FillRandomArray(v, n, 10, 50000, true, 1);
		for (int j = n-1; j >= 1; j--)
		{
			root = insert_balanced(root, v, 0, n - 1);
			p = OS_SELECT(root, 1+ rand() % j+1,op);
			if (p != NULL)
				root = delNode(root, p->key,op);
				root->size--;
		}
	}
	q.showReport();


}
int main()
{
//	demo();
perofrm();
	return 0;
}