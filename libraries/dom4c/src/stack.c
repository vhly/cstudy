//
//  stack.c
//  dom4c
//
//  Created by vhly on 12-11-19.
//  Copyright (c) 2012年 vhly. All rights reserved.
//

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

// Private functions

StackItem *FindBottomItem(StackStore stack)
{
    StackItem *ret = NULL;
    if (stack != NULL) {
        ret = stack;
        while (ret != NULL) {
            if (ret->prevItem != NULL) {
                ret = ret->prevItem;
            } else {
                break;
            }
        }
    }
    return stack;
}

StackItem *FindTopItem(StackStore stack)
{
    StackItem *ret = NULL;
    if (stack != NULL) {
        ret = stack;
        while (ret != NULL) {
            if (ret->nextItem != NULL) {
                ret = ret->nextItem;
            } else {
                break;
            }
        }
    }
    return stack;
}

// Public functions

StackItem *CreateEmptyItem()
{
    return CreateItem(NULL);
}

StackItem *CreateItem(void *object)
{
    StackItem *ret = (StackItem *)malloc(sizeof(StackItem));
    ret->object = object;
    ret->nextItem = NULL;
    ret->prevItem = NULL;
    return ret;
}

void PushItem(StackStore stack, StackItem *item)
{
    if (stack != NULL && item != NULL) {
        StackItem *top = FindTopItem(stack);
        if (top != NULL) {
            top->nextItem = item;
            item->prevItem = top;
        }
    }
}

StackItem *PopItem(StackStore stack)
{
    StackItem *ret = NULL;
    if (stack != NULL) {
        ret = FindTopItem(stack);
        if (ret != NULL) {
            if (ret->prevItem != NULL) {
                ret->prevItem->nextItem = NULL;
                ret->prevItem = NULL;
            }
        }
    }
    return ret;
}

StackItem *PeekItem(StackStore stack)
{
    return FindTopItem(stack);
}

int StackSize(StackStore stack)
{
    int ret = 0;
    if (stack != NULL) {
        StackItem *bottom = FindBottomItem(stack);
        if (bottom != NULL) {
            while (bottom != NULL) {
                ret++;
                if (bottom->nextItem != NULL) {
                    bottom = bottom->nextItem;
                } else {
                    break;
                }
            }
        }
    }
    return ret;
}

void ClearItems(StackStore stack)
{
    if (stack != NULL) {
        StackItem *top = FindTopItem(stack);
        StackItem *tmp = NULL;
        while (top != NULL) {
            top->nextItem = NULL;
            top->object = NULL;
            if (top->prevItem != NULL) {
                tmp = top;
                top = top->prevItem;
                tmp->prevItem = NULL;
            } else {
                break;
            }
        }
    }
}
