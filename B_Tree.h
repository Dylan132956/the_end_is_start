#pragma once
#include <iostream>
using namespace std;

#define B_N 10
int t = 2;
//B树结点结构
struct node
{
	int n;//当前存储在结点x中的关键字数
	char key[B_N];//n个关键字，以非降序存放
	bool leaf;//TRUE:x是叶子；FALSE:x是内结点
	node *child[B_N + 1];//指向其n+1个孩子的指针
					   //构造函数
	node(int num, bool IsLeaf) :n(num), leaf(IsLeaf) {}
	//磁盘读写操作
	void Disk_Read() {}
	void Disk_Write() {}
};
//B树结构
class B_Tree
{
public:
	//指向根结点
	node *root;
	B_Tree() :root(NULL) {}

	//从以x为根结点的树中寻找关键字为k的结点，若找到，将结果存入y中，返回其是第几个关键字
	int B_Tree_Search(node *x, char k, node&y);
	//构造一棵带树结点的空树
	void B_Tree_Create();
	//分裂，把y分裂为两个结点，选择其中一个关键字插入到x中的第i个位置
	void B_Tree_Split_Child(node *x, int i, node *y);
	//将关键字k插入到一个未满的结点x中
	void B_Tree_Insert_Nonfull(node *x, char k);
	//向T中插入关键字k
	void B_Tree_Insert(char k);
	//删除T树中关键字为k的结点，由于是递归方法，当前处理的是x结点
	void B_Tree_Delete(node *x, char k);
	//按关键字从小到大输出结点
	void Print(node *n);
	//销毁B树
	void Destory(node *n);
};

