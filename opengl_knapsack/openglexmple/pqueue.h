/* Own Priority Queue for Branch and Bound Knapsack */
#pragma once
#include <iostream>
#include "node.h"

class PQ {
public:
	Node* head;
	Node* tail;
	Node* idx;
	int n = 0;

	PQ() {
		head = new Node();
		idx = head;
	}
	~PQ() {
		idx = head->next;
		while (idx != NULL) {
			Node* temp = idx->next;
			delete idx;
			idx = temp;
		}
	}

	bool empty() { return(head->next == NULL); }	// check if queue is empty

	void insert(int lev, int hier, int prof, int wei, int bnd) {	// insert element to priority queue
		idx = head;
		while (true) {
			if (idx->next == NULL) {
				Node* temp = idx;
				idx = idx->next;
				idx = new Node(lev, hier, prof, wei, bnd);
				temp->next = idx;
				break;
			}
			else {
				if (idx->bound >= bnd && idx->next->bound < bnd) {

					Node* temp = new Node(lev, hier, prof, wei, bnd);
					temp->next = idx->next;
					idx->next = temp;
					break;
				}
				else idx = idx->next;
			}
		}
		n++;
	}

	void print() {	// print all elements in queue
		std::cout << "--Printing Elements--" << std::endl;
		idx = head->next;
		for (int i = 1; idx != NULL; i++) {
			std::cout << i << " : " << idx->level << " " << idx->lr << " " << idx->profit << " " << idx->weight << " " << idx->bound << std::endl;
			idx = idx->next;
		}
	}

	void remove(int& lev, int& hier, int& prof, int& wei, int& bnd) {	// remove element from priority queue
		idx = head;
		if (idx->next == NULL) return;

		idx = idx->next;
		Node* temp = idx->next;
		// value out
		lev = idx->level;
		hier = idx->lr;
		prof = idx->profit;
		wei = idx->weight;
		bnd = idx->bound;

		head->next = temp;
		delete idx;

		n--;
	}

};