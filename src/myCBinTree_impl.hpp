#ifndef MYCBINTREE_IMPL_HPP_
#define MYCBINTREE_IMPL_HPP_

#include "myCBinTree_decl.hpp"

//
// CBinTree 逆向构造函数
//
// @param arr 已知二叉树各结点值     mode 是以 PRECO 先序
//                                           MIDO  中序
//                                           AFTRO 后序  形式表现的
template<typename T>
CBinTree<T>::CBinTree(Array<T>& seq1, int mode1, Array<T>& seq2, int mode2) {
	// 已知先序和中序
	if ( mode1 == PRECO && mode2 == MIDO ) {
		std::unordered_map<T, size_t> mid_map;
		
		for (int i = 0;i < seq2.size();i ++) {
			mid_map[ seq2[i] ] = i;
		}

		root = treeBuilder(seq1, 0, seq1.size() - 1, seq2, 0, seq2.size() - 1, mid_map);
	}
	// 已知中序和后序
	else if ( mode1 == MIDO && mode2 == AFTERO ) {
		std::unordered_map<T, size_t> mid_map;

		for (int i = 0;i < seq1.size();i ++) {
			mid_map[ seq1[i] ] = i;
		}

		long ed = seq2.size() - 1;
		root = treeBuilder(seq1, 0, seq1.size() - 1, seq2, ed, mid_map);
	}
	else {
		throw std::out_of_range("[CBinTree]: Invalid Pattern Combination!");
	}
}

//
// clear 清空二叉树函数
//
template<typename T>
void CBinTree<T>::clear() {
	if ( empty() ) return;

	Queue<Node*> q;
	q.push(root);

	while (!q.empty()) {
		Node* tmp = q.front();
		q.pop();

		if (tmp->left != nullptr) q.push(tmp->left);
		if (tmp->right != nullptr) q.push(tmp->right);

		delete tmp;
	}

	hashMap.clear();
	root = nullptr;
}

//
// empty 判断二叉树是否为空
//
template<typename T>
bool CBinTree<T>::empty() const {
	return root == nullptr;
}

//
// initRoot 初始化根结点
//
// @param  val  初始化的值
//
template<typename T>
void CBinTree<T>::initRoot(const T val) {
	if ( root != nullptr ) {
		throw std::out_of_range("[CBinTree]: Root Existed.");
		return;
	}

	root = new Node(val, "root");
	hashMap.insert("root");
}

//
// insert 插入函数
//
// @param _pa 被插入的编号   side 插入边  val 元素值  _id 插入编号
//
template<typename T>
void CBinTree<T>::insert(const String _pa, int side, const T val, const String _id) {
	Node* ptr = find(_pa);

	if ( ptr != nullptr ) {
		if ( hashMap.count(_id) ) {
			throw std::out_of_range("[CBinTree]: Id Is Duplicated!");
			return;
		}

		switch ( side ) {
			case LEFT: {
				if ( ptr -> left != nullptr ) {
					throw std::out_of_range("[CBinTree]: LEFT Full.");
					return;
				}
				ptr -> left = new Node(val, _id);;
			} break;

			case RIGHT: {
				if ( ptr -> right != nullptr ) {
					throw std::out_of_range("[CBinTree]: RIGHT Full.");
					return;
				}
				ptr -> right = new Node(val, _id);;
			} break;

			default:
				throw std::out_of_range("[CBinTree]: Side Need LEFT Or RIGHT.");
				return;
		}

		hashMap.insert(_id);
	}
	else {
		throw std::out_of_range("[CBinTree]: Cannot Find _pa Id.");
	}
}

//
// traverse 遍历函数
//
// @param mode 模式
//
template<typename T>
Array<T> CBinTree<T>::traverse(int mode) {
	Array<T> res;
	switch (mode) {
	case PRECO:
		pre_traverse(root, res);
		break;
	case MIDO:
		mid_traverse(root, res);
		break;
	case AFTERO:
		aft_traverse(root, res);
		break;
	default:
		throw std::out_of_range("[CBinTree]: Cannot Find The Mode!");
	}
	return res;
}

