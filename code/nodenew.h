#ifndef NODE_H
#define NODE_H

#include <stdint.h>
#include <map>
#include <set>
#include <vector>

#define BITLENGTH 8

//forward declaration
class Node;

//TIPS
//	Chord leverages Remote Procedure Call (RPC) to either iteratively or recursively 
//	to lookup a key located at other nodes. It is easy to mimic RPC in simulation settings
//	For example,
/*
	int remoteLookup(uint8_t key, Node* remoteNode) {
		return remoteNode->localLookup(uint8_t key);
	}

	RECURSIVE:
	int remoteLookup(uint8_t key, Node* remoteNode) {
		return remoteNode->remoteLookup(key, anotheRemoterNode);
	}
*/


//The following code is just for reference. You can define your own finger table class.
//Since the index uniquely determines the interval, only the successor needs to be maintained.  
class FingerTable{

public:
	/**
	 * @param nodeId: the id of node hosting the finger table.
	 */
	FingerTable(uint8_t nodeId);
	void set(size_t index, Node* successor){
		fingerTable_[index] = successor;
	}
	uint8_t get(size_t index) {
		return fingerTable_[index];
	}
	// TODO: complete print function
	void prettyPrint();
private:
	uint8_t nodeId_;
	std::vector<Node*> fingerTable_;
};

FingerTable::FingerTable(uint8_t nodeId): nodeId_(nodeId) {
	// According to Chord paper, the finger table starts from index=1
	fingerTable_.resize(BITLENGTH + 1);
}

class Node {


public:
	Node(uint8_t id): id_(id){

	}
	//TODO: implement node join function
	//keys should be migrated to new node as well
	/**
	 * @param node: the first node to contact with to initialize join process. If this is the first node to join the Chord network, the parameter is NULL.
	 */
	void join(Node* node){
		if(node == NULL){
			// add first node to network
		}
		else{
			for(int i=1; i<BITLENGTH+1; i++){
				printf(fingerTable_.get(i));
			}
		}
	};

	//TODO: implement DHT lookup
	//upon join, the updated finger table should be printed to the screen
	//upon join, print the keys that are migrated
	uint8_t find(uint8_t key){
		// check local keys for keyt
		auto search = localKeys_.find(key);
		// if search is successful
		if(search != localKeys_.end()){
			// return value from dictionary key query
			return search->second;
		}

		// else, find key in proper node from finger table

	};

	//TODO: implement DHT key insertion
	//node needs to query the key from the Chord network. Querying keys are not maintained locally
	//upon find, the sequence of nodes that the node talks to should be printed to the screen too
	void insert(uint8_t key, uint8_t value){
		// if (key is to be inserted into this node){
			// localKeys_.insert(key, value);
		// }
	};


	//TODO: implement DHT key deletion
	void remove(uint8_t key){
		// check local keys for key
		auto search = localKeys_.find(key);
		// if search is successful
		if(search != localKeys_.end()){
			// delete value from dictionary key query
			localKeys_.erase(key);
		}
		else{
			// find key in proper node from finger table
			// delete key
		}
	};

	//OPTIONAL TODO (20% extra): implement node leaving
	//not sure if param is supposed to be id
	//locate the node, move keys maintained in the node to another node
	void leave(uint8_t id){

	};
private:
	uint64_t id_;
	FingerTable fingerTable_;
	std::map<uint8_t, uint8_t> localKeys_;
};

#endif
