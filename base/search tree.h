#pragma once

#include <string>

using namespace std;

template <class T>
class NodeTree
{
	NodeTree<T>* parent;
	NodeTree<T>* leftChild;
	NodeTree<T>* rightChild;
public:
	string name;
	T data;

	int heightDiff;		//left heght-right height
	bool isLeftChild;

	NodeTree();
	NodeTree(string _name, T _data);
	
	void SetChild(NodeTree<T>* child, bool left);
	NodeTree<T>* GetChild(bool left);
	NodeTree<T>* GetParent();
	void Rotate(bool leftChild);
};

template <class T>
class SearchTree
{
protected:
	NodeTree<T>* head;
	int height;
	int DataCount;

	bool Balance(NodeTree<T>* _node);
	void Clear(NodeTree<T>* start);
	NodeTree<T>* FindNode(string name);
private:
	const bool firstRecordLeft = true;
public:
	SearchTree();
	~SearchTree();

	T* Find(string name);
	void Insert(string _name, T& _data);

	int GetHeight();
};

template<class T>
NodeTree<T>* SearchTree<T>::FindNode(string name)
{
	bool nextLeft = firstRecordLeft;
	NodeTree<T>* curRecord = head->GetChild(nextLeft);

	//go down, looking for parent for newRecord
	while (curRecord != nullptr)
	{
		if (curRecord->name == name)
		{
			return curRecord;
		}
		nextLeft = name.length() < curRecord->name.length() ||
			(name.length() == curRecord->name.length() && name < curRecord->name);

		curRecord = curRecord->GetChild(nextLeft);
	}

	return nullptr;
}

template<class T>
bool SearchTree<T>::Balance(NodeTree<T>* _node)
{
	if (_node == nullptr)
	{
		return false;
	}

	int heightDiff = _node->heightDiff;
	if (heightDiff == 2 || heightDiff == -2)
	{
		bool badChildLeft = heightDiff == 2;
		NodeTree<T>* badChild = _node->GetChild(badChildLeft);

		//if big rotation
		if (-heightDiff / 2 == badChild->heightDiff)
		{
			NodeTree<T>* badChildChild = badChild->GetChild(!badChildLeft);
			int k = badChildChild->heightDiff;
			badChild->Rotate(!badChildLeft);
			_node->Rotate(badChildLeft);

			badChildChild->heightDiff = 0;
			_node->heightDiff = (k < 0 ? 1 : 0);
			badChild->heightDiff = (k < 0 ? 0 : -k);
		}
		else
		{
			int k = badChild->heightDiff;
			_node->Rotate(badChildLeft);
			_node->heightDiff = (k == 0 ? -1 : 0);
			badChild->heightDiff = (k == 0 ? 1 : 0);
		}
		return true;
	}
	return false;
}

template<class T>
void SearchTree<T>::Clear(NodeTree<T>* start)
{
	if (start == nullptr)
	{
		return;
	}
	Clear(start->GetChild(true));
	Clear(start->GetChild(false));
	delete start;
}

template<class T>
SearchTree<T>::SearchTree()
{
	head = new NodeTree<T>;
	height = 0;
	DataCount = 0;
}

template<class T>
SearchTree<T>::~SearchTree()
{
	Clear(head->GetChild(firstRecordLeft));
	head->SetChild(nullptr, firstRecordLeft);
	DataCount = 0;
}

template<class T>
T* SearchTree<T>::Find(string name)
{
	NodeTree<T>* result = FindNode(name);
	return (result == nullptr ? nullptr : &(result->data));
}

template<class T>
void SearchTree<T>::Insert(string _name, T& _data)
{
	NodeTree<T>* curRecord = head->GetChild(firstRecordLeft);
	NodeTree<T>* parentRecord = head;
	bool nextLeft = firstRecordLeft;

	//go down, looking for parent for newRecord
	while (curRecord != nullptr)
	{
		if (curRecord->name == _name)
		{
			throw "Item with same name already exists";
		}
		nextLeft = _name.length() < curRecord->name.length() ||
			(_name.length() == curRecord->name.length() && _name < curRecord->name);

		parentRecord = curRecord;
		curRecord = curRecord->GetChild(nextLeft);
	}
	NodeTree<T>* newRecord = new NodeTree<T>(_name, _data);
	parentRecord->SetChild(newRecord, nextLeft);

	//go up, updating heightDiff
	curRecord = parentRecord;
	bool prevRecordLeft = newRecord->isLeftChild;
	bool afterBalance = false;
	while (curRecord != head)
	{
		if (!afterBalance)
		{
			curRecord->heightDiff += (prevRecordLeft ? 1 : -1);
		}
		afterBalance = Balance(curRecord);

		if (curRecord->heightDiff == 0)
		{
			break;
		}
		else if (curRecord == head->GetChild(firstRecordLeft))
		{
			height++;
		}

		prevRecordLeft = curRecord->isLeftChild;
		curRecord = curRecord->GetParent();
	}
	if (DataCount == 0)
	{
		height++;
	}
	DataCount++;
}

template<class T>
int SearchTree<T>::GetHeight()
{
	return height;
}


template<class T>
NodeTree<T>::NodeTree()
{
	leftChild = nullptr;
	rightChild = nullptr;
	parent = nullptr;
	heightDiff = 0;
	isLeftChild = false;
}

template<class T>
NodeTree<T>::NodeTree(string _name, T _data)
{
	leftChild = nullptr;
	rightChild = nullptr;
	parent = nullptr;
	heightDiff = 0;
	isLeftChild = false;
	name = _name;
	data = _data;
}

template<class T>
void NodeTree<T>::SetChild(NodeTree<T>* child, bool left)
{
	NodeTree<T>* prevChild = (left ? leftChild : rightChild);
	if (prevChild != nullptr)
	{
		prevChild->parent = nullptr;
	}
	(left ? leftChild : rightChild) = child;
	if (child != nullptr)
	{
		if (child->parent != nullptr)
		{
			child->parent->SetChild(nullptr, child->isLeftChild);
		}

		child->parent = this;
		child->isLeftChild = left;
	}
}
template<class T>
NodeTree<T>* NodeTree<T>::GetChild(bool left)
{
	return (left ? leftChild : rightChild);
}
template<class T>
NodeTree<T>* NodeTree<T>::GetParent()
{
	return parent;
}
template<class T>
void NodeTree<T>::Rotate(bool leftChild)
{
	NodeTree<T>* child = GetChild(leftChild);
	GetParent()->SetChild(child, isLeftChild);
	if (child != nullptr)
	{
		SetChild(child->GetChild(!leftChild), leftChild);
		child->SetChild(this, !leftChild);
	}
}