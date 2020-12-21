#pragma once
#include <iostream>
using namespace std;

#define B_N 10
int t = 2;
//B�����ṹ
struct node
{
	int n;//��ǰ�洢�ڽ��x�еĹؼ�����
	char key[B_N];//n���ؼ��֣��Էǽ�����
	bool leaf;//TRUE:x��Ҷ�ӣ�FALSE:x���ڽ��
	node *child[B_N + 1];//ָ����n+1�����ӵ�ָ��
					   //���캯��
	node(int num, bool IsLeaf) :n(num), leaf(IsLeaf) {}
	//���̶�д����
	void Disk_Read() {}
	void Disk_Write() {}
};
//B���ṹ
class B_Tree
{
public:
	//ָ������
	node *root;
	B_Tree() :root(NULL) {}

	//����xΪ����������Ѱ�ҹؼ���Ϊk�Ľ�㣬���ҵ������������y�У��������ǵڼ����ؼ���
	int B_Tree_Search(node *x, char k, node&y);
	//����һ�ô������Ŀ���
	void B_Tree_Create();
	//���ѣ���y����Ϊ������㣬ѡ������һ���ؼ��ֲ��뵽x�еĵ�i��λ��
	void B_Tree_Split_Child(node *x, int i, node *y);
	//���ؼ���k���뵽һ��δ���Ľ��x��
	void B_Tree_Insert_Nonfull(node *x, char k);
	//��T�в���ؼ���k
	void B_Tree_Insert(char k);
	//ɾ��T���йؼ���Ϊk�Ľ�㣬�����ǵݹ鷽������ǰ�������x���
	void B_Tree_Delete(node *x, char k);
	//���ؼ��ִ�С����������
	void Print(node *n);
	//����B��
	void Destory(node *n);
};

