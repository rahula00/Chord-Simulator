#include "node.h"
#include<iostream>
using namespace std;


Node* Node::findSuccesor(uint8_t id) {
    auto succ = findPredecessor(id);
    return succ->getSuccesor();
}

Node* Node::findPredecessor(uint8_t id) {
  Node* temp = this;
  while(temp->getID() != id) {
      temp = temp->closestPrecedingFinger(id)->getSuccesor();
  }
  return temp;
}

Node* Node::closestPrecedingFinger(uint8_t id) {
    for (auto& entry: FingerTable_.getInner()) {
        cout << "Entry: " << entry->getID();
    }
    return this;
}


void Node::join(Node* node){
    

    if(node == NULL){
        // creates FT with all successors set to NULL
        FingerTable_.initInnerFT(node);
        succesor = this;
        predecessor = this;
        for(int i=1; i<BITLENGTH+1; i++){
            FingerTable_.set(i, succesor);
        }
    }
    else{  
        //init_finger_table(node)
        //update_others
        std::map<uint8_t, uint8_t> a = transfer(node);

    }

    FingerTable_.prettyPrint(this);
}

// void Node::Leave() {
//     //to do?
// }

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


