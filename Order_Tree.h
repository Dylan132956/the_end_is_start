#pragma once


//////////////////////////////////////////////////////////////////////////
//红黑树
#define ORDER_TREE


#define RED 1
#define BLACK 0

struct Order_TreeNode;

struct Order_Tree
{
	Order_TreeNode* root;
	Order_TreeNode* nil;
	Order_Tree();
};

struct Order_TreeNode
{
	int k;
	int color;
#ifdef ORDER_TREE
	int size;
#endif
	Order_TreeNode* p;
	Order_TreeNode* left;
	Order_TreeNode* right;

	//Order_TreeNode(Order_Tree* T, int key)
	//{
	//	color = RED;
	//	p = left = right = T->nil;
	//	k = key;
	//}
	//Order_TreeNode()
	//{
	//}
};
#ifdef ORDER_TREE
Order_TreeNode Order_NILL = { -1, BLACK, 0, &Order_NILL, &Order_NILL, &Order_NILL };
#else
Order_TreeNode NILL = { -1, BLACK, NULL, NULL, NULL };
#endif


Order_Tree::Order_Tree()
{
	nil = &Order_NILL;
	root = nil;
}

void Left_Rotate(Order_Tree* T, Order_TreeNode* x)
{
	Order_TreeNode* y = x->right;
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

#ifdef ORDER_TREE
	y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
#endif
}

void Right_Rotate(Order_Tree* T, Order_TreeNode* x)
{
	Order_TreeNode* y = x->left;
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
#ifdef ORDER_TREE
	y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
#endif
}

void RB_Insert_Fixup(Order_Tree* T, Order_TreeNode* z)
{
	while (z->p->color == RED)
	{
		if (z->p->p->left == z->p)
		{
			Order_TreeNode* y = z->p->p->right;
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
			Order_TreeNode* y = z->p->p->left;
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

void RB_Insert(Order_Tree* T, Order_TreeNode* z)
{
	Order_TreeNode* y = T->nil;
	Order_TreeNode* x = T->root;
	while (x != T->nil)
	{
		y = x;
#ifdef ORDER_TREE
		x->size++;
#endif
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

void RB_Transplant(Order_Tree* T, Order_TreeNode* u, Order_TreeNode* v)
{
	if (u->p == T->nil)
		T->root = v;
	else if (u->p->left == u)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

void RB_Delete_Fixup(Order_Tree* T, Order_TreeNode* x)
{
	while (x != T->root && x->color == BLACK)
	{
		if (x == x->p->left)
		{
			Order_TreeNode* w = x->p->right;
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
			Order_TreeNode* w = x->p->left;
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

Order_TreeNode* Order_Tree_Minimum(Order_Tree* tree, Order_TreeNode* x)
{
	while (x->left != tree->nil)
	{
		x = x->left;
	}
	return x;
}

Order_TreeNode* Order_Tree_Maximum(Order_Tree* tree, Order_TreeNode* x)
{
	while (x->right != tree->nil)
	{
		x = x->right;
	}
	return x;
}

void RB_Delete(Order_Tree* T, Order_TreeNode* z)
{
	Order_TreeNode* y = z;
	int y_Original_color = y->color;
	Order_TreeNode* x = T->nil;
	if (z->left == T->nil)
	{
		x = z->right;
#ifdef ORDER_TREE
		//nil没有的p为NULL,没有指向nil时会崩溃。
		Order_TreeNode* p = x->p;
		while (p != T->nil)
		{
			p->size--;
			p = p->p;
		}
#endif
		RB_Transplant(T, z, z->right);
	}
	else if (z->right == T->nil)
	{
		x = z->left;
#ifdef ORDER_TREE
		Order_TreeNode* p = x->p;
		while (p != T->nil)
		{
			p->size--;
			p = p->p;
		}
#endif
		RB_Transplant(T, z, z->left);
	}
	else
	{
		y = Order_Tree_Minimum(T, z->right);

#ifdef ORDER_TREE
		y->size = z->size - 1;
		Order_TreeNode* p = y->p;
		while (p != T->nil)
		{
			p->size--;
			p = p->p;
		}
#endif

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

Order_TreeNode* RB_Search(Order_Tree* tree, Order_TreeNode* x, int key)
{
	if (x == tree->nil || x->k == key)
		return x;
	if (x->k > key)
		return RB_Search(tree, x->left, key);
	else
		return RB_Search(tree, x->right, key);

}

Order_TreeNode* Order_Tree_Successor(Order_Tree* tree, Order_TreeNode* x)
{
	if (x->right != tree->nil)
		return Order_Tree_Minimum(tree, x->right);
	Order_TreeNode* y = x->p;
	while (y != tree->nil && y->right == x)
	{
		x = y;
		y = y->p;
	}
	//y为nil时无后继
	return y;
}

Order_TreeNode* Order_Tree_Predecesor(Order_Tree* tree, Order_TreeNode* x)
{
	if (x->left != tree->nil)
		return Order_Tree_Maximum(tree, x->left);
	Order_TreeNode* y = x->p;
	while (y != tree->nil && y->left == x)
	{
		x = y;
		y = y->p;
	}
	return y;
}

void Inorder_Order_Tree_Walk(Order_Tree* tree, Order_TreeNode* x)
{
	if (x != tree->nil) {
		Inorder_Order_Tree_Walk(tree, x->left);
		printf("%d : ", x->k);
		if (x->color == 1)
			printf("red ");
		else
			printf("black ");
		printf("r(%d) ", x->size);
		Inorder_Order_Tree_Walk(tree, x->right);

	}
}

Order_TreeNode* OS_Select(Order_TreeNode* x, int i)
{
	int r = x->left->size + 1;
	if (r == i)
		return x;
	if (i <= r)
		return OS_Select(x->left, i);
	else
		return OS_Select(x->right, i - r);
}

int OS_Rank(Order_Tree* T, Order_TreeNode* x)
{
	int r = x->left->size + 1;
	Order_TreeNode* y = x;
	while (y != T->nil)
	{
		if (y->p->right == y)
			r += y->p->left->size + 1;
		y = y->p;
	}
	return r;
}

void Free_Mem(Order_Tree* tree, Order_TreeNode* x)
{
	if (x != tree->nil)
	{
		Free_Mem(tree, x->left);
		Free_Mem(tree, x->right);
		delete x;
	}
}

#undef ORDER_TREE
