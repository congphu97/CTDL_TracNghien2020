#ifndef List_H
#include "List.h"
#endif 

#ifndef LIST_CPP
#define LIST_CPP

template<class T>
node<T>* List<T>::createnode(List<T>::dataPtr dat) {
	node<T>* ptrtemp = nullptr;
	ptrtemp = new List<T>::nodeOjb;
	if (ptrtemp != nullptr) {
		ptrtemp->info = dat;
		ptrtemp->next = nullptr;
	}
	return ptrtemp;
}

template<class T>
node<T>* List<T>::insertfirst(dataPtr dat)
{
	if (dat == nullptr) return nullptr;
	nodePtr ptrtemp = createnode(dat);
	if (ptrtemp == nullptr) return nullptr;
	else
	{
		++_count;
		ptrtemp->next = _first;
		_first = ptrtemp;
		if (_last == nullptr) _last = _first;
	}
	return ptrtemp;
}

template<class T>
node<T>* List<T>::insertlast(dataPtr dat)
{
	if (dat == nullptr) return nullptr;
	nodePtr ptrtemp = createnode(dat);
	if (ptrtemp == nullptr) return nullptr;
	else
	{
		++_count;
		if (isempty()) _first = ptrtemp;
		else _last->next = ptrtemp;
		_last = ptrtemp;
	}
	return ptrtemp;
}

template<class T>
node<T>* List<T>::insertCen(T* ptrdatsam, T* ptrDat)
{
	if (ptrdatsam == nullptr || ptrDat == nullptr) return nullptr;
	if (isempty()) return insertfirst(ptrDat);
	if (_last->info == ptrdatsam) return insertlast(ptrDat);
	else
	{
		nodePtr temp = nullptr;
		temp = search(ptrdatsam);
		if (temp != nullptr) {
			nodePtr tempDat = createnode(ptrDat);
			if (tempDat != nullptr) {
				++_count;
				tempDat->next = temp->next;
				temp->next = tempDat;
				return tempDat;
			}
		}
	}
	return nullptr;
}

template<class T>
node<T>* List<T>::insertCen(nodePtr ptrN, T* ptrdat)
{
	nodePtr temp;
	temp = createnode(ptrdat);
	if (temp == nullptr)return nullptr;
	temp->next = ptrN->next;
	ptrN->next = temp;
	if (ptrN == _last) _last = ptrN;
	return temp;
}

template<class T>
node<T>* List<T>::insertConst(T* ptrDat)
{
	if (ptrDat == nullptr)return nullptr;
	if (isempty() || _ptr(_first->info) > _ptr(ptrDat)) return insertfirst(ptrDat);
	nodePtr temp = createnode(ptrDat);
	_last->next = temp;
	temp->next = _first;
	nodePtr trav = _first;
	while (_ptr(trav->next->info) < _ptr(ptrDat)) trav = trav->next;
	if (trav == _last) {
		_last = temp;
		++_count;
		_last->next = nullptr;
		return temp;
	}
	temp->next = trav->next;
	trav->next = temp;
	_last->next = nullptr;
	++_count;
	return temp;
}

template<class T>
bool List<T>::Addlast(nodePtr value)
{
	if (value == nullptr) return 0;
	else
	{
		++_count;
		if (isempty()) _first = value;
		else _last->next = value;
		_last = value;
	}
	return 1;
}

template<class T>
bool List<T>::AddFirt(nodePtr Value)
{
	if (Value == nullptr) return 0;
	else
	{
		++_count;
		Value->next = _first;
		_first = Value;
		if (_last == nullptr) _last = _first;
	}
	return 1;
}

template<class T>
void List<T>::clear()
{
	while (!isempty())
	{
		delete getfirst()->info;
		Delfirst();
	}
}
template<class T>
bool List<T>::Delfirst()
{
	if (isempty()) return 0;
	nodePtr temp = _first->next;
	if (_first == _last) _last = nullptr;
	delete _first;
	_first = temp;
	--_count;
	return 1;
}
template<class T>
bool List<T>::DelCen(T* ptrDat, int& index)
{
	index = -1;
	if (isempty() || ptrDat == nullptr) return -1;
	if (_ptr(ptrDat) == _ptr(_first->info)) {
		index = 0;
		return Delfirst();
	}
	nodePtr temp = _first;
	index = 0;
	while (temp->next != nullptr && _ptr(ptrDat) != _ptr(temp->next->info)) {
		temp = temp->next;
		index++;
	}
	if (temp->next == nullptr) return -1;
	if (temp->next == _last) {
		delete _last;
		_last = temp;
		temp->next = nullptr;
	}
	else
	{
		nodePtr bktemp = temp->next->next;
		delete temp->next;
		temp->next = bktemp;
	}
	--_count;
	return true;
}
template<class T>
bool List<T>::DelLast()
{
	if (_last == _first) return Delfirst();
	nodePtr temp = _first;
	while (temp->next != nullptr) temp = temp->next;
	if (temp->next == _last) return 0;
	if (temp->next == _last) {
		delete _last;
		_last = temp;
		temp->next = nullptr;
		--_count;
	}
	return 1;
}
template<class T>
bool List<T>::DelNode(nodePtr Nde)
{
	if (Nde == _first) return Delfirst();
	if (Nde == _last) return DelLast();
	return DelCen(Nde->info);
}
template<class T>
bool List<T>::AddList(List<T>& list)
{
	if (list.isempty()) return 0;
	if (!isempty()) _ptr(this) = list;
	else {
		_last->next = list.getfirst();
		_last = list.getLast();
		_count += list._count;
	}
	return 1;
}

template<class T>
bool List<T>::isempty()
{
	return _first == nullptr;
}

template<class T>
node<T>* List<T>::search(dataPtr dat)
{
	if (isempty()) return nullptr;
	nodePtr _Cur = _first;
	nodePtr tempdat = createnode(dat);
	_last->next = tempdat;

	while (_ptr(_Cur->info) != _ptr(dat)) _Cur = _Cur->next;

	if (_Cur == tempdat) _Cur = nullptr;
	delete tempdat;
	_last->next = nullptr;
	return _Cur;
}

template<class T>
int List<T>::searchIndex(dataPtr dat)
{
	if (isempty()) return -1;
	nodePtr _Cur = _first;
	nodePtr tempdat = createnode(dat);
	_last->next = tempdat;
	int index = 0;
	while (_ptr(_Cur->info) != _ptr(dat)) {
		index++;
		_Cur = _Cur->next;
	}

	if (_Cur == tempdat) {
		index = -1;
		_Cur = nullptr;
	}
	delete tempdat;
	_last->next = nullptr;
	return index;
}

template<class T>
node<T>* List<T>::getfirst()
{
	return _first;
}

template<class T>
node<T>* List<T>::getLast()
{
	return _last;
}

template<class T>
int List<T>::getSize()
{
	return _count;
}

template<class T>
void List<T>::Sort()
{
	if (isempty() || _count < 2) return;
	nodePtr num1 = _first;
	nodePtr num2;
	for (; num1->next != nullptr; num1 = num1->next)
		for (num2 = num1->next; num2 != nullptr; num2 = num2->next) {
			if (_ptr(num1->info) > _ptr(num2->info)) {
				swap(num1->info, num2->info);
			}
		}
}

template<class T>
List<T>::~List()
{
	while (!isempty())
	{
		Delfirst();
	}
}

template<class T>
List<T>::List()
{

}


#endif //!LIST_CPP