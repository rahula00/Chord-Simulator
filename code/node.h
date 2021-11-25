#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include <tuple>

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
	// TODO: complete print function
	void prettyPrint();

	void initInnerFT(Node* node) {
		innerFingerTable_ = std::vector<Node*>(BITLENGTH, node);
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
	Node(uint8_t id): id_(id){}
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

	Node* findSuccesor(uint8_t id);
	Node* findPredecessor(uint8_t id);
	Node* closestPrecedingFinger(uint8_t id);
	void testPrint();

	Node* getSuccesor() {
		return succesor;
	}
	Node* getPredecessor() {
		return predecessor;
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

#endif