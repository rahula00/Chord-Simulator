#include "node.h"
#include <iostream>
#include <cassert>
using namespace std;

// checks if key is between vars a and b
// uint8 range = [0, 255]
bool betweenExclusive(uint8_t left, uint8_t right, uint8_t key){
    if(key == right || key == left) {
        return false;
    }
    if (left >= right){      
        return ((key > left) || (key < right));
    } else if (right > left){
        return ((key > left) && (key < right));
    }
    return false;
}


bool betweenLeftInclusive(uint8_t left, uint8_t right, uint8_t key){
    if(key == left) {
        return true;
    }
    if (left >= right){    
        return ((key > left) || (key < right));
    } else if (right > left){
        return ((key > left) && (key < right));
    }
    return false;
}

Node* Node::findSuccessor(uint8_t id) {
    Node* nP = findPredecessor(id);
    return nP->get(1);
}

Node* Node::findPredecessor(uint8_t id) {
    

    Node* nP = this;
    Node* nP_successor = nP->get(1);
    bool between = betweenLeftInclusive(nP->getID(), nP_successor->getID(), id);
    while( !between ){
        nP = nP->closestPrecedingFinger(id);
        nP_successor = nP->get(1);
        between = betweenLeftInclusive(nP->getID(), nP_successor->getID(), id);
    }
    return nP;
}

Node* Node::closestPrecedingFinger(uint8_t id) {  
    Node* n = this; 
    for(int i=BITLENGTH; i>0; --i) {
        Node* finger_i_node = get(i);
        if(betweenExclusive(n->getID(), id, finger_i_node->getID())){
            return finger_i_node;
        }
    }
    return n;
}

// finger[k].start = (n + 2**k-1)
uint8_t Node::getStart(uint8_t k){
    uint8_t n = id_;
    return n + pow(2, k-1);
}

// initialize finger table of local node;
// n0 is an arbitrary node already in the network
// n.init_finger_table(n0)
void Node::init_finger_table(Node* node) {
    Node* n = this;

    uint8_t start = getStart(1);
    FingerTable_.set(1, node->findSuccessor(start));

    Node* successor = FingerTable_.get(1);
    predecessor = successor->predecessor;
    successor->predecessor = n;

    for(int i=1; i < BITLENGTH; i++){
        Node* finger_i_node = get(i);
        uint8_t n = id_;
        if(betweenExclusive(n, finger_i_node->getID(), getStart(i+1))){
            FingerTable_.set(i+1, finger_i_node);
        }
        else{
            FingerTable_.set(i+1, node->findSuccessor(getStart(i+1)));
        }
    }
}

// update all nodes whose finger tables should refer to n
void Node::update_others(){
    for(int i = 1; i <= BITLENGTH;  i++) {
        Node* n = this;
        uint8_t findPredOfThis = (n->getID() - pow(2,i-1));
        Node* p = findPredecessor(findPredOfThis);
        p->update_finger_table(n, i);
    }
}

void Node::update_finger_table(Node* s, uint8_t i){
    Node* n = this;
    bool between = betweenExclusive(n->getID(), get(i)->getID(), s->getID());
    if(between){      
        FingerTable_.set(i, s);
        Node* p = predecessor;
        p->update_finger_table(s, i);
    }
}


void Node::join(Node *node)
{
    if (node) {
        init_finger_table(node); 
        update_others();
        this->localKeys_ = this->transfer();
        printf("\n\nNode %d joined. Printing new finger tables. \n", this->getID());
        printFingerTables(false);
        printf("\n\nNode %d joined. Printing all local keys. \n", this->getID());
        printAllLocalKeys(false);
    } else {
        predecessor = this;
        for (int i = 1; i < BITLENGTH + 1; i++){
            FingerTable_.set(i, this);
        }
        printf("\n\nNode %d joined. Printing first finger table. \n", this->getID());
        FingerTable_.prettyPrint(this);
    }  
}

void Node::printFingerTables(bool lowestFound){
    
    Node* n = this->getSuccessor();
    Node* lowestNode = this;
    if(lowestFound) {
        
        this->prettyPrint();
    }
    if(n->getID() < lowestNode->getID()){
        lowestNode = n;
    }
    while(this != n) {
        if(lowestFound) {
            n->prettyPrint();
        }
        n = n->getSuccessor();
        if(n->getID() < lowestNode->getID()){
            lowestNode = n;
        }
    }
    
    if(!lowestFound){
        lowestNode->printFingerTables(true);
    }
}

