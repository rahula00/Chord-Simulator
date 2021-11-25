#include "node.h"
#include<iostream>
using namespace std;

Node* Node::findSuccesor(uint8_t id) {
    auto succ = findPredecessor(id);
    return succ.getSuccesor();
}

Node* Node::findPredecessor(uint8_t id) {
    while()
}

Node* Node::closestPrecedingFinger(uint8_t id) {
    
}
void Node::join(Node* node){
    if(node){
        
        //fingerTable_.insert(std::pair<uint8_t,Node*>(node->id_, node));
      
    }
    else {
        if (fingerTable_.empty()) {
            fingerTable_.insert(std::pair<uint8_t,Node*>(id_, NULL));
        } else { //Error joining NULL node when fingerTable is non-empty
		    cerr << "Error: Unable to join NULL node when FingerTable is not empty!\n";
            exit(1);
        }
    }
}

uint8_t Node::find(uint8_t key){
    // check local keys for keyt
    auto search = localKeys_.find(key);
    // if search is successful
    if(search != localKeys_.end()){
        // return value from dictionary key query
        return search->second;
    }
    else{
        cerr << "NNN\n";
        exit(1);
    }
}

void Node::insert(uint8_t key, uint8_t val){
    // if (fingerTable_.size()==1 && fingerTable.) {

    
    std::pair<std::map<uint8_t, uint8_t>::iterator,bool> ret;
    ret = localKeys_.insert(std::pair<uint8_t,uint8_t>(key,val));
    
    if(ret.second == false) {
        //do something, key already exists
    }
}

void Node::remove(uint8_t key){
    localKeys_.erase(key);
}

void Node::testPrint(){
    printf("bussy");
}


