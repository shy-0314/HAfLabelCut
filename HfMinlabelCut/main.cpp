#include <iostream>
#include <map>
#include <random>
#include <vector>
#include <algorithm>
#include "GraphAdjMat.h"
#include "ObjArrayList.h"
#include<fstream>
#include<string>
#include <cstring>
struct edge{
    int a, b;
    string w;
    edge() = default;
    edge(int _a, int _b, string _w) {
        a = _a;
        b = _b;
        w =_w;
    }
};
struct ans{
    int a, b,temp,count;

    ans() = default;
    ans(int _a, int _b, int _temp, int _count) {
        a = _a;
        b = _b;
        count =_count;
        temp= _temp;

    }
};
vector<ans> Overall;
string storepath="D:\\DOWNLOAD FROM EDGE\\FILE\\AARTICLE\\DATASTORE\\SPG\\final\\";
string logs_dir_path="D:\\DOWNLOAD FROM EDGE\\FILE\\AARTICLE\\DATASTORE\\SPG\\500\\50_59";
bool cmp(pair<string,int> a, pair<string,int> b) {
    return a.second > b.second;
}
std::vector<std::string> stringSplit(const std::string& str, char delim) {
    std::size_t previous = 0;
    std::size_t current = str.find(delim);
    std::vector<std::string> elems;
    while (current != std::string::npos) {
        if (current > previous) {
            elems.push_back(str.substr(previous, current - previous));
        }
        previous = current + 1;
        current = str.find(delim, previous);
    }
    if (previous != str.size()) {
        elems.push_back(str.substr(previous));
    }
    return elems;
}
int countF=0;
set<string> QRongYu(set<string> originlabel,GraphAdjMat g){
    cout<<"=========去冗余==============" <<endl;
    bool flag=0;
//记录对应边的
//    vector<vector<string>> vec;
    set<string> temp=originlabel;
//    map<string, vector<int>> mapVec;
//    做一个全去掉的图 此时不连通
    vector<edge> edges;
    for(auto it:temp){
        for (int i = 0; i < g.vexNum; i++) {
            for (int j = 0; j < g.vexNum; j++) {
                if (g.arcs[i][j].adj != g.nonAdjInt && g.arcs[i][j].label == it) {
                    g.arcs[i][j].adj = 0;
                    edges.emplace_back(i,j,it);
                }
            }
        }
    }

//需要做一个记录每个标签对应边的


        for(auto it:temp){
            cout<<it<<endl;
            for (int i = 0; i < edges.size(); i++) {
                    if (edges[i].w == it) {
                        int from=edges[i].a;
                        int to=edges[i].b;
                        g.arcs[from][to].adj = 1;
                        g.arcs[to][from].adj = 1;
                    }

            }
            flag=g.Display_BFS("s").havet;
//            若联通 则下一个 若不连通 则将这个标签去掉
        if(!flag){
//            flag此时是0 如果4个都是1则没必要继续
            originlabel.erase(it);
//            temp=originlabel;
            cout<<"no连通"<<endl;

        }else{
           cout<<"连通"<<endl;
//           则不将这个标签去掉，并把之前加上的边拿下来
            for (int i = 0; i < edges.size(); i++) {
                if (edges[i].w == it) {
                    int from=edges[i].a;
                    int to=edges[i].b;
                    g.arcs[from][to].adj = 0;
                    g.arcs[to][from].adj = 0;
                }

            }
        }
        }


    cout<<"所以最后存在的标签有：";
    for (auto i:originlabel) {
        cout<<i<<" ";

    }
    cout<<endl;
    return originlabel;
}
int randInt(int a, int b) {
    return rand() % (b - a + 1) + a;//NOLINT
}
set<string> Ford_Fulkersen(GraphAdjMat udg3,GraphAdjMat udg4){
//使用BFS获得路径
    vector<int> path=udg3.BFS("s");
//    udg3.Display();
    while(path.size()!=0){
    for (int i = 1; i < path.size(); ++i) {
//        cout<<path[i]<<endl;
//        添加反向边
        int from=path[i-1];
        int to=path[i];
//        正方向加1，反方向减1
        udg3.arcs[from][to].adj=udg3.arcs[from][to].adj-1;
        udg3.arcs[to][from].adj=udg3.arcs[to][from].adj+1;
    }
//    udg3.Display();
//再次寻找直到找不到
    path=udg3.BFS("s");}
//    在此时的增广路上找s可达的顶点
    GraphAdjMat::solutionsfort flag=udg3.Display_BFS("s");
    set<string> vertexs=flag.vertexs;
//    cout<<"此时s可达的顶点有：";
//    for (auto i : vertexs){
//        cout<<i<<" ";
//    }
//        cout<<endl;
//    cout<<vertexs.size()<<endl;
    set<string> label= udg4.Findadj(vertexs);

//        cout<<label.size()<<endl;

    return  label;
}
//从txt文件读成vector<vector> int
vector<vector<string>> read(string filename){
    vector<vector<string>> vec;
    vec.clear();
    ifstream infile;
    infile.open(filename, ios::in);
    if (!infile.is_open())
    {
        cout << "读取文件失败" << endl;
        return vec ;
    }
    //第五种读取方法
    string s;
    vector<string>v1;
    while (getline(infile,s))
    {


        v1.push_back(s);

    }
    for (int i = 0; i < v1.size(); i++)
    { vector<int> tmp;

        vector<string> temp= stringSplit(v1[i], 32);
//        for( int i=0;i< temp.size();i++){
//            int x=atoi(temp[i].c_str());
//            tmp.push_back(x);
//        }
        vec.push_back(temp);
        temp.clear();
    }
    infile.close();
    string start=vec[0][1];
    string t=vec[0][2];

    for (int i=1;i<vec.size();i++){
//        cout<<i<<endl;
        for (int j=0;j<vec[i].size()-1;j++){
            if (vec[i][j]==start){
                vec[i][j]="s";
            }else if (vec[i][j]==t){
                vec[i][j]="t";
            }
//            cout<<vec[i][j]<<" ";
        }
//        cout<<endl;
    }
    return vec;
}
set<string> chaji(set<string> temp,set<string> havechoosed){
//计算
vector<string> hh;
    for (auto it = havechoosed.begin(); it != havechoosed.end(); it++){
        auto it2 = temp.find(*it);
        if ( it2 == temp.end() ) {
            // 未找到元素
            cout<<"NOT FOUND"<< endl;
        }
        else {
            // 找到
//            cout << "找到了元素： " << *it<< endl;
//            temp.erase(*it);
hh.push_back(*it);

        }
    }
    for (int i = 0; i < hh.size(); i++) {
        temp.erase(hh[i]);
    }
//    cout<<"temp:"<<endl;
//    for(auto i:temp){
//        cout<<i;
//    }
    return temp;
}
set<string> final(vector< pair<string,int> > vec2,GraphAdjMat udg3){
//    按分数依次试标签看是否断开
    GraphAdjMat::solutionsfort flag;
    set<string> over;
    for(int ii=0;ii<vec2.size();ii++){
//        cout<<"第"<<ii+1<<"次选中的标签是："<<vec2[ii].first<<endl;
        for(int i=0; i<udg3.vexNum; i++){
            for( int j=0; j<udg3.vexNum;j++){
                if(udg3.arcs[i][j].adj != udg3.nonAdjInt&&udg3.arcs[i][j].label==vec2[ii].first){
//                    cout<<"第"<<i<<"+"<<j<<endl;
                    udg3.arcs[i][j].adj=0;

                }}
        }
//        udg3.Display();
        flag=udg3.Display_BFS("s");
        if(flag.havet){
//            cout<<"仍然连通且包含t"<<endl;
            over.insert(vec2[ii].first);
        }
        else{
//            cout<<"不连通"<<endl;
//        保存此时的choosed
            over.insert(vec2[ii].first);
            return over;
        }

    }
}

