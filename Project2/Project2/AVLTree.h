#pragma once
#include <iostream>
using namespace std;
#include<assert.h>
//���ȶ�����

template <class K, class V>

struct NodeTree
{
	int _bf;//ƽ������
	pair<K, V> _kv;//�����������
	NodeTree<K, V>* _left;
	NodeTree<K, V>* _right;
	NodeTree<K, V>* _parent;//ΪʲôҪ������һ����ָ���أ�Ϊ�˺������ϸ���ƽ�����ӷ���

	NodeTree(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
	{ }

};

template <class K, class V>
class AVLTree
{

	typedef NodeTree<K, V> Node;
public:

	bool Insert(const pair<K, V>& kv)
	{
		//AVL���Ĳ�������������Ĳ���+����ƽ������
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		//˵���ö��������ǿ�������ô�ͽ��бȽ��ҵ�λ��
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				//��¼����λ��
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		//�ߵ��������curΪ���ˣ�����λ���Ѿ��ҵ���
		cur = new Node(kv);

		if (kv.first > parent->_kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		//ע�����������������Ҫע�⸸ָ��
		cur->_parent = parent;
		//�����������Ѿ���ɣ�������AVL������Ҫ����ƽ������
		while (parent)//���ϲ��ϸ��£�ֱ�����µ�����㣬���������Ͳ���Ҫ������
		{
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}
			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				//˵���������߶ȸı䣬��Ӱ�����ȣ���Ҫ���ϸ���ƽ������
				cur = parent;
				parent = parent->_parent;
			
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//˵������������ˣ���Ҫ��������ת,����ƽ��
				//���ľ�����cur�������Ϊparent���ҽ�㣬��parent��Ϊcur�����㡣
				//Ҫ����ת����Ȼ��һ����������
				// ��ת��ƽ�⣬�߶ȱ��


				//��ƽ���������кܶ���
				if (parent->_bf == 2 && cur->_bf == 1)//��������ǵ����ұ߸ߣ��������ɽ��
				{
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == -1)//��������ǵ�����߸ߣ��ҵ������ɽ��
				{
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)//����������ǲ��ǵ�����һ�߸��ˣ����ǳ������ߣ�һ�߸�һ�ߵͣ���Ҫʹ��˫��������Ҫ�ȶ�curʹ���������ٶ�parentʹ������
				{
					RotateRL(parent);

				}
				else if (parent->_bf == -2 && cur->_bf == 1)//�������Ҳ�����ߣ����ǵ�����һ�߸ߣ���Ҫʹ��˫������ʹ��������ʹ������
				{
					RotateLR(parent);

				}
				//��������break��ȥ
				break;
			}
			else
				{
					assert(false);
				}
			
		}
		return true;
	}
	void RotateL(Node* parent)//����
	{

		Node* cur = parent->_right;
		
		Node* curleft = cur->_left;
		parent->_right = curleft;
		if (curleft)
		{
			curleft->_parent = parent;
		}
		cur->_left = parent;
		Node* pp = parent->_parent;
		parent->_parent = cur;



		if (parent==_root)
		{
			//��ô����cur���Ǹ������
			_root = cur;
			cur->_parent = nullptr;
		}
		else
		{
			if (pp->_left == parent)
			{
				pp->_left = cur;
			}
			else
			{
				pp->_right = cur;
			}

			cur->_parent = pp;
			//��ת��cur��parent bf��Ϊ0?
		}
		cur->_bf = parent->_bf = 0;
	}
	void RotateR(Node* parent)//�ҵ���
	{
		Node* cur = parent->_left;

		Node* curright = cur->_right;
		
		parent->_left = curright;
		if (curright)
		{
			curright->_parent = parent;
		}
		Node* ppnode = parent->_parent;
		cur->_right = parent;
		parent->_parent = cur;

		if (ppnode == nullptr)
		{
			//˵��cur�ͱ�ɸ��ڵ���
			_root = cur;
			cur->_parent = nullptr;
		}
		else
		{
			if (ppnode->_left == parent)
			{
				ppnode->_left = cur;
			}
			else
			{
				ppnode->_right = cur;
			}
			cur->_parent = ppnode;
		}
		cur->_bf = parent->_bf = 0;
	}
	void RotateRL(Node* parent)
	{

		//˫����ע�⻹Ҫ����ƽ�����ӣ���Ϊ˫����cur parent��ƽ�����Ӷ���0�˲�����
		//����curleft��ƽ��������ȷ��˭��ƽ��������Ҫ����
		Node* cur = parent->_right;
		Node* curleft = cur->_left;

		RotateR(parent->_right);//�ȶ�curʹ������
		RotateL(parent);//�ٶ�parent����
		if (curleft->_bf == 0)
		{
			curleft->_bf = 0;
			cur->_bf = 0;
			parent->_bf = 0;
		}
		else if (curleft->_bf == -1)
		{
			cur->_bf = 1;
			parent->_bf = 0;
			curleft->_bf = 0;
		}
		else if (curleft->_bf == 1)
		{
			parent->_bf = -1;
			cur->_bf = 0;
			curleft->_bf = 0;
		}
		//˫���󣬾Ϳ���ֱ��break�ˣ�
		else
		{
			assert(false);
		}
	}
	void RotateLR(Node* parent)
	{
		
		//�ȼ�¼λ��������ת
		// 
		//�����Ҫ����ƽ������
		Node* cur = parent->_left;
		Node* curright = cur->_right;

		RotateL(parent->_left);//�ȶ�curʹ������
		RotateR(parent);//�ٶ�parentʹ������
		if (curright->_bf == 0)
		{
			//������Ϲ�ϵ
			cur->_bf = 0;
			parent->_bf = 0;
			curright->_bf = 0;
		}
		else if (curright->_bf == -1)
		{
			cur->_bf = 0;
			parent->_bf = 1;
			curright->_bf = 0;
		}
		else if (curright->_bf == 1)
		{
			cur->_bf = -1;
			parent->_bf = 0;
			curright->_bf = 0;
		}
		//˫���󣬾Ϳ���ֱ��break�ˣ�
	
	}
	
	

