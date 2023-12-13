# MyDataStructure

Some basics of DS in C++, Coding by myself.

Use  `make`  To Run This Code. 

You can test the Code by `main.cpp`.



Here's some details about these folders:

​	`src`  folder is where the source code for  `MyDataStucture` stored.

​	`problem` folder has some DS problems (updating).

In order to support template better, I use the file style just be like: xxx_decl.hpp, xxx_impl.hpp.

For Example,  `Array`  is declared in `myArray_decl.hpp`, and it's implementation is written in `myArray_impl.hpp`. If you want to use `Array`, just include `myArray.hpp` .



Here's some DS tools I wrote:

| Container                       | Name         | Head File       | Iterator    | Can Use Index |
| ------------------------------- | ------------ | --------------- | ----------- | ------------- |
| Array (数组)                    | array<T>     | myArray.hpp     | support     | support       |
| List (链表)                     | List<T>      | myList.hpp      | not support | support       |
| Stack (栈)                      | Stack<T>     | myStack.hpp     | not support | not support   |
| Queue (队列)                    | Queue<T>     | myQueue.hpp     | not support | not support   |
| String  (字符串)                | String       | myString.hpp    | support     | support       |
| Binary Tree (二叉树)            | CBinTree<T>  | myCBinTree.hpp  | not support | not support   |
| Binary Search Tree (二叉搜索树) | BBinTree<T>  | myBBinTree.hpp  | not support | not support   |
| Huffman Tree (哈夫曼树)         | HuffmTree<T> | myHuffmTree.hpp | not support | not support   |
| Heap (堆)                       | Heap<T>      | myHeap.hpp      | not support | not support   |
| Generalized table (广义表)      | GList<T>     | myGList.hpp     | not support | support       |



Here's the way to use these containers.

* Array

  * initalize it by: 
    * Array<T>a(n);                            generate a new array, length is n.
    * Array<T>a(n, val);                     generate a new array, length is n, each element is val.
    * Array<T>(others);                     generate a new array by other array.
    * Array<T>a = {1, 2, 3 ...};           generate a new array by {}.        

  * insert an element:
    * a.insert(val, idx);
    * a.push_back(val);
  * return special value:
    * a.back();
    * a[idx];
  * delete value from array:
    * a.erase(idx);
    * a.erase(iterator);
    * a.clear();

* List

  * initalize it by:
    * List<T>a(other)                       generate a new List by other list.
  * insert an element:
    * a.insert(val);
    * a.insert(val, idx);
  * return special value:
    * a[idx];                                       also support negtive number, means count backwards.
  * delete value from list:
    * a.erase(idx);
    * a.clear();

* Stack 

  * initalize it by:
    * Stack<T>a(other);                   generate a new Stack by other stack.
  * insert an element:
    * a.push(val);
  * pop the top:
    * a.pop();
  * return special value:
    * a.top();
  * delete all elements:
    * a.clear();

* Queue

  * initalize it by:
    * Queue<T>a(other);               generate a new Queue by other queue.
  * insert an element:
    * a.push(val);
  * pop the tail:
    * a.pop();
  * return special value:
    * a.front();
  * delete all elements;
    * a.clear();

* String

  * initalize it by:
    * String a = "ABCD";              generate a new String like C++ string.
    * String a = other;                 generate a new String by other.
    * String a("ABCD");               generate a new String by ()
    * String a = other;                 generate a new String by other.
  * insert an element or String:
    * a.addFront(ch);
    * a = a + ch;
    * a += ch;
  * delete elements from String:
    * a.pop_back();
    * a.erase(idx, len);
    * a.clear();
  * return special value:
    * a[idx];
    * a.substr(idx, len);
    * a.c_str();

* CBinTree

  * initalize it by:
    * initRoot(root);                                                                         generate a new Binary Tree by init root.
    * CBinTree<T>a(seq1, mode1, seq2, mode2);                     generate a new Binary Tree by two Array and two mode.
      * Use pre-order and mid-order to build a binary tree:    CBinTree<T>a(seq1, PRECO, seq2, MIDO);
      * Use aft-order and mid-order to build a binary tree:     CBinTree<T>a(seq1, AFTRO, seq2, MIDO);
  * insert an element:
    * a.insert(parent_id, side, value, id);                                      side includes: LEFT, RIGHT
  * modify by id:
    * a.modify(id, value);
  * traverse by mode:
    * a.traverse(mode)                               				    mode includes:  PRECO, MIDO, AFTRO
  * other function:
    * a.has(val);                                                                                find value is exist.
    * a.delSubTree(id);                                                                    delete the sub-tree of id.
    * a.isFull();                                                                                   whether it is a full binary tree.
    * a.isComplete();                                                                        whether it is a complete binary tree.

* BBinTree

  * initalize it by:
    * BBinTree<T>a(comparer);                                                     generate a new binary search tree by a compare function; 
  * insert an element:
    * a.insert(value);
  * traverse by mode:
    * a.traverse(mode);
  * other function
    * a.merge(other);
    * a.isFull();
    * a.isComplete();
    * a.has(value);

* Heap

  * insert an element:
    * a.insert(value);
  * return special value:
    * a.top();
  * delete the top of the heap:
    * a.pop();

* HuffmTree

  * initalize it by:
    * HuffmTree<T>a(data)                      generate a new HuffmTree by an Array.
    * HuffmTree<T>a(frqc);                      generate a new HuffmTree by a frequence map table, frqc is  `map<T, size_t>`.
  * export the huffman code:
    * a.export(data);
  * export the huffman code table:
    * a.exportTable();
  * analyze the huffman code and return the plaintext.
    * a.explain(huffman code);

* GList

  * initalize it by:
    * GList<T>a(node);                generate a new GList by a GList or just an element.
    * GList<T>a(value);               generate a new GList by an element.
    * GList<T>a = {A, {B, C}, {{D, E}, F}, G};   generate a new GList by {};
  * insert an element or a GList:
    * a.push_back(node);
    * a.push)back(value);
  * delete elements:
    * a.erase(idx);
  * other functions:
    * a[idx];                                 return the idx-th GList of entire GList, if it has not only one layer, you can use `a[idx][jdx][kdx]...`
    * a.front()                              return the first GList;
    * a.amount()                         return the number of GList;
    * a.getSubList()                    return the sub list of GList;



The Problem folders will be updated soon.

I'm a fresh man, some code may be not less than satisfactory, I will repair it after.

If you can feedback bugs or provide a better way to optimize these algorithms, I would be appreciated it a lot.
