////�ļ�����"GraphAdjMat_Test.cpp"
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
//    //��ʼ����������
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
//    //��ʼ���ߣ���������
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
////    �Ѿ�ѡ���ı�ǩ
//    set<string> havechoosed;
//
////    ����ѡ��ǩ
//    set<string> willchoosed;
//
//    set<string> temp;
//
//    //����1������ͼ
//    cout << endl << "����ͼ��ʼ����" << endl;
//    GraphAdjMat * udg = new GraphAdjMat(GraphAdjMat::UDG);
//    udg->Init(vexs, arcsList);
//    udg->Display();
////    ObjArrayList<string> * vexs2 = new ObjArrayList<string>();
////    vexs2->Add(v6);
//set<string> origin;
//origin.insert("s");
//    set label=udg->Findadj(origin);
//    vector<string> labelA(label.begin(), label.end()); // ʹ�õ���������vector����
////    ѡ��һ����ǩ
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<int32_t> distrib(0, label.size()-1);
//    std::cout << "choosed " << distrib(gen)<< std::endl;
//
//    string choosed=labelA[distrib(gen)];
//    havechoosed.insert(choosed);
////    ������ͼ
//    GraphAdjMat * mst=udg->InitMST(choosed,vexs);
//    mst->Display();
////    �жϸ���ͼ�Ƿ���ͨ ��s��ʼ����������������Ƿ񵽴�t�Ϳ�����
//    GraphAdjMat::solutionsfort flag=mst->Display_BFS("s");
//// if(!flag.havet){
////     ���û�ҵ������±߽綥�� ����s��
////     ��Ķ��㡾��ʵ����BFS�Ľ���� vertex��Ҫȥ�� �Ѿ�ѡ��ı�ǩ��Ӧ�ı� ��ʵ����ֱ����ѡ���в�ѡ�� ���Ҫ��ôʵ�֣�
//         temp=udg->Findadj(flag.vertexs);
//    for (auto it = havechoosed.begin(); it != havechoosed.end(); it++){
//        auto it2 = temp.find(*it);
//        if ( it2 == temp.end() ) {
//            // δ�ҵ�Ԫ��
//            cout<<"NOT FOUND"<< endl;
//        }
//        else {
//            // �ҵ�
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