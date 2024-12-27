#ifndef Chain_
#define Chain_
#include <iostream>
#include "cnode.h"
#include "xcept.h"

template <class T>
class Chain
{
public:
	Chain() { first = 0; }
	~Chain();
	bool IsEmpty() const { return first == 0; }
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(const T& x) const;
	Chain<T>& Delete(int k, T& x);
	Chain<T>& Insert(int k, const T& x);
	bool Update(int k, const T& newValue);
	double CalculateAverage() const; // 9. Aver(): a method that finds the sum of the elements of a linked list.
	// The method should return the average of the elements in the list.

private:
	ChainNode<T>* first; // pointer to first node
};

template <class T>
Chain<T>::~Chain()
{
	// Chain destructor. Delete all nodes in chain.
	ChainNode<T>* next; // next node
	while (first)
	{
		next = first->link;
		delete first;
		first = next;
	}
}

template <class T>
int Chain<T>::Length() const
{
	// Return the number of elements in the chain.
	ChainNode<T>* current = first;
	int len = 0;
	while (current)
	{
		len++;
		current = current->link;
	}
	return len;
}

template <class T>
bool Chain<T>::Find(int k, T& x) const // time complexity: O(n)
{
	// Set x to the k'th element in the chain. Return false if no k'th; return true otherwise.
	if (k < 1)
		return false;
	ChainNode<T>* current = first;
	int index = 1; // index of current

	while (index < k && current)
	{
		current = current->link;
		index++;
	}

	if (current)
	{
		x = current->data;
		return true;
	}
	return false; // no k'th element
}

/*
template<class T>
bool Chain<T>::Find(int k, T& x) const
{
	// Set x to the k'th element in the chain. Return false if no k'th; return true otherwise.
	if ((k < 1 )||(K > Length()) return false;	//invalied value of parameter k
	if (first == 0) return false;	//empty list

	ChainNode<T> *current = first;
	for (int i=1 ; i<=k && current!=0 ; i++)
		current = current->link;
	x = current->data;
	return true;
}
*/

template <class T>
int Chain<T>::Search(const T& x) const
{
	// Locate x.  Return position of x if found. Return 0 if x not in the chain.
	ChainNode<T>* current = first;
	int index = 1; // index of current
	while (current && current->data != x)
	{
		current = current->link;
		index++;
	}
	if (current)
		return index;
	return 0;
}

/*
template<class T>
int Chain<T>::Search(const T& x) const
	{
	// Locate x.  Return position of x if found. Return 0 if x not in the chain.
	ChainNode<T> *current = first;
	for (int i=1 ; i<=Length() && current!=0 && current->data!= x ; i++)
		current = current->link;
	if (current!=0) return i;
	return 0;
	}

template<class T>
int Chain<T>::Search(const T& x) const
	{
	// Locate x.  Return position of x if found. Return 0 if x not in the chain.
	ChainNode<T> *current;
	int index=0;
	for (current=first ; current!=0 && current->data!= x ; current=current->link)
		index++;
	if (current!=0) return index;
	return 0;
	}
*/

template <class T>
Chain<T>& Chain<T>::Delete(int k, T& x)
{
	// Set x to the k'th element and delete it. Throw OutOfBounds exception if no k'th element.
	if (k < 1 || !first)
		throw OutOfBounds(); // no k'th

	// p will eventually point to k'th node
	ChainNode<T>* p = first;

	// move p to k'th & remove from chain
	if (k == 1)				 // p already at k'th
		first = first->link; // remove
	else
	{
		// use q to get to k-1'st
		ChainNode<T>* q = first;
		for (int index = 1; index < k - 1 && q; index++)
			q = q->link;
		if (!q || !q->link)
			throw OutOfBounds(); // no k'th
		p = q->link;			 // k'th
		q->link = p->link;		 // remove from chain
	}

	// save k'th element and free node p
	x = p->data;
	delete p;
	return *this;
}

template <class T>
Chain<T>& Chain<T>::Insert(int k, const T& x)
{
	// Insert x after the k'th element.
	// Throw OutOfBounds exception if no k'th element.
	// Pass NoMem exception if inadequate space.
	if (k < 0)
		throw OutOfBounds();

	// p will eventually point to k'th node
	ChainNode<T>* p = first;
	for (int index = 1; index < k && p; index++) // move p to k'th
		p = p->link;
	if (k > 0 && !p)
		throw OutOfBounds(); // no k'th

	// insert
	ChainNode<T>* y = new ChainNode<T>;
	y->data = x;
	if (k)
	{
		// insert after p
		y->link = p->link;
		p->link = y;
	}
	else
	{
		// insert as first element
		y->link = first;
		first = y;
	}
	return *this;
}


template <class T>
bool Chain<T>::Update(int k, const T& newValue)
{
	// Update the k'th element to the newValue.
	if (k < 1)
		return false; // invalid position
	ChainNode<T>* current = first;
	int index = 1; // index of current node

	// Traverse the list to find the k'th node
	while (index < k && current)
	{
		current = current->link;
		index++;
	}

	// Check if the k'th element exists
	if (current)
	{
		current->data = newValue; // update value
		return true;
	}
	return false; // no k'th element to update
}


// 9. Aver(): a method that finds the sum of the elements of a linked list.
// The method should return the average of the elements in the list.
template <class T>
double Chain<T>::CalculateAverage() const
{
	ChainNode<T>* current = first;
	double sum = 0;
	int len = 0;
	while (current)
	{
		sum += current->data;
		len++;
		current = current->link;
	}
	if (len == 0)
		return 0;
	return sum / len;
}



#endif