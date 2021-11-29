#include "node.h"
#include <iostream>
using namespace std;

// checks if key is between vars a and b
// bool between(uint8_t a, uint8_t b, uint8_t key){
//     printf("a is %d, b is %d\n", a, b);
//     uint8_t start = min(a,b);
//     uint8_t end = max(a,b);
//     if((key >= start) && (key <= end)){
//         return true;
//     }
//     return false;
// }

// checks if key is between vars a and b
// uint8 range = [0, 255]
bool between(uint8_t a, uint8_t b, uint8_t key, bool aInc, bool bInc){
    // if not a inclusive, increase a by 1
    if(!aInc){
        a++;
    }
    // if not b inclusive, decrease b by 1
    if(!bInc){
        b--;
    }
    if (a > b){    
        printf("a(%d) is greater than b(%d), key is %d\n", a, b, key);
        printf("searching range [%d, 255], [0, %d]\n", a, b);
        if((key >= a && key <= 255) || (key >= 0 && key <= b)){
            printf("Key is in between!\n");
        }
        else{
            printf("Key is NOT in between!\n");
        }
        return (key >= a && key <= 255) || (key >= 0 && key <= b);
    }
    else if (b > a){
        printf("a(%d) is smaller than b(%d), key is %d\n", a, b, key);
        printf("searching range [%d, %d]\n", a, b);
        if((key >= a) && (key <= b)){
            printf("Key is in between!\n");
        }
        else{
            printf("Key is NOT in between!");
        }
        return (key >= a) && (key <= b);
    }
    else{
        return key == a;
    }

    return false;
}

Node* Node::findSuccessor(uint8_t id)
{
    Node* succ = findPredecessor(id);
    cout << (int) succ->getSuccessor()->getID() << " is the succ of " << (int) id << endl;
    return succ->getSuccessor();
}

Node *Node::findPredecessor(uint8_t id)
{
    Node *temp = this;
    int loopCnt = 0;
    while ( !between(temp->getID(), temp->getSuccessor()->getID(), id, false, true) ) {
        printf("FIND PRED LOOP\n");
        temp = temp->closestPrecedingFinger(id);
        loopCnt++;
        if(loopCnt >  10) {
            break;
        }
    }
    //loops infinitely because its its own pred
    // printf("Predecessor Found: %d\n", temp->getID());
    cout << (int) temp->getID() << " is the pred of " << (int) id << endl;
    return temp;
}

Node *Node::closestPrecedingFinger(uint8_t id)
{
    std::vector<Node*> fingers = FingerTable_.getInner();
    for(int i=BITLENGTH; i>0; --i) {
        printf("Searching between %d and %d\n", this->getID(), id);
        fflush(stdout);

        if(between(this->getID(), id, fingers[i]->getID(), false, false)){
            printf("RETURNED fingers[i]: id %d\n", fingers[i]->getID());
            return fingers[i];
        }
    }
    return this;
}

// initialize finger table of local node;
// n0 is an arbitrary node already in the network
// n.init_finger_table(n0)
void Node::init_finger_table(Node* node){
    // finger[1].node = n0.find_successor(finge`                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            r[1].start);
    uint8_t fingerStart = id_ + 1; // 1 = 2**0
    FingerTable_.set( 1, node->findSuccessor(fingerStart) );
    // predecessor = successor.predecessor;
    successor = FingerTable_.get(1);
    predecessor = successor->getPredecessor();
    // successor.predecessor = n;
    successor->setPredecessor(this);
    // for i = 1 to m - 1
    for(int i=1; i<BITLENGTH; i++){
        std::vector<Node*> fingers = FingerTable_.getInner();
        uint8_t fingerStart = id_ + pow(2, i); //returns start of finger i+1 (NOT 1)
        // if (finger[i+1].start is in [n, finger[i].node))
        printf("INIT FINGER TABLE FOR LOOP\n");
        if(between(id_, fingers[i]->getID(), fingerStart, true, false)){
            // finger[i+1].node = finger[i].node;
            FingerTable_.set(i+1, fingers[i]);
        }
        else{
            // finger[i+ 1].node = node.find successor(finger[i+ 1].start);
            FingerTable_.set(i+1, node->findSuccessor(fingerStart));
        }
    }
}

// update all nodes whose finger
// // tables should refer to n
void Node::update_others(){
    for(int i=1; i<=BITLENGTH; i++){
        Node *p = findPredecessor(this->getID()-pow(2,i-1));
        p->update_finger_table(this, i); 
    }
}

void Node::update_finger_table(Node* s, uint8_t i){
    if( between(this->getID(), FingerTable_.get(i)->getID(), s->getID(), true, false) ){
        printf("UPDATE FINGER TABLE LOOP\n");
        FingerTable_.set(i, s);
        Node* p = predecessor;
        p->update_finger_table(s, i);
    }
    
}


void Node::join(Node *node)
{
    // Adding node to existing network
    // if (this->getID() == 63){
    //     node->hack(this);
    //     node->getFingerTable().prettyPrint(node);
    // }


    if (node)
    {
        FingerTable_.initInnerFT(NULL);
        init_finger_table(node);
        update_others();

        // 1. Initialize the predecessor and fingers of node n.
        // 2. Update the fingers and predecessors of existing nodes to reflect
        // the addition of n.
        // 3. Notify the higher layer software so that it can transfer state
        // (e.g. values) associated with keys that node n is now responsible for.
        // update_others

        // std::map<uint8_t, uint8_t> a = transfer(node);
        
    }
    // First node in network
    else
    {
        FingerTable_.initInnerFT(node);
        successor = this;
        predecessor = this;
        // Set all successors in FT to self
        for (int i = 1; i < BITLENGTH + 1; i++)
        {
            FingerTable_.set(i, successor);
        }
    }

    FingerTable_.prettyPrint(this);
}

// void Node::Leave() {
//     //to do?
// }

uint8_t Node::find(uint8_t key)
{
    // check local keys for keyt
    auto search = localKeys_.find(key);
    // if search is successful
    if (search != localKeys_.end())
    {
        // return value from dictionary key query
        return search->second;
    }
    else
    {
        cerr << "NNN\n";
        exit(1);
    }
}

void Node::insert(uint8_t key, uint8_t val)
{

    std::pair<std::map<uint8_t, uint8_t>::iterator, bool> ret;
    ret = localKeys_.insert(std::pair<uint8_t, uint8_t>(key, val));

    if (ret.second == false)
    {
        // do something, key already exists
    }
}

void Node::remove(uint8_t key)
{
    localKeys_.erase(key);
}


