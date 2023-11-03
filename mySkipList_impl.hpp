#ifndef MYSKIPLIST_IMPL_HPP_
#define MYSKIPLIST_IMPL_HPP_

//
// 构造初始化
//
// @param  level  初始化层数
template<typename T>
SkipList<T>::SkipList(const size_t level) {
	for (size_t i = 0;i < level;i ++) {
		layer.insert(nullptr);
	}
}

//
// 析构释放
//
template<typename T>
SkipList<T>::~SkipList() {
	clear();
}

//
// insert 插入元素函数
//
// @param val 插入元素值  s 为score分配
//
template<typename T>
void SkipList<T>::insert(const T val) {
	if ( s > 1 || s < 0 ) {
		throw std::out_of_range("[SkipList]: Score Out Of Range! Must Be [0, 1] \n");
		return;
	}
	if ( count(val) ) return;

	size_t curLevel = getRandom(s);
	Node *pre = nullptr;
	
	for (size_t i = 0; i < curLevel ;i ++) {
		Node *it, *cur = new Node(val, s);
		for (it = layer[i]; it -> next != nullptr ; it = it -> next) {
			if ( val > it -> elem ) {
				break;
			}
		}

		cur -> next = it -> next;
		cut -> pre = it;
		it -> next -> pre = cur;
		it -> next = cur;

		if ( pre != nullptr ) {
			cur -> down = pre;
		}

		pre = cur;
	}
}

//
// count 查询元素函数
//
// @param val 指查询元素值
//
template<typename T>
bool SkipList<T>::count(const T val) {
	size_t maxLevel = layer.length();
	
	for (Node* it = layer[maxLevel - 1]; it != nullptr; ) {
		if ( it -> elem == val ) {
			return true;
		}
		else if ( it -> elem < val ) {
			if ( it -> next != nullptr && it -> next -> elem > val ) {
				it = it -> down;
			}
			else {
				it = it -> next;
			}
		}
	}
	return false;
}

//
// erase 清除函数
//
// @param val 清除值
//
template<typename T>
void SkipList<T>::erase(const T val) {
	size_t maxLevel = layer.length();
	long curLevel = maxLevel - 1;

	for (Node* it = layer[maxLevel - 1]; it != nullptr ; ) {
		if ( it -> elem == val ) {
			for (Node *jt = it, *tmp = nullptr; jt != nullptr ;) {
				if ( jt == layer[curLevel] ) {
					layer[curLevel --] = jt -> next;
				}

				if ( jt -> pre != nullptr ) {
					jt -> pre -> next = jt -> next;
					
					if ( jt -> next != nullptr ) {
						jt -> next -> pre = jt -> pre;
					}
				}	

				tmp = jt;
				jt = jt -> down;
				delete tmp;
			}
			return;
		}
		else if ( it -> elem < val ) {
			if ( it -> next != nullptr && it -> next -> elem > val ) {
				it = it -> down;
				curLevel --;
			}
			else {
				it = it -> next;
			}
		}
	}

}

//
// clear 清空跳表
//
template<typename T>
void SkipList<T>::clear() {
	for (size_t i = 0; i < layer.length() ;i ++) {
		size_t len = layer[i].length();
		for (size_t j = 0; j < len ;j ++) {
			delete layer[i][j];
		}
		layer[i] = nullptr;
	}
}

//
// 随机生成层数
//
// @param s 指score的概率
//
template<typename T>
size_t SkipList<T>::getRandom(const double s) const {
	MY_SRAND_OPEN
	
	size_t maxLevel = layer.length();
	size_t curLevel = 0;

	while ( (rand() / double(RAND_MAX)) < s && curLevel < maxLevel ) {
		curLevel ++;
	}
	return curLevel;
}

#endif