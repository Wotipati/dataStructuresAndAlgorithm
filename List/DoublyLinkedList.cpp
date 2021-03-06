//
//  DoublyLinkedList.cpp
//  List
//
//  Created by Seita Kayukawa on 2018/01/16.
//  Copyright © 2018年 Seita Kayukawa. All rights reserved.
//

#include "DoublyLinkedList.h"

DoublyLinkedList::~DoublyLinkedList(){
    Node *nodeSearcher = beginNode_;
    Node *next_Node;
    while(nodeSearcher!= nullptr){
        next_Node = nodeSearcher->next_;
        delete nodeSearcher;
        nodeSearcher = next_Node;
    }
}


DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList &src){
    this->beginNode_ = nullptr;
    this->endNode_= nullptr;
    this->listLength_ = 0;

    Node *nodeSearcher = src.beginNode_;
    while(nodeSearcher != nullptr){
        pushBackNode(nodeSearcher->data_);
        nodeSearcher = nodeSearcher->next_;
    }
}


DoublyLinkedList &DoublyLinkedList::operator=(DoublyLinkedList src){
    Node *srcNodePtr = src.beginNode_;
    if(this->listLength_ <= 0){
        this->pushBackNode(srcNodePtr->data_);
        srcNodePtr = srcNodePtr->next_;
    }
    Node *thisNodePtr = this->beginNode_;

    if(this->listLength_ <= src.listLength_){
        while(thisNodePtr->next_ != nullptr){
            thisNodePtr->data_ = srcNodePtr->data_;
            thisNodePtr = thisNodePtr->next_;
            srcNodePtr = srcNodePtr->next_;
        }

        while(srcNodePtr != nullptr){
            this->pushBackNode(srcNodePtr->data_);
            srcNodePtr = srcNodePtr->next_;
        }
    }
    else{
        while(srcNodePtr->next_ != nullptr){
            thisNodePtr->data_ = srcNodePtr->data_;
            thisNodePtr = thisNodePtr->next_;
            srcNodePtr = srcNodePtr->next_;
        }
        while(this->listLength_ > src.listLength_){
            this->popBackNode();
        }
    }
    return *this;
}


bool DoublyLinkedList::replaceNode(int newData_, int index){
    if(abs(index)>listLength_ || index==0){
        std::cout << "ERROR: out of range" << std::endl;
        return false;
    }

    if(index>0){
        Node *nodeSearcher = beginNode_;
        for(int i=0; i<index-1; i++){
            nodeSearcher = nodeSearcher->next_;
        }
        nodeSearcher->data_ = newData_;
    }
    else{
        Node *nodeSearcher = endNode_;
        for(int i=0; i<index-1; i++){
            nodeSearcher = nodeSearcher->prev_;
        }
        nodeSearcher->data_ = newData_;
    }
    return true;
}


bool DoublyLinkedList::pushBackNode(int newData_){
    Node *newNode;
    newNode = new Node;
    newNode->data_ = newData_;
    newNode->next_ = nullptr;

    Node *nodeSearcher;
    if(!beginNode_ || listLength_ == 0){
        newNode->prev_ = nullptr;
        beginNode_ = newNode;
        endNode_ = newNode;
    }
    else{
        nodeSearcher = beginNode_;
        while(nodeSearcher->next_){
            nodeSearcher = nodeSearcher->next_;
        }
        nodeSearcher->next_ = newNode;
        newNode->prev_ = nodeSearcher;
        endNode_ = newNode;
    }
    listLength_ += 1;
    return true;
}


