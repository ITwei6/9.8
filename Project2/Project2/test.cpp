#include "AVLTree.h"
#include <vector>
void test()
{
	const int N = 10;
	vector<int> v = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	v.reserve(N);
	srand(time(0));
	/*for( int i = N; i > 1; i--)
	{
		v.push_back(i);
	}*/
	AVLTree<int, int> avt; 
	for (auto e : v)
	{
		avt.Insert(make_pair(e, e));
		if (e == 16)
		{
			cout << "-" << endl;
		}
		cout << "insert:" << e << "->" << avt.IsBalance() << endl;
	}
}
int main()
{
	
	test();
	//if (parent == grandfahter->left)
	//{
	//	Node* uncle = grandfather->right;
	//}
	//else//parent==grandfather->right 父亲在祖父的右边,那么叔叔就在左边
	//{
	//	Node* uncle = grandfather->left;

	//	//首先分析uncle存在并且为红的情况
	//	if (uncle&& uncle->color = RED)
	//	{
	//		//变色+向上处理
	//		//叔叔和祖父变色
	//		parent->color = uncle->color = BLACK;   
	//		grandfather->color = RED;
	//		//往上处理
	//		cur = grandfahter;
	//		parent = cur->parent;
	//	}
	//	else//uncle不存在或者uncle存在为黑色
	//	{
	//		//旋转+变色
	//		//如何旋转要看父亲和cur的位置关系
	//		if (cur == parent->right)//单纯右边高
	//		{
	//			rotateL(grandfahter);
	//			//变色
	//			parent->color = BLACK;
	//			grandfather->color = RED;

	//		}
	//		else
	//		{
	//			//要进行双旋,先右旋，再左旋
	//			rotateR(parent);
	//			rotateL(grandfather);
	//			//变色
	//			cur->color = BLACK;
	//			grandfather->color = RED;

	//		}
	//	}
	//}
	
}