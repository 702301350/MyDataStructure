#ifndef MYBINTREE_IMPL_HPP_
#define MYBINTREE_IMPL_HPP_

#include "myBinTree_decl.hpp"

//
// isEmpty 返回树是否为空
//
template<typename T>
bool BinTree<T>::empty() const {
	return root == nullptr;
}

//
// clear 清空树
//
template<typename T>
void BinTree<T>::clear() {
	if ( empty() ) return;

	Queue<Node*> q;
	q.push(root);

	while ( !q.empty() ) {
		Node* tmp = q.front();
		q.pop();

		if ( tmp -> left  != nullptr ) q.push(tmp -> left);
		if ( tmp -> right != nullptr ) q.push(tmp -> right);
	
		delete tmp;
	}

	hashMap.clear();
	root = nullptr;
}


//
// traverse 返回遍历数组
//
// @param mode 遍历模式
//			   PRECO     先序
//             MIDO      中序
//             AFTERO    后序
template <typename T>
Array<T> BinTree<T>::traverse(int mode) {
	Array<T> res;
	switch( mode ) {
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
			throw std::out_of_range("[BinTree]: Cannot Find The Mode!");
	}
	return res;
}

//
// insert 将元素出入到编号为 num 节点的左右边
//
// @param val 插入的值   compare 自定义判断函数
//
template<typename T>
void BinTree<T>::insert(const T val, const String _id) {
	if ( hashMap.count(_id) ) {
		throw std::out_of_range("[BinTree]: Id Is Duplicated!");
		return;
	}
	hashMap.insert(_id);

	Node *node = new Node(val, _id);
	Node *ptr  = root;

	while ( ptr != nullptr ) {
		if ( compare(node -> data, ptr -> data) ) {
			if ( ptr -> left == nullptr ) {
				ptr -> left = node;
				break;
			}
			ptr = ptr -> left;
		}
		else {
			if ( ptr -> right == nullptr ) {
				ptr -> right = node;
				break;
			}
			ptr = ptr -> right;
		}
	}

	if ( root == nullptr ) {
		root = node;
	}
}

//
// count 查找元素是否存在
//
// @param val 查询元素值
//
template<typename T>
bool BinTree<T>::has(const T val) const {
	Node *ptr = root;
	
	while ( ptr != nullptr ) {
		if ( ptr -> data == val ) { 
			return true;
		}
		if ( compare(val, ptr -> data) ) {
			ptr = ptr -> left;
		}
		else {
			ptr = ptr -> right;
		}
	}
	return false;
}

//
// get 获取id编号对应元素的值
//
// @param _id 查询的编号
//
template<typename T>
T& BinTree<T>::get(const String _id) const {
	Node* ptr = find(_id);
	if ( ptr != nullptr ) {
		return ptr -> data;
	}
	else {
		throw std::out_of_range("[BinTree]: Cannot Get Value From A Undeclared Id.");
		return 0;
	}
}

//
// delSubTree 删除对应编号的子树
// 
// @param _id 删除的编号
//
template<typename T>
void BinTree<T>::delSubTree(const String _id) {
	Node *now = find(_id);
	if ( now != nullptr ) {
		//遍历删除结点
		std::function<void (Node*)>func;
		func = [&](Node* ptr) {
			if ( ptr == nullptr ) return;

			func(ptr -> left);
			func(ptr -> right);

			if ( ptr != now ) {
				hashMap.erase(ptr -> id);
				delete ptr;
			}
		};

		func(now);
		
		now -> left = nullptr;
		now -> right = nullptr;
	}
	else {
		throw std::out_of_range("[BinTree]: Cannot Erase A Undeclared Id.");		
	}
}

//
// merge 二叉树嫁接
//
// @param node 被合并的二叉树的结点
//
template <typename T>
void BinTree<T>::merge(BinTree<T>* tree) {
		Node* now = tree -> root;
		
		//遍历添加结点
		std::function<void (Node*)>func;
		func = [&](Node* ptr) {
			if ( ptr == nullptr ) return;

			insert(ptr -> data, ptr -> id);

			func(ptr -> left);
			func(ptr -> right);
		};

		func(now);
}

