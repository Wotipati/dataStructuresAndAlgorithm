//
//  MyList.h
//  List
//
//  Created by Seita Kayukawa on 2018/01/16.
//  Copyright © 2018年 Seita Kayukawa. All rights reserved.
//

#ifndef MyList_h
#define MyList_h

#include <stdio.h>
#include <iostream>

class MyList{
public:
    MyList();
    ~MyList();
    void replaceNode(int newData, int index);
    void pushbackNode(int newData);
    void insertNode(int newData, int index);
    void popbackNode();
    void deleteNode(int index);
    void display();
    
private:
    MyList *beginNode_;
    MyList *endNode_;
    MyList *prev_;
    MyList *next_;
    int data_;
    int listLength_;
};

#endif /* MyList_h */
