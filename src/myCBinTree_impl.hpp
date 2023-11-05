#ifndef MYCBINTREE_IMPL_HPP_
#define MYCBINTREE_IMPL_HPP_

#include "myCBinTree_decl.hpp"

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
// aft_traverse 中序遍历
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


#endif