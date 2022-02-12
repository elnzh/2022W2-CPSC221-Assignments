#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  clear();
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node *p, const Block &ndata) {
    Node *curr= new Node(ndata);
    length_++;
    Node *next;
    if(head_==NULL){
        head_ = curr;
    }else if(p==NULL) {
        curr->next=head_;
        head_->prev=curr;
        head_=curr;
        curr->prev=NULL;
    }else if(p->next==NULL) {
            p->next = curr;
            curr->prev = p;
            curr->next = NULL;

    } else{
      next = p->next;
      p->next = curr;
      curr->prev = p;
      curr->next = next;
      next-> prev = curr;
    }
    
    return curr;
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {
    if(p==q || p == NULL || q ==NULL){
        return;
    }

  if(p==head_){
      swapHead(p, q);
      return;
  }
  if(q==head_){
      swapHead(q, p);
      return;
  }
   Node* pPrev=p->prev;
   Node* pNext =p->next;
   Node* qPrev=q->prev;
   Node* qNext =q->next;
   if(pPrev!=q && qPrev!=p){
       if(qNext==nullptr){
           pPrev->next=q;
           q->prev=pPrev;
           q->next=pNext;
           pNext->prev=q;
           qPrev->next=p;
           p->prev=qPrev;
           p->next= nullptr;
           return;
       }
       if(pNext==NULL){
           qPrev->next=p;
           p->prev=qPrev;
           p->next=qNext;
           qNext->prev=q;
           pPrev->next=q;
           q->prev=pPrev;
           q->next=NULL;
           return;
       }
       pPrev->next =q;
       q->prev=pPrev;
       q->next =pNext;
       pNext->prev=q;
       p->prev = qPrev;
       qPrev->next = p;
       p->next=qNext;
       qNext->prev = p;
   }else if(pPrev==q ){
       swapBetween(q, p);
   }else if(qPrev==p){
       swapBetween(p,q);
   }



}
/**
 * swap two nodes if they are between each other
 * @param before the node  before
 * @param after the node after before
 */
void Chain::swapBetween(Node *before, Node * after){
    Node *p=before->prev;
    if(after->next==NULL){
        p->next=after;
        after->prev=p;
        after->next=before;
        before->prev=after;
        before->next=NULL;
        return;
    }

    Node* n=after->next;
    p->next=after;
    after->prev=p;

    after->next=before;
    before->prev=after;

    before->next=n;
    n->prev=before;
    return;

}
/**
 * swap the node with a head node
 * @param p the head_
 * @param q the other Node to swap
 */
void Chain::swapHead(Node *p, Node * q){
    Node* pNext = p->next;
    Node* qPrev =q->prev;
    //swap with the last element
    if(q->next==NULL && pNext!=q){
       pNext->prev=q;
       q->next=pNext;
       q->prev=NULL;
       qPrev->next=p;
       p->prev=qPrev;
       p->next=NULL;
       head_=q;
       return;
    }

    //if they are next to each other
    if(qPrev==p){
        //if q is the last element
        if(q->next==NULL){
            p->next=NULL;
            p->prev=q;
            q->prev=NULL;
            q->next=p;
        }else{
            Node* qNext = q->next;
            p->next =qNext;
            qNext->prev=p;
            q->next=p;
            p->prev=q;
            q->prev =NULL;
        }
        head_=q;
        return;
    }else{
        Node* qNext = q->next;
        p->next = qNext;
        qNext->prev=p;
        qPrev->next=p;
        p->prev=qPrev;
        q->prev=NULL;
        q->next=pNext;
        pNext->prev=q;
        head_=q;
        return;
    }
}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
    Node *curr = head_;

    while(curr!=NULL){
        Node *next =curr->next;
        delete curr;
        curr=next;
    }
    head_=NULL;
    length_=0;
    // Node *curr = head_;

//    while(curr->next !=NULL && curr!=NULL){
//      head_ = head_->next;
//      //std::cout<<"delete"<<std::endl;
//
//      delete curr;
//
//      curr=head_;
//
//    }
//    delete head_;
//    head_=NULL;
//    curr=NULL;


}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
clear();
if(other.head_== NULL){
    return;
}
    head_=new Node(other.head_->data);
    Node *otherNext =other.head_;
    Node *prev = NULL;
    Node *next =head_;
    for(int i=1; i<other.size();i++){
        otherNext=otherNext->next;
        next->next=new Node(otherNext->data);
        prev=next;
        next=next->next;
        next->prev=prev;
        next->next=NULL;
    }
    length_= other.length_;


}

/* Modifies the current chain: 
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block 
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {
  double arr[length_];
  Node *curr=head_;

  for(unsigned int i=0;i<(unsigned)length_;i++){
      arr[i]=findMinDistance(curr);
      if(curr->next!=NULL){
          curr=curr->next;
      }
  }

  int frontIndex = findMaxIndex(arr);

  //search for the first block
  Node *front=head_;
  for(unsigned int i=0;i<(unsigned)frontIndex;i++){
    front=front->next;
  }
  swap(front, head_);


   Node* temp = head_;

  for(unsigned int i=1;i<(unsigned)length_;i++){
      temp = unscrambleNext(temp);
    if(temp->next!=NULL){
        temp=temp->next;
    }
}


}

double Chain::findMinDistance(Node *curr){
    Node* next =head_;
    char isFirst=true;
    double min=10000;
    double temp=10000;

    while(next->next!=NULL && next!=NULL){
        if(next!=curr && isFirst){
            min = next->data.distanceTo(curr->data);
            isFirst = false;
        }else if(next!=curr){
            temp = next->data.distanceTo(curr->data);
            if(temp<min){
               min=temp;
            }
        }
        next=next->next;
    }
    //std::cout<<"findMinDistance loop exit"<<std::endl;
    temp = next->data.distanceTo(curr->data);
    if(temp<min){
        min=temp;
    }

  return min;
}


int Chain::findMaxIndex(double *arr){

  double max=arr[0];
  int index=0;

  for(unsigned int i=1;i<(unsigned)length_;i++){
    if(arr[i]>max){
        max=arr[i];
        index=i;
    }
  }

    return index;
}


Chain::Node * Chain::unscrambleNext(Node *start){
  Node *next = start->next;
  double min=start->data.distanceTo(next->data);
  double temp;
  Node* minNode=next;
  while(next->next!=NULL && next!=NULL){
      temp=start->data.distanceTo(next->data);
      if(temp<min){
        min = temp;
        minNode = next;
      }
      next=next->next;

  }
  //std::cout<<"unScrambleNext loop exit"<<std::endl;
    temp=start->data.distanceTo(next->data);
    if(temp<min){
        min = temp;
        minNode = next;
    }

  swap(start->next, minNode);
  return start;

}






