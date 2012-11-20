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
#define NODE_TYPE_ATTRIBUTE 3


typedef struct _Node {
    char nodeType;
    
    char* nodeName;
    
    char* nodeValue;
    
    // prev sub
    struct _Node *prevSub;
    
    struct _Node *nextSub;
    
    struct _Node *children;
    
} Node;

typedef Node Attribute, *Attributes;

typedef Node Element;

#pragma mark -
#pragma mark Element Operation

Node *CreateEmptyNode();

Node *CreateNode(char *name);

Node *FindNodeByName(Node *nodeList, char type, char *name);

#pragma mark -
#pragma mark Element Operation

Element *CreateEmptyElement();

Element *CreateElement(char *eleName);

/**
 * Add sub element to parent
 * @param parent Element
 * @param sub    Element
 */
void AddElement(Element *parent, Element *sub);




#pragma mark -
#pragma mark Attribute Operation

Attribute *CreateAttribute(char *attName, char *attValue);

void SetAttribute(Element *element, Attribute *attr);

Attribute *GetAttribute(Element *element, char *attName);

#pragma mark -

/**
 * Add node to parent element
 * This function usally used by add Text to Element
 * @param parent Element
 * @param node   Node
 */
void addNode(Node *parent, Node *node);

#endif // dom4c_dom4c_h