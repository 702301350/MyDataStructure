#ifndef MYHEAP_DECL_HPP_
#define MYHEAP_DECL_HPP_

#include "myArray.hpp"

template<typename T, typename C = std::less<T>>
class Heap {
	private:
		Array<T> data;  // 数据组
		C cmp;          // 比较对象

	public:
		Heap() {}
		~Heap() {}

		// 插入元素
		void insert(T val);

		// 判断堆是否为空
		bool empty() const;	

		// 获取堆大小
		size_t size() const;

		// 获取栈顶
		T top() const;

		// 弹出栈顶
		void pop();

	private:
		// 上浮
		void up();

		// 下沉
		void down();
};

#endif