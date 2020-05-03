#ifndef __HIERARCHICAL_LIST_H__
#define __HIERARCHICAL_LIST_H__

#include <stack>

using namespace std;

template <class T>
struct Node
{
	T data;
	Node<T>* pNext;
	Node<T>* pDown;
	Node() : data(), pNext(nullptr), pDown(nullptr) {}
};

template <class T>
class HierList
{
protected:
	Node<T>* pFirst;
	Node<T>* pCurrent;
	stack<Node<T>*> pre_levels;
public:
	HierList() : pFirst(nullptr), pCurrent(nullptr), length(0) {}
	HierList(const HierList<T>& _list);
	~HierList();

	HierList<T>& operator=(HierList<T>&& _list);
	
	void InsertNext(const T& _data);
	void InsertDown(const T& _data);
	bool GoNext();
	bool GoDown();
	bool GoUp();
	T& ReadCurrent();
};

#endif
