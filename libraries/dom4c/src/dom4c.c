//
//  dom4c.c
//  dom4c
//
//  Created by vhly on 12-11-19.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "dom4c.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Private functions

Node *FindLastChild(Node *parent)
{
    Node *ret = NULL;
    if (parent != NULL) {
        ret = parent->children;
        while (ret != NULL) {
            if (ret->nextSub != NULL) {
                ret = ret->nextSub;
            } else {
                break;
            }
        }
    }
    return ret;
}

// Public functions

Node *CreateEmptyNode()
{
    return CreateNode(NULL);
}

Node *CreateNode(char *name)
{
    Node *ret = (Node *)malloc(sizeof(Node));
    ret->nodeName = name;
    ret->nodeType = 0;
    ret->prevSub = NULL;
    ret->nextSub = NULL;
    ret->children = NULL;
    return ret;
}

Node *FindNodeByName(Node *nodeList, char type, char *name)
{
    Node *ret = NULL;
    if (nodeList != NULL && name != NULL) {
        switch (type) {
            case NODE_TYPE_ELEMENT:
            case NODE_TYPE_ATTRIBUTE:
            case NODE_TYPE_TEXT:
                {
                    Node *cur = nodeList;
                    while (cur != NULL) {
                        if (cur->nodeType == type) {
                            int cmp = strcmp(cur->nodeName, name);
                            if (cmp == 0) {
                                ret = cur;
                                break;
                            }
                        }
                        if (cur->nextSub != NULL) {
                            cur = cur->nextSub;
                        }
                    }
                }
                break;
                
            default:
                break;
        }
    }
    return ret;
}

Element *CreateEmptyElement()
{
    return CreateElement(NULL);
}

Element *CreateElement(char *eleName)
{
    Element *ret = (Element *)malloc(sizeof(Element));
    ret->nodeName = eleName;
    ret->nodeType = NODE_TYPE_ELEMENT;
    ret->nodeValue = NULL;
    ret->prevSub = NULL;
    ret->nextSub = NULL;
    ret->children = NULL;
    return ret;
}

void AddElement(Element *parent, Element *sub)
{
    addNode(parent, sub);
}


Attribute *CreateAttribute(char *attName, char *attValue)
{
    Attribute *ret = NULL;
    if (attName != NULL && attValue != NULL) {
        ret = (Attribute *)malloc(sizeof(Attribute));
        ret->nodeType = NODE_TYPE_ATTRIBUTE;
        ret->nodeName = attName;
        ret->nodeValue = attValue;
        ret->prevSub = NULL;
        ret->nextSub = NULL;
        ret->children = NULL;
    }
    return ret;
}

void SetAttribute(Element *element, Attribute *attr)
{
    if (element != NULL && attr != NULL) {
        Node *last = FindLastChild(element);
        if (last == NULL) {
            element->children = attr;
        } else {
            last->nextSub = attr;
            attr->prevSub = last;
        }
    }
}

Attribute *GetAttribute(Element *element, char *attName)
{
    Attribute *ret = NULL;
    if (element != NULL && attName != NULL) {
        ret = FindNodeByName(element->children, NODE_TYPE_ATTRIBUTE, attName);
    }
    return ret;
}


void addNode(Node *parent, Node *node)
{
    if (parent != NULL && node != NULL) {
        Node *last = FindLastChild(parent);
        if (last == NULL) {
            parent->children = node;
        } else {
            last->nextSub = node;
            node->prevSub = last;
        }
    }
}
