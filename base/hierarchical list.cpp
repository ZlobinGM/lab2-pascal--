#include "hierarchical list.h"

template<class T>
inline HierList<T>::HierList(const HierList<T>& _list)
{
}

template<class T>
HierList<T>::~HierList()
{
}

template<class T>
HierList<T>& HierList<T>::operator=(HierList<T>&& _list)
{
	// TODO: вставьте здесь оператор return
}

template<class T>
void HierList<T>::InsertNext(const T& _data)
{
}

template<class T>
void HierList<T>::InsertDown(const T& _data)
{
}

template<class T>
bool HierList<T>::GoNext()
{
	return false;
}

template<class T>
bool HierList<T>::GoDown()
{
	return false;
}

template<class T>
bool HierList<T>::GoUp()
{
	return false;
}

template<class T>
T& HierList<T>::ReadCurrent()
{
	// TODO: вставьте здесь оператор return
}