//
// erase 删除对应编号的结点
//
// @param _id 删除的编号
//
template<typename T>
void BinTree<T>::erase(const String _id) {
	Array<std::pair<T, String>> arr;

	// 遍历储存
	std::function<void (Node*)>func;
	func = [&](Node* ptr) {
		if ( ptr == nullptr ) return;
		
		if ( ptr -> id != _id ) {
			arr.push_back({ptr -> data, ptr -> id});
		}

		func(ptr -> left);
		func(ptr -> right);
		
		delete ptr;
	};
	func(root);

	// 重新构建树
	root = nullptr;
	hashMap.clear();
	for (auto &x : arr) {
		insert(x.first, x.second);
	}
}

//
// isFull 判断二叉树是否是满二叉树
//
template<typename T>
bool BinTree<T>::isFull() const {
	return (1 << deepth()) - 1 == size();
}

//
// isComplete 判断二叉树是否是完全二叉树
//
template<typename T>
bool BinTree<T>::isComplete() const {
	if ( root == nullptr ) return true;

	Queue<Node*> q;
	q.push(root);

	int flag = 0;
	while ( !q.empty() ) {
		Node* tmp = q.front();
		q.pop();

		if ( tmp == nullptr ) {
			flag = 1;
		}
		else {
			if ( flag ) { 
				return false;
			}
			q.push(tmp -> left);
			q.push(tmp -> right);
		}
	}
	return true;
} 

//
// size 返回该二叉树的大小
//
template<typename T>
const size_t BinTree<T>::size() const {
	if ( root == nullptr ) return 0;

	Queue<Node*> q;
	q.push(root);

	size_t _size = 0;
	while ( !q.empty() ) {
		Node* tmp = q.front();
		q.pop();

		if ( tmp != nullptr ) _size ++;
		if ( tmp -> left  != nullptr ) q.push(tmp -> left);
		if ( tmp -> right != nullptr ) q.push(tmp -> right);
	}
	return _size;
}

//
// deepth 返回该二叉树的深度
//
template<typename T>
const size_t BinTree<T>::deepth() const {
	// 遍历获取深度
	std::function<size_t (Node*)>func;
	func = [&](Node* ptr) {
		if ( ptr == nullptr ) return 0;

		int l = func(ptr -> left);
		int r = func(ptr -> right);

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
typename BinTree<T>::Node* BinTree<T>::find(const String _id) const {
	Node *now = root, *res = nullptr;

	//遍历查找结点
	std::function<Node* (Node*)>func;
	func = [&](Node* ptr) -> Node* {
		if ( ptr == nullptr ) { 
			return nullptr;
		}
		if ( ptr -> id == _id ) {
			return ptr;
		} 

		Node* t = func(ptr -> left);
		if ( t != nullptr ) return t;

		return func(ptr -> right);
	};

	return func(now);
}

//
// pre_traverse 先序遍历
//
// @param node 遍历的二叉树  arr 输出的遍历数组
//
template<typename T>
void BinTree<T>::pre_traverse(typename BinTree<T>::Node* node, Array<T>& arr) {
	if ( node == nullptr ) return;
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
void BinTree<T>::mid_traverse(typename BinTree<T>::Node* node, Array<T>& arr) {
	if ( node == nullptr ) return;

	mid_traverse(node -> left, arr);

	arr.push_back(node -> data);

	mid_traverse(node -> right, arr);
}

//
// aft_traverse 中序遍历
//
// @param node 遍历的二叉树 arr 输出的遍历数组
//
template<typename T>
void BinTree<T>::aft_traverse(typename BinTree<T>::Node* node, Array<T>& arr) {
	if ( node == nullptr ) return;

	aft_traverse(node -> left, arr);
	aft_traverse(node -> right, arr);

	arr.push_back(node -> data);
}

#endif