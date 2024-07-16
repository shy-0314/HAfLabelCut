////文件名："GraphAdjMat_Test.cpp"
////#include "stdafx.h"
//#include <iostream>
//#include <random>
//#include <vector>
//#include <algorithm>
//#include "GraphAdjMat.h"
//#include "ObjArrayList.h"
//#include "tools.h"
//using namespace std;
//
//void print(string val)
//{
//    cout << val << " ";
//}
//
//int main()
//{
//    //初始化顶点数据
//    string * v1 = new string("v1");
//    string * v2 = new string("v2");
//    string * v3 = new string("v3");
//    string * v6 = new string("s");
//    string * v7 = new string("t");
//    ObjArrayList<string> * vexs = new ObjArrayList<string>();
//    vexs->Add(v1);
//    vexs->Add(v2);
//    vexs->Add(v3);
//    vexs->Add(v6);
//    vexs->Add(v7);
//
//    //初始化边（弧）数据
//    GraphAdjMat::ArcData * arc1 = new GraphAdjMat::ArcData{ "v1", "v2", "b" };
//    GraphAdjMat::ArcData * arc2 = new GraphAdjMat::ArcData{ "v2", "t", "c" };
//    GraphAdjMat::ArcData * arc3 = new GraphAdjMat::ArcData{ "v1", "v3", "b"};
//    GraphAdjMat::ArcData * arc4 = new GraphAdjMat::ArcData{ "s", "v1", "a"};
//    GraphAdjMat::ArcData * arc5 = new GraphAdjMat::ArcData{ "s", "v3", "c" };
//    GraphAdjMat::ArcData * arc7 = new GraphAdjMat::ArcData{ "v3", "t", "a" };
//    ObjArrayList<GraphAdjMat::ArcData> * arcsList = new ObjArrayList<GraphAdjMat::ArcData>();
//    arcsList->Add(arc1);
//    arcsList->Add(arc2);
//    arcsList->Add(arc3);
//    arcsList->Add(arc4);
//    arcsList->Add(arc5);
//    arcsList->Add(arc7);
//
////    已经选过的标签
//    set<string> havechoosed;
//
////    从中选标签
//    set<string> willchoosed;
//
//    set<string> temp;
//
//    //测试1：无向图
//    cout << endl << "无向图初始化：" << endl;
//    GraphAdjMat * udg = new GraphAdjMat(GraphAdjMat::UDG);
//    udg->Init(vexs, arcsList);
//    udg->Display();
////    ObjArrayList<string> * vexs2 = new ObjArrayList<string>();
////    vexs2->Add(v6);
//set<string> origin;
//origin.insert("s");
//    set label=udg->Findadj(origin);
//    vector<string> labelA(label.begin(), label.end()); // 使用迭代器构造vector数组
////    选择一个标签
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<int32_t> distrib(0, label.size()-1);
//    std::cout << "choosed " << distrib(gen)<< std::endl;
//
//    string choosed=labelA[distrib(gen)];
//    havechoosed.insert(choosed);
////    构造子图
//    GraphAdjMat * mst=udg->InitMST(choosed,vexs);
//    mst->Display();
////    判断该子图是否连通 从s开始做广度优先搜索看是否到达t就可以了
//    GraphAdjMat::solutionsfort flag=mst->Display_BFS("s");
//// if(!flag.havet){
////     如果没找到，更新边界顶点 就是s可
////     达的顶点【其实就是BFS的结果】 vertex需要去掉 已经选择的标签对应的边 其实可以直接在选择中不选他 这块要怎么实现？
//         temp=udg->Findadj(flag.vertexs);
//    for (auto it = havechoosed.begin(); it != havechoosed.end(); it++){
//        auto it2 = temp.find(*it);
//        if ( it2 == temp.end() ) {
//            // 未找到元素
//            cout<<"NOT FOUND"<< endl;
//        }
//        else {
//            // 找到
//            cout << "point to  " << *it<< endl;
//            temp.erase(*it);
//        }
//    }
//    for (auto it = temp.begin(); it != temp.end(); it++)
//        cout <<"intemP:"<< *it << " ";
//
//
//
//
//
//
//
//
//
//
//    return 0;
//}