//����xΪ����������Ѱ�ҹؼ���Ϊk�Ľ�㣬���ҵ������������y�У��������ǵڼ����ؼ���
int B_Tree::B_Tree_Search(node *x, char k, node&y)
{
	int i = 1;
	//�ҵ���һ���ؼ��ֲ�����k��i
	while (i < x->n && k > x->key[i])
		i++;
	//��key[i] = k�����ҵ���
	if (i <= x->n && k == x->key[i])
	{
		//���������y��
		y = *x;
		//�������ǵڼ����ؼ���
		return i;
	}
	//��û�ҵ����򷵻ؿ�
	if (x->leaf)
	{
		//	&y = NULL;
		return 0;
	}
	//���������������ң���ݹ���ҵ�i������
	x->child[i]->Disk_Read();
	return B_Tree_Search(x->child[i], k, y);
}
//����һ�ô������Ŀ���
void B_Tree::B_Tree_Create()
{
	//����һ�������
	//��ʼʱ�������ΪҶ�ӽ�㣬�������û�йؼ���
	root = new node(0, true);
	root->Disk_Write();
}
//���ѣ���y����Ϊ������㣬ѡ������һ���ؼ��ֲ��뵽x�еĵ�i��λ��
void B_Tree::B_Tree_Split_Child(node *x, int i, node *y)
{
	int j;
	//����һ���½��z
	//Ҫ��y����Ϊy��z�����z��Ҷ��������y��ͬ
	//����ǰy��2t-1���ؼ��֣����Ѻ�ǰt-1������y����t-1������z���м��t������x
	node *z = new node(t - 1, y->leaf);
	y->n = t - 1;
	//��t-1���ؼ������θ��Ƹ�z
	for (j = 1; j < t; j++)
		z->key[j] = y->key[j + t];
	//����к��ӣ�����ҲҪ���ƹ�ȥ��ԭ����2t��������ǰt������y����t������z
	if (y->leaf == false)
	{
		for (j = 1; j <= t; j++)
			z->child[j] = y->child[j + t];
	}
	//ʹz��Ϊx�ĵ�i+1������(y�Ѿ���x�ĵ�i������)
	for (j = x->n + 1; j > i; j--)
		x->child[j + 1] = x->child[j];
	x->child[i + 1] = z;
	//��y�е�t���ؼ��ֲ��뵽x�ĵ�i��λ��
	for (j = x->n; j >= i; j--)
		x->key[j + 1] = x->key[j];
	x->key[i] = y->key[t];
	//x�Ĺؼ���+1
	x->n++;
	y->Disk_Write();
	z->Disk_Write();
	x->Disk_Write();
}
//���ؼ���k���뵽һ��δ���Ľ��x��
void B_Tree::B_Tree_Insert_Nonfull(node *x, char k)
{
	int i = x->n;
	//��x��Ҷ�ӽ��
	if (x->leaf)
	{
		//�ҵ��ò����λ��
		while (i >= 1 && k < x->key[i])
		{
			x->key[i + 1] = x->key[i];
			i--;
		}
		//����ؼ���k
		x->key[i + 1] = k;
		x->n++;
		x->Disk_Write();
	}
	//������Ҷ�ӽ��
	else
	{
		//�ҵ��ò����λ��
		while (i >= 1 && k < x->key[i])
			i--;
		i++;
		//��ȡ�亢�ӣ����ؼ��ֲ��뵽���ĺ����У����������
		x->child[i]->Disk_Read();
		//��������
		if (x->child[i]->n == 2 * t - 1)
		{
			//�Ժ���ִ�з��Ѳ��������Ѻ󣬺��Ӳ���Ϊ����
			B_Tree_Split_Child(x, i, x->child[i]);
			if (k > x->key[i])
				i++;
		}
		//���Ӳ�����ֱ�ӶԺ��ӽ��в������
		B_Tree_Insert_Nonfull(x->child[i], k);
	}
}
//��T�в���ؼ���k
void B_Tree::B_Tree_Insert(char k)
{
	node *r = root, *s;
	//�����������
	if (r->n == 2 * t - 1)
	{
		//����һ���µĽ��,���µĽ����Ϊ�����
		root = new node(0, false);
		root->child[1] = r;
		//��ԭ��������Ϊ������㣬�ֱ���Ϊs�ĵ�0�����Ӻ͵�1������
		B_Tree_Split_Child(root, 1, r);
		//�ѹؼ���k���뵽������У���ʱ�����һ������
		B_Tree_Insert_Nonfull(root, k);
	}
	//������㲻��
	else
		//ֱ�Ӱѹؼ��ֲ��뵽�������
		B_Tree_Insert_Nonfull(r, k);
}
//ɾ��T���йؼ���Ϊk�Ľ�㣬�����ǵݹ鷽������ǰ�������x���
void B_Tree::B_Tree_Delete(node *x, char k)
{
	int i, j;
	//�ҵ�x�е�һ����С��k�Ĺؼ��֣����������λ��
	for (i = 1; i <= x->n; i++)
		if (x->key[i] >= k)
			break;
	//y�ǹؼ���k֮ǰ�Ľ��,��С��k�������
	//z�ǹؼ���k֮��Ľ��,������k����С����
	node *y = x->child[i], *z = x->child[i + 1], *d;
	//���ؼ���k�ڽ��x�еĵ�i��λ��
	if (x->key[i] == k && i <= x->n)
	{
		//1)y��Ҷ�ӽ�㣬��ֱ�Ӵ�x��ɾ��k
		if (x->leaf == true)
		{
			//�ؼ�������ǰ��
			for (j = i; j < x->n; j++)
				x->key[j] = x->key[j + 1];
			//�ؼ�����-1
			x->n--;
			if (x->n == 0 && root == x)
			{
				delete x;
				root = NULL;
			}
			return;
		}
		//2)x���ڽ��
		//2-a��x��ǰ��k���ӽ��y��������t���ؼ���
		if (y->n >= t)
		{
			//�ҳ�k����yΪ���������е�ǰ��d
			d = y;
			while (d->leaf == false)
				d = d->child[d->n + 1];
			//��dȡ��k
			x->key[i] = d->key[d->n];
			//�ݹ��ɾ��d
			B_Tree_Delete(y, d->key[d->n]);
			//Destory(y);
		}
		//2-b��x��λ��k֮����ӽ��z��������t���ؼ���
		else if (z->n >= t)
		{
			//�ҳ�k����zΪ���������еĺ��d
			d = z;
			while (d->leaf == false)
				d = d->child[1];
			//��dȡ��k
			x->key[i] = d->key[1];
			//�ݹ��ɾ��d
			B_Tree_Delete(z, d->key[1]);
			//Destory(z);
		}
		//2-c��y��z��ֻ��t-1���ؼ��֣���k��z�����йؼ��ֺϲ���y��ʹ��xʧȥk��ָ��z��ָ��
		else
		{
			//��k�ؼ��ֺϲ���y
			y->key[y->n + 1] = k;
			//��z�����йؼ��ֺϲ���y
			for (j = 1; j <= z->n; j++)
				y->key[y->n + j + 1] = z->key[j];
			//����к��ӣ�����ҲҪ�ϲ�
			if (y->leaf == false)
			{
				//ʹ��xָ��z��ָ��
				for (j = 1; j <= z->n + 1; j++)
					y->child[y->n + j + 1] = z->child[j];
			}
			//y����2t-1���ؼ���
			y->n = y->n + 1 + z->n;
			//ʹ��xʧȥk
			for (j = i; j < x->n; j++)
				x->key[j] = x->key[j + 1];
			//ʹxʧȥָ��z��ָ��
			for (j = i + 1; j <= x->n; j++)
				x->child[j] = x->child[j + 1];
			x->n--;
			//���x�Ǹ���㣬x
			if (x->n == 0 && root == x)
			{
				delete x;
				root = y;
			}
			//�ͷ�z
			delete z;
			//��k��y�еݹ�ɾ��
			B_Tree_Delete(y, k);
			//Destory(y);
		}
	}
	//3)�ؼ��ֲ��ڽ��x�У���ض�����k����ȷ�������ĸ�x->child[i]
	else
	{
		//x��Ҷ�ӽ��,�ҵ�����㶼û���ҵ�k����k��������
		if (x->leaf == true)
		{
			cout << "error:not exist" << endl;
			return;
		}
		//x���ڽ��
		//3-a:child[i]��ֻ��t-1���ؼ���
		if (y->n == t - 1)
		{
			//���������ֵ�x->child[i+1](��z��ʾ)��������t���ؼ���
			if (i <= x->n && i <= x->n && z->n >= t)
			{
				//��x�еĹؼ����½���y
				y->n++;
				y->key[y->n] = x->key[i];
				//��z��ĳһ�ؼ���������x
				x->key[i] = z->key[1];
				for (j = 1; j < z->n; j++)
					z->key[j] = z->key[j + 1];
				//��z�ʺϵ���Ůָ���Ƶ�y
				if (y->leaf == false)
				{
					y->child[y->n + 1] = z->child[1];
					for (j = 1; j <= z->n; j++)
						z->child[j] = z->child[j + 1];
				}
				//z�Ĺؼ�����-1
				z->n--;
			}
			//���������ֵ�x->child[i-1]��������t���ؼ���
			else if (i > 1 && x->child[i - 1]->n >= t)
			{
				//��x�еĹؼ����½���y
				for (j = y->n; j >= 1; j--)
					y->key[j + 1] = y->key[j];
				y->key[1] = x->key[i - 1];
				y->n++;
				//��y�������ֵ�x->child[i-1]��ĳһ�ؼ���������x
				x->key[i - 1] = x->child[i - 1]->key[x->child[i - 1]->n];
				//�����ֵ��ʺϵ���Ůָ���Ƶ�y
				if (y->leaf == false)
				{
					for (j = y->n; j >= 1; j--)
						y->child[j + 1] = y->child[j];
					y->child[1] = x->child[i - 1]->child[x->child[i - 1]->n + 1];
				}
				//x->child[i-1]�Ĺؼ�����-1
				x->child[i - 1]->n--;
			}
			//y�������������ֵܶ�ֻ��t-1���ؼ��֣���������һ���ֵܺϲ�
			else
			{
				//�����һ�����(��z��ʾ)�ϲ�
				if (i <= x->n)
				{
					//��x->key[i]����y��
					y->key[y->n + 1] = x->key[i];
					//��z�����йؼ��ֲ���y��
					for (j = 1; j <= z->n; j++)
						y->key[j + y->n + 1] = z->key[j];
					//����к��ӣ����к���ҲҪ����
					if (y->leaf == false)
					{
						for (j = 1; j <= z->n + 1; j++)
							y->child[j + y->n + 1] = z->child[j];
					}
					//�޸�y�Ĺؼ�����
					y->n = y->n + 1 + z->n;
					//��x->key[i]��x���Ƴ�
					for (j = i; j < x->n; j++)
						x->key[j] = x->key[j + 1];
					//��ָ��z��ָ���x->child���Ƴ�
					for (j = i + 1; j <= x->n; j++)
						x->child[j] = x->child[j + 1];
					//x�Ĺؼ�����-1
					x->n--;
					delete z;
					//������㱻ɾ�������¸����
					if (x->n == 0 && root == x)
					{
						delete x;
						root = y;
					}
				}
				//��ǰ��һ�����ϲ�
				else
				{
					//��z=x->child[i-1],y=x->child[i]����z����y��
					z = y; i--;
					y = x->child[i];
					//��x->key[i]����y��
					y->key[y->n + 1] = x->key[i];
					//��z�����йؼ��ֲ���y��
					for (j = 1; j <= z->n; j++)
						y->key[j + y->n + 1] = z->key[j];
					//����к��ӣ����к���ҲҪ����
					if (y->leaf == false)
					{
						for (j = 1; j <= z->n + 1; j++)
							y->child[j + y->n + 1] = z->child[j];
					}
					//�޸�y�Ĺؼ�����
					y->n = y->n + 1 + z->n;
					//��x->key[i]��x���Ƴ�
					for (j = i; j < x->n; j++)
						x->key[j] = x->key[j + 1];
					//��ָ��z��ָ���x->child���Ƴ�
					for (j = i + 1; j <= x->n; j++)
						x->child[j] = x->child[j + 1];
					//x�Ĺؼ�����-1
					x->n--;
					//������㱻ɾ�������¸����
					delete z;
					if (x->n == 0 && root == x)
					{
						delete x;
						root = y;
					}
				}
			}
		}
		//�ݹ�ִ��ɾ������
		B_Tree_Delete(y, k);
	}
}
//���ؼ��ִ�С����������
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
