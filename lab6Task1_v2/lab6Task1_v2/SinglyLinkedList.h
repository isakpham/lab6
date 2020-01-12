/*
 * SinglyLinkedList.h
 *
 *  Created on: 27 Nov 2018
 *      Author: teelai
 */

#ifndef SINGLYLINKEDLIST_H_
#define SINGLYLINKEDLIST_H_

class Node {
private:
	int data;
	Node* next;
	Node* previous;
public:
	Node(int data);
	virtual ~Node();
	int getData();
	void setData(int data);
	Node* getNext();
	void setNext(Node *next);
	Node* getPrev();
	void setPrev(Node* prev);
};

class SinglyLinkedList {
private:
	Node *head;
public:
	int length;
	SinglyLinkedList();
	virtual ~SinglyLinkedList();
	void addFirst(Node *data);
	bool replace(Node* oldNode, Node* newNode);
	void add(Node* data, int pos);
	bool remove(int pos);
	void display_forward();
	void display_backward();
	int search(Node *data);
	int lengthOfList();
	Node* nodeAt(int pos);
	
};

#endif /* SINGLYLINKEDLIST_H_ */