set<string> findMinCut2(set<string> labels,GraphAdjMat udg2){
//    第二种方案：在L中按照某种规则（均匀随机，按照某种概率的随机，或者按照某种贪心规则）选择一个标签，
//停止条件 仍联通
    GraphAdjMat::solutionsfort flag;
    flag.havet=true;
    string linjie;//临界标签
    vector<edge> edges;
while(flag.havet){
//    只要该连通图中还包含t就一直进行以下步骤
//    选择标签 。去掉 然后再选
    //    随机选择一个标签 将其对应的边删掉 这里的havechoosed还是很有必要
    vector<string> labelA(labels.begin(), labels.end()); // 使用迭代器构造vector数组
    //    选择一个标签
//    存储对应的边
    int choose= randInt(0,labels.size()-1);
    string choosed=labelA[choose];
    labels.erase(choosed);
//     去掉选择的标签所对应的边
        for(int i=0; i<udg2.vexNum; i++){
            for( int j=0; j<udg2.vexNum;j++){
                if(udg2.arcs[i][j].adj != udg2.nonAdjInt&&udg2.arcs[i][j].label==choosed){
                    edges.emplace_back(i,j,choosed);
                    udg2.arcs[i][j].adj=0;
                }}
        }

//    udg2.Display();
     flag=udg2.Display_BFS("s");
    if(flag.havet){
//        cout<<"仍然连通且包含t"<<endl;
    }else{
//        cout<<"不连通"<<endl;
//        保存此时的choosed
        linjie=choosed;
//        cout<<"临界的标签是: "<<linjie<<endl;
    }

}
//    第二阶段，把linjie加回原图
    for (int i = 0; i < edges.size(); ++i) {
        if(edges[i].w==linjie){
            udg2.arcs[edges[i].a][edges[i].b].adj=1;
        }
    }
//    cout<<"把邻接标签加回原图的图结构"<<endl;
//    udg2.Display();
//    遍历此时的labels 依次去掉标签 联通--去掉  不连通--留下
//    cout <<"此时的标签除了临界标签还有:";
    vector<string> labelsP;
//    for (auto it = labels.begin(); it != labels.end(); it++)
//        cout << *it << " ";
//    cout<<endl;
    set<string> final;

    for (auto it = labels.begin(); it != labels.end(); it++) {
//        依次选择剩余的标签
//        cout<<"现在选中的标签是: "<<*it<<endl;
        for (int i = 0; i < udg2.vexNum; i++) {
            for (int j = 0; j < udg2.vexNum; j++) {
                if (udg2.arcs[i][j].adj != udg2.nonAdjInt && udg2.arcs[i][j].label == *it) {
                    udg2.arcs[i][j].adj = 0;
                    edges.emplace_back(i,j,*it);
                }
            }
        }

//        cout<<"把选中标签去掉的图结构"<<endl;
//        udg2.Display();
        flag=udg2.Display_BFS("s");
        if(flag.havet){
//            仍联通 去掉这个标签
        string temp=*it;
            labelsP.push_back(temp);
//        labels.erase(temp);

        }
        else{
            for (int i = 0; i < udg2.vexNum; i++) {
                for (int i = 0; i < edges.size(); ++i) {
                    if(edges[i].w==*it){
                        udg2.arcs[edges[i].a][edges[i].b].adj=1;
                    }
                }
            }
//            cout<<"把选中标签"<<*it<<"加回的图结构"<<endl;
//            udg2.Display();
        }
    }
//    labelsP= QuChuRongYu(labels,udg2);
    for (int i = 0; i < labelsP.size(); i++) {
        labels.erase(labelsP[i]);
    }
    labels.insert(linjie);
//    cout <<"最终得到的标签是：";

//    for (auto it = labels.begin(); it != labels.end(); it++)
//        cout << *it << " ";
//    cout<<endl;
    return labels;
}