	int Heigh(Node* root)//����������ĸ߶ȵ�
	{
 		if (root == nullptr)
			return 0;

		int HeightL = Heigh(root->_left);
		int HeightR = Heigh(root->_right);

		return HeightL > HeightR ? HeightL + 1 : HeightR + 1;
	}

	bool _isbalance(Node* root)//����������Ƿ�ƽ���
	{
		if (root == nullptr)
			return true;

		int highL = Heigh(root->_left);
		int highR = Heigh(root->_right);

		if (highR - highL != root->_bf)
		{
			cout << "ƽ�������쳣:" <<root->_kv.first<<"-"<< root->_bf << " " << endl;
			return false;
		}
		return abs(highR-highL)<2
			&& _isbalance(root->_left)
			&& _isbalance(root->_right);

	}
	bool isbalance()
	{
		return _isbalance(_root);
	}

private:
	Node* _root=nullptr;
};

#pragma once

#include<iostream>
#include<assert.h>
using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	pair<K, V> _kv;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;  // balance factor

	AVLTreeNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(kv);
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}

		cur->_parent = parent;

		// ... ����ƽ��
		// ����ƽ������
		while (parent)
		{
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else // if (cur == parent->_right)
			{
				parent->_bf++;
			}

			if (parent->_bf == 0)
			{
				// ���½���
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				// �������ϸ���
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				// ������ƽ���ˣ���Ҫ��ת
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					RotateRL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					RotateLR(parent);
				}

				break;
			}
			else
			{
				assert(false);
			}
		}


		return true;
	}

	void RotateL(Node* parent)
	{
		++_rotateCount;

		Node* cur = parent->_right;
		Node* curleft = cur->_left;

		parent->_right = curleft;
		if (curleft)
		{
			curleft->_parent = parent;
		}

		cur->_left = parent;

		Node* ppnode = parent->_parent;

		parent->_parent = cur;


		if (parent == _root)
		{
			_root = cur;
			cur->_parent = nullptr;
		}
		else
		{
			if (ppnode->_left == parent)
			{
				ppnode->_left = cur;
			}
			else
			{
				ppnode->_right = cur;

			}

			cur->_parent = ppnode;
		}

		parent->_bf = cur->_bf = 0;
	}


	void RotateR(Node* parent)
	{
		++_rotateCount;

		Node* cur = parent->_left;
		Node* curright = cur->_right;

		parent->_left = curright;
		if (curright)
			curright->_parent = parent;

		Node* ppnode = parent->_parent;
		cur->_right = parent;
		parent->_parent = cur;

		if (ppnode == nullptr)
		{
			_root = cur;
			cur->_parent = nullptr;
		}
		else
		{
			if (ppnode->_left == parent)
			{
				ppnode->_left = cur;
			}
			else
			{
				ppnode->_right = cur;
			}

			cur->_parent = ppnode;
		}

		parent->_bf = cur->_bf = 0;
	}

	void RotateRL(Node* parent)
	{
		Node* cur = parent->_right;
		Node* curleft = cur->_left;
		int bf = curleft->_bf;

		RotateR(parent->_right);
		RotateL(parent);

		if (bf == 0)
		{
			cur->_bf = 0;
			curleft->_bf = 0;
			parent->_bf = 0;
		}
		else if (bf == 1)
		{
			cur->_bf = 0;
			curleft->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1)
		{
			cur->_bf = 1;
			curleft->_bf = 0;
			parent->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	void RotateLR(Node* parent)
	{
		Node* cur = parent->_left;
		Node* curright = cur->_right;
		int bf = curright->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		if (bf == 0)
		{
			parent->_bf = 0;
			cur->_bf = 0;
			curright->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			cur->_bf = 0;
			curright->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = 0;
			cur->_bf = -1;
			curright->_bf = 0;
		}
	}

	int Height()
	{
		return Height(_root);
	}

	int Height(Node* root)
	{
		if (root == nullptr)
			return 0;

		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);

		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	bool IsBalance()
	{
		return IsBalance(_root);
	}

	bool IsBalance(Node* root)
	{
		if (root == nullptr)
			return true;

		int leftHight = Height(root->_left);
		int rightHight = Height(root->_right);

		if (rightHight - leftHight != root->_bf)
		{
			cout << "ƽ�������쳣:" << root->_kv.first << "->" << root->_bf << endl;
			return false;
		}

		return abs(rightHight - leftHight) < 2
			&& IsBalance(root->_left)
			&& IsBalance(root->_right);
	}

private:
	Node* _root = nullptr;

public:
	int _rotateCount = 0;
};
