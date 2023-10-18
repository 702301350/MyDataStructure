#ifndef MYSKIPLIST_DECL_HPP_
#define MYSKIPLIST_DECL_HPP_

#include "myDef.hpp"
#include "myArray.hpp"
#include "myList.hpp"

//跳表
template<typename T>
class SkipList {
	private:
		Array<List<T>>data;
	public:
		SkipList(size_t n) {
			data = Array<List<T>>(n);
		}
		SkipList(const SkipList<List<T>>& other) {
			*this = other;
		}

		~SkipList() {}

		// 插入元素
		void insert(const T val);

		// 删除元素
		void erase(size_t idx);

		// 查询元素存在
		bool count(const T val);

		// = 重载, 赋值
		SkipList<T>& operator=(const SkipList<List<T>>& other);

	private:
		// 获取随机层数
		size_t getRandom();
};

#endif