#pragma once
//////////////////////////////////////////////////////////////////////////
//二叉搜索树
struct TreeNode
{
	int key;
	TreeNode* p;
	TreeNode* left;
	TreeNode* right;
	TreeNode() {
		left = NULL;
		right = NULL;
		p = NULL;
	}
};

struct Tree
{
	TreeNode* root;
	Tree() {
		root = NULL;
	}
};

TreeNode* Tree_Search(TreeNode* pNode, int key)
{
	if (pNode == NULL || pNode->key == key)
		return pNode;
	if (pNode->key > key)
		return Tree_Search(pNode->left, key);
	else
		return Tree_Search(pNode->right, key);
}

TreeNode* Iterative_Tree_Search(TreeNode* pNode, int key)
{
	while (pNode != NULL && pNode->key != key)
	{
		if (pNode->key > key)
			pNode = pNode->left;
		else
			pNode = pNode->right;
	}
	return pNode;
}

TreeNode* Tree_Minimum(TreeNode* pNode)
{
	while (pNode->left != NULL)
	{
		pNode = pNode->left;
	}
	return pNode;
}

TreeNode* Tree_Maximum(TreeNode* pNode)
{
	while (pNode->right != NULL)
	{
		pNode = pNode->right;
	}
	return pNode;
}

TreeNode* Tree_Successor(TreeNode* pNode)
{
	if (pNode->right != NULL)
		return Tree_Minimum(pNode->right);

	TreeNode* y = pNode->p;
	while (y != NULL && pNode == y->right)
	{
		pNode = y;
		y = y->p;
	}
	return y;
}

TreeNode* Tree_Predecessor(TreeNode* pNode)
{
	if (pNode->left != NULL)
		return Tree_Maximum(pNode->left);

	TreeNode* y = pNode->p;
	while (y != NULL && pNode == y->left)
	{
		pNode = y;
		y = y->p;
	}
	return y;
}

void Tree_Insert(Tree* tree, TreeNode* z)
{
	TreeNode* y = NULL;
	TreeNode* x = tree->root;
	while (x != NULL)
	{
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	//可以保证z为根节点的时候，在未初始化NULL的情况下将根节点的父节点置空
	z->p = y;
	if (y == NULL)
		tree->root = z;
	else if (y->key > z->key)
	{
		y->left = z;
	}
	else
	{
		y->right = z;
	}
}

void Transplant(Tree* tree, TreeNode* u, TreeNode* v)
{
	if (u->p == NULL)
	{
		tree->root = v;
	}
	else if (u->p->left == u)
	{
		u->p->left = v;
	}
	else if (u->p->right == u)
	{
		u->p->right = u;
	}
	if (v != NULL)
		v->p = u->p;
}

void Tree_Delete(Tree* tree, TreeNode* z)
{
	if (z->left == NULL)
	{
		Transplant(tree, z, z->right);
	}
	else if (z->right == NULL)
	{
		Transplant(tree, z, z->left);
	}
	else
	{
		TreeNode* y = Tree_Minimum(z->right);
		if (y->p != z)
		{
			Transplant(tree, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		Transplant(tree, z, y);
		y->left = z->left;
		y->left->p = y;
	}
	delete z;
}

void Inorder_Tree_Walk(TreeNode *x) {
	if (x != NULL) {
		Inorder_Tree_Walk(x->left);
		printf("%d ", x->key);
		Inorder_Tree_Walk(x->right);
	}
}

void free_mem(TreeNode *x) {
	if (x != NULL) {
		free_mem(x->left);
		free_mem(x->right);
		free(x);
	}
}