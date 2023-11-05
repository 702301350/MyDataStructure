#ifndef MYBBINTREE_IMPL_HPP_
#define MYBBINTREE_IMPL_HPP_

#include "myBBinTree_decl.hpp"

//
// isEmpty 返回树是否为空
//
template<typename T>
bool BBinTree<T>::empty() const {
	return root == nullptr;
}

//
// clear 清空树
//
template<typename T>
void BBinTree<T>::clear() {
	if (empty()) return;

	Queue<Node*> q;
	q.push(root);

	while (!q.empty()) {
		Node* tmp = q.front();
		q.pop();

		if (tmp->left != nullptr) q.push(tmp->left);
		if (tmp->right != nullptr) q.push(tmp->right);

		delete tmp;
	}

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
Array<T> BBinTree<T>::traverse(int mode) {
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
		throw std::out_of_range("[BBinTree]: Cannot Find The Mode!");
	}
	return res;
}

//
// insert 将元素出入到编号为 num 节点的左右边
//
// @param val 插入的值   compare 自定义判断函数
//
template<typename T>
void BBinTree<T>::insert(const T val) {
	Node* node = new Node(val);
	Node* ptr = root;

	while (ptr != nullptr) {
		if (compare(node->data, ptr->data)) {
			if (ptr->left == nullptr) {
				ptr->left = node;
				break;
			}
			ptr = ptr->left;
		}
		else {
			if (ptr->right == nullptr) {
				ptr->right = node;
				break;
			}
			ptr = ptr->right;
		}
	}

	if (root == nullptr) {
		root = node;
	}
}

//
// count 查找元素是否存在
//
// @param val 查询元素值
//
template<typename T>
bool BBinTree<T>::has(const T val) const {
	Node* ptr = root;

	while (ptr != nullptr) {
		if (ptr->data == val) {
			return true;
		}
		if (compare(val, ptr->data)) {
			ptr = ptr->left;
		}
		else {
			ptr = ptr->right;
		}
	}
	return false;
}

//
// merge 二叉树嫁接
//
// @param node 被合并的二叉树的结点
//
template <typename T>
void BBinTree<T>::merge(BBinTree& tree) {
	Node* now = tree.root;

	//遍历添加结点
	std::function<void(Node*)>func;
	func = [&](Node* ptr) {
		if (ptr == nullptr) return;

		insert(ptr->data);

		func(ptr->left);
		func(ptr->right);
	};

	func(now);
}

//
// erase 删除对应编号的结点
//
// @param _id 删除的编号
//
template<typename T>
void BBinTree<T>::erase(const T val, const size_t k) {
	size_t cnt = 0;
	Array<T>res;

	//遍历结点
	std::function<void(Node*)>func;
	func = [&](Node* ptr) {
		if (ptr == nullptr) return;

		if (ptr->data != val || cnt >= k) {
			res.push_back(ptr->data);
		}
		if (ptr->data == val && cnt < k) {
			cnt ++;
		}

		func(ptr->left);
		func(ptr->right);
	};
	func(root);

	// 重建树
	clear();
	for (T x : res) {
		insert(x);
	}
}

//
// isFull 判断二叉树是否是满二叉树
//
template<typename T>
bool BBinTree<T>::isFull() const {
	return (1 << deepth()) - 1 == size();
}

//
// isComplete 判断二叉树是否是完全二叉树
//
template<typename T>
bool BBinTree<T>::isComplete() const {
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
const size_t BBinTree<T>::size() const {
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
const size_t BBinTree<T>::deepth() const {
	// 遍历获取深度
	std::function<size_t(Node*)>func;
	func = [&](Node* ptr) {
		if (ptr == nullptr) return 0;

		int l = func(ptr->left);
		int r = func(ptr->right);

		return 1 + std::max(l, r);
	};

	return func(root);
}

//
// pre_traverse 先序遍历
//
// @param node 遍历的二叉树  arr 输出的遍历数组
//
template<typename T>
void BBinTree<T>::pre_traverse(typename BBinTree<T>::Node* node, Array<T>& arr) {
	if (node == nullptr) return;
	arr.push_back(node->data);

	pre_traverse(node->left, arr);
	pre_traverse(node->right, arr);
}

//
// mid_traverse 中序遍历
//
// @param node 遍历的二叉树 arr 输出的遍历数组
//
template<typename T>
void BBinTree<T>::mid_traverse(typename BBinTree<T>::Node* node, Array<T>& arr) {
	if (node == nullptr) return;

	mid_traverse(node->left, arr);

	arr.push_back(node->data);

	mid_traverse(node->right, arr);
}

//
// aft_traverse 后序遍历
//
// @param node 遍历的二叉树 arr 输出的遍历数组
//
template<typename T>
void BBinTree<T>::aft_traverse(typename BBinTree<T>::Node* node, Array<T>& arr) {
	if (node == nullptr) return;

	aft_traverse(node->left, arr);
	aft_traverse(node->right, arr);

	arr.push_back(node->data);
}

#endif
