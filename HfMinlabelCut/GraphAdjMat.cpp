//文件名："GraphAdjMat.cpp"
//#include "stdafx.h"
#include <set>
#include <string>
#include <vector>
#include "ObjArrayList.h"
#include "LinkQueue.h"
#include "GraphAdjMat.h"
using namespace std;

GraphAdjMat::GraphAdjMat(int type)
{
    /*
    .	构造函数：初始化图类型
    */
    this->type = type;
    this->vexNum = 0;
    this->arcNum = 0;
    if (this->type == DG || this->type == UDG)
    {
        //图的不相邻 int 值 0
        this->nonAdjInt = 0;
    }
    else
    {
        //网的不相邻 int 值 无穷大
        this->nonAdjInt = this->_INFINITY;
    }
}

//GraphAdjMat::~GraphAdjMat()
//{
//    /*
//    .	析构函数：销毁图
//    */
//    //1.释放顶点空位置索引队列
//    int * e;
//    while (vexs_null_index_queue->GetHead() != NULL)
//    {
//        e = vexs_null_index_queue->DeQueue();
//        delete e;
//    }
//    delete vexs_null_index_queue;
//
//}

void GraphAdjMat::Init(ObjArrayList<string> * vexs, ObjArrayList<ArcData> * arcsList)
{
    /*
    .	初始化顶点、边数据，并构建 图|网
    .	入参：
    .		vexs: 顶点 列表
    .		arcsList: 边数据 列表
    */
    //1.初始化顶点数据
    if (vexs->Length() > this->_MAX_VERTEX_NUM)
    {
        return;
    }
    for (int i = 0; i < vexs->Length(); i++)
    {
        this->vexs[i] = *vexs->Get(i);
    }
    this->vexNum = vexs->Length();
    //1.1.初始化顶点数组空顶点位置索引队列
    for (int i = vexs->Length(); i < _MAX_VERTEX_NUM; i++)
    {
        vexs_null_index_queue->EnQueue(new int(i));
    }
    //2.根据初始化的图类型，创建指定的图
    switch (this->type)
    {

        case UDG:
            _CreateUDG(arcsList); break;

        default:
            break;
    }
}



void GraphAdjMat::_CreateUDG(ObjArrayList<ArcData> * arcsList)
{
    /*
    .	创建无向图
    .	顶点相邻关系：0|不相邻 1|相邻
    .	邻接矩阵为 对称矩阵
    */
    //初始化临时 边对象
    ArcData * arcData = NULL;
    //初始化 矩阵二维坐标
    int m = 0, n = 0;
    //初始化边的邻接矩阵
    for (int i = 0; i < this->vexNum; i++)
    {
        for (int j = 0; j <this->vexNum; j++)
        {
            this->arcs[i][j].adj = 0;
            this->arcs[i][j].label = "";
        }
    }
    //遍历边数据列表
    for (int i = 0; i < arcsList->Length(); i++)
    {
        //按序获取边（弧）
        arcData = arcsList->Get(i);
        //定位（或设置）边的两端顶点位置
        m = _Locate(arcData->Tail);
        n = _Locate(arcData->Head);
        //设置顶点相邻 为 1 （有向）
        if (this->arcs[m][n].adj == 1 || this->arcs[n][m].adj == 1)
        {
            //去除重复边
            continue;
        }
        this->arcs[m][n].adj = 1;
        this->arcs[m][n].label = arcData->Label;
        this->arcs[n][m].adj = 1;
        this->arcs[n][m].label = arcData->Label;
        //边 计数
        this->arcNum++;
    }
}



int GraphAdjMat::_Locate(string vertex)
{
    /*
    .	定位顶点元素位置
    .		后期可改成【字典树】，顶点数超过100个后定位顶点位置可更快
    */
    //遍历定位顶点位置
//    cout<<"vertex"<<vertex<<endl;
    for (int i = 0; i < this->vexNum; i++)
    {
        if (vertex == this->vexs[i])
        {
            return i;
        }
    }
    cout << endl << "vertex " << vertex << " not exist" << endl;
    return -1;
}
int GraphAdjMat::_LocateVertexName(string vertex)
{
    /*
    .	定位顶点元素位置
    .		后期可改成【字典树】，顶点数超过100个后定位顶点位置可更快
    */
    //遍历定位顶点位置
    for (int i = 0; i < this->vexNum; i++)
    {
        if (vertex == this->vexs[i])
        {
            return i;
        }
    }
    cout << endl << "vertex " << vertex << " not exist" << endl;
    return -1;
}

