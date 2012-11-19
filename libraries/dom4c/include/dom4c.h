//
//  dom4c.h
//  dom4c
//
//  Created by vhly on 12-11-19.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef dom4c_dom4c_h
#define dom4c_dom4c_h

#define NODE_TYPE_ELEMENT 1
#define NODE_TYPE_TEXT    2


typedef struct _Node {
    char nodeType;
    char* nodeName;
    
    // prev sub
    struct _Node *prevSub;
    
    struct _Node *nextSub;
    
    struct _Node *children;
    
} Node;

typedef struct _Attribute {
    char *attName;
    char *attValue;

    struct _Attribute *prevSub;
    struct _Attribute *nextSub;
} Attribute, *Attributes;

typedef struct _Element {
    Node *parentNode;
    Attributes attributes;
} Element;

Node *CreateEmptyNode();

Node *CreateNode(char *name);

Element *CreateEmptyElement();

Element *CreateElement(char *eleName);

#endif // dom4c_dom4c_h