//
// has 元素是否存在函数
//
// @param val 元素值
//
template<typename T>
bool CBinTree<T>::has(const T val) const {
	bool flag = false;

	std::function<void (Node*)>func;
	func = [&](Node* ptr) {
		if ( ptr == nullptr ) return;

		if ( ptr -> data == val ) {
			flag = true;
			return;
		}

		func(ptr -> left);
		func(ptr -> right);
	};
	func(root);

	return flag;
}

//
// delSubTree 删除指定编号结点的子树
//
// @param id 指定编号
//
template<typename T>
void CBinTree<T>::delSubTree(const String _id) {
	Node* now = find(_id);
	if (now != nullptr) {
		//遍历删除结点
		std::function<void (Node*)>func;
		func = [&](Node* ptr) {
			if (ptr == nullptr) return;

			func(ptr->left);
			func(ptr->right);

			if (ptr != now) {
				hashMap.erase(ptr->id);
				delete ptr;
			}
		};

		func(now);

		now->left = nullptr;
		now->right = nullptr;
	}
	else {
		throw std::out_of_range("[CBinTree]: Cannot Erase A Undeclared Id.");
	}
}

//
// modify 通过id修改值
//
// @param _id 查询编号
//
template<typename T>
void CBinTree<T>::modify(const String _id, const T val) {
	Node* ptr = find(_id);
	if (ptr != nullptr) {
		ptr -> data = val;
	}
	else {
		throw std::out_of_range("[CBinTree]: Cannot Modify Value From A Undeclared Id.");
	}
}

//
// get 获取id编号对应元素的值
//
// @param _id 查询的编号
//
template<typename T>
T CBinTree<T>::get(const String _id) const {
	Node* ptr = find(_id);
	if (ptr != nullptr) {
		return ptr -> data;
	}
	else {
		throw std::out_of_range("[CBinTree]: Cannot Get Value From A Undeclared Id.");
		return 0;
	}
}

//
// isFull 判断二叉树是否是满二叉树
//
template<typename T>
bool CBinTree<T>::isFull() const {
	return (1 << deepth()) - 1 == size();
}

//
// isComplete 判断二叉树是否是完全二叉树
//
template<typename T>
bool CBinTree<T>::isComplete() const {
	if (root == nullptr) return true;

	Queue<Node*> q;
	q.push(root);

	int flag = 0;
	while (!q.empty()) {
		Node* tmp = q.front();
		q.pop();

		if (tmp == nullptr) {
			flag = 1;
		}
		else {
			if (flag) {
				return false;
			}
			q.push(tmp->left);
			q.push(tmp->right);
		}
	}
	return true;
}

//
// size 返回该二叉树的大小
//
template<typename T>
const size_t CBinTree<T>::size() const {
	if (root == nullptr) return 0;

	Queue<Node*> q;
	q.push(root);

	size_t _size = 0;
	while (!q.empty()) {
		Node* tmp = q.front();
		q.pop();

		if (tmp != nullptr) _size++;
		if (tmp->left != nullptr) q.push(tmp->left);
		if (tmp->right != nullptr) q.push(tmp->right);
	}
	return _size;
}

//
// deepth 返回该二叉树的深度
//
template<typename T>
const size_t CBinTree<T>::deepth() const {
	// 遍历获取深度
	std::function<size_t (Node*)>func;
	func = [&](Node* ptr) {
		if (ptr == nullptr) return 0;

		int l = func(ptr->left);
		int r = func(ptr->right);

		return 1 + std::max(l, r);
	};

	return func(root);
}

