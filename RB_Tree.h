#pragma once


//////////////////////////////////////////////////////////////////////////
//红黑树
#define RED 1
#define BLACK 0

struct RB_TreeNode;

struct RB_Tree
{
	RB_TreeNode* root;
	RB_TreeNode* nil;
	RB_Tree();
};

struct RB_TreeNode
{
	int k;
	int color;
	RB_TreeNode* p;
	RB_TreeNode* left;
	RB_TreeNode* right;

	//RB_TreeNode(RB_Tree* T, int key)
	//{
	//	color = RED;
	//	p = left = right = T->nil;
	//	k = key;
	//}
	//RB_TreeNode()
	//{
	//}
};

RB_TreeNode NILL = { -1, BLACK, NULL, NULL, NULL };

RB_Tree::RB_Tree()
{
	nil = &NILL;
	root = nil;
}

void Left_Rotate(RB_Tree* T, RB_TreeNode* x)
{
	RB_TreeNode* y = x->right;
	x->right = y->left;
	if (y->left != T->nil)
		y->left->p = x;
	y->p = x->p;
	if (x->p == T->nil)
		T->root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

void Right_Rotate(RB_Tree* T, RB_TreeNode* x)
{
	RB_TreeNode* y = x->left;
	x->left = y->right;
	if (y->right != T->nil)
		y->right->p = x;
	y->p = x->p;
	if (x->p == T->nil)
		T->root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->right = x;
	x->p = y;
}

void RB_Insert_Fixup(RB_Tree* T, RB_TreeNode* z)
{
	while (z->p->color == RED)
	{
		if (z->p->p->left == z->p)
		{
			RB_TreeNode* y = z->p->p->right;
			if (y->color == RED)
			{
				z->p->color = BLACK;    //case1
				y->color = BLACK;       //case1
				z->p->p->color = RED;   //case1
				z = z->p->p;
			}
			else
			{
				if (z == z->p->right)
				{
					z = z->p;
					Left_Rotate(T, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				Right_Rotate(T, z->p->p);
			}
		}
		else
		{
			RB_TreeNode* y = z->p->p->left;
			if (y->color == RED)
			{
				z->p->color = BLACK;    //case1
				y->color = BLACK;       //case1
				z->p->p->color = RED;   //case1
				z = z->p->p;
			}
			else
			{
				if (z == z->p->left)
				{
					z = z->p;
					Right_Rotate(T, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				Left_Rotate(T, z->p->p);
			}
		}
	}
	T->root->color = BLACK;
}

void RB_Insert(RB_Tree* T, RB_TreeNode* z)
{
	RB_TreeNode* y = T->nil;
	RB_TreeNode* x = T->root;
	while (x != T->nil)
	{
		y = x;
		if (x->k > z->k)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if (y == T->nil)
	{
		T->root = z;
	}
	else if (y->k > z->k)
		y->left = z;
	else
		y->right = z;
	z->left = T->nil;
	z->right = T->nil;
	z->color = RED;
	RB_Insert_Fixup(T, z);
}

void RB_Transplant(RB_Tree* T, RB_TreeNode* u, RB_TreeNode* v)
{
	if (u->p == T->nil)
		T->root = v;
	else if (u->p->left == u)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

void RB_Delete_Fixup(RB_Tree* T, RB_TreeNode* x)
{
	while (x != T->root && x->color == BLACK)
	{
		if (x == x->p->left)
		{
			RB_TreeNode* w = x->p->right;
			//有个孩子为红色，x->p必为黑色
			if (w->color == RED/* && x->p->color == BLACK*/)
			{
				w->color = BLACK;
				x->p->color = RED;
				Left_Rotate(T, x->p);
				w = x->p->right;
			}

			if (w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;
				x = x->p;
			}
			else if (w->left->color == RED)
			{
				w->color = RED;
				w->left->color = BLACK;
				Right_Rotate(T, w);
				w = x->p->right;
			}
			w->color = x->p->color;
			w->right->color = BLACK;
			x->p->color = BLACK;
			Left_Rotate(T, x->p);
			x = T->root;
		}
		else
		{
			RB_TreeNode* w = x->p->left;
			//有个孩子为红色，x->p必为黑色
			if (w->color == RED/* && x->p->color == BLACK*/)
			{
				w->color = BLACK;
				x->p->color = RED;
				Right_Rotate(T, x->p);
				w = x->p->left;
			}

			if (w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;
				x = x->p;
			}
			else if (w->right->color == RED)
			{
				w->color = RED;
				w->right->color = BLACK;
				Left_Rotate(T, w);
				w = x->p->left;
			}
			w->color = x->p->color;
			w->left->color = BLACK;
			x->p->color = BLACK;
			Right_Rotate(T, x->p);
			x = T->root;
		}
	}
	x->color = BLACK;
}

RB_TreeNode* RB_Tree_Minimum(RB_Tree* tree, RB_TreeNode* x)
{
	while (x->left != tree->nil)
	{
		x = x->left;
	}
	return x;
}

RB_TreeNode* RB_Tree_Maximum(RB_Tree* tree, RB_TreeNode* x)
{
	while (x->right != tree->nil)
	{
		x = x->right;
	}
	return x;
}

void RB_Delete(RB_Tree* T, RB_TreeNode* z)
{
	RB_TreeNode* y = z;
	int y_Original_color = y->color;
	RB_TreeNode* x = T->nil;
	if (z->left == T->nil)
	{
		x = z->right;
		RB_Transplant(T, z, z->right);
	}
	else if (z->right == T->nil)
	{
		x = z->left;
		RB_Transplant(T, z, z->left);
	}
	else
	{
		y = RB_Tree_Minimum(T, z->right);
		x = y->right;
		y_Original_color = y->color;
		if (y->p == z)
			x->p = y;         //这一句貌似是废话
		else
		{
			RB_Transplant(T, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		RB_Transplant(T, z, y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	delete z;
	if (y_Original_color == BLACK)
		RB_Delete_Fixup(T, x);
}

RB_TreeNode* RB_Search(RB_Tree* tree, RB_TreeNode* x, int key)
{
	if (x == tree->nil || x->k == key)
		return x;
	if (x->k > key)
		return RB_Search(tree, x->left, key);
	else
		return RB_Search(tree, x->right, key);

}

RB_TreeNode* RB_Tree_Successor(RB_Tree* tree, RB_TreeNode* x)
{
	if (x->right != tree->nil)
		return RB_Tree_Minimum(tree, x->right);
	RB_TreeNode* y = x->p;
	while (y != tree->nil && y->right == x)
	{
		x = y;
		y = y->p;
	}
	//y为nil时无后继
	return y;
}

RB_TreeNode* RB_Tree_Predecesor(RB_Tree* tree, RB_TreeNode* x)
{
	if (x->left != tree->nil)
		return RB_Tree_Maximum(tree, x->left);
	RB_TreeNode* y = x->p;
	while (y != tree->nil && y->left == x)
	{
		x = y;
		y = y->p;
	}
	return y;
}

void Inorder_RB_Tree_Walk(RB_Tree* tree, RB_TreeNode* x)
{
	if (x != tree->nil)
	{
		Inorder_RB_Tree_Walk(tree, x->left);

		printf("%d : ", x->k);
		if (x->color == 1)
			printf("red ");
		else
			printf("black ");
		Inorder_RB_Tree_Walk(tree, x->right);
	}
}

void Free_Mem(RB_Tree* tree, RB_TreeNode * x)
{
	if (x != tree->nil)
	{
		Free_Mem(tree, x->left);
		Free_Mem(tree, x->right);
		delete x;
	}
}
