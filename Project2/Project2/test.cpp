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
	//else//parent==grandfather->right �������游���ұ�,��ô����������
	//{
	//	Node* uncle = grandfather->left;

	//	//���ȷ���uncle���ڲ���Ϊ������
	//	if (uncle&& uncle->color = RED)
	//	{
	//		//��ɫ+���ϴ���
	//		//������游��ɫ
	//		parent->color = uncle->color = BLACK;   
	//		grandfather->color = RED;
	//		//���ϴ���
	//		cur = grandfahter;
	//		parent = cur->parent;
	//	}
	//	else//uncle�����ڻ���uncle����Ϊ��ɫ
	//	{
	//		//��ת+��ɫ
	//		//�����תҪ�����׺�cur��λ�ù�ϵ
	//		if (cur == parent->right)//�����ұ߸�
	//		{
	//			rotateL(grandfahter);
	//			//��ɫ
	//			parent->color = BLACK;
	//			grandfather->color = RED;

	//		}
	//		else
	//		{
	//			//Ҫ����˫��,��������������
	//			rotateR(parent);
	//			rotateL(grandfather);
	//			//��ɫ
	//			cur->color = BLACK;
	//			grandfather->color = RED;

	//		}
	//	}
	//}
	
}