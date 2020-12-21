#pragma once

template<class T>
struct HaffmanNode
{
	T data;
	HaffmanNode<T> *left;
	HaffmanNode<T> *right;
	HaffmanNode()
	{
		left = NULL;
		right = NULL;
	}
	bool operator < (const HaffmanNode& o)
	{
		return data < o.data;
	}
	static void freemem(HaffmanNode<T> * root)
	{
		if (root != NULL)
		{
			freemem(root->left);
			freemem(root->right);
			delete root;
		}
	}
};