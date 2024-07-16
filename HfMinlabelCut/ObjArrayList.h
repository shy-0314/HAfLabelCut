//文件名："ObjArrayList.h"
#pragma once
#ifndef ObjArrayList_H_
#define ObjArrayList_H_
#include <iostream>
using namespace std;

/*
.	对象顺序列表类 模板实现
*/
template <typename ElemType>
class ObjArrayList
{
private:
    ElemType **arr;	//指针的指针，一维列表指针
    int length;	//列表长度
    int size;	//列表大小
    const int DEFAULT_LENGTH = 10;	//默认长度
    const int INCREMENT_STEP = 10;	//增长步长
    void _AllocSpace(int size = 0, int type = 0);	//分配内存空间	0|malloc  1|realloc
    bool _IsFull();	//判断列表是否满
public:
    ObjArrayList();	//无参构造
    ObjArrayList(int m);	//有参构造
    ~ObjArrayList();	//析构函数
    int Length();	//获取列表长度
    int Size();	//获取列表大小
    void Add(ElemType *e);	//顺序增加一个元素
    void Add(int i, ElemType *e);	//指定位置增加一个元素
    ElemType *Get(int i);	//获取指定位置元素
    friend ostream & operator << (ostream &out, ObjArrayList<ElemType> *list)
    {
        /*
        .	友元函数：重载输出操作符
        */
        cout << "The List is : ";
        for (int i = 0; i < list->Length(); i++)
        {
            cout << i << "_";
            if (list->Get(i) != NULL)
                cout << list->Get(i);
            else
                cout << "(NULL) ";
            if (i != list->Length() - 1)
                cout << ",";
            if (i % 10 == 9)
                cout << endl;
        }
        return out;
    }
};

template <typename ElemType>
ObjArrayList<ElemType>::ObjArrayList()
{
    /*
    .	无参构造
    */
    _AllocSpace(this->DEFAULT_LENGTH, 0);	//申请指针列表表空间：默认大小
    this->length = 0;
    this->size = this->DEFAULT_LENGTH;
}

template <typename ElemType>
ObjArrayList<ElemType>::ObjArrayList(int m)
{
    /*
    .	有参构造
    */
    _AllocSpace(m, 0);	//申请指针列表表空间：m 大小
    this->length = 0;
    this->size = m;
}

template <typename ElemType>
ObjArrayList<ElemType>::~ObjArrayList()
{
    /*
    .	析构函数：销毁对象列表（同时销毁元素内存）
    */
    if (this->arr == NULL)
    {
        return;
    }
    for (int i = 0; i < this->size; i++)
    {
        delete *(this->arr + i);
    }
    delete[] this->arr;
}

template <typename ElemType>
void ObjArrayList<ElemType>::_AllocSpace(int size, int type)
{
    /*
    .	分配内存空间
    .	参数：
    .	int size: 列表大小（元素个数）
    .	int type: 0|malloc  1|realloc
    */
    //新分配的内存起始地址索引
    int start = 0;
    //临时对象数组指针
    ElemType** p = NULL;
    //1.首次分配内存
    if (type == 0)
    {
        //this->arr = (ElemType **)malloc(size * sizeof(ElemType *));
        this->arr = new ElemType*[size];	//参考指针数组，保持 new 与 delete 配对
    }
        //2.重新分配内存
    else if (type == 1)
    {
        //this->arr = (ElemType **)realloc(this->arr, size * sizeof(ElemType *));
        //将原对象数组元素赋值到新数组中，并删除原数组
        p = this->arr;
        this->arr = new ElemType*[size];
        //1.迁移。注此时 this->size 还是原来的大小
        for (int i = 0; i < this->size; i++) {
            this->arr[i] = p[i];
        }
        //2.销毁原数组
        delete[] p;
        //空位起始地址
        start = this->length;
    }
    //3.初始化新分配内存元素为 NULL
    for (int i = start;	i < size; i++)
    {
        *(this->arr + i) = NULL;
    }
}

template <typename ElemType>
int ObjArrayList<ElemType>::Length()
{
    /*
    .	获取列表长度
    */
    return this->length;
}

template <typename ElemType>
int ObjArrayList<ElemType>::Size()
{
    /*
    .	获取列表大小
    */
    return this->size;
}

template <typename ElemType>
void ObjArrayList<ElemType>::Add(ElemType *e)
{
    /*
    .	顺序增加一个元素
    */
    //重新分配空间大小
    int resize = 0;
    if (_IsFull())
    {
        //顺序增加一个默认步长大小的内存空间
        resize = this->size + this->INCREMENT_STEP;
        _AllocSpace(resize, 1);
        this->size = resize;
    }
    *(this->arr + this->length) = e;
    this->length++;
}

template <typename ElemType>
void ObjArrayList<ElemType>::Add(int i, ElemType *e)
{
    /*
    .	指定位置增加一个元素
    */
    //重新分配空间大小
    int resize = 0;
    ElemType *p = NULL;
    //1.位置 i 在已有列表长度内
    if (i <= this->length - 1)
    {
        //若 i 位置已有元素，先销毁原数据内存，再添加新元素
        p = *(this->arr + i);
        if (p != NULL)
            delete p;
        *(this->arr + i) = e;
    }
        //2.位置 i 在已有列表长度外，但还在列表大小范围内
    else if (i <= this->size - 1)
    {
        *(this->arr + i) = e;
        this->length = i + 1;
    }
        //3.位置 i 在超出列表大小，需重新分配内存
    else
    {
        //按 内存增长步长的整数倍， 增加一段新内存
        resize = ((i + 1) / this->INCREMENT_STEP + 1) * this->INCREMENT_STEP;
        _AllocSpace(resize, 1);
        this->size = resize;
        *(this->arr + i) = e;
        this->length = i + 1;
    }

}

template <typename ElemType>
ElemType *ObjArrayList<ElemType>::Get(int i)
{
    /*
    .	获取指定位置元素
    */
    return *(this->arr + i);
}

template <typename ElemType>
bool ObjArrayList<ElemType>::_IsFull()
{
    /*
    .	判断列表是否满
    */
    return this->length == this->size ? true : false;
}

#endif // !ObjArrayList_H_