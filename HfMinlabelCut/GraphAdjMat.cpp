//�ļ�����"GraphAdjMat.cpp"
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
    .	���캯������ʼ��ͼ����
    */
    this->type = type;
    this->vexNum = 0;
    this->arcNum = 0;
    if (this->type == DG || this->type == UDG)
    {
        //ͼ�Ĳ����� int ֵ 0
        this->nonAdjInt = 0;
    }
    else
    {
        //���Ĳ����� int ֵ �����
        this->nonAdjInt = this->_INFINITY;
    }
}

//GraphAdjMat::~GraphAdjMat()
//{
//    /*
//    .	��������������ͼ
//    */
//    //1.�ͷŶ����λ����������
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
    .	��ʼ�����㡢�����ݣ������� ͼ|��
    .	��Σ�
    .		vexs: ���� �б�
    .		arcsList: ������ �б�
    */
    //1.��ʼ����������
    if (vexs->Length() > this->_MAX_VERTEX_NUM)
    {
        return;
    }
    for (int i = 0; i < vexs->Length(); i++)
    {
        this->vexs[i] = *vexs->Get(i);
    }
    this->vexNum = vexs->Length();
    //1.1.��ʼ����������ն���λ����������
    for (int i = vexs->Length(); i < _MAX_VERTEX_NUM; i++)
    {
        vexs_null_index_queue->EnQueue(new int(i));
    }
    //2.���ݳ�ʼ����ͼ���ͣ�����ָ����ͼ
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
    .	��������ͼ
    .	�������ڹ�ϵ��0|������ 1|����
    .	�ڽӾ���Ϊ �Գƾ���
    */
    //��ʼ����ʱ �߶���
    ArcData * arcData = NULL;
    //��ʼ�� �����ά����
    int m = 0, n = 0;
    //��ʼ���ߵ��ڽӾ���
    for (int i = 0; i < this->vexNum; i++)
    {
        for (int j = 0; j <this->vexNum; j++)
        {
            this->arcs[i][j].adj = 0;
            this->arcs[i][j].label = "";
        }
    }
    //�����������б�
    for (int i = 0; i < arcsList->Length(); i++)
    {
        //�����ȡ�ߣ�����
        arcData = arcsList->Get(i);
        //��λ�������ã��ߵ����˶���λ��
        m = _Locate(arcData->Tail);
        n = _Locate(arcData->Head);
        //���ö������� Ϊ 1 ������
        if (this->arcs[m][n].adj == 1 || this->arcs[n][m].adj == 1)
        {
            //ȥ���ظ���
            continue;
        }
        this->arcs[m][n].adj = 1;
        this->arcs[m][n].label = arcData->Label;
        this->arcs[n][m].adj = 1;
        this->arcs[n][m].label = arcData->Label;
        //�� ����
        this->arcNum++;
    }
}



int GraphAdjMat::_Locate(string vertex)
{
    /*
    .	��λ����Ԫ��λ��
    .		���ڿɸĳɡ��ֵ�����������������100����λ����λ�ÿɸ���
    */
    //������λ����λ��
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
    .	��λ����Ԫ��λ��
    .		���ڿɸĳɡ��ֵ�����������������100����λ����λ�ÿɸ���
    */
    //������λ����λ��
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
    .	��ʾ ͼ|�� ������������顢�ڽӾ���
    */
    //��ʾ��������
    //ע����ɾ��ĳ���м���Ŷ���󣬶�������Ͳ���������
    cout << endl << "vertexs:" << endl;
    for (int i = 0, num = 0; i < this->vexNum && num < this->vexNum; i++)
    {
        if (this->vexs[i] != "")
        {
            cout << " (" << i << ")" << this->vexs[i];
            num++;
        }
    }
    //��ʾ�ߣ��ڽӾ���
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
    .	����һ���¶���
    */
    //1.�ж϶����Ƿ��Ѵ���
    if (_Locate(*vertex) > -1)
    {
        cout << endl << "�ö����Ѵ��ڡ�" << endl;
        return;
    }
    //2.�ж϶������Ƿ�ﵽ����
    if (this->vexNum >= this->_MAX_VERTEX_NUM)
    {
        cout << endl << "�������Ѵ����ޡ�" << endl;
        return;
    }
    //3.�����¶��㣬��������������
    int * index = vexs_null_index_queue->DeQueue();	//�ӿ�λ������������ȡ
    this->vexs[*index] = *vertex;
    this->vexNum++;
    //4.�����Ķ������ڽӾ����в���Ҫ���κβ������ѳ�ʼ����

}

