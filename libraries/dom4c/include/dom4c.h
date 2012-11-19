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
    
    struct _Element *parentElement;
    
} Element;

Node *CreateEmptyNode();

Node *CreateNode(char *name);

Element *CreateEmptyElement();

Element *CreateElement(char *eleName);

/**
 * Add sub element to parent
 * @param parent Element
 * @param sub    Element
 */
void AddElement(Element *parent, Element *sub);

/**
 * Add node to parent element
 * This function usally used by add Text to Element
 * @param parent Element
 * @param node   Node
 */
void addNode(Element *parent, Node *node);

#endif // dom4c_dom4c_h