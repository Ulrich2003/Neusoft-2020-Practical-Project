//
// Created by Vichien on 2020/8/16.
//
#include <iostream>
#include <sstream>
#include <vector>
#define Zero 0
#define MVNum 100
bool visited[100]={false};//用于区分顶点有无被访问
using namespace std;

/**
 * 构建无向网
 */
class AMGraph{
public :
    int vexs[MVNum];//顶点表
    int arcs[MVNum][MVNum];//邻接矩阵
    int vexnum,arcnum;//图的点数和边数
};

/**
 * 查找顶点信息：把顶点1,2,3转换为0,1,2
 * @param G 顶点所在的图
 * @param u 顶点编号
 * @return 返回顶点编号对应的下标
 */
int LocateVex(AMGraph G, int u) {
    //在图G中查找顶点u，存在则返回顶点表中的下标
    for(int i=0;i<G.vexnum;i++){
        if(u==G.vexs[i]){
            return i;
        }
    }
    return -1;
}

/**
 * 采用邻接矩阵创建无向网
 */
void CreateUDN(AMGraph &G){
    while (true) {
        cout << "----------请输入总顶点数和总边数----------" << endl;
        cout << "请输入总顶点数：";
        cin >> G.vexnum;
        cout << "请输入总边数：";
        cin >> G.arcnum;
        cout<<"------------------请检查-------------------"<<endl;
        cout<<"总顶点数："<<G.vexnum<<"  总边数："<<G.arcnum<<endl;
        cout<<"1)正确  2)重新输入"<<endl;
        cout<<"请确定你输入的数据：";
        int n;
        cin>>n;
        if(n==1){
            break;
        } else{
            continue;
        }
    }
    cout<<endl;
    for(int i=0;i<G.vexnum;i++){
        G.vexs[i]=i+1;
    }

    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            G.arcs[i][j]=Zero;//边的权值默认为极大值
        }
    }
    int v1,v2;//传入一条边依附的两个点的编号
    int w;//设置边的权值，下面默认为1
    cout<<"-------请依次输入相连的两个点的编号,按【回车】继续-------"<<endl;
    int i=0,j=0;
    for(int k=0;k<G.arcnum;k++){
        cout<<"------------【输入“-1”即可清除上一组数据并重新输入】------------"<<endl;
        cout<<"请输入图中一条边所依附的【第一个】点：";
        cin>>v1;
        if(v1==-1){//如果输入-1
            k-=2;
//                cout<<"i="<<i<<",j="<<j<<","<<G.arcs[i][j]<<","<<G.arcs[j][i]<<endl;
            G.arcs[i][j]=--G.arcs[i][j];//边<v1，v2>的权值为w
            G.arcs[j][i]=G.arcs[i][j];
//                cout<<G.arcs[i][j]<<","<<G.arcs[j][i]<<endl;
            continue;
        }
        i=LocateVex(G,v1);//把顶点1,2,3转成0,1,2
        while (i==-1){
            cout<<"【ERROR】您输入的第一个顶点（编号）有误，请重新输入"<<endl;
            cout<<"请输入图中一条边所依附的【第一个】点：";
            cin>>v1;
            i=LocateVex(G,v1);
        }
        cout<<"请输入图中一条边所依附的【第二个】点：";
        cin>>v2;
        j=LocateVex(G,v2);
        while (j==-1){
            cout<<"【ERROR】您输入的第二个顶点（编号）有误，请重新输入"<<endl;
            cout<<"请输入图中一条边所依附的【第二个】点：";
            cin>>v2;
            j=LocateVex(G,v2);
        }
//        cout<<"请输入这条边的权值：";
//        cin>>w;
        //数据均合法的话赋值到图的二维数组中（可达矩阵）
        G.arcs[i][j]=++G.arcs[i][j];//边<v1，v2>的权值为w
        G.arcs[j][i]=G.arcs[i][j];
    }
}
/**
 * 采用邻接矩阵进行图的深度优先搜索遍历
 * @param G 要DFS深度查找的图
 * @param v 开始查找的点
 */
