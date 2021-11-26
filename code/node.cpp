#include "node.h"
#include <iostream>
using namespace std;

// checks if key is between vars a and b
bool between(uint8_t a, uint8_t b, uint8_t key){
    uint8_t start = min(a,b);
    uint8_t end = max(a,b);
    if((key >= start) && (key <= end)){
        return true;
    }
    return false;
}

Node* Node::findSuccesor(uint8_t id)
{
    Node* succ = findPredecessor(id);
    return succ->getSuccesor();
}

Node *Node::findPredecessor(uint8_t id)
{
    Node *temp = this;
    while ( !between(temp->getID(), temp->getSuccesor()->getID(), id) )
    {
        // why is the -> getSuccessor here?
        // temp = temp->closestPrecedingFinger(id)->getSuccesor();
        temp = temp->closestPrecedingFinger(id);
    }
    
    return temp;
}

Node *Node::closestPrecedingFinger(uint8_t id)
{
    std::vector<Node*> fingers = FingerTable_.getInner();
    for(int i=BITLENGTH; i>0; --i){
        printf("i = %d\n", i);
        printf("Searching between %d and %d\n", this->getID(), id);
        fflush(stdout);

        if(between(this->getID(), id, fingers[i]->getID())){
            cout << "RETURNED fingers[i]";
            return fingers[i];
        }
    }
    // for (auto &entry : FingerTable_.getInner())
    // {
    //     cout << "Entry: " << entry->getID();
    //     if(entry->getID() == id{
    //     if(entry->getID() == id{
    //         return
    //     }
    // }
    return this;
}

// initialize finger table of local node;
// n0 is an arbitrary node already in the network
// n.init_finger_table(n0)
//     finger[1].node = n0.find_successor(finger[1].start);
//     predecessor = successor.predecessor;
//     successor.predecessor = n;
//     for i = 1 to m 􀀀 1
//         if (finger[i+1].start is in [n, finger[i].node))
//             finger[i+1].node = finger[i].node;
//         else
//             finger[i+ 1].node = n0.find successor(finger[i+ 1].start);


// initialize finger table of local node;
// n0 is an arbitrary node already in the network
// n.init_finger_table(n0)
void Node::init_finger_table(Node* node){
    // finger[1].node = n0.find_successor(finger[1].start);
    uint8_t fingerStart = id_ + 1; // 1 = 2**0
    FingerTable_.set( 1, node->findSuccesor(fingerStart) );
    cout << "seg fault above\n";
    // predecessor = successor.predecessor;
    predecessor = succesor->getPredecessor();
    // successor.predecessor = n;
    succesor->setPredecessor(this);
    // for i = 1 to m - 1

    
    for(int i=1; i<BITLENGTH; i++){
        std::vector<Node*> fingers = FingerTable_.getInner();
        uint8_t fingerStart = id_ + pow(2, i); //returns start of finger i+1 (NOT i)
        // if (finger[i+1].start is in [n, finger[i].node))
        if(between(id_, fingers[i]->getID(), fingerStart)){
            // finger[i+1].node = finger[i].node;
            FingerTable_.set(i+1, fingers[i]);
        }
        else{
            // finger[i+ 1].node = node.find successor(finger[i+ 1].start);
            FingerTable_.set(i+1, node->findSuccesor(fingerStart));
        }

    //         finger[i+1].node = finger[i].node;
    //     else
    //         finger[i+ 1].node = n0.find successor(finger[i+ 1].start);

    }
  

}

void Node::join(Node *node)
{
    // Adding node to existing network
    if (node)
    {
        FingerTable_.initInnerFT(NULL);
        init_finger_table(node);
        // update_others()

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
        succesor = this;
        predecessor = this;
        // Set all successors in FT to self
        for (int i = 1; i < BITLENGTH + 1; i++)
        {
            FingerTable_.set(i, succesor);
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


