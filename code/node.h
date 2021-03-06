#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include <tuple>
#include <iostream>
#include <random>
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
	FingerTable(uint8_t nodeId) : nodeId_(nodeId) {
		innerFingerTable_ = std::vector<Node*>(BITLENGTH + 1);
	}
	FingerTable() = default;
	void set(size_t index, Node* successor){
		innerFingerTable_[index] = successor;
	}


	Node* get(size_t index) {
		return innerFingerTable_[index];
	}

	void prettyPrint(Node* node);

	uint8_t getID(){
		return nodeId_;
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
	uint8_t find(uint8_t key,Node* pred = NULL);
	//TODO: implement DHT key insertion
	void insert(uint8_t key, uint8_t value);
	void insert(uint8_t key);
	//TODO: implement DHT key deletion
	void remove(uint8_t key);
	void update(uint8_t key, int val) {
		localKeys_[key] = val;
	}
	Node* get(size_t index) {
		return FingerTable_.get(index);
	}

	void set(size_t index, Node* node) {
		FingerTable_.set(index, node);
	}

	FingerTable getFingerTable(){
		return FingerTable_;
	}

	void init_finger_table(Node* node);
	uint8_t getStart(uint8_t id);
	Node* getNode(uint8_t id);
	void update_others();
	void update_finger_table(Node* s, uint8_t i);

	Node* findSuccessor(uint8_t id);
	Node* findPredecessor(uint8_t id);
	Node* closestPrecedingFinger(uint8_t id);

	void prettyPrint(){
		FingerTable_.prettyPrint(this);
	}

	void printLocalKeys();

	Node* getSuccessor() {
		return FingerTable_.get(1);
	}
	Node* getPredecessor() {
		if(predecessor == NULL){
			cerr << "Predecessor is null";
			exit(EXIT_FAILURE);
		}
		return predecessor;
	}
	void setSuccessor(Node* node) {
		FingerTable_.set(1, node);
	}
	void setPredecessor(Node* node) {
		predecessor = node;
	}
	Node* RPCgetSuccessor(Node * node) {
		return node->getSuccessor();
	}
	Node* RPCgetPredeccessor(Node * node) {
		return node->getPredecessor();
	}
	uint8_t getID() {
		return id_;
	}
	uint8_t RPCgetID(Node* node) {
		return node->getID();
	}
	
	std::map<uint8_t, int> transfer();
	void printFingerTables(bool lowestFound);
	void printAllLocalKeys(bool lowestFound);
	
	// void printValues() {
	// 	for ( const auto &keyVal :  localKeys_) {
	// 		cout << "Key: " << (int) keyVal.first << "Val: " << keyVal.second << endl; 
	// 	}
	// }

private:
	Node* predecessor;
	uint8_t id_;
	FingerTable FingerTable_;
	std::map<uint8_t, int> localKeys_;
};

inline void FingerTable::prettyPrint(Node* node){
	uint8_t predID = node->getPredecessor()->getID();
	uint8_t succID = node->getSuccessor()->getID();
	printf("---------Node ID:%d---------\n", nodeId_);
	printf("Successor: %d Predecessor: %d\n", succID, predID);
	printf("FingerTables:\n");
	for(int i=1; i<BITLENGTH+1; i++){
		uint8_t k = nodeId_ + pow(2, i-1);
		uint8_t k2 = k + pow(2, i-1);
		if(innerFingerTable_[i]){
			printf("| k = %d [ %d , %d )	succ. = %d |\n", i, k, k2, innerFingerTable_[i]->getID());
		}
		else{
			printf("| k = %d [ %d , %d )	succ. = ? |\n", i, k, k2);
		}
	}
	printf("-----------------------------\n");
	printf("*****************************\n");
}

#endif