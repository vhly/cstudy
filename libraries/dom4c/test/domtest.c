#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "dom4c.h"

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
    
}
void TestStackPeek()
{
    
}

void TestStack()
{
    TestStackPush();
    
    TestStackPop();
    
    TestStackPeek();
}

int main(int argc, char *argv[]){
	printf("Hello for DOM4C Test\n");
    
    TestStack();
    
    
	return 0;
}


