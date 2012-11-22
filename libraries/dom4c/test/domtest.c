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
    testAssertEquals(NULL, node->nodeName, "nodeName must NULL\n");
    
    free(node);
    
    node = CreateNode("RSS");
    
    testAssertStringEquals("RSS", node->nodeName, "nodeName must RSS\n");
    
    free(node);
    
    Element *el = CreateElement("RSS");
    
    testAssertStringEquals("RSS", el->nodeName, "nodeName must RSS\n");
    
    Element *sub1 = CreateElement("channel");
    
    AddElement(el, sub1);
    
    testAssertEquals(sub1, el->children, "sub1 must same to el->children\n");
    
    Element *sub2 = CreateElement("data");
    
    AddElement(el, sub2);
    
    Node *nn = FindNodeByName(el->children, NODE_TYPE_ELEMENT, "data");
    
    testAssertNotNull(nn, "data must found\n");
    
    testAssertStringEquals("data", nn->nodeName, "data item name must data");
    
    free(sub2);
    
    free(sub1);
    
    free(el);
    
}

void TestAttribute()
{
    Attribute *att = CreateAttribute("href", "http://www.google.com/");
    
    testAssertStringEquals("href", att->nodeName, "att name must is href\n");
    
    testAssertStringEquals("http://www.google.com/", att->nodeValue, "att value must is http://www.google.com/\n");
    
    Element *el = CreateElement("a");
    
    SetAttribute(el, att);
    
    testAssertNotNull(el->children, "attribute set is Error\n");
    
    Attribute *a1 = GetAttribute(el, "href");
    
    testAssertNotNull(a1, "Cant find attribute href\n");
    
    free(att);
    
    free(el);
    
}

void TestFind()
{
    
    NodeList nlist = CreateNode("rss");
    
    Node *cur = NULL;
    
    int i;
    
    for (i = 0; i < 10; i++) {
        cur = CreateNode("channel");
        addNode(nlist, cur);
    }
    
    NodeList result = FindNodesByName(nlist, NODE_TYPE_NODE, "channel");
    
    printf("Find nodes\n");
    
    testAssertNotNull(result, "find must not null\n");
    
    free(nlist);
    
}

void TestDom()
{
    TestNodeCreate();
    
    TestAttribute();
    
    TestFind();
}

int main(int argc, char *argv[]){
	printf("Hello for DOM4C Test\n");
    
    TestStack();
    
    TestDom();
    
    printf("Finished\n");
	
    return 0;
}


