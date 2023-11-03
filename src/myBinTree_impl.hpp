#ifndef MYBINTREE_IMPL_HPP_
#define MYBINTREE_IMPL_HPP_

#include "myBinTree_decl.hpp"

//
// isEmpty 返回树是否为空
//
template<typename T>
bool BinTree<T>::empty() const {
	return head == nullptr;
}

//
// clear 清空树
//
template<typename T>
void BinTree<T>::clear() {
	if ( empty() ) return;

	Queue<Node*> q;
	q.push(head);

	while ( !q.empty() ) {
		Node* tmp = q.front();
		q.pop();

		if ( tmp -> left  != nullptr ) q.push(tmp -> left);
		if ( tmp -> right != nullptr ) q.push(tmp -> right);
	
		delete tmp;
	}

	head = nullptr;
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
			pre_traverse(res);
			break;
		case MIDO:
			mid_traverse(res);
			break;
		case AFTERO:
			aft_traverse(res);
			break;
		default:
			throw std::out_of_range("[BinTree]: Cannot Find The Mode!");
	}
	return res;
}

//
// erase 删除对应编号的结点
//
// @param num  删除的编号
//
template<typename T>
void BinTree<T>::erase(const String num) {
	
}

//
// merge 二叉树嫁接
//
// @param node 被嫁接的二叉树的结点   side 嫁接的边
//
template <typename T>
void BinTree<T>::merge(typename BinTree<T>::Node* node, int side) {

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