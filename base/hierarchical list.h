#pragma once

#include <stack>

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
	std::stack<Node<T>*> pre_levels;
public:
	HierList() : pFirst(nullptr), pCurrent(nullptr) {}
	HierList(HierList<T>& _list);
	~HierList();

	HierList<T>& operator=(HierList<T>&& _list);
	
	void InsertNext(const T& _data); //if HierList is empty, insert first value
	void InsertDown(const T& _data); //only if current not nullptr
	void GoFirst();
	bool GoNext();
	bool GoDown();
	bool GoUp();
	T& ReadCurrent(); //only if current not nullptr
};

template<class T>
HierList<T>::HierList(HierList<T>& _list)
{
	pFirst = new Node<T>;
	pFirst->data = _list.pFirst->data;
	pCurrent = pFirst;
	_list.GoFirst();
	bool flag_not_all = true;
	while (true)
	{
		while (_list.GoDown())
		{
			InsertDown(_list.ReadCurrent());
			GoDown();
		}
		if (_list.GoNext())
		{
			InsertNext(_list.ReadCurrent());
			GoNext();
			continue;
		}

		flag_not_all = false;
		while (_list.GoUp())
		{
			GoUp();
			if (_list.GoNext())
			{
				InsertNext(_list.ReadCurrent());
				GoNext();
				flag_not_all = true;
				break;
			}
			else
				flag_not_all = false;
		}
		if (!flag_not_all) break;
	}
	GoFirst();
}

template<class T>
HierList<T>::~HierList()
{
	GoFirst();
	bool flag_not_all = true;
	Node<T>* del;
	while (true)
	{
		while (GoDown());
		del = pCurrent;
		if (GoNext())
		{
			delete del;
			continue;
		}

		flag_not_all = false;
		while (GoUp())
		{
			delete del;
			del = pCurrent;
			if (GoNext())
			{
				delete del;
				flag_not_all = true;
				break;
			}
			else
				flag_not_all = false;
		}
		if (!flag_not_all) {
			delete del;
			break;
		}
	}
}

template<class T>
HierList<T>& HierList<T>::operator=(HierList<T>&& _list)
{
	pFirst = _list.pFirst;
	_list.pFirst = nullptr;
	pCurrent = _list.pCurrent;
	_list.pCurrent = nullptr;
	stack<Node<T>*> tmp;
	while (!_list.pre_levels.empty())
	{
		tmp.push(_list.pre_levels.top());
		_list.pre_levels.pop();
	}
	while (!tmp.empty())
	{
		pre_levels.push(tmp.top());
		tmp.pop();
	}
	return *this;
}

template<class T>
void HierList<T>::InsertNext(const T& _data)
{
	if (pFirst == nullptr) {
		pFirst = new Node<T>;
		pCurrent = pFirst;
		pCurrent->pDown = pCurrent->pNext = nullptr;
		pCurrent->data = _data;
		return;
	}
	Node<T>* tmp = pCurrent->pNext;
	pCurrent->pNext = new Node<T>;
	pCurrent->pNext->pDown = nullptr;
	pCurrent->pNext->pNext = tmp;
	pCurrent->pNext->data = _data;
	return;
}

template<class T>
void HierList<T>::InsertDown(const T& _data)
{
	if (pCurrent == nullptr) throw "no current element in hierarchical list";
	if (pCurrent->pDown == nullptr) {
		pCurrent->pDown = new Node<T>;
		pCurrent->pDown->pDown = pCurrent->pDown->pNext = nullptr;
		pCurrent->pDown->data = _data;
		return;
	}
	Node<T>* tmp = pCurrent->pDown;
	while (tmp->pNext != nullptr) tmp = tmp->pNext;
	tmp->pNext = new Node<T>;
	tmp->pNext->pDown = tmp->pNext->pNext = nullptr;
	tmp->pNext->data = _data;
}

template<class T>
void HierList<T>::GoFirst()
{
	pCurrent = pFirst;
	while (!pre_levels.empty()) pre_levels.pop();
}

template<class T>
bool HierList<T>::GoNext()
{
	if (pCurrent == nullptr || pCurrent->pNext == nullptr) return false;
	pCurrent = pCurrent->pNext;
	return true;
}

template<class T>
bool HierList<T>::GoDown()
{
	if (pCurrent == nullptr || pCurrent->pDown == nullptr) return false;
	pre_levels.push(pCurrent);
	pCurrent = pCurrent->pDown;
	return true;
}

template<class T>
bool HierList<T>::GoUp()
{
	if (pre_levels.empty()) return false;
	pCurrent = pre_levels.top();
	pre_levels.pop();
	return true;
}

template<class T>
T& HierList<T>::ReadCurrent()
{
	if (pCurrent == nullptr) throw "no element to read in hierarchical list";
	return pCurrent->data;
}