//
// find 查找函数
//
// @param _id 查询的id
//
template<typename T>
typename CBinTree<T>::Node* CBinTree<T>::find(const String _id) const {
	Node* now = root, * res = nullptr;

	//遍历查找结点
	std::function<Node* (Node*)>func;
	func = [&](Node* ptr) -> Node* {
		if (ptr == nullptr) {
			return nullptr;
		}
		if (ptr->id == _id) {
			return ptr;
		}

		Node* t = func(ptr->left);
		if (t != nullptr) return t;

		return func(ptr->right);
	};

	return func(now);
}

//
// pre_traverse 先序遍历
//
// @param node 遍历的二叉树  arr 输出的遍历数组
//
template<typename T>
void CBinTree<T>::pre_traverse(typename CBinTree<T>::Node* node, Array<T>& arr) {
	if (node == nullptr) return;
	arr.push_back(node -> data);

	pre_traverse(node -> left, arr);
	pre_traverse(node -> right, arr);
}

//
// mid_traverse 中序遍历
//
// @param node 遍历的二叉树 arr 输出的遍历数组
//
template<typename T>
void CBinTree<T>::mid_traverse(typename CBinTree<T>::Node* node, Array<T>& arr) {
	if (node == nullptr) return;

	mid_traverse(node -> left, arr);

	arr.push_back(node -> data);

	mid_traverse(node -> right, arr);
}

//
// aft_traverse 后序遍历
//
// @param node 遍历的二叉树 arr 输出的遍历数组
//
template<typename T>
void CBinTree<T>::aft_traverse(typename CBinTree<T>::Node* node, Array<T>& arr) {
	if (node == nullptr) return;

	aft_traverse(node -> left, arr);
	aft_traverse(node -> right, arr);

	arr.push_back(node -> data);
}

//
// treeBuilderPM 通过先序和中序构建二叉树的函数
//
// @param pre 先序数组   pre_st 先序起   pre_ed 先序终   mid 中序   mid_st 中序起   mid_ed 中序终  mid_hash 映射哈希表
//
template<typename T>
typename CBinTree<T>::Node* CBinTree<T>::treeBuilder(Array<T>& pre, size_t pre_st, size_t pre_ed, Array<T>& mid, size_t mid_st, size_t mid_ed, std::unordered_map<T, size_t>& mid_hash) {
	static long long cnt = 1;
    if ( pre_st > pre_ed || mid_st > mid_ed ) {
        return nullptr;
    }

	T val = pre[pre_st];
	
	Node* node = new Node(val, (empty()) ? "root" : String::toString(cnt ++));

	size_t idx  = mid_hash[val];
    size_t left = idx - mid_st;

    node -> left  = treeBuilder(pre, pre_st + 1, pre_st + left, mid, mid_st, idx - 1, mid_hash);
    node -> right = treeBuilder(pre, pre_st + left + 1, pre_ed, mid, idx + 1, mid_ed, mid_hash);

    return node;
}

//
// treeBuilderPM 通过先序和中序构建二叉树的函数
//
// @param pre 先序数组   pre_st 先序起   pre_ed 先序终   mid 中序   mid_st 中序起   mid_ed 中序终  mid_hash 映射哈希表
//
template<typename T>
typename CBinTree<T>::Node* CBinTree<T>::treeBuilder(Array<T>& mid, size_t mid_st, size_t mid_ed, Array<T>& aft, long& aft_ed, std::unordered_map<T, size_t>& mid_hash) {
	static long long cnt = 1;
    if ( mid_st > mid_ed || aft_ed < 0 ) {
        return nullptr;
    }

	T val = aft[aft_ed];
	
	Node* node = new Node(val, (empty()) ? "root" : String::toString(cnt ++));
	
	size_t idx = mid_hash[val];
	aft_ed --;

	node -> right = treeBuilder(mid, idx + 1, mid_ed, aft, aft_ed, mid_hash);
	node -> left  = treeBuilder(mid, mid_st, idx - 1, aft, aft_ed, mid_hash);
	return node;
}

#endif
