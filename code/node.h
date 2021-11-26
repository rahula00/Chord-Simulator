#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include <tuple>
#include <iostream>
using namespace std;

#define BITLENGTH 8

//forward declaration
class Node;

//The following code is just for reference. You can define your own finger table class.
//Since the index uniquely determines the interval, only the successor needs to be maintained.  
class FingerTable {
public:
	/**
	 * @param nodeId: the id of node hosting the finger table.
	 */
	FingerTable(uint8_t nodeId) : nodeId_(nodeId) {}
	FingerTable() = default;
	void set(size_t index, Node* successor){
		innerFingerTable_[index] = successor;
	}
	Node* get(size_t index) {
		return innerFingerTable_[index];
	}

	void prettyPrint(Node* node);

	void initInnerFT(Node* node) {
		// finger table starts at 1
		innerFingerTable_ = std::vector<Node*>(BITLENGTH + 1, node);
	}

	uint8_t getID(){
		return nodeId_;
	}

	void setID(uint8_t id){
		nodeId_ = id;
	}

	std::vector<Node*> getInner() {
		return innerFingerTable_;
	}

private:
	uint8_t nodeId_;
	std::vector<Node*> innerFingerTable_;
};

// FingerTable::FingerTable(uint8_t nodeId): nodeId_(nodeId) {
// 	// According to Chord paper, the finger table starts from index=1
// 	innerFingerTable_.resize(BITLENGTH + 1);
// }

class Node {
public:
	static uint8_t nodeCnt;
	Node(uint8_t id): id_(id){
		FingerTable_ = FingerTable(id);
	}
	Node() = default;
	//TODO: implement node join function
	/**
	 * @param node: the first node to contact with to initialize join process. If this is the first node to join the Chord network, the parameter is NULL.
	 */
	void join(Node* node);
	//TODO: implement DHT lookup
	uint8_t find(uint8_t key);
	//TODO: implement DHT key insertion
	void insert(uint8_t key, uint8_t value);
	//TODO: implement DHT key deletion
	void remove(uint8_t key);

	void init_finger_table(Node* node);

	Node* findSuccesor(uint8_t id);
	Node* findPredecessor(uint8_t id);
	Node* closestPrecedingFinger(uint8_t id);
	void testPrint();

	Node* getSuccesor() {
		if(succesor == NULL){
			cerr << "Successor is null";
			exit(EXIT_FAILURE);
		}
		return succesor;
	}
	Node* getPredecessor() {
		if(predecessor == NULL){
			cerr << "Predecessor is null";
			exit(EXIT_FAILURE);
		}
		return predecessor;
	}
	void setSuccesor(Node* node) {
		succesor = node;
	}
	void setPredecessor(Node* node) {
		predecessor = node;
	}

	uint8_t getID() {
		return id_;
	}
	std::map<uint8_t, uint8_t> transfer(Node* node) {
		std::map<uint8_t, uint8_t> toTransfer;
		Node* P = findPredecessor(getID());
		for ( const auto &keyVal :  localKeys_) {
			if (keyVal.first - node->id_ > keyVal.first - getID()) {
				toTransfer[keyVal.first] = keyVal.second;
			}
		}
		return toTransfer;
	} 
	
	

private:
	Node* succesor;
	Node* predecessor;
	uint8_t id_;
	FingerTable FingerTable_;
	std::map<uint8_t, uint8_t> localKeys_;
};

inline void FingerTable::prettyPrint(Node* node){
	uint8_t predID = node->getPredecessor()->getID();
	uint8_t succID = node->getSuccesor()->getID();

	printf("----------Node ID:%d----------\n", nodeId_);
	printf("Successor: %d Predecessor: %d\n", succID, predID);
	printf("FingerTables:\n");
	for(int i=1; i<BITLENGTH+1; i++){
		uint8_t k = nodeId_ + pow(2, i-1);
		uint8_t k2 = k + pow(2, i-1);
		printf("| k = %d [ %d , %d )	succ. = %d |\n", k, k, k2, innerFingerTable_[i]->getID());
	}
	printf("-----------------------------\n");
	printf("*****************************\n");
}

#endif