set<string>  findMinCut(set<string> origin,GraphAdjMat g, ObjArrayList<string> * vexs){
    //    已经选过的标签
    set<string> havechoosed;
//找到的所有标签
    set<string> temp;
    //这一步是为了找s邻接的标签
    temp=g.Findadj(origin);

    vector<string> labelA(temp.begin(), temp.end()); // 使用迭代器构造vector数组
//    cout<<"找s邻接的标签: ";
//    for (int i=0;i<labelA.size();i++){
//        cout<<labelA[i]<<" ";
//    }
//    cout<<endl;
//    选择一个标签


//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<int32_t> distrib(0, temp.size()-1);
int rand= randInt(0,temp.size()-1);
//    std::cout << "选择的数字是： " << distrib(gen);
    string choosed=labelA[rand];
//    cout<<" 选择的标签是： "<<choosed<<endl;
    havechoosed.insert(choosed);
//    构造子图
    GraphAdjMat * mst=g.InitMST(havechoosed,vexs);
//    mst->Display();
//    判断该子图是否连通 从s开始做广度优先搜索看是否到达t就可以了
    GraphAdjMat::solutionsfort flag=mst->Display_BFS("s");

 while(!flag.havet&&!temp.empty()) {
// 如果没有找到t
     temp = g.Findadj(flag.vertexs);
//     cout<<"现在在vertexs中的有: ";
//     for (auto i : flag.vertexs){
//         cout<<i<<" ";
//     }
//     cout<<endl;
     temp = chaji(temp, havechoosed);
     if(temp.empty()){havechoosed.clear();
         cout<<"无解"<<endl;
         return havechoosed;}
//     cout<<"接下来在这些label中选一个: ";
//     for (auto i : temp){
//         cout<<i<<" ";
//     }
//     cout<<endl;
     vector<string> labelA(temp.begin(), temp.end()); // 使用迭代器构造vector数组
//    选择一个标签

     int choose = randInt(0, temp.size() - 1);
     choosed = labelA[choose];
//     cout<<" daszdf"<<endl;
     havechoosed.insert(choosed);
//    构造子图
//     for (auto i : havechoosed){
//         cout<<i<<" ";
//     }
// }
     //这里有点问题 回来修改一下
     mst = g.InitMST(havechoosed, vexs);
//     mst->Display();
//    判断该子图是否连通 从s开始做广度优先搜索看是否到达t就可以了

     flag = mst->Display_BFS("s");
//     cout<<"tenp.size()"<<endl;
//     cout<<temp.size()<<endl;
//cout<<"flag0"<<endl;
//cout<<flag.havet<<endl;
 }
 //have choosed是选择的 去冗余操作其实是在最终的mst上依次去掉看效果
    vector<edge> edges;
    vector<string>labelsP;

    for (auto it = havechoosed.begin(); it != havechoosed.end(); it++) {
//        依次选择剩余的标签
//        cout<<"方案1：现在选中的标签是: "<<*it<<endl;
        for (int i = 0; i < mst->vexNum; i++) {
            for (int j = 0; j < mst->vexNum; j++) {
//                cout<< mst->arcs[i][j].label;
                if (mst->arcs[i][j].adj != mst->nonAdjInt && mst->arcs[i][j].label == *it) {
                    mst->arcs[i][j].adj = 0;
                    edges.emplace_back(i,j,*it);

                }
            }
        }

//        cout<<"把选中标签去掉的图结构"<<endl;
//       mst->Display();
        flag=mst->Display_BFS("s");
        if(flag.havet){
//            仍联通 去掉这个标签
            string temp=*it;
            labelsP.push_back(temp);
//        labels.erase(temp);

        }
        else{
            for (int i = 0; i < mst->vexNum; i++) {
                for (int i = 0; i < edges.size(); ++i) {
                    if(edges[i].w==*it){
                        mst->arcs[edges[i].a][edges[i].b].adj=1;
                    }
                }
            }
//            cout<<"把选中标签"<<*it<<"加回的图结构"<<endl;
//            mst->Display();
        }
    }
    for (int i = 0; i < labelsP.size(); i++) {
        havechoosed.erase(labelsP[i]);
    }
//    labelsP= QuChuRongYu(labels,udg2);

    return havechoosed;
}

