#ifndef MYQUEUE_DECL_HPP_
#define MYQUEUE_DECL_HPP_

#include "myArray.hpp"

template<typename T>
class Queue {
	private:
		Array<T>data;

	public:
		Queue() {}
		~Queue() {}

		// push 入队函数
		void push(T val);

		// pop 出队函数
		void pop();

		// 返回队列大小
		size_t size();

		// 获取队列首元素
		const T& front();

		// 查看元素是否为空
		bool empty();
};

#endif