void DFS(AMGraph G,int v=0){
//    cout<<v;//访问第v个顶点
    visited[v]= true;//把访问过的点设置为true
    //依次检测邻接矩阵v所在的行
    for(int w=0;w<G.vexnum;w++){
        if((G.arcs[v][w]!=0)&&(!visited[w])){
            DFS(G,w);
            //w是v的邻接点，如果w未访问，则递归调用DFS
        }
    }
}
/**
 * 初始化visited
 */
void initVisited(){
    for(int i=0;i<100;i++){
        visited[i]= false;
    }
}
/**
 * 采用dfs判断图的连通性
 * @return
 */
bool judgeDfs(AMGraph G){
    DFS(G);
    for(int i=0;i<G.vexnum;i++){
        if(visited[i]== false){
            initVisited();
            return false;
        }
    }
    initVisited();
    return true;
}
bool judgeDfs(AMGraph G,vector<int>v){
    DFS(G);
    for(int i=0;i<v.size();i++){
        visited[v[i]]= true;
    }
    for(int i=0;i<G.vexnum;i++){
        if(visited[i]== false){
            initVisited();
            return false;
        }
    }
    initVisited();
    return true;
}

void printJudge(AMGraph G){
    bool result=judgeDfs(G);
    if(result){
        cout<<"****此无向图【是】连通图****"<<endl;
    }else{
        cout<<"****此无向图【不是】连通图****"<<endl;
    }
}

class Welcome {
    /**
     * dfs求无向图所有的分支
     * @param graph 传入的图
     */
    void dfsBranch(AMGraph G,int v=0){
        cout<<"-"<<G.vexs[v];
        visited[v]= true;//把访问过的点设置为true
        //依次检测邻接矩阵v所在的行
        for(int w=0;w<G.vexnum;w++){
            if((G.arcs[v][w]!=0)&&(!visited[w])){
                dfsBranch(G,w);
                //w是v的邻接点，如果w未访问，则递归调用DFS
            }
        }
    }
    void branch(AMGraph G){
        dfsBranch(G);
        for(int i=0;i<G.vexnum;i++){
            if(!visited[i]){
                cout<<endl;
                dfsBranch(G,i);
            }
        }
        cout<<endl;
        initVisited();
    }

