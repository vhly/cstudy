//
//  dom4c.h
//  dom4c
//
//  Created by vhly on 12-11-19.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef dom4c_dom4c_h
#define dom4c_dom4c_h

#define NODE_TYPE_NODE 0
#define NODE_TYPE_ELEMENT 1
#define NODE_TYPE_TEXT    2
#define NODE_TYPE_ATTRIBUTE 3
#define NODE_TYPE_COMMENT 4


typedef struct _Node {
    char nodeType;
    
    char* nodeName;
    
    char* nodeValue;
    
    // prev sub
    struct _Node *prevSub;
    
    struct _Node *nextSub;
    
    struct _Node *children;
    
} Node, *NodeList;

typedef Node Attribute, *Attributes;

typedef Node Element;

#pragma mark -
#pragma mark Node Operation

/**
 * Create empty node
 * @return Node empty node for operations
 */
Node *CreateEmptyNode();

/**
 * Create named node with parameter
 * @param name
 * @param Node
 */
Node *CreateNode(char *name);

/**
 * Find  first node item which named by parameter in NodeList<br/>
 * This function will return node item ref and not modify it
 * @param nodeList NodeList
 * @param type node type
 * @param name
 * @return Node result node or NULL
 * @see FindNodesByName
 */
Node *FindNodeByName(NodeList nodeList, char type, char *name);

/**
 * Find some nodes witch named by parameter<br/>
 * This function will copy node content and return a new instance of node<br/>
 * The result contains nodes which copy from origin node data, but node's children ref not modify.
 * @param parent  Node which node will be find
 * @param type    node type
 * @param name    node name
 * @return NodeList found nodes copy
 * @see FindNodeByName
 */
NodeList FindNodesByName(Node *parent, char type, char *name);

#pragma mark -
#pragma mark Element Operation

/**
 * Create empty Element instance.
 * @return Element
 */
Element *CreateEmptyElement();

/**
 * Create element which name is.
 * @param eleName element name
 * @return Element
 */
Element *CreateElement(char *eleName);

/**
 * Add sub element to parent
 * @param parent Element
 * @param sub    Element
 */
void AddElement(Element *parent, Element *sub);




#pragma mark -
#pragma mark Attribute Operation

/**
 * Create Attribute by name and value
 * @param attName   Attribute's name
 * @param attValue  Attribute's value
 * @return Attribute
 */
Attribute *CreateAttribute(char *attName, char *attValue);

/**
 * Set element's attribute
 * @param element the element which set
 * @param attr Attribute
 * @see GetAttribute
 */
void SetAttribute(Element *element, Attribute *attr);

/**
 * Get element's attribute by attribute's name
 * @param element Element
 * @param attName Attribute's name
 * @return Attribute
 * @see SetAttribute
 */
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