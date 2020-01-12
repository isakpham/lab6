/*
 * SinglyLinkedList.cpp
 *
 *  Created on: 27 Nov 2018
 *      Author: teelai
 */

#include "SinglyLinkedList.h"
#include <iostream>

using namespace std;

SinglyLinkedList::SinglyLinkedList() {
	this->head = nullptr;
}

SinglyLinkedList::~SinglyLinkedList() {
	// TODO Auto-generated destructor stub
}

void SinglyLinkedList::addFirst(Node *data) {

	if (head != nullptr) {
		data->setPrev(head);
		head->setNext(data);
	}
	head = data;
	this->length++;
	
}

bool SinglyLinkedList::replace(Node* oldNode, Node* newNode)
{
	
	if (this->search(oldNode) != -1)
	{
		Node* current = head;
		for (int i = 0; i < length; i++)
		{
			if (current == oldNode)
			{
				this->remove(i);
				this->add(newNode, i-2);
				return true;
			}
			current = current->getPrev();
		}		
	}
	return false;

	
}

void SinglyLinkedList::add(Node* data, int pos)
{
	if (pos <= length)
	{
	Node* current = head;
	Node* previous = head;
	Node* next = head;
	for (int i = 0; i <= pos; i++)
	{
		if (i == pos ) {
			
			current->setPrev(data);
			next->setNext(data);
			data->setPrev(next);
			data->setNext(current);
		}
		current = current->getPrev();
		next = current->getPrev();
	}
	this->length++;
	
	}
}


bool SinglyLinkedList::remove(int pos) {
	Node* next = head;
	Node *current = head;
	Node *previous = head;
	for (int i = 0; i <= pos; i++)
	{
		if (i == pos-1) {
			previous->setPrev(current->getPrev());
			next = current->getPrev();
			next->setNext(current->getNext());
			length--;
			delete current;
			return true;
		}
		previous = current;
		current = current->getPrev();
	}
	return false;
}

void SinglyLinkedList::display_forward() {
	Node* current = head;
	for (int i = 0; i < length; i++)
	{
			cout << current->getData() << " ";
			current = current->getPrev();
	}
	cout << endl;
}

void SinglyLinkedList::display_backward()
{
	Node* current = this->nodeAt(length-1);
	for (int i = 0; i < length; i++)
	{
		cout << current->getData() << " ";
		current = current->getNext();
	}
	cout << endl;
	
}

int SinglyLinkedList::search(Node *data) {
	Node *current = head;
	while (current != nullptr) {
		if (current == data) {
			return current->getData();
		}
		current = current->getPrev();
	}
	return -1;
}

Node* SinglyLinkedList::nodeAt(int pos)
{
	Node* current = head;
	for (size_t i = 0; i < pos; i++)
	{
		
		for (int i = 0; i <= pos; i++)
		{
			if (i == pos) {
				return current;
			}
			current = current->getPrev();
		}
	}
	return nullptr;
}

int Node::getData() {
	return data;
}
void Node::setData(int data) {
	this->data = data;
}
Node* Node::getNext() {
	return next;
}
void Node::setNext(Node *next) {
	this->next = next;
}

Node* Node::getPrev()
{
	return previous;
}

void Node::setPrev(Node* prev)
{
	this->previous = prev;
}

Node::Node(int d) {
	this->data = d;
	this->next = nullptr;
	this->previous = nullptr;
}

Node::~Node() {
}

int SinglyLinkedList::lengthOfList()
{
	return this->length;
}

int main() {

	SinglyLinkedList list;
	Node *n1 = new Node(1);
	Node *n2 = new Node(2);
	Node *n3 = new Node(3);
	Node *n4 = new Node(4);
	Node* n5 = new Node(5);
	Node* n6 = new Node(6);
	Node* n7 = new Node(7);
	list.addFirst(n1);
	list.addFirst(n2);
	list.addFirst(n3);
	list.addFirst(n4);
	list.addFirst(n5);
	list.addFirst(n6);
	//list.add(n5, 3);
	//list.display();

	//cout << n->getData() << endl;
	//delete n;
	list.display_forward();
	list.replace(n3, n7);
	list.display_forward();
	cout << list.lengthOfList();
	//list.display_backward();
	//cout << list.search(n5) << endl;
	
}