void GraphAdjMat::Display()
{
    /*
    .	显示 图|网 （输出顶点数组、邻接矩阵）
    */
    //显示顶点数组
    //注：当删除某个中间序号顶点后，顶点数组就不是连续的
    cout << endl << "vertexs:" << endl;
    for (int i = 0, num = 0; i < this->vexNum && num < this->vexNum; i++)
    {
        if (this->vexs[i] != "")
        {
            cout << " (" << i << ")" << this->vexs[i];
            num++;
        }
    }
    //显示边（邻接矩阵）
    cout << endl << "graph:" << endl;
    cout << "    ";
    for (int i = 0; i < this->vexNum; i++)
    {
        cout << "[" << i << "]";
    }
    cout << endl;
    for (int i = 0; i < this->vexNum; i++)
    {
        cout << "[" << i << "] ";
        for (int j = 0; j < this->vexNum; j++)
        {
            if (this->arcs[i][j].adj == this->_INFINITY)
                cout << " + ";
            else
                cout << " " << this->arcs[i][j].adj << " ";
        }
        cout << endl;
    }
}

void GraphAdjMat::InsertVertex(string *vertex)
{
    /*
    .	插入一个新顶点
    */
    //1.判断顶点是否已存在
    if (_Locate(*vertex) > -1)
    {
        cout << endl << "该顶点已存在。" << endl;
        return;
    }
    //2.判断顶点数是否达到上限
    if (this->vexNum >= this->_MAX_VERTEX_NUM)
    {
        cout << endl << "顶点数已达上限。" << endl;
        return;
    }
    //3.插入新顶点，并自增顶点总数
    int * index = vexs_null_index_queue->DeQueue();	//从空位置索引队列中取
    this->vexs[*index] = *vertex;
    this->vexNum++;
    //4.新增的顶点在邻接矩阵中不需要作任何操作（已初始化）

}

void GraphAdjMat::DeleteVertex(string *vertex)
{
    /*
    .	删除一个顶点
    */
    //1.判断顶点是否已存在
    int index = _Locate(*vertex);
    if (index == -1)
    {
        cout << endl << "该顶点不存在。" << endl;
        return;
    }
    //2.删除该顶点，并自减顶点总数
    this->vexs[index] = "";
    this->vexNum--;
    //3.清除邻接矩阵 index 行列的数据，即将此行列 恢复初始化状态
    if (this->type == DG || this->type == UDG)
    {
        //图
        for (int i = 0; i < this->_MAX_VERTEX_NUM; i++)
        {
            this->arcs[i][index].adj = 0;
            this->arcs[index][i].adj = 0;
        }
    }
    else
    {
        //网
        for (int i = 0; i < this->_MAX_VERTEX_NUM; i++)
        {
            this->arcs[i][index].adj = this->_INFINITY;
            this->arcs[index][i].adj = this->_INFINITY;
        }
    }
}


void GraphAdjMat::InsertArc(ArcData *arc)
{
    /*
    .	插入一条新边（弧）
    .		若已存在，将对其更新
    */
    //1.定位顶点位置
    int i = _Locate(arc->Tail);
    int j = _Locate(arc->Head);
    //2.判断顶点是否存在
    if (i == -1 || j == -1)
    {
        cout << endl << "该边顶点不存在。" << endl;
        return;
    }
    //3.插入/更新一条边
  if (this->type == UDG)
    {
        //无向无权图
        this->arcs[i][j].adj = 1;
        this->arcs[j][i].adj = 1;
    }

}

void GraphAdjMat::DeleteArc(ArcData *arc)
{
    /*
    .	删除一条边（弧）
    */
    //1.定位顶点位置
    int i = _Locate(arc->Tail);
    int j = _Locate(arc->Head);
    //2.判断顶点是否存在
    if (i == -1 || j == -1)
    {
        cout << endl << "该边顶点不存在。" << endl;
        return;
    }
    //3.删除一条边，即 恢复初始化状态
if (this->type == UDG)
    {
        //无向无权图
        this->arcs[i][j].adj = 0;
        this->arcs[j][i].adj = 0;
    }

}