    /**
     * 判断无向图邻接矩阵的第v个顶点还有跟其他顶点连接吗
     * @param G 传入的图
     * @param v 第v个顶点
     * @return false表示还有跟其他顶点连接
     */
    bool isNull(AMGraph G,int v){
        for(int w=0;w<G.vexnum;w++){
            if(G.arcs[v][w]){
                return false;
            }
        }
        return true;
    }
    /**
     * 判断欧拉图专用的dfs
     * 特点：顶点可以重复走
     * @param G 传入的图
     * @param v 开始遍历的顶点
     */
     vector<int>vec;
     vector<int>result;
     bool bridge=0;
    void DFSEuler(AMGraph &G,int v=0){
        result.push_back(v+1);
//            cout<<"-"<<v+1<<endl;
//            printG(G);
        bool b=1;
        bool c=1;
        //依次检测邻接矩阵v所在的行
        for(int w=G.vexnum-1;w>=0;w--){
            if(G.arcs[v][w]!=0){
                //尽量不要走桥 （去掉这条边之后整个图不连通）
                //边只可以走一次
                G.arcs[v][w]=G.arcs[w][v]=--G.arcs[v][w];
                if(isNull(G,v)){
                    //如果第v个顶点已经没跟其他顶点连接，从狭义上屏蔽它，不要影响连通性判断
                    vec.push_back(v);
                    c=0;
                }
                if(!judgeDfs(G,vec)){//倘若不连通
                    G.arcs[v][w]=G.arcs[w][v]=++G.arcs[v][w];//把边还它，重新找其他路
                    if(!vec.empty()&&c){
                        vec.pop_back();
                    }
                    continue;
                } else{
                    b=0;
                    DFSEuler(G,w);
                }
            }
        }
        //如果整一行都是桥的话，无奈只能选个桥走走咯
        if(b){
            bool judge=1;
            for(int w=G.vexnum-1;w>=0;w--){
                if(G.arcs[v][w]!=0){
                    G.arcs[v][w]=G.arcs[w][v]=--G.arcs[v][w];
                    if(isNull(G,v)){
                        //如果第v个顶点已经没跟其他顶点连接，从狭义上屏蔽它，不要影响连通性判断
                        vec.push_back(v);
                    }
                    judge=0;
                    DFSEuler(G,w);
                }
            }
            if(judge){
                //如果一个桥都没有，表示走死了，暴力退出整个递归
//                cout<<"暴力"<<endl;
//                printG(G);
                for(int i=0;i<G.vexnum;i++){
                    for(int j=0;j<G.vexnum;j++){
                        if(G.arcs[i][j]==1){
                            bridge=1;
                        }
                    }
                }
                for(int i=0;i<G.vexnum;i++){
                    for(int j=0;j<G.vexnum;j++){
                        G.arcs[i][j]=0;
                    }
                }
            }
        }
    }
    /**
     * 无向图的欧拉性判别和导出欧拉回路
     * @param G 进行判别的图
     */
    void euler(AMGraph G){
        //不连通肯定不是欧拉图
        if(!judgeDfs(G)){
            cout<<"----此图【不是】欧拉图----"<<endl;
            return;
        }
        DFSEuler(G);
        if(bridge){
            cout<<"----此图【不是】欧拉图----"<<endl;
            bridge=0;
            return;
        }
        for(int i=0;i<G.vexnum;i++){
            for(int j=0;j<G.vexnum;j++){
                if(G.arcs[i][j]==1){
                    cout<<"----此图【不是】欧拉图----"<<endl;
                    return;
                }
            }
        }
        if(result[0]==result[result.size()-1]){
            cout<<"----此图【是】欧拉图----"<<endl;
            cout<<"其欧拉回路为："<<endl;
            for(int i:result){
                cout<<"-"<<i;
            }
            cout<<endl;
        } else{
            cout<<"----此图【不是】欧拉图----"<<endl;
            /*for(int i:result){
                cout<<"-"<<i;
            }
            cout<<endl;*/
        }

        //方法结束 初始化到原来的状态
        vec.clear();
        result.clear();
    }
/**
 * 无向图功能选择界面
 */
    void undigraph(AMGraph G) {
        while (true) {
            cout << "--------------------------------------" << endl;
            cout << "1.无向图的连通性判断" << endl;
            cout << "2.求无向图的所有分支" << endl;
            cout << "3.无向图的欧拉性判别及导出欧拉回路" << endl;
            cout << "4.返回主页"<<endl;
            cout << "请输入您所需功能的编号：";
            int n;
            cin >> n;
            switch (n) {
                case 1: {
                    printJudge(G);
                    break;
                }
                case 2: {
                    branch(G);
                    break;
                }
                case 3: {
                    euler(G);
                    break;
                }
                case 4:{
                    initVisited();
                    return;
                }
                default: {
                    cout << "【ERROR】您输入的编号有误，请重新输入：" << endl;
                }
            }
            system("pause");
        }
    }
    /**
     * 创建有向图
     * @param G 传入要操作的图
     */
    void createDN(AMGraph &G){
        while (true) {
            cout << "----------请输入总顶点数和总边数----------" << endl;
            cout << "请输入总顶点数：";
            cin >> G.vexnum;
            cout << "请输入总边数：";
            cin >> G.arcnum;
            cout<<"------------------请检查-------------------"<<endl;
            cout<<"总顶点数："<<G.vexnum<<"  总边数："<<G.arcnum<<endl;
            cout<<"1)正确  2)重新输入"<<endl;
            cout<<"请确定你输入的数据：";
            int n;
            cin>>n;
            if(n==1){
                break;
            } else{
                continue;
            }
        }
        cout<<endl;
        //初始化顶点编号
        for(int i=0;i<G.vexnum;i++){
            G.vexs[i]=i+1;
        }

        for(int i=0;i<G.vexnum;i++){
            for(int j=0;j<G.vexnum;j++){
                G.arcs[i][j]=Zero;//边的权值默认为0
            }
        }
        int v1,v2;
//        int w;
        cout<<"-------请依次输入相连的两个点的编号，方向为【点1-->点2】,按【回车】继续-------"<<endl;
        int i=0,j=0;
        for(int k=0;k<G.arcnum;k++){
            cout<<"------------【输入“-1”即可清除上一组数据并重新输入】------------"<<endl;
            cout<<"请输入图中一条边所依附的【第一个】点，【点1-->】：";
            cin>>v1;
            if(v1==-1){
                k-=2;
                G.arcs[i][j]--;
                continue;
            }
            i=LocateVex(G,v1);
            while (i==-1){
                cout<<"【ERROR】您输入的第一个顶点（编号）有误，请重新输入"<<endl;
                cout<<"请输入图中一条边所依附的【第一个】点，【点1-->】：";
                cin>>v1;
                i=LocateVex(G,v1);
            }
            cout<<"请输入图中一条边所依附的【第二个】点，【-->点2】：";

            cin>>v2;
            j=LocateVex(G,v2);
            while (j==-1){
                cout<<"【ERROR】您输入的第二个顶点（编号）有误，请重新输入"<<endl;
                cout<<"请输入图中一条边所依附的【第二个】点，【-->点2】：";
                cin>>v2;
                j=LocateVex(G,v2);
            }
//        cout<<"请输入这条边的权值：";
//        cin>>w;
//            w=1;
            G.arcs[i][j]++;//边<v1，v2>的权值为w
        }
    }
    /**
     * 测试用，打印图
     * @param G 要打印的图
     */
    void printG(AMGraph G){
        for(int i=0;i<G.vexnum;i++){
            for(int j=0;j<G.vexnum;j++){
                cout<<G.arcs[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    void printVisited1(AMGraph G){
        for(int i=0;i<G.vexnum;i++){
            for(int j=0;j<G.vexnum;j++){
                cout<<visited1[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    /**
    * 弱连通性判断
    * @param G
    */
    void printJudge1(AMGraph G){
        bool result=judgeDfs(G);
        if(result){
            cout<<"****此有向图【是】弱连通图****"<<endl;
        }else{
            cout<<"****此有向图【不是】弱连通图****"<<endl;
        }
    }
    /**
     * 有向图改无向图
     */
    void theWeakConnectivity(AMGraph G){
        for(int i=0;i<G.vexnum;i++){
            for(int j=0;j<G.vexnum;j++){
                if(G.arcs[i][j]==0){
                    continue;
                } else{
                    G.arcs[j][i]=G.arcs[i][j];
                }
            }
        }
        printJudge1(G);
    }

    int tab=0;
    int visited1[100][100];
    void initVisited1(){
        for(int i=0;i<100;i++){
            for(int j=0;j<100;j++){
                visited1[i][j]=0;
            }
        }
    }
    /**
     * 用DFS判断图是否是单向连通图
     * @param G 要判断的图
     * @param tab 全局标记，标记顶点tab究竟能到达其他哪个顶点
     * @param v DFS开始搜索时出发的第一个顶点
     */
    void DFS(AMGraph G,int tab,int v=0){
//    cout<<v;//访问第v个顶点
        //依次检测邻接矩阵v所在的行
        for(int w=0;w<G.vexnum;w++){
            if(G.arcs[v][w]!=0 && visited1[tab][w]==0){
                visited1[tab][w]=1;
                DFS(G,tab,w);
                //w是v的邻接点，如果w未访问，则递归调用DFS
            }
        }
    }
    /**
     * 单向连通性判断
     * @param G
     */
    bool unidirectionalConnectivity(AMGraph G){
        //初始化
        initVisited1();
        for(int i=0;i<G.vexnum;i++){
            tab=i;
            DFS(G,tab,i);
        }
        for(int i=0;i<G.vexnum;i++){
            for(int j=0;j<G.vexnum;j++){
                if(i==j){
                    continue;
                }
                if(visited1[i][j]==0){
                    if(visited1[j][i]==0){
                        return false;
                    }
                }
            }
        }
        return true;
    }
    /**
     * 强连通性判断
     */
    bool stronglyConnected(AMGraph G){
        initVisited1();
        for(int i=0;i<G.vexnum;i++){
            tab=i;
            DFS(G,tab,i);
        }
        for(int i=0;i<G.vexnum;i++){
            for(int j=0;j<G.vexnum;j++){
                if(visited1[i][j]==0){
                    return false;
                }
            }
        }
        return true;
    }
    void digraph(AMGraph G){
        while (true) {
            cout << "--------------------------------------" << endl;
            cout << "1.判断有向图的弱连通性" << endl;
            cout << "2.判断有向图的单向连通性" << endl;
            cout << "3.判断有向图的强连通性" << endl;
            cout << "4.返回主页"<<endl;
            cout << "请输入您所需功能的编号：";
            int n;
            cin >> n;
            switch (n) {
                case 1: {
                    theWeakConnectivity(G);
                    break;
                }
                case 2: {
                    bool judge;
                    judge=unidirectionalConnectivity(G);
                    if(judge){
                        cout<<"****此有向图【是】单向连通图****"<<endl;
                    } else{
                        cout<<"****此有向图【不是】单向连通图****"<<endl;
                    }
                    initVisited1();
                    break;
                }
                case 3: {
                    bool judge=stronglyConnected(G);
                    if(judge){
                        cout<<"****此有向图【是】强连通图****"<<endl;
                    }else{
                        cout<<"****此有向图【不是】强连通图****"<<endl;
                    }
                    initVisited1();
                    break;
                }
                case 4:{
                    initVisited();
                    initVisited1();
                    return;
                }
                default: {
                    cout << "【ERROR】您输入的编号有误，请重新输入：" << endl;
                }
            }
            system("pause");
        }
    }
    void enterUndigraph(){
        AMGraph G;
        CreateUDN(G);
        undigraph(G);
    }

    void enterDigraph(){
        AMGraph G;
        createDN(G);
        digraph(G);
    }
public:
    /**
     * 欢迎界面
     */
    void welcome() {
        while (true) {
            cout << "-------主页-------" << endl;
            cout << "1.无向图" << endl;
            cout << "2.有向图" << endl;
            cout << "3.退出系统" << endl;
            cout << "请选择您要输入的图形类型：";
            int n;
            cin >> n;
            switch (n) {
                case 1: {
                    enterUndigraph();
                    break;
                }
                case 2: {
                    enterDigraph();
                    break;
                }
                case 3: {
                    cout << "---------------------" << endl;
                    cout << "系统退出中...谢谢您的使用" << endl;
                    cout << "---------------------" << endl;
                    return;
                }
                default: {
                    cout << "【ERROR】您输入的结果有误，请重新输入" << endl;
                    system("pause");
                    break;
                }
            }
        }
    }
};
int main(){
    cout<<"******************************************"<<endl;
    cout<<"****欢迎使用《n阶图G的连通性及欧拉性判别系统》****"<<endl;
    cout<<"******************************************"<<endl;
    Welcome welcome;
    welcome.welcome();
}

