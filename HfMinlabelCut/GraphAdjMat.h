//
// Created by DELL on 2024/1/16.
//

#ifndef INC_12_6_GRAPHADJMAT_H
#define INC_12_6_GRAPHADJMAT_H
//文件名："GraphAdjMat.h"
#pragma once

#include <limits>
#include <string>
#include <set>
#include "ObjArrayList.h"
#include "LinkQueue.h"
#include <vector>
using namespace std;

/*
.	图（邻接矩阵实现） Graph Adjacency Matrix
.	相关术语：
.		顶点 Vertex ； 边 Arc ；权 Weight ；
.		有向图 Digraph ；无向图 Undigraph ；
.		有向网 Directed Network ；无向网 Undirected Network ；
*/

class GraphAdjMat
{
    /*
    .	边（弧） 单元，注：邻接矩阵单元
    */
    struct ArcCell
    {
        int adj;		//邻接顶点关系。图：0|不相邻 1|相邻 ；网：无穷（INT_MAX）|不相邻  权值（W）|相邻
        string label;	//边（弧）信息
    };

public:
    /*
    .	图 种类
    */
    enum GraphType
    {
        DG,			//有向图，默认 0
        UDG,		//无向图，默认 1
        DN,			//有向网，默认 2
        UDN			//无向网，默认 3
    };
    /*
    .	边（弧）数据，注：供外部初始化边数据使用
    */
    struct  ArcData
    {
        string Tail;	//弧尾
        string Head;	//弧头
        string Label;		//权重 这里可以换成label
    };
    struct solutionsfort
    {
        bool havet;
        set<string> vertexs ;
    };
//private:
    const int _INFINITY = INT_MAX;				//无穷大  注：包含于头文件 <limits>
    static const int _MAX_VERTEX_NUM = 60;		//支持最大顶点数

    //静态存储结构
    string vexs[_MAX_VERTEX_NUM];						//顶点表
    ArcCell arcs[_MAX_VERTEX_NUM][_MAX_VERTEX_NUM];		//边（弧）矩阵
    int vexNum;			//顶点数
    int arcNum;			//边数
    int type;			//图种类
    int nonAdjInt;		//不相邻 int 值：0|无权 无穷|有权

    LinkQueue<int> *vexs_null_index_queue = new LinkQueue<int>();		//顶点数组中空顶点位置索引队列 （需要销毁）
    bool vexs_visited[_MAX_VERTEX_NUM];			//顶点访问标记数组：0|未访问 1|已访问

    void _CreateDG(ObjArrayList<ArcData> * arcsList);			//创建有向图
    void _CreateUDG(ObjArrayList<ArcData> * arcsList);			//创建无向图
    void _CreateDN(ObjArrayList<ArcData> * arcsList);			//创建有向网
    void _CreateUDN(ObjArrayList<ArcData> * arcsList);			//创建无向网

    int _Locate(string vertex);					//定位顶点元素位置
    int _LocateVertexName(string vertex);

    void _DFS_R(int index);						//深度优先遍历 递归

public:
    GraphAdjMat(int type);						//构造函数：初始化图类型
//    ~GraphAdjMat();								//析构函数：销毁图存储空间
    void Init(ObjArrayList<string> * vexs, ObjArrayList<ArcData> * arcsList);		//初始化顶点、边数据为 图|网
    void Display();								//显示 图|网
    void InsertVertex(string *vertex);			//插入一个新顶点
    void DeleteVertex(string *vertex);			//删除一个顶点
    void InsertArc(ArcData *arc);				//插入一条新边（弧）
    void DeleteArc(ArcData *arc);				//删除一条边（弧）
    void Display_DFS(string *vertex);			//从指定顶点开始，深度优先遍历
   solutionsfort Display_BFS(string vertex);			//从指定顶点开始，广度优先遍历
    set<string> Findadj(set<string> vertex);  //输出指定顶点列表的邻接边


    GraphAdjMat * InitMST(set<string> label,ObjArrayList<string> * vexs);		//初始化，先把所有顶点加进去，再根据label把第一次所得的边加进去
    GraphAdjMat * MiniSpanTree_Kruskal(string * vertex);	//最小生成树（Kruskal 算法）
    bool IsConnected(string *vertex); //判断是否包含t且联通 从s开始 s是v几
//    GraphAdjMat *InitMST(string *label, ObjArrayList<string> *vexs);
//  返回最短路长度
    vector<int> BFS(string vertex);
};


#endif //INC_12_6_GRAPHADJMAT_H