void GraphAdjMat::DeleteVertex(string *vertex)
{
    /*
    .	ɾ��һ������
    */
    //1.�ж϶����Ƿ��Ѵ���
    int index = _Locate(*vertex);
    if (index == -1)
    {
        cout << endl << "�ö��㲻���ڡ�" << endl;
        return;
    }
    //2.ɾ���ö��㣬���Լ���������
    this->vexs[index] = "";
    this->vexNum--;
    //3.����ڽӾ��� index ���е����ݣ����������� �ָ���ʼ��״̬
    if (this->type == DG || this->type == UDG)
    {
        //ͼ
        for (int i = 0; i < this->_MAX_VERTEX_NUM; i++)
        {
            this->arcs[i][index].adj = 0;
            this->arcs[index][i].adj = 0;
        }
    }
    else
    {
        //��
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
    .	����һ���±ߣ�����
    .		���Ѵ��ڣ����������
    */
    //1.��λ����λ��
    int i = _Locate(arc->Tail);
    int j = _Locate(arc->Head);
    //2.�ж϶����Ƿ����
    if (i == -1 || j == -1)
    {
        cout << endl << "�ñ߶��㲻���ڡ�" << endl;
        return;
    }
    //3.����/����һ����
  if (this->type == UDG)
    {
        //������Ȩͼ
        this->arcs[i][j].adj = 1;
        this->arcs[j][i].adj = 1;
    }

}

void GraphAdjMat::DeleteArc(ArcData *arc)
{
    /*
    .	ɾ��һ���ߣ�����
    */
    //1.��λ����λ��
    int i = _Locate(arc->Tail);
    int j = _Locate(arc->Head);
    //2.�ж϶����Ƿ����
    if (i == -1 || j == -1)
    {
        cout << endl << "�ñ߶��㲻���ڡ�" << endl;
        return;
    }
    //3.ɾ��һ���ߣ��� �ָ���ʼ��״̬
if (this->type == UDG)
    {
        //������Ȩͼ
        this->arcs[i][j].adj = 0;
        this->arcs[j][i].adj = 0;
    }

}

void GraphAdjMat::Display_DFS(string *vertex)
{
    /*
    .	������ȱ�����ʾ����ָ�����㿪ʼ
    */
    //1.�ж϶����Ƿ����
    int index = _Locate(*vertex);
    if (index == -1)
        return;
    //2.��ʼ�������������
    for (int i = 0; i < this->_MAX_VERTEX_NUM; i++)
    {
        this->vexs_visited[i] = 0;
    }
    //3.������ȱ��� �ݹ�
    cout << "������ȱ��������Ӷ���" << *vertex << "��ʼ��" << endl;
    _DFS_R(index);
}

void GraphAdjMat::_DFS_R(int index)
{
    /*
    .	������ȱ��� �ݹ�
    .		����/�����㷨��һ����
    .		����ͼ|�����Ե�ǰ����ĳ��ȷ������
    .		����ͼ|�����Ե�ǰ��������ڽ�㷽������������Ϊ�����ȡ��������ǳ��ȣ�
    */
    //1.���ʶ��㣬������ѷ���
    cout << this->vexs[index] << " ";
    this->vexs_visited[index] = 1;
    //2.���������ڶ���
    for (int i = 0; i < this->_MAX_VERTEX_NUM; i++)
    {
        //����ֵ ���� ������intֵ��0|��Ȩ  ����|��Ȩ������δ�����ʹ�ʱ���ɷ���
        if (this->arcs[index][i].adj != this->nonAdjInt && this->vexs_visited[i] != 1)
        {
            _DFS_R(i);
        }
    }
}

GraphAdjMat::solutionsfort GraphAdjMat::Display_BFS(string vertex)
{
    /*
    .	������ȱ�����ʾ����ָ�����㿪ʼ
    .		���������Ĳ�α����㷨
    */
    solutionsfort flag;
    set<string> vertexs;
    //1.�ж϶����Ƿ����
    int index = _Locate(vertex);
    if (index == -1)
        return flag;
    //2.��ʼ�������������
    for (int i = 0; i < this->_MAX_VERTEX_NUM; i++)
    {
        this->vexs_visited[i] = 0;
    }
    //3.������ȱ���
//    cout << "BFS ��ʼ��  " << vertex << endl;

    //3.1.��ʼ������
    LinkQueue<int> * vexQ = new LinkQueue<int>();
    //3.2.���ʿ�ʼ���㣬����Ƿ��ʡ����
//    cout <<"BFS���ʵ����㣺"<< this->vexs[index] <<" ";
    this->vexs_visited[index] = 1;
    int count=1;
    vertexs.insert("s");
    vexQ->EnQueue(new int(index));
    //3.3.���ӣ��������ڽӶ��㣨��һ��Σ������ʺ����
    while (vexQ->GetHead() != NULL)
    {
        index = *vexQ->DeQueue();
        for (int j = 0; j < this->vexNum; j++)
        {
            //δ���ʹ����ڽӶ���
            if (this->arcs[index][j].adj != this->nonAdjInt && this->vexs_visited[j] != 1)
            {
                //���ʶ��㣬����Ƿ��ʡ����
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
    //4.�ͷŶ���
    int * e;
    while (vexQ->GetHead() != NULL)
    {
        e = vexQ->DeQueue();
        delete e;
    }
    delete vexQ;

    auto it = vertexs.find("t");

    if ( it == vertexs.end() ) {
        // δ�ҵ�Ԫ��
//        cout<<"BFS û�ҵ� t"<< endl;
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
        // �ҵ�
//        cout << "BFS ��ͨ�ҵ� " << *it<< endl;
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
//    ��ʼ��path
    for (int i = 0; i < this->vexNum; ++i) {
        path[i]=-1;

    }
    for(int i = 0; i < this->vexNum; i++)
    {
        d[i] = 10000000;  //��ʼ��·������
        path[i] = -1; //���·�����ĸ��������
    }
    set<string> vertexs;
    //1.�ж϶����Ƿ����
    int index = _Locate(vertex);
    d[index]=0;
    if (index == -1)
        return finalpath;
    //2.��ʼ�������������
    for (int i = 0; i < this->vexNum; i++)
    {
        this->vexs_visited[i] = 0;
    }
    //3.������ȱ���
//    cout << "BFS ��ʼ��  " << vertex << endl;

    //3.1.��ʼ������
    LinkQueue<int> * vexQ = new LinkQueue<int>();
    //3.2.���ʿ�ʼ���㣬����Ƿ��ʡ����
//    cout <<"BFS���ʵ����㣺"<< this->vexs[index] <<" ";

    this->vexs_visited[index] = 1;
    vexQ->EnQueue(new int(index));
    //3.3.���ӣ��������ڽӶ��㣨��һ��Σ������ʺ����
    while (vexQ->GetHead() != NULL)
    {
//        cout<<index<<endl;
        index = *vexQ->DeQueue();
        for (int j = 0; j < _MAX_VERTEX_NUM; j++)
        {
            //δ���ʹ����ڽӶ���
            if (this->arcs[index][j].adj != this->nonAdjInt && this->vexs_visited[j] != 1)
            {
                d[j]=d[index]+1;
                path[j]=index;
                //���ʶ��㣬����Ƿ��ʡ����
//                cout <<"  " <<this->vexs[j];
                vertexs.insert(this->vexs[j]);
                this->vexs_visited[j] = 1;
                vexQ->EnQueue(new int(j));
            }
        }


    }
//    cout<<" "<<endl;
    //4.�ͷŶ���
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
//        cout<<"�Ҳ�����s��t��·����"<<endl;
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
//���켯�ϴ洢label
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


//    cout << "�����ڵķ�֧�ڽӵı�ǩ��: ";
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
//    ���������Arccell �������ǩ��
//    cout <<"��������Щ��ǩ��ʼ������ ";
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