void GraphAdjMat::Display_DFS(string *vertex)
{
    /*
    .	深度优先遍历显示，从指定顶点开始
    */
    //1.判断顶点是否存在
    int index = _Locate(*vertex);
    if (index == -1)
        return;
    //2.初始化顶点访问数组
    for (int i = 0; i < this->_MAX_VERTEX_NUM; i++)
    {
        this->vexs_visited[i] = 0;
    }
    //3.深度优先遍历 递归
    cout << "深度优先遍历：（从顶点" << *vertex << "开始）" << endl;
    _DFS_R(index);
}

void GraphAdjMat::_DFS_R(int index)
{
    /*
    .	深度优先遍历 递归
    .		有向/无向算法是一样的
    .		有向图|网，以当前顶点的出度方向遍历
    .		无向图|网，以当前顶点的相邻结点方向遍历（可理解为“出度”，但不是出度）
    */
    //1.访问顶点，并标记已访问
    cout << this->vexs[index] << " ";
    this->vexs_visited[index] = 1;
    //2.访问其相邻顶点
    for (int i = 0; i < this->_MAX_VERTEX_NUM; i++)
    {
        //当边值 不是 不相邻int值（0|无权  无穷|有权），且未被访问过时，可访问
        if (this->arcs[index][i].adj != this->nonAdjInt && this->vexs_visited[i] != 1)
        {
            _DFS_R(i);
        }
    }
}

GraphAdjMat::solutionsfort GraphAdjMat::Display_BFS(string vertex)
{
    /*
    .	广度优先遍历显示，从指定顶点开始
    .		类似于树的层次遍历算法
    */
    solutionsfort flag;
    set<string> vertexs;
    //1.判断顶点是否存在
    int index = _Locate(vertex);
    if (index == -1)
        return flag;
    //2.初始化顶点访问数组
    for (int i = 0; i < this->_MAX_VERTEX_NUM; i++)
    {
        this->vexs_visited[i] = 0;
    }
    //3.广度优先遍历
//    cout << "BFS 开始于  " << vertex << endl;

    //3.1.初始化队列
    LinkQueue<int> * vexQ = new LinkQueue<int>();
    //3.2.访问开始顶点，并标记访问、入队
//    cout <<"BFS访问到顶点："<< this->vexs[index] <<" ";
    this->vexs_visited[index] = 1;
    int count=1;
    vertexs.insert("s");
    vexQ->EnQueue(new int(index));
    //3.3.出队，并遍历邻接顶点（下一层次），访问后入队
    while (vexQ->GetHead() != NULL)
    {
        index = *vexQ->DeQueue();
        for (int j = 0; j < this->vexNum; j++)
        {
            //未访问过的邻接顶点
            if (this->arcs[index][j].adj != this->nonAdjInt && this->vexs_visited[j] != 1)
            {
                //访问顶点，并标记访问、入队
//               cout<<"index "<<index;
//               cout <<"FANG  " <<this->vexs[j]<<endl;
                vertexs.insert(this->vexs[j]);
                count++;
                this->vexs_visited[j] = 1;
                vexQ->EnQueue(new int(j));
            }
        }

    }
//    cout<<" "<<endl;
    //4.释放队列
    int * e;
    while (vexQ->GetHead() != NULL)
    {
        e = vexQ->DeQueue();
        delete e;
    }
    delete vexQ;

    auto it = vertexs.find("t");

    if ( it == vertexs.end() ) {
        // 未找到元素
//        cout<<"BFS 没找到 t"<< endl;
//         cout<<" "<<endl;
        flag.havet= false;
        flag.vertexs=vertexs;
//        flag.vertexs=vertexs;
//cout<<"flag.flag.vertexs=vertexs;"<<vertexs.size()<<endl;
//        cout<<"flag.flag.vertexs=vertexs;"<<count<<endl;
vector<string> hh;
//cout<<vertexs.size();
//for(auto it:vertexs){
////            cout<<"it"<<it<<endl;
//            if(it.empty()){
//cout<<"kong"<<endl;
//            }
////        }
//        for (int i = 0; i < hh.size(); i++) {
//            vertexs.erase(hh[i]);
//        }
//cout<<"havet"<<endl;
//cout<<flag.havet<<endl;
        return flag;
    }
    else {
        // 找到
//        cout << "BFS 连通且到 " << *it<< endl;
//        cout<<" "<<endl;
        flag.havet= true;
        return flag;
    }

}
vector<int> GraphAdjMat::BFS(string vertex)
{
    vector<int> finalpath;
    int d[this->vexNum];
    int path[this->vexNum];
//    初始化path
    for (int i = 0; i < this->vexNum; ++i) {
        path[i]=-1;

    }
    for(int i = 0; i < this->vexNum; i++)
    {
        d[i] = 10000000;  //初始化路径长度
        path[i] = -1; //最短路径从哪个顶点过来
    }
    set<string> vertexs;
    //1.判断顶点是否存在
    int index = _Locate(vertex);
    d[index]=0;
    if (index == -1)
        return finalpath;
    //2.初始化顶点访问数组
    for (int i = 0; i < this->vexNum; i++)
    {
        this->vexs_visited[i] = 0;
    }
    //3.广度优先遍历
//    cout << "BFS 开始于  " << vertex << endl;

    //3.1.初始化队列
    LinkQueue<int> * vexQ = new LinkQueue<int>();
    //3.2.访问开始顶点，并标记访问、入队
//    cout <<"BFS访问到顶点："<< this->vexs[index] <<" ";

    this->vexs_visited[index] = 1;
    vexQ->EnQueue(new int(index));
    //3.3.出队，并遍历邻接顶点（下一层次），访问后入队
    while (vexQ->GetHead() != NULL)
    {
//        cout<<index<<endl;
        index = *vexQ->DeQueue();
        for (int j = 0; j < _MAX_VERTEX_NUM; j++)
        {
            //未访问过的邻接顶点
            if (this->arcs[index][j].adj != this->nonAdjInt && this->vexs_visited[j] != 1)
            {
                d[j]=d[index]+1;
                path[j]=index;
                //访问顶点，并标记访问、入队
//                cout <<"  " <<this->vexs[j];
                vertexs.insert(this->vexs[j]);
                this->vexs_visited[j] = 1;
                vexQ->EnQueue(new int(j));
            }
        }


    }
//    cout<<" "<<endl;
    //4.释放队列
    int * e;
    while (vexQ->GetHead() != NULL)
    {
        e = vexQ->DeQueue();
        delete e;
    }
    delete vexQ;

    int t= _Locate("t");
//    cout<<t<<endl;
    int s= _Locate("s");
    int temp=path[t];
    if(temp==-1){
//        cout<<"找不到从s到t的路线了"<<endl;
        return finalpath;
    }
    finalpath.insert(finalpath.begin(),t);
    finalpath.insert(finalpath.begin(),temp);
    while (temp!=s){
        temp=path[temp];
        finalpath.insert(finalpath.begin(),temp);
    }

//    for (int i = 0; i < finalpath.size(); ++i) {
//        cout<<finalpath[i]<<" ";
//
//    }
//    cout<<" "<<endl;
    return finalpath;

}