bool DoublyLinkedList::insertNode(int newData_, int index){
    if(abs(index)>listLength_+1 || index == 0){
        std::cout << "ERROR: out of range" << std::endl;
        return false;
    }

    Node *newNode;
    newNode = new Node;
    newNode->data_ = newData_;

    if(index == -1 || index == listLength_+1){
        pushBackNode(newData_);
    }
    else if(index == 1 || index == -(listLength_+1)){
        newNode->prev_ = nullptr;
        newNode->next_ = beginNode_;
        beginNode_->prev_ = newNode;
        beginNode_ = newNode;
        listLength_ += 1;
    }
    else if(index>1){
        Node *nodeSearcher = beginNode_;
        for(int i=1; i<index; i++){
            nodeSearcher = nodeSearcher->next_;
        }
        Node *nodeSearcherPrev = nodeSearcher->prev_;
        newNode->next_ = nodeSearcher;
        newNode->prev_ = nodeSearcherPrev;
        nodeSearcherPrev->next_ = newNode;
        nodeSearcher->prev_ = newNode;
        listLength_ += 1;
    }else{
        Node *nodeSearcher = endNode_;
        for(int i=-1; i>index; i--){
            nodeSearcher = nodeSearcher->prev_;
        }
        Node *nodeSearcherNext = nodeSearcher->next_;
        newNode->next_ = nodeSearcherNext;
        newNode->prev_ = nodeSearcher;
        nodeSearcher->next_ = newNode;
        nodeSearcherNext->prev_ = newNode;
        listLength_ += 1;
    }
    return true;
}


bool DoublyLinkedList::popBackNode(){
    if(listLength_ == 0){
        std::cout << "ERROR: stack underflow" <<std::endl;
        return false;
    }
    else if(listLength_ == 1){
        listLength_ = 0;
        beginNode_->data_ = 0;
        return true;
    }
    endNode_ = endNode_->prev_;
    delete endNode_->next_;
    endNode_->next_ = nullptr;
    listLength_ -= 1;
    return true;
}


int DoublyLinkedList::getData(int index) const{
    if(abs(index)>listLength_ || index==0){
        std::cout << "ERROR: out of range" << std::endl;
        return -1;
    }

    if(index>=1){
        Node *nodeSearcher = beginNode_;
        for(int i=1; i<index; i++){
            nodeSearcher = nodeSearcher->next_;
        }
        return nodeSearcher->data_;
    }
    else{
        Node *nodeSearcher = endNode_;
        for(int i=-1; i>index; i--){
            nodeSearcher = nodeSearcher->prev_;
        }
        return nodeSearcher->data_;
    }
}



bool DoublyLinkedList::deleteNode(int index){
    if(listLength_ == 0){
        std::cout << "ERROR: stack underflow" <<std::endl;
        return false;
    }

    if(abs(index)>listLength_ || index==0){
        std::cout << "ERROR: out of range" << std::endl;
        return false;
    }

    if(listLength_ == 1){
        popBackNode();
    }

    else if(index == 1 || index == -1*listLength_){
        beginNode_ = beginNode_->next_;
        delete beginNode_->prev_;
        beginNode_->prev_ = nullptr;
        listLength_ -= 1;
    }
    else if(index == -1 || index == listLength_){
        popBackNode();
    }
    else if(index>1){
        Node *nodeSearcher = beginNode_;
        for(int i=1; i<index-1; i++){
            nodeSearcher = nodeSearcher->next_;
        }
        Node *deletingNode = nodeSearcher->next_;
        nodeSearcher->next_ = deletingNode->next_;
        nodeSearcher->next_->prev_ = nodeSearcher;
        listLength_ -= 1;
        delete deletingNode;
    }
    else{
        Node *nodeSearcher = endNode_;
        for(int i=-1; i>index+1; i--){
            nodeSearcher = nodeSearcher->prev_;
        }
        Node *deletingNode = nodeSearcher->prev_;
        nodeSearcher->prev_ = deletingNode->prev_;
        nodeSearcher->prev_->next_ = nodeSearcher;
        listLength_ -= 1;
        delete deletingNode;
    }
    return true;
}


void DoublyLinkedList::display() const{
    Node *nodeSearcher = beginNode_;
    while(nodeSearcher->next_){
        std::cout << nodeSearcher->data_ << ", ";
        nodeSearcher = nodeSearcher->next_;
    }
    std::cout << nodeSearcher->data_ << std::endl;
}