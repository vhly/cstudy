//
//  stack.h
//  dom4c
//
//  Created by vhly on 12-11-19.
//  Copyright (c) 2012年 vhly. All rights reserved.
//

#ifndef dom4c_stack_h
#define dom4c_stack_h

typedef struct _StackItem {
    void *object;
    struct _StackItem *prevItem;
    struct _StackItem *nextItem;
} StackItem, *StackStore;


StackItem *CreateEmptyItem();

StackItem *CreateItem(void *object);

void PushItem(StackStore stack, StackItem *item);

StackItem *PopItem(StackStore stack);

StackItem *PeekItem(StackStore stack);

int StackSize(StackStore stack);

/**
 * Remove all item ref and all items point will set NULL
 *
 */
void ClearItems(StackStore stack);

#endif
