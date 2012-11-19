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

// Private functions

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

Element *CreateEmptyElement()
{
    return CreateElement(NULL);
}

Element *CreateElement(char *eleName)
{
    Element *ret = (Element *)malloc(sizeof(Element));
    Node *node = CreateNode(eleName);
    ret->parentNode = node;
    ret->attributes = NULL;
    return ret;
}
