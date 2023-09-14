#pragma once
#include <iostream>
using namespace std;
#include<assert.h>
//首先定义结点

template <class K, class V>

struct NodeTree
{
	int _bf;//平衡因子
	pair<K, V> _kv;//结点里存的数据
	NodeTree<K, V>* _left;
	NodeTree<K, V>* _right;
	NodeTree<K, V>* _parent;//为什么要多增加一个父指针呢？为了后面往上更新平衡因子方便

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
		//AVL树的插入就是搜索树的插入+更新平衡因子
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		//说明该二叉树不是空树，那么就进行比较找到位置
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				//记录结点的位置
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
		//走到这里表明cur为空了，表明位置已经找到了
		cur = new Node(kv);

		if (kv.first > parent->_kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		//注意这个是三叉链，还要注意父指针
		cur->_parent = parent;
		//正常插入结点已经完成，接下来AVL树还需要更新平衡因子
		while (parent)//往上不断更新，直到更新到根结点，根结点上面就不需要更新了
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
				//说明该子树高度改变，会影响祖先，需要往上更新平衡因子
				cur = parent;
				parent = parent->_parent;
			
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//说明这个树生病了，需要调整，旋转,将树平衡
				//核心就是让cur的左结点成为parent的右结点，让parent成为cur的左结点。
				//要求旋转后，仍然是一个颗搜索树
				// 旋转后平衡，高度变低


				//不平衡的树情况有很多种
				if (parent->_bf == 2 && cur->_bf == 1)//这种情况是单纯右边高，左单旋即可解决
				{
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == -1)//这种情况是单纯左边高，右单旋即可解决
				{
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)//这种情况就是不是单纯的一边高了，而是出现曲线，一边高一边低，需要使用双旋这里需要先对cur使用右旋，再对parent使用左旋
				{
					RotateRL(parent);

				}
				else if (parent->_bf == -2 && cur->_bf == 1)//这种情况也是折线，不是单纯的一边高，需要使用双旋，先使用左旋再使用右旋
				{
					RotateLR(parent);

				}
				//最后调整完break出去
				break;
			}
			else
				{
					assert(false);
				}
			
		}
		return true;
	}
	void RotateL(Node* parent)//左单旋
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
			//那么这样cur就是根结点了
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
			//旋转后cur和parent bf都为0?
		}
		cur->_bf = parent->_bf = 0;
	}
	void RotateR(Node* parent)//右单旋
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
			//说明cur就变成根节点了
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

		//双旋后注意还要调整平衡因子，因为双旋后将cur parent的平衡因子都置0了不合理
		//根据curleft的平衡因子来确定谁的平衡因子需要调整
		Node* cur = parent->_right;
		Node* curleft = cur->_left;

		RotateR(parent->_right);//先对cur使用右旋
		RotateL(parent);//再对parent左旋
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
		//双旋后，就可以直接break了，
		else
		{
			assert(false);
		}
	}
	void RotateLR(Node* parent)
	{
		
		//先记录位置再能旋转
		// 
		//最后还需要调整平衡因子
		Node* cur = parent->_left;
		Node* curright = cur->_right;

		RotateL(parent->_left);//先对cur使用左旋
		RotateR(parent);//再对parent使用右旋
		if (curright->_bf == 0)
		{
			//减少耦合关系
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
		//双旋后，就可以直接break了，
	
	}
	
	

	int Heigh(Node* root)//用来检查树的高度的
	{
 		if (root == nullptr)
			return 0;

		int HeightL = Heigh(root->_left);
		int HeightR = Heigh(root->_right);

		return HeightL > HeightR ? HeightL + 1 : HeightR + 1;
	}

	bool _isbalance(Node* root)//用来检查树是否平衡的
	{
		if (root == nullptr)
			return true;

		int highL = Heigh(root->_left);
		int highR = Heigh(root->_right);

		if (highR - highL != root->_bf)
		{
			cout << "平衡因子异常:" <<root->_kv.first<<"-"<< root->_bf << " " << endl;
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

		// ... 控制平衡
		// 更新平衡因子
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
				// 更新结束
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				// 继续往上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				// 子树不平衡了，需要旋转
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
			cout << "平衡因子异常:" << root->_kv.first << "->" << root->_bf << endl;
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
