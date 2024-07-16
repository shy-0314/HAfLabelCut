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
    cout<<"=========ȥ����==============" <<endl;
    bool flag=0;
//��¼��Ӧ�ߵ�
//    vector<vector<string>> vec;
    set<string> temp=originlabel;
//    map<string, vector<int>> mapVec;
//    ��һ��ȫȥ����ͼ ��ʱ����ͨ
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

//��Ҫ��һ����¼ÿ����ǩ��Ӧ�ߵ�


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
//            ����ͨ ����һ�� ������ͨ �������ǩȥ��
        if(!flag){
//            flag��ʱ��0 ���4������1��û��Ҫ����
            originlabel.erase(it);
//            temp=originlabel;
            cout<<"no��ͨ"<<endl;

        }else{
           cout<<"��ͨ"<<endl;
//           �򲻽������ǩȥ��������֮ǰ���ϵı�������
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


    cout<<"���������ڵı�ǩ�У�";
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
//ʹ��BFS���·��
    vector<int> path=udg3.BFS("s");
//    udg3.Display();
    while(path.size()!=0){
    for (int i = 1; i < path.size(); ++i) {
//        cout<<path[i]<<endl;
//        ��ӷ����
        int from=path[i-1];
        int to=path[i];
//        �������1���������1
        udg3.arcs[from][to].adj=udg3.arcs[from][to].adj-1;
        udg3.arcs[to][from].adj=udg3.arcs[to][from].adj+1;
    }
//    udg3.Display();
//�ٴ�Ѱ��ֱ���Ҳ���
    path=udg3.BFS("s");}
//    �ڴ�ʱ������·����s�ɴ�Ķ���
    GraphAdjMat::solutionsfort flag=udg3.Display_BFS("s");
    set<string> vertexs=flag.vertexs;
//    cout<<"��ʱs�ɴ�Ķ����У�";
//    for (auto i : vertexs){
//        cout<<i<<" ";
//    }
//        cout<<endl;
//    cout<<vertexs.size()<<endl;
    set<string> label= udg4.Findadj(vertexs);

//        cout<<label.size()<<endl;

    return  label;
}
//��txt�ļ�����vector<vector> int
vector<vector<string>> read(string filename){
    vector<vector<string>> vec;
    vec.clear();
    ifstream infile;
    infile.open(filename, ios::in);
    if (!infile.is_open())
    {
        cout << "��ȡ�ļ�ʧ��" << endl;
        return vec ;
    }
    //�����ֶ�ȡ����
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
//����
vector<string> hh;
    for (auto it = havechoosed.begin(); it != havechoosed.end(); it++){
        auto it2 = temp.find(*it);
        if ( it2 == temp.end() ) {
            // δ�ҵ�Ԫ��
            cout<<"NOT FOUND"<< endl;
        }
        else {
            // �ҵ�
//            cout << "�ҵ���Ԫ�أ� " << *it<< endl;
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
//    �����������Ա�ǩ���Ƿ�Ͽ�
    GraphAdjMat::solutionsfort flag;
    set<string> over;
    for(int ii=0;ii<vec2.size();ii++){
//        cout<<"��"<<ii+1<<"��ѡ�еı�ǩ�ǣ�"<<vec2[ii].first<<endl;
        for(int i=0; i<udg3.vexNum; i++){
            for( int j=0; j<udg3.vexNum;j++){
                if(udg3.arcs[i][j].adj != udg3.nonAdjInt&&udg3.arcs[i][j].label==vec2[ii].first){
//                    cout<<"��"<<i<<"+"<<j<<endl;
                    udg3.arcs[i][j].adj=0;

                }}
        }
//        udg3.Display();
        flag=udg3.Display_BFS("s");
        if(flag.havet){
//            cout<<"��Ȼ��ͨ�Ұ���t"<<endl;
            over.insert(vec2[ii].first);
        }
        else{
//            cout<<"����ͨ"<<endl;
//        �����ʱ��choosed
            over.insert(vec2[ii].first);
            return over;
        }

    }
}

set<string> findMinCut2(set<string> labels,GraphAdjMat udg2){
//    �ڶ��ַ�������L�а���ĳ�ֹ��򣨾������������ĳ�ָ��ʵ���������߰���ĳ��̰�Ĺ���ѡ��һ����ǩ��
//ֹͣ���� ����ͨ
    GraphAdjMat::solutionsfort flag;
    flag.havet=true;
    string linjie;//�ٽ��ǩ
    vector<edge> edges;
while(flag.havet){
//    ֻҪ����ͨͼ�л�����t��һֱ�������²���
//    ѡ���ǩ ��ȥ�� Ȼ����ѡ
    //    ���ѡ��һ����ǩ �����Ӧ�ı�ɾ�� �����havechoosed���Ǻ��б�Ҫ
    vector<string> labelA(labels.begin(), labels.end()); // ʹ�õ���������vector����
    //    ѡ��һ����ǩ
//    �洢��Ӧ�ı�
    int choose= randInt(0,labels.size()-1);
    string choosed=labelA[choose];
    labels.erase(choosed);
//     ȥ��ѡ��ı�ǩ����Ӧ�ı�
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
//        cout<<"��Ȼ��ͨ�Ұ���t"<<endl;
    }else{
//        cout<<"����ͨ"<<endl;
//        �����ʱ��choosed
        linjie=choosed;
//        cout<<"�ٽ�ı�ǩ��: "<<linjie<<endl;
    }

}
//    �ڶ��׶Σ���linjie�ӻ�ԭͼ
    for (int i = 0; i < edges.size(); ++i) {
        if(edges[i].w==linjie){
            udg2.arcs[edges[i].a][edges[i].b].adj=1;
        }
    }
//    cout<<"���ڽӱ�ǩ�ӻ�ԭͼ��ͼ�ṹ"<<endl;
//    udg2.Display();
//    ������ʱ��labels ����ȥ����ǩ ��ͨ--ȥ��  ����ͨ--����
//    cout <<"��ʱ�ı�ǩ�����ٽ��ǩ����:";
    vector<string> labelsP;
//    for (auto it = labels.begin(); it != labels.end(); it++)
//        cout << *it << " ";
//    cout<<endl;
    set<string> final;

    for (auto it = labels.begin(); it != labels.end(); it++) {
//        ����ѡ��ʣ��ı�ǩ
//        cout<<"����ѡ�еı�ǩ��: "<<*it<<endl;
        for (int i = 0; i < udg2.vexNum; i++) {
            for (int j = 0; j < udg2.vexNum; j++) {
                if (udg2.arcs[i][j].adj != udg2.nonAdjInt && udg2.arcs[i][j].label == *it) {
                    udg2.arcs[i][j].adj = 0;
                    edges.emplace_back(i,j,*it);
                }
            }
        }

//        cout<<"��ѡ�б�ǩȥ����ͼ�ṹ"<<endl;
//        udg2.Display();
        flag=udg2.Display_BFS("s");
        if(flag.havet){
//            ����ͨ ȥ�������ǩ
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
//            cout<<"��ѡ�б�ǩ"<<*it<<"�ӻص�ͼ�ṹ"<<endl;
//            udg2.Display();
        }
    }
//    labelsP= QuChuRongYu(labels,udg2);
    for (int i = 0; i < labelsP.size(); i++) {
        labels.erase(labelsP[i]);
    }
    labels.insert(linjie);
//    cout <<"���յõ��ı�ǩ�ǣ�";

//    for (auto it = labels.begin(); it != labels.end(); it++)
//        cout << *it << " ";
//    cout<<endl;
    return labels;
}



set<string>  findMinCut(set<string> origin,GraphAdjMat g, ObjArrayList<string> * vexs){
    //    �Ѿ�ѡ���ı�ǩ
    set<string> havechoosed;
//�ҵ������б�ǩ
    set<string> temp;
    //��һ����Ϊ����s�ڽӵı�ǩ
    temp=g.Findadj(origin);

    vector<string> labelA(temp.begin(), temp.end()); // ʹ�õ���������vector����
//    cout<<"��s�ڽӵı�ǩ: ";
//    for (int i=0;i<labelA.size();i++){
//        cout<<labelA[i]<<" ";
//    }
//    cout<<endl;
//    ѡ��һ����ǩ


//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<int32_t> distrib(0, temp.size()-1);
int rand= randInt(0,temp.size()-1);
//    std::cout << "ѡ��������ǣ� " << distrib(gen);
    string choosed=labelA[rand];
//    cout<<" ѡ��ı�ǩ�ǣ� "<<choosed<<endl;
    havechoosed.insert(choosed);
//    ������ͼ
    GraphAdjMat * mst=g.InitMST(havechoosed,vexs);
//    mst->Display();
//    �жϸ���ͼ�Ƿ���ͨ ��s��ʼ����������������Ƿ񵽴�t�Ϳ�����
    GraphAdjMat::solutionsfort flag=mst->Display_BFS("s");

 while(!flag.havet&&!temp.empty()) {
// ���û���ҵ�t
     temp = g.Findadj(flag.vertexs);
//     cout<<"������vertexs�е���: ";
//     for (auto i : flag.vertexs){
//         cout<<i<<" ";
//     }
//     cout<<endl;
     temp = chaji(temp, havechoosed);
     if(temp.empty()){havechoosed.clear();
         cout<<"�޽�"<<endl;
         return havechoosed;}
//     cout<<"����������Щlabel��ѡһ��: ";
//     for (auto i : temp){
//         cout<<i<<" ";
//     }
//     cout<<endl;
     vector<string> labelA(temp.begin(), temp.end()); // ʹ�õ���������vector����
//    ѡ��һ����ǩ

     int choose = randInt(0, temp.size() - 1);
     choosed = labelA[choose];
//     cout<<" daszdf"<<endl;
     havechoosed.insert(choosed);
//    ������ͼ
//     for (auto i : havechoosed){
//         cout<<i<<" ";
//     }
// }
     //�����е����� �����޸�һ��
     mst = g.InitMST(havechoosed, vexs);
//     mst->Display();
//    �жϸ���ͼ�Ƿ���ͨ ��s��ʼ����������������Ƿ񵽴�t�Ϳ�����

     flag = mst->Display_BFS("s");
//     cout<<"tenp.size()"<<endl;
//     cout<<temp.size()<<endl;
//cout<<"flag0"<<endl;
//cout<<flag.havet<<endl;
 }
 //have choosed��ѡ��� ȥ���������ʵ�������յ�mst������ȥ����Ч��
    vector<edge> edges;
    vector<string>labelsP;

    for (auto it = havechoosed.begin(); it != havechoosed.end(); it++) {
//        ����ѡ��ʣ��ı�ǩ
//        cout<<"����1������ѡ�еı�ǩ��: "<<*it<<endl;
        for (int i = 0; i < mst->vexNum; i++) {
            for (int j = 0; j < mst->vexNum; j++) {
//                cout<< mst->arcs[i][j].label;
                if (mst->arcs[i][j].adj != mst->nonAdjInt && mst->arcs[i][j].label == *it) {
                    mst->arcs[i][j].adj = 0;
                    edges.emplace_back(i,j,*it);

                }
            }
        }

//        cout<<"��ѡ�б�ǩȥ����ͼ�ṹ"<<endl;
//       mst->Display();
        flag=mst->Display_BFS("s");
        if(flag.havet){
//            ����ͨ ȥ�������ǩ
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
//            cout<<"��ѡ�б�ǩ"<<*it<<"�ӻص�ͼ�ṹ"<<endl;
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
//    ����һ�����̣�
//    1. ��ֹ��������ѡ��ǩΪ0���ҵ�t ������ظ�
//    2.

//��ʼ��ͼ����������
//��ʼ����������
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

    //    ��ʼ������
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


    //��ʼ����
    ObjArrayList<GraphAdjMat::ArcData> * arcsList = new ObjArrayList<GraphAdjMat::ArcData>();
    for (int i=1;i<vec.size();i++){
        GraphAdjMat::ArcData * temp = new GraphAdjMat::ArcData{ vec[i][0], vec[i][1], vec[i][2] };
        arcsList->Add(temp);

    }

//���ݸ����ı���Ϣͳ�����еı�ǩ
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
//        ����100��
        GraphAdjMat * udg = new GraphAdjMat(GraphAdjMat::UDG);
        GraphAdjMat * udg2= new GraphAdjMat(GraphAdjMat::UDG);
         udg7= new GraphAdjMat(GraphAdjMat::UDG);
        udg->Init(vexs, arcsList);
//        udg->Display();
        udg2->Init(vexs, arcsList);
        udg7->Init(vexs, arcsList);

     set<string> label=  findMinCut(origin,*udg,vexs);
//     cout<<"����1����"<<endl;
//     cout<<"����ѡ��ı�ǩ�У�";
//     for(auto iii:label){
//         cout<<iii<<" ";
//     }
//     cout<<endl;
     set<string> label1=  findMinCut2(labels,*udg2);
////   ע�����ﲻ����С��
////
//   �ı�ǩ ���Ǵ����Ҫ
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
 //   ���map���
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
////     �������Щ��ǩ��Ҫ�ȸ�����Щ��ǩ����ͼ
//    cout<<endl;




    set<string> labelsfor1stage;
    int B = vexs->Length();
    cout<<"B----"<<B<<endl;
    B=pow(B,0.66);
//    cout<<"B----"<<B<<endl;
//���Ʋ���
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
    //        ������·���漰����ȫɾȥ��
            for (int i = 1; i <finalpath.size() ; i++) {
                int from=finalpath[i-1];
                int to=finalpath[i];
//                cout<<"from-"<<from<<"to-"<<to<<endl;
                udg4->arcs[from][to].adj=0;
                udg4->arcs[to][from].adj=0;
                labelsfor1stage.insert(udg4->arcs[to][from].label);
            }
            finalpath=udg4->BFS("s");
//            ֱ����ÿ��finalpath�����label����
//            cout<<finalpath.size()<<endl;
        }


//    �ڴ�ʱ��ͼ������Сs-t��

    set<string> labelsfor2stage=Ford_Fulkersen(*udg4,*udg5);
        set<string >finallabel;
    set_union(labelsfor1stage.begin(), labelsfor1stage.end(), labelsfor2stage.begin(), labelsfor2stage.end(), insert_iterator<set<string>>(finallabel, finallabel.begin()));
    cout<<"��������Щ��ǩ�� ";
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
    freopen(filename.c_str(), "wb", stdout);//��b��Ϊ������linux

    for (int i = 0; i < Overall.size(); ++i) {

        printf("%d %d %d %d\n", Overall[i].a,Overall[i].b,Overall[i].temp,Overall[i].count);
    }
    printf("%d       %d\n", xiaoyu,dengyu);
    fclose(stdout);

}

