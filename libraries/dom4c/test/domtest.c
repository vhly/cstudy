#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "dom4c.h"

#include "testdefine.h"

void TestStackPush()
{
    StackStore stack = CreateEmptyItem();
    
    StackItem *item1 = CreateItem("RSS");
    
    PushItem(stack, item1);
    
    int sz = StackSize(stack);
    
    printf("Stack TestPush size : %d\n",sz);
}

void TestStackPop()
{
    StackStore stack = CreateEmptyItem();
    
    StackItem *item1 = CreateItem("RSS");
    
    PushItem(stack, item1);
    
    int sz = StackSize(stack);
    
    printf("Stack TestPop size1 : %d\n",sz);
    
    PopItem(stack);
    
    sz = StackSize(stack);
    
    printf("Stack TestPop size2 : %d\n",sz);
}
void TestStackPeek()
{
    StackStore stack = CreateEmptyItem();
    
    StackItem *item1 = CreateItem("RSS");
    
    PushItem(stack, item1);
    
    StackItem *item2 = PeekItem(stack);
    
    if (item2 != NULL) {
        char *cc = (char *)item2->object;
        int cmp = strcmp("RSS", cc);
        printf("Peek Object compare is : %d\n", cmp);
    } else {
        printf("Peek Error\n");
    }
}

void TestStack()
{
    TestStackPush();
    
    TestStackPop();
    
    TestStackPeek();
}

void TestNodeCreate()
{
    Node *node = CreateEmptyNode();
    testAssertEquals(NULL, node->nodeName, "nodeName must NULL");
    
    free(node);
    
    node = CreateNode("RSS");
    
    testAssertStringEquals("RSS", node->nodeName, "nodeName must RSS");
    
    free(node);
    
    Element *el = CreateElement("RSS");
    
    testAssertStringEquals("RSS", el->nodeName, "nodeName must RSS");
    
    free(el);
    
}



void TestDom()
{
    TestNodeCreate();
}

int main(int argc, char *argv[]){
	printf("Hello for DOM4C Test\n");
    
    TestStack();
    
    TestDom();
    
	return 0;
}


