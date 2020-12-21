#pragma once


//////////////////////////////////////////////////////////////////////////

#define RED 1
#define BLACK 0

struct Interval
{
	int high;
	int low;
};

struct Interval_TreeNode;

struct Interval_Tree
{
	Interval_TreeNode* root;
	Interval_TreeNode* nil;
	Interval_Tree();
};

struct Interval_TreeNode
{
	int k;
	int color;
	int max;
	Interval Int;
	Interval_TreeNode* p;
	Interval_TreeNode* left;
	Interval_TreeNode* right;

	//Interval_TreeNode(Interval_Tree* T, int key)
	//{
	//	color = RED;
	//	p = left = right = T->nil;
	//	k = key;
	//}
	//Interval_TreeNode()
	//{
	//}
};

Interval_TreeNode Interval_NILL = { -1, BLACK, 0, 0, 0, NULL, NULL, NULL };



Interval_Tree::Interval_Tree()
{
	nil = &Interval_NILL;
	root = nil;
}


int MAX(int a, int b, int c)
{
	int temp = a > b ? a : b;
	return temp > c ? temp : c;
}


void Left_Rotate(Interval_Tree* T, Interval_TreeNode* x)
{
	Interval_TreeNode* y = x->right;
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

	y->max = x->max;
	x->max = MAX(x->Int.high, x->left->max, x->right->max);

}

void Right_Rotate(Interval_Tree* T, Interval_TreeNode* x)
{
	Interval_TreeNode* y = x->left;
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

	y->max = x->max;
	x->max = MAX(x->Int.high, x->left->max, x->right->max);
}

void RB_Insert_Fixup(Interval_Tree* T, Interval_TreeNode* z)
{
	while (z->p->color == RED)
	{
		if (z->p->p->left == z->p)
		{
			Interval_TreeNode* y = z->p->p->right;
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
			Interval_TreeNode* y = z->p->p->left;
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

void RB_Insert(Interval_Tree* T, Interval_TreeNode* z)
{
	Interval_TreeNode* y = T->nil;
	Interval_TreeNode* x = T->root;
	while (x != T->nil)
	{
		y = x;
		x->max = MAX(x->Int.high, x->max, z->Int.high);
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
	z->max = z->Int.high;
	z->color = RED;
	RB_Insert_Fixup(T, z);
}

void RB_Transplant(Interval_Tree* T, Interval_TreeNode* u, Interval_TreeNode* v)
{
	if (u->p == T->nil)
		T->root = v;
	else if (u->p->left == u)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

void RB_Delete_Fixup(Interval_Tree* T, Interval_TreeNode* x)
{
	while (x != T->root && x->color == BLACK)
	{
		if (x == x->p->left)
		{
			Interval_TreeNode* w = x->p->right;
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
			Interval_TreeNode* w = x->p->left;
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

Interval_TreeNode* Interval_Tree_Minimum(Interval_Tree* tree, Interval_TreeNode* x)
{
	while (x->left != tree->nil)
	{
		x = x->left;
	}
	return x;
}

Interval_TreeNode* Interval_Tree_Maximum(Interval_Tree* tree, Interval_TreeNode* x)
{
	while (x->right != tree->nil)
	{
		x = x->right;
	}
	return x;
}

void RB_Delete(Interval_Tree* T, Interval_TreeNode* z)
{
	Interval_TreeNode* y = z;
	int y_Original_color = y->color;
	Interval_TreeNode* x = T->nil;
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
		y = Interval_Tree_Minimum(T, z->right);
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
	Interval_TreeNode* p = x->p;
	while (p != T->nil)
	{
		p->max = MAX(p->Int.high, p->left->max, p->right->max);
		p = p->p;
	}
	if (y_Original_color == BLACK)
		RB_Delete_Fixup(T, x);
}

bool Overlap(Interval i, Interval z)
{
	if (i.high < z.low || z.high < i.low)
		return false;
	else
		return true;
}

Interval_TreeNode* Interval_Serach(Interval_Tree* tree, Interval i)
{
	Interval_TreeNode* x = tree->root;
	while (x != tree->nil && !Overlap(x->Int, i))
	{
		if (x->left != tree->nil && i.low <= x->left->max)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

Interval_TreeNode* RB_Search(Interval_Tree* tree, Interval_TreeNode* x, int key)
{
	if (x == tree->nil || x->k == key)
		return x;
	if (x->k > key)
		return RB_Search(tree, x->left, key);
	else
		return RB_Search(tree, x->right, key);

}

Interval_TreeNode* Interval_Tree_Successor(Interval_Tree* tree, Interval_TreeNode* x)
{
	if (x->right != tree->nil)
		return Interval_Tree_Minimum(tree, x->right);
	Interval_TreeNode* y = x->p;
	while (y != tree->nil && y->right == x)
	{
		x = y;
		y = y->p;
	}
	//y为nil时无后继
	return y;
}

Interval_TreeNode* Interval_Tree_Predecesor(Interval_Tree* tree, Interval_TreeNode* x)
{
	if (x->left != tree->nil)
		return Interval_Tree_Maximum(tree, x->left);
	Interval_TreeNode* y = x->p;
	while (y != tree->nil && y->left == x)
	{
		x = y;
		y = y->p;
	}
	return y;
}

void Inorder_Interval_Tree_Walk(Interval_Tree* tree, Interval_TreeNode* x)
{
	if (x != tree->nil)
	{
		Inorder_Interval_Tree_Walk(tree, x->left);
		cout << x->k << " " << x->color << " " << x->Int.low << " " << x->Int.high << " " << x->max << endl;
		Inorder_Interval_Tree_Walk(tree, x->right);
	}
}

void Free_Mem(Interval_Tree* tree, Interval_TreeNode * x)
{
	if (x != tree->nil)
	{
		Free_Mem(tree, x->left);
		Free_Mem(tree, x->right);
		delete x;
	}
}