void Node::printAllLocalKeys(bool lowestFound){
    
    Node* n = this->getSuccessor();
    Node* lowestNode = this;
    if(lowestFound) {
        
        this->printLocalKeys();
    }
    if(n->getID() < lowestNode->getID()){
        lowestNode = n;
    }
    while(this != n) {
        if(lowestFound) {
            n->printLocalKeys();
        }
        n = n->getSuccessor();
        if(n->getID() < lowestNode->getID()){
            lowestNode = n;
        }
    }
    
    if(!lowestFound){
        lowestNode->printAllLocalKeys(true);
    }
}

// DEFAULT VALUE OF pred is NULL
uint8_t Node::find(uint8_t key, Node* pred) {

    if(pred == NULL){
        printf("Look-up result of key %d from node %d with path [%d", key, this->getID(), this->getID());
    }
    else{
        printf(",%d", this->getID());
    }    

    auto iter = localKeys_.find(key);
    if ( iter != localKeys_.end() ) {
        if(iter->second != -1){
            printf("] value is %d\n", iter->second);
            return iter->second;
        }
        else{
            printf("] value is None\n");
            printf("\033[1;31m\tValue of key %d is None.\033[0m\n", key);
            return 0;
        }
    } 

    Node* n = this;
    while(!betweenLeftInclusive(n->getID(), n->getSuccessor()->getID(), key)) {
        n = n->getSuccessor();
    }
    Node* lookupNode = n->getSuccessor();
    if(lookupNode == this) {
        printf("] key was not found\n");
        printf("\033[1;31m\tKey %d was not found.\033[0m\n", key);
        return 0;
    }

    
    return lookupNode->find(key, this);
}

void Node::insert(uint8_t key, uint8_t val) {
    Node* n = this;
    while(!betweenLeftInclusive(n->getID(), n->getSuccessor()->getID(), key)) {
        n = n->getSuccessor();
    }
    Node* insertNode = n->getSuccessor();
    insertNode->update(key, val);
    printf("Inserted new key %d into node %d. Printing all local keys.\n", key, insertNode->getID());
    insertNode->printAllLocalKeys(false);
}

void Node::insert(uint8_t key) { 
    Node* n = this;
    while(!betweenLeftInclusive(n->getID(), n->getSuccessor()->getID(), key)) {
        n = n->getSuccessor();
    }
    Node* insertNode = n->getSuccessor();
    printf("Inserting key %d into node %d\n", key, insertNode->getID());
    insertNode->update(key, -1);
    printf("Inserted new key %d into node %d. Printing all local keys.\n", key, insertNode->getID());
    insertNode->printAllLocalKeys(false);
}

std::map<uint8_t, int> Node::transfer() {
    Node* n = this;
    Node* nSucc = n->get(1);
    std::map<uint8_t, int> toTransfer;
    std::map<uint8_t, int>::iterator iter;
    std::map<uint8_t, int> nSuccCopy = nSucc->localKeys_;

    for (auto const& pair : nSucc->localKeys_) {
        uint8_t key = pair.first;
        int val = pair.second;
        if((key < n->getID()) && (n->getID() < nSucc->getID())){
            if(val == -1){
                printf("migrate key %d and val None from node %d to node %d\n", key, nSucc->getID(),this->getID());
            }
            else{
                printf("migrate key %d and val %d from node %d to node %d\n", key, val, nSucc->getID(),this->getID());
            }
            
            toTransfer[key] = val;
            nSuccCopy.erase(key);
        }
    }
    nSucc->localKeys_ = nSuccCopy;
    return toTransfer;
}

void Node::remove(uint8_t key)
{
    printf("Removing key %d from node %d\n", key, this->getID());
    localKeys_.erase(key);
}

void Node::printLocalKeys(){
    printf("----------Node ID:%d----------\n", id_);
    printf("{");
    for(auto it = localKeys_.cbegin(); it != localKeys_.cend(); ++it)
        {
            if(it->second != -1){
                printf("%d: %d", it->first, it->second);
            }
            else{
                printf("%d: None", it->first);
            }
            it++;
            if(it != localKeys_.cend()){
                printf(", ");
            }
            it--;
        }
    printf("}\n\n");
}


