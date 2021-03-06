//
// Created by Seita Kayukawa on 2018/01/19.
//

#ifndef LIST_DoublyLinkedListTEMPLATE_H
#define LIST_DoublyLinkedListTEMPLATE_H

#include <stdio.h>
#include <iostream>

template <typename T>
class DoublyLinkedListTemp{
public:
    DoublyLinkedListTemp():beginNode_(nullptr),endNode_(nullptr),listLength_(0){}
    ~DoublyLinkedListTemp();
    DoublyLinkedListTemp(const DoublyLinkedListTemp& other);
    DoublyLinkedListTemp &operator=(DoublyLinkedListTemp<T> src);
    bool replaceNode(T newData, int index);
    bool pushBackNode(T newData);
    bool insertNode(T newData, int index);
    bool popBackNode();
    bool deleteNode(int index);
    void display();

private:
    struct Node{
        Node *prev_;
        Node *next_;
        T data_;
    };
    Node *beginNode_;
    Node *endNode_;
    int listLength_;
};


template <typename T>
DoublyLinkedListTemp<T>::DoublyLinkedListTemp(const DoublyLinkedListTemp &src){
    this->beginNode_ = nullptr;
    this->endNode_= nullptr;
    this->listLength_ = 0;

    Node *nodeSearcher = src.beginNode_;
    while(nodeSearcher != nullptr){
        pushBackNode(nodeSearcher->data_);
        nodeSearcher = nodeSearcher->next_;
    }
}


template <typename T>
DoublyLinkedListTemp<T> &DoublyLinkedListTemp<T>::operator=(DoublyLinkedListTemp<T> src){
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


template <typename T>
bool DoublyLinkedListTemp<T>::replaceNode(T newData_, int index){
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

template <typename T>
bool DoublyLinkedListTemp<T>::pushBackNode(T newData_){
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

template <typename T>
bool DoublyLinkedListTemp<T>::insertNode(T newData_, int index){
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


template <typename T>
void DoublyLinkedListTemp<T>::display(){
    Node *nodeSearcher = beginNode_;
    while(nodeSearcher->next_){
        std::cout << nodeSearcher->data_ << ", ";
        nodeSearcher = nodeSearcher->next_;
    }
    std::cout << nodeSearcher->data_ << std::endl;
}


template <typename T>
bool DoublyLinkedListTemp<T>::popBackNode(){
    if(listLength_ == 0){
        std::cout << "ERROR: stack underflow" <<std::endl;
        return false;
    }
    else if(listLength_ == 1){
        listLength_ = 0;
        return true;
    }
    endNode_ = endNode_->prev_;
    delete endNode_->next_;
    endNode_->next_ = nullptr;
    listLength_ -= 1;
    return true;
}


template <typename T>
bool DoublyLinkedListTemp<T>::deleteNode(int index){
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

    if(index == 1 || index == -1*listLength_){
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


template <typename T>
DoublyLinkedListTemp<T>::~DoublyLinkedListTemp(){
    Node *nodeSearcher = beginNode_;
    Node *next_Node;
    while(nodeSearcher!= nullptr){
        next_Node = nodeSearcher->next_;
        delete nodeSearcher;
        nodeSearcher = next_Node;
    }
}

#endif //LIST_DoublyLinkedListTEMPLATE_H