set<string> GraphAdjMat::Findadj(set<string> vexs1){
int length=vexs1.size();
//构造集合存储label
    set<string> s;
    for (auto i : vexs1)
    {
        int index= _Locate(i);
        for(int j=0; j<this->vexNum; j++){
            if(this->arcs[index][j].adj != this->nonAdjInt){
                ArcCell l=this->arcs[index][j];
//               cout << l.label;
                s.insert(l.label);
            }
        }
    }


//    cout << "与现在的分支邻接的标签有: ";
//    for (auto it = s.begin(); it != s.end(); it++)
//        cout << *it << " ";
//    cout <<endl;
    return s;
}
bool IsConnected(string *vertex){
    return true;
}

GraphAdjMat * GraphAdjMat::InitMST(set<string>  label,ObjArrayList<string> * vexs){
    GraphAdjMat * mst = new GraphAdjMat(GraphAdjMat::UDG);
    mst->Init(vexs, new ObjArrayList<ArcData>());
//    遍历这个的Arccell 有这个标签的
//    cout <<"用以下这些标签初始化树： ";
    for (auto it = label.begin(); it != label.end(); it++){
//        cout <<*it << " ";

    for(int i=0; i<this->vexNum; i++){
        for( int j=0; j<this->vexNum;j++){
        if(this->arcs[i][j].adj != this->nonAdjInt&&this->arcs[i][j].label==*it){
            mst->arcs[i][j].adj=1;
            mst->arcs[i][j].label=*it;
        }}
}}
//    cout<<endl;
return mst;
}