#ifndef MYSTACK_DECL_HPP_
#define MYSTACK_DECL_HPP_

#include "myArray.hpp"
#include "myList.hpp"

template<typename T>
class Stack {
	private:
		Array<T>data;

	public:
		Stack() {}
		Stack(const Stack<T>& other) {
			*this = other;
		}
		~Stack() {}

		// 弹出栈顶
		void pop();

		// 返回栈顶元素
		const T& top();

		// 入栈
		void push(T val);

		// 返回栈的大小
		size_t size();

		// 清空栈
		void clear();

		// 判断栈是否为空
		bool empty();

		// 重载= 赋值
		Stack<T>& operator=(const Stack<T>& other);

		// 重载= 赋值 常量
		const Stack<T>& operator=(const Stack<T>& other) const;
};

#endif
