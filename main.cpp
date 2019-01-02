#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct BiTNode{
    int data;
    struct BiTNode *lchild,*rchild;
}Node,*BTree;

typedef struct _Stack{
    Node *values[100];
    int top;
}Stack;

typedef struct _Queue{
    Node *values[100];
    int front,tail;
}Queue;

int BinTreeHigh1(BTree tree);
int BinTreeHigh2(BTree tree);
int BinTreeHigh3(BTree tree);

Node* createTree();

void initStack(Stack *stack);
void push(Stack *stack,Node *node);
Node* pop(Stack *stack);
Node* gettop(Stack *stack);
bool isEmpty(Stack *stack);

void initQueue(Queue *queue);
void push(Queue *queue,Node *node);
Node* pop(Queue *queue);
Node* getfront(Queue *queue);
int size(Queue *queue);
bool isEmpty(Queue *queue);

static int i=0;

int main()
{
    Node *head=createTree();
    printf("TreeHigh1=%d\n",BinTreeHigh1(head));
    printf("TreeHigh2=%d\n",BinTreeHigh2(head));
    printf("TreeHigh3=%d\n",BinTreeHigh3(head));
    return 0;
}

Node* createTree(){
    Node *p;
    if(i<15){
        p=(Node*)malloc(sizeof(Node));
        p->data=i++;
        p->lchild=createTree();
        p->rchild=createTree();
    }else{
        p=NULL;
    }
    return p;
}

int BinTreeHigh1(BTree tree){
    int li,ri;
    if(tree==NULL){
        return 0;
    }
    li=BinTreeHigh1(tree->lchild);
    ri=BinTreeHigh1(tree->rchild);
    return (li>ri?li:ri)+1;
}

int BinTreeHigh2(BTree tree){
    if(tree==NULL){
        return 0;
    }
    Node *p=tree,*r=NULL;
    int num=0,max=0;
    Stack *stack=(Stack*)malloc(sizeof(Stack));
    initStack(stack);
    while(p||!isEmpty(stack)){
        while(p){
            push(stack,p);
            num++;
            if(num>max){
                max=num;
            }
            p=p->lchild;
        }
        p=gettop(stack);
        if(p->rchild&&p->rchild!=r){
            p=p->rchild;
        }else{
            p=pop(stack);
            num--;
            r=p;
            p=NULL;
        }
    }
    return max;
}

int BinTreeHigh3(BTree tree){
    int depth=0,i,width;
    Node *p=tree;
    Queue *queue=(Queue*)malloc(sizeof(Queue));
    initQueue(queue);
    push(queue,p);
    while(!isEmpty(queue)){
        depth++;
        width=size(queue);
        for(i=0;i<width;i++){
            p=getfront(queue);
            pop(queue);
            if(p->lchild!=NULL)
                push(queue,p->lchild);
            if(p->rchild!=NULL)
                push(queue,p->rchild);
        }
    }
    return depth;
}

void initStack(Stack *stack){
    stack->top=0;
    memset(stack->values,NULL,100);
}

bool isEmpty(Stack *stack){
    if(stack->top<=0){
        return true;
    }else{
        return false;
    }
}

Node *gettop(Stack *stack){
    if(stack->top>0){
        return stack->values[stack->top-1];
    }else{
        return NULL;
    }
}

void push(Stack *stack, Node *node){
    if(stack->top<100){
        stack->values[stack->top++]=node;
    }
}

Node* pop(Stack *stack){
    if(stack->top>0){
        return stack->values[--stack->top];
    }else{
        return NULL;
    }
}

void initQueue(Queue *queue){
    queue->front=queue->tail=0;
    memset(queue->values,0,100);
}

void push(Queue *queue,Node *node){
    if(queue->tail<100){
        queue->values[queue->tail++]=node;
    }
}

Node* pop(Queue *queue){
    if((queue->tail-queue->front)>0){
        return queue->values[queue->front++];
    }else{
        return NULL;
    }
}

Node* getfront(Queue *queue){
    if((queue->tail-queue->front)>0){
        return queue->values[queue->front];
    }else{
        return queue->values[queue->front];
    }
}

int size(Queue *queue){
    return queue->tail-queue->front;
}

bool isEmpty(Queue *queue){
    if((queue->tail-queue->front)>0){
        return false;
    }else{
        return true;
    }
}