int main() {
//    梳理一下流程：
//    1. 终止条件：可选标签为0或找到t 否则就重复
//    2.

//初始化图在这里做：
//初始化顶点数据
vector<string> vs= stringSplit(logs_dir_path,'\\');
storepath=storepath+vs[6]+"+"+vs[7]+".txt";
cout<<storepath<<endl;
    srand(314);
    int xiaoyu=0;
    int dengyu=0;
int down=0; int up=50;
for(int in=down;in<up;in++){

    string filename=logs_dir_path+"\\"+  to_string(in) + ".txt";
//string filename="\"D:\\DOWNLOAD FROM EDGE\\FILE\\AARTICLE\\DATASTORE\\SPG\\10\\10_19\\0.txt\"";
    cout<<"=================================="<<filename<<"=================================="<<endl;
    vector<vector<string>> vec=read(filename);
    ObjArrayList<string> * vexs = new ObjArrayList<string>();

    //    初始化顶点
    int x=atoi(vec[0][0].c_str());
    int s=atoi(vec[0][1].c_str());
    int t=atoi(vec[0][2].c_str());
    cout<<"s: "<<s<<" t: "<<t<<endl;
    for(int i=0;i<x;i++){
        string * temp;
        if(i==s){
            temp=new string ("s");
        }else if(i==t){
            temp=new string ("t");
        }else{
        temp=new string (to_string(i));}
        vexs->Add(temp);
    }


    //初始化边
    ObjArrayList<GraphAdjMat::ArcData> * arcsList = new ObjArrayList<GraphAdjMat::ArcData>();
    for (int i=1;i<vec.size();i++){
        GraphAdjMat::ArcData * temp = new GraphAdjMat::ArcData{ vec[i][0], vec[i][1], vec[i][2] };
        arcsList->Add(temp);

    }

//根据给定的边信息统计所有的标签
    set<string> labels;
    map<string,int> labelmap;
    for (int i = 0; i < arcsList->Length(); i++)
    {
        labels.insert(arcsList->Get(i)->Label);
    }
    cout <<"labels:";
    for (auto it = labels.begin(); it != labels.end(); it++)
    {
        cout << *it << " ";
        labelmap[*it]=0;
    }

    cout << endl << "Init Graph" << endl;
    set<string> origin;
    origin.insert("s");
    GraphAdjMat * udg7;
    int q=log(labels.size())*20;

    for (int i = 0; i < q; ++i) {
//        运行100次
        GraphAdjMat * udg = new GraphAdjMat(GraphAdjMat::UDG);
        GraphAdjMat * udg2= new GraphAdjMat(GraphAdjMat::UDG);
         udg7= new GraphAdjMat(GraphAdjMat::UDG);
        udg->Init(vexs, arcsList);
//        udg->Display();
        udg2->Init(vexs, arcsList);
        udg7->Init(vexs, arcsList);

     set<string> label=  findMinCut(origin,*udg,vexs);
//     cout<<"方案1结束"<<endl;
//     cout<<"最终选择的标签有：";
//     for(auto iii:label){
//         cout<<iii<<" ";
//     }
//     cout<<endl;
     set<string> label1=  findMinCut2(labels,*udg2);
////   注意这里不是最小割
////
//   的标签 而是打分需要
        for (auto it = label.begin(); it != label.end(); it++){
//        cout <<"labels:"<< *it << " ";

//            labelmap[*it]=labelmap[*it]+(10-label.size())*10;
            labelmap[*it]=labelmap[*it]+1;
        }
        for (auto it = label1.begin(); it != label1.end(); it++){
//        cout <<"labels1:"<< *it << " ";
        labelmap[*it]=labelmap[*it]+1;}

        delete udg;
//        cout<<"11111111111"<<endl;
        delete udg2;
    }
 //   输出map结果
//    for (auto it = labelmap.begin(); it != labelmap.end(); it++) {
//        cout << it -> first << " " << it -> second << endl;
//    }
    vector< pair<string,int> > vec2;
    for(map<string,int>::iterator it = labelmap.begin(); it != labelmap.end(); it++){
        vec2.push_back( pair<string,int>(it->first,it->second) );
    }
    sort(vec2.begin(),vec2.end(),cmp);
    GraphAdjMat * udg3 = new GraphAdjMat(GraphAdjMat::UDG);
    udg3->Init(vexs, arcsList);

    set<string> labelH=final(vec2,*udg7);
    labelH= QRongYu(labelH,*udg3);
////     这里的这些标签需要先根据这些标签做个图
//    cout<<endl;




    set<string> labelsfor1stage;
    int B = vexs->Length();
    cout<<"B----"<<B<<endl;
    B=pow(B,0.66);
//    cout<<"B----"<<B<<endl;
//近似操作
    GraphAdjMat * udg4= new GraphAdjMat(GraphAdjMat::UDG);
    udg4->Init(vexs, arcsList);
//    udg4.Display();
    GraphAdjMat * udg5= new GraphAdjMat(GraphAdjMat::UDG);
    udg5->Init(vexs, arcsList);
    GraphAdjMat * udg6= new GraphAdjMat(GraphAdjMat::UDG);
    udg6->Init(vexs, arcsList);
//    udg5->Display();
    vector<int> finalpath=udg4->BFS("s");
//    cout<<finalpath.size()<<endl;
        while(finalpath.size()<B+1&&finalpath.size()!=0){
    //        把这条路上涉及的线全删去。
            for (int i = 1; i <finalpath.size() ; i++) {
                int from=finalpath[i-1];
                int to=finalpath[i];
//                cout<<"from-"<<from<<"to-"<<to<<endl;
                udg4->arcs[from][to].adj=0;
                udg4->arcs[to][from].adj=0;
                labelsfor1stage.insert(udg4->arcs[to][from].label);
            }
            finalpath=udg4->BFS("s");
//            直接在每个finalpath这里加label就行
//            cout<<finalpath.size()<<endl;
        }


//    在此时的图上找最小s-t割

    set<string> labelsfor2stage=Ford_Fulkersen(*udg4,*udg5);
        set<string >finallabel;
    set_union(labelsfor1stage.begin(), labelsfor1stage.end(), labelsfor2stage.begin(), labelsfor2stage.end(), insert_iterator<set<string>>(finallabel, finallabel.begin()));
    cout<<"最终有这些标签： ";
    for(auto i:finallabel){
        cout<<i<<" ";
    }
   finallabel= QRongYu(finallabel,*udg6);








    int temp;
    if( labelH.size()<=finallabel.size()){
        temp=1;
        if(labelH.size()==finallabel.size()){
            dengyu+=1;
        }else{
            xiaoyu+=1;
        }
    }else{
        temp=0;
    }
    countF+=temp;
    Overall.emplace_back(labelH.size(),finallabel.size(),temp,countF);
    delete udg3;
    delete udg4;
    delete udg5;
    delete udg6;
    delete udg7;
    delete arcsList;
    delete vexs;
}
    string filename = storepath;
    freopen(filename.c_str(), "wb", stdout);//加b是为了适配linux

    for (int i = 0; i < Overall.size(); ++i) {

        printf("%d %d %d %d\n", Overall[i].a,Overall[i].b,Overall[i].temp,Overall[i].count);
    }
    printf("%d       %d\n", xiaoyu,dengyu);
    fclose(stdout);

}