//从以x为根结点的树中寻找关键字为k的结点，若找到，将结果存入y中，返回其是第几个关键字
int B_Tree::B_Tree_Search(node *x, char k, node&y)
{
	int i = 1;
	//找到第一个关键字不大于k的i
	while (i < x->n && k > x->key[i])
		i++;
	//若key[i] = k，则找到了
	if (i <= x->n && k == x->key[i])
	{
		//将结果存入y中
		y = *x;
		//返回其是第几个关键字
		return i;
	}
	//若没找到，则返回空
	if (x->leaf)
	{
		//	&y = NULL;
		return 0;
	}
	//若还有子树可以找，则递归查找第i个子树
	x->child[i]->Disk_Read();
	return B_Tree_Search(x->child[i], k, y);
}
//构造一棵带树结点的空树
void B_Tree::B_Tree_Create()
{
	//生成一个根结点
	//初始时，根结点为叶子结点，根结点中没有关键字
	root = new node(0, true);
	root->Disk_Write();
}
//分裂，把y分裂为两个结点，选择其中一个关键字插入到x中的第i个位置
void B_Tree::B_Tree_Split_Child(node *x, int i, node *y)
{
	int j;
	//生成一个新结点z
	//要把y分裂为y和z，因此z的叶子属性与y相同
	//分裂前y有2t-1个关键字，分裂后前t-1个属于y，后t-1个属于z，中间第t个属于x
	node *z = new node(t - 1, y->leaf);
	y->n = t - 1;
	//后t-1个关键字依次复制给z
	for (j = 1; j < t; j++)
		z->key[j] = y->key[j + t];
	//如果有孩子，孩子也要复制过去，原来有2t个子树，前t个属于y，后t个属于z
	if (y->leaf == false)
	{
		for (j = 1; j <= t; j++)
			z->child[j] = y->child[j + t];
	}
	//使z作为x的第i+1个孩子(y已经是x的第i个孩子)
	for (j = x->n + 1; j > i; j--)
		x->child[j + 1] = x->child[j];
	x->child[i + 1] = z;
	//把y中第t个关键字插入到x的第i个位置
	for (j = x->n; j >= i; j--)
		x->key[j + 1] = x->key[j];
	x->key[i] = y->key[t];
	//x的关键字+1
	x->n++;
	y->Disk_Write();
	z->Disk_Write();
	x->Disk_Write();
}
//将关键字k插入到一个未满的结点x中
void B_Tree::B_Tree_Insert_Nonfull(node *x, char k)
{
	int i = x->n;
	//若x是叶子结点
	if (x->leaf)
	{
		//找到该插入的位置
		while (i >= 1 && k < x->key[i])
		{
			x->key[i + 1] = x->key[i];
			i--;
		}
		//插入关键字k
		x->key[i + 1] = k;
		x->n++;
		x->Disk_Write();
	}
	//若不是叶子结点
	else
	{
		//找到该插入的位置
		while (i >= 1 && k < x->key[i])
			i--;
		i++;
		//读取其孩子，将关键字插入到它的孩子中，分两种情况
		x->child[i]->Disk_Read();
		//孩子已满
		if (x->child[i]->n == 2 * t - 1)
		{
			//对孩子执行分裂操作，分裂后，孩子不变为不满
			B_Tree_Split_Child(x, i, x->child[i]);
			if (k > x->key[i])
				i++;
		}
		//孩子不满，直接对孩子进行插入操作
		B_Tree_Insert_Nonfull(x->child[i], k);
	}
}
//向T中插入关键字k
void B_Tree::B_Tree_Insert(char k)
{
	node *r = root, *s;
	//若根结点已满
	if (r->n == 2 * t - 1)
	{
		//申请一个新的结点,将新的结点作为根结点
		root = new node(0, false);
		root->child[1] = r;
		//将原根结点分裂为两个结点，分别作为s的第0个孩子和第1个孩子
		B_Tree_Split_Child(root, 1, r);
		//把关键字k插入到根结点中，此时根结点一定不满
		B_Tree_Insert_Nonfull(root, k);
	}
	//若根结点不满
	else
		//直接把关键字插入到根结点中
		B_Tree_Insert_Nonfull(r, k);
}
//删除T树中关键字为k的结点，由于是递归方法，当前处理的是x结点
void B_Tree::B_Tree_Delete(node *x, char k)
{
	int i, j;
	//找到x中第一个不小于k的关键字，即待处理的位置
	for (i = 1; i <= x->n; i++)
		if (x->key[i] >= k)
			break;
	//y是关键字k之前的结点,即小于k的最大孩子
	//z是关键字k之后的结点,即大于k的最小孩子
	node *y = x->child[i], *z = x->child[i + 1], *d;
	//若关键字k在结点x中的第i个位置
	if (x->key[i] == k && i <= x->n)
	{
		//1)y是叶子结点，则直接从x中删除k
		if (x->leaf == true)
		{
			//关键字依次前移
			for (j = i; j < x->n; j++)
				x->key[j] = x->key[j + 1];
			//关键字数-1
			x->n--;
			if (x->n == 0 && root == x)
			{
				delete x;
				root = NULL;
			}
			return;
		}
		//2)x是内结点
		//2-a：x中前于k的子结点y包含至少t个关键字
		if (y->n >= t)
		{
			//找出k在以y为根的子树中的前驱d
			d = y;
			while (d->leaf == false)
				d = d->child[d->n + 1];
			//用d取代k
			x->key[i] = d->key[d->n];
			//递归地删除d
			B_Tree_Delete(y, d->key[d->n]);
			//Destory(y);
		}
		//2-b：x是位于k之后的子结点z包含至少t个关键字
		else if (z->n >= t)
		{
			//找出k在以z为根的子树中的后继d
			d = z;
			while (d->leaf == false)
				d = d->child[1];
			//用d取代k
			x->key[i] = d->key[1];
			//递归地删除d
			B_Tree_Delete(z, d->key[1]);
			//Destory(z);
		}
		//2-c：y和z都只有t-1个关键字，将k和z中所有关键字合并进y，使得x失去k和指向z的指针
		else
		{
			//将k关键字合并进y
			y->key[y->n + 1] = k;
			//将z中所有关键字合并进y
			for (j = 1; j <= z->n; j++)
				y->key[y->n + j + 1] = z->key[j];
			//如果有孩子，孩子也要合并
			if (y->leaf == false)
			{
				//使得x指向z的指针
				for (j = 1; j <= z->n + 1; j++)
					y->child[y->n + j + 1] = z->child[j];
			}
			//y包含2t-1个关键字
			y->n = y->n + 1 + z->n;
			//使得x失去k
			for (j = i; j < x->n; j++)
				x->key[j] = x->key[j + 1];
			//使x失去指向z的指针
			for (j = i + 1; j <= x->n; j++)
				x->child[j] = x->child[j + 1];
			x->n--;
			//如果x是根结点，x
			if (x->n == 0 && root == x)
			{
				delete x;
				root = y;
			}
			//释放z
			delete z;
			//将k从y中递归删除
			B_Tree_Delete(y, k);
			//Destory(y);
		}
	}
	//3)关键字不在结点x中，则必定包含k的正确的子树的根x->child[i]
	else
	{
		//x是叶子结点,找到根结点都没有找到k，则k不在树中
		if (x->leaf == true)
		{
			cout << "error:not exist" << endl;
			return;
		}
		//x是内结点
		//3-a:child[i]中只有t-1个关键字
		if (y->n == t - 1)
		{
			//它的相邻兄弟x->child[i+1](用z表示)包含至少t个关键字
			if (i <= x->n && i <= x->n && z->n >= t)
			{
				//将x中的关键字下降至y
				y->n++;
				y->key[y->n] = x->key[i];
				//将z的某一关键字上升至x
				x->key[i] = z->key[1];
				for (j = 1; j < z->n; j++)
					z->key[j] = z->key[j + 1];
				//将z适合的子女指针移到y
				if (y->leaf == false)
				{
					y->child[y->n + 1] = z->child[1];
					for (j = 1; j <= z->n; j++)
						z->child[j] = z->child[j + 1];
				}
				//z的关键字数-1
				z->n--;
			}
			//它的相邻兄弟x->child[i-1]包含至少t个关键字
			else if (i > 1 && x->child[i - 1]->n >= t)
			{
				//将x中的关键字下降至y
				for (j = y->n; j >= 1; j--)
					y->key[j + 1] = y->key[j];
				y->key[1] = x->key[i - 1];
				y->n++;
				//将y的相邻兄弟x->child[i-1]的某一关键字上升至x
				x->key[i - 1] = x->child[i - 1]->key[x->child[i - 1]->n];
				//将该兄弟适合的子女指针移到y
				if (y->leaf == false)
				{
					for (j = y->n; j >= 1; j--)
						y->child[j + 1] = y->child[j];
					y->child[1] = x->child[i - 1]->child[x->child[i - 1]->n + 1];
				}
				//x->child[i-1]的关键字数-1
				x->child[i - 1]->n--;
			}
			//y和其所有相邻兄弟都只有t-1个关键字，则与其中一个兄弟合并
			else
			{
				//与后面一个结点(用z表示)合并
				if (i <= x->n)
				{
					//将x->key[i]并入y中
					y->key[y->n + 1] = x->key[i];
					//将z中所有关键字并入y中
					for (j = 1; j <= z->n; j++)
						y->key[j + y->n + 1] = z->key[j];
					//如果有孩子，所有孩子也要并入
					if (y->leaf == false)
					{
						for (j = 1; j <= z->n + 1; j++)
							y->child[j + y->n + 1] = z->child[j];
					}
					//修改y的关键字数
					y->n = y->n + 1 + z->n;
					//将x->key[i]从x中移出
					for (j = i; j < x->n; j++)
						x->key[j] = x->key[j + 1];
					//把指向z的指针从x->child中移出
					for (j = i + 1; j <= x->n; j++)
						x->child[j] = x->child[j + 1];
					//x的关键字数-1
					x->n--;
					delete z;
					//若根结点被删除，更新根结点
					if (x->n == 0 && root == x)
					{
						delete x;
						root = y;
					}
				}
				//与前面一个结点合并
				else
				{
					//令z=x->child[i-1],y=x->child[i]，把z并入y中
					z = y; i--;
					y = x->child[i];
					//将x->key[i]并入y中
					y->key[y->n + 1] = x->key[i];
					//将z中所有关键字并入y中
					for (j = 1; j <= z->n; j++)
						y->key[j + y->n + 1] = z->key[j];
					//如果有孩子，所有孩子也要并入
					if (y->leaf == false)
					{
						for (j = 1; j <= z->n + 1; j++)
							y->child[j + y->n + 1] = z->child[j];
					}
					//修改y的关键字数
					y->n = y->n + 1 + z->n;
					//将x->key[i]从x中移出
					for (j = i; j < x->n; j++)
						x->key[j] = x->key[j + 1];
					//把指向z的指针从x->child中移出
					for (j = i + 1; j <= x->n; j++)
						x->child[j] = x->child[j + 1];
					//x的关键字数-1
					x->n--;
					//若根结点被删除，更新根结点
					delete z;
					if (x->n == 0 && root == x)
					{
						delete x;
						root = y;
					}
				}
			}
		}
		//递归执行删除操作
		B_Tree_Delete(y, k);
	}
}
//按关键字从小到大输出结点
void B_Tree::Print(node *n)
{
	int i;
	for (i = 1; i <= n->n; i++)
	{
		if (n->leaf == false)
			Print(n->child[i]);
		cout << n->key[i] << ' ';
	}
	if (n->leaf == false)
		Print(n->child[n->n + 1]);
}

void B_Tree::Destory(node *n)
{
	if (n->leaf == false)
	{
		for (int i = 1; i <= n->n + 1; i++)
		{
			Destory(n->child[i]);
		}
		delete n;
	}
	else
	{
		delete n;
	}

	//int i;
	//for (i = 1; i <= n->n+1; i++)
	//{
	//	if (n->leaf == false)
	//		Print(n->child[i]);
	//	cout << n->key[i] << ' ';
	//}
	//if (n->leaf == false)
	//	Print(n->child[n->n + 1]);
}
