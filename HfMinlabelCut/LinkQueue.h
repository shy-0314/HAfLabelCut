//文件名："LinkQueue.h"
#pragma once
#ifndef LINKQUEUE_H_
#define LINKQUEUE_H_

/*
	链队列 类模板定义	LinkQueue (Linked Queue)
		注：采用链尾插入法时，需添加一个头结点，以使后续入队元素操作一致
*/

template <typename ElemType>
class LinkQueue
{
    /*
        链队列
    */
    struct Node
    {
        ElemType *data;
        Node *next;
    };
private:
    Node * front;	//队头指针
    Node * rear;	//队尾指针
public:
    LinkQueue();	//无参构造
    ~LinkQueue();	//析构函数：销毁链队
    void EnQueue(ElemType *e);	//入队
    ElemType *DeQueue();	//出队
    ElemType *GetHead();	//获取队头元素
    ElemType *GetLast();	//获取队尾元素
    //void Display();	//显示队列元素
};

template <typename ElemType>
LinkQueue<ElemType>::LinkQueue()
{
    /*
        无参构造
    */
    //1.建立头结点
    Node *p = new Node;
    p->next = NULL;
    //2.队头队尾指针指向头结点
    this->rear = p;
    this->front = this->rear;
}

template <typename ElemType>
LinkQueue<ElemType>::~LinkQueue()
{
    /*
        析构函数：销毁队列
            注：采用链头删除法
    */
    Node *p;
    //从front 头结点遍历到链尾
    int i = 0;
    while (this->front != NULL)	//条件：尾结点 next == NULL
    {
        p = this->front;
        this->front = this->front->next;
        delete p;
        i++;
    }
//    cout << "DESTORY " << i - 1 << " ITEMS" << endl;	//计数时，去除头结点
}

template <typename ElemType>
void LinkQueue<ElemType>::EnQueue(ElemType *e)
{
    /*
        入队
    */
    //1.建立入队结点
    Node *p = new Node;
    p->data = e;
    p->next = NULL;
    this->rear->next = p;
    //2.队尾指针后移至入队结点
    this->rear = p;
}

template <typename ElemType>
ElemType *LinkQueue<ElemType>::DeQueue()
{
    /*
        出队
    */
    //1.空队列判断
    if (this->front == this->rear)
    {
        cout << "EMPTY CAN'T DEQUEUE" << endl;
        return NULL;
    }
    //2.非空队时，取队头元素结点
    Node *p = this->front->next;
    ElemType *e = p->data;
    //3.移除队头元素结点
    this->front->next = p->next;
    delete p;
    //4.若头结点 next 域为空，即无元素结点，此时将 rear = front
    if (this->front->next == NULL)
    {
        this->rear = this->front;
    }
    return e;
}

template <typename ElemType>
ElemType *LinkQueue<ElemType>::GetHead()
{
    /*
        取队头
    */
    //1.空队列判断
    if (this->front == this->rear)
    {
//        cout << "EMPTY NO HEAD" << endl;
        return NULL;
    }
    //2.非空队时，取队头元素结点
    return this->front->next->data;
}

template <typename ElemType>
ElemType *LinkQueue<ElemType>::GetLast()
{
    /*
        取队尾
    */
    //1.空队列判断
    if (this->front == this->rear)
    {
//        cout << "EMPTY NO TAIL" << endl;
        return NULL;
    }
    //2.非空队时，取队尾元素结点
    return this->rear->data;
}

#endif // !LINKQUEUE_H_