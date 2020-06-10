#include "rpn-stack.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct _rpn_stack
{
    void * data;
    struct _rpn_stack* next;
}rpn_stack_t;

rpn_stack_t* rpn_stack_new(){
    rpn_stack_t *stack;
    stack = (rpn_stack_t*)malloc(sizeof(rpn_stack_t));
    assert(stack);
    stack->data = NULL;
    stack->next = NULL;
    return stack;
}

void rpn_stack_push(rpn_stack_t *stack, void* data){
    rpn_stack_t *new_node;
    new_node = (rpn_stack_t*)malloc(sizeof(rpn_stack_t));
    new_node->data;
    new_node->next = stack;
    stack = new_node;
}

void* rpn_stack_pop(rpn_stack_t* stack){
    rpn_stack_t *temp;
    if (stack->data == NULL){
        return NULL; 
    }
    void *ret;
    temp = stack;
    stack = stack->next;
    temp->next = NULL;
    ret = temp->data;
    free(temp);
    return ret;
}

int rpn_stack_empty(rpn_stack_t* stack) {
    return stack == NULL;
}

void* rpn_stack_peek(rpn_stack_t *stack) {
    if(rpn_stack_empty(stack)){
        return NULL;
    } else {
        return stack->data;
    }
}

void rpn_stack_del(rpn_stack_t *stack) {
    while(!rpn_stack_empty(stack)){
        rpn_stack_pop(stack);
    }
}