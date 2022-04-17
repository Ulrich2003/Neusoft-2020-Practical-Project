﻿## 2020大一C++程序设计项目 小学期源码公开
作者：传扬

**文章末尾附加源码**
## 项目设计
**1.数据输入和储存**
本系统内核采用邻接矩阵，但主界面是通过点和边的关系来进行输入的，这样用户可以直观的把图形输入到计算机里，不需要掌握“离散数学”上的“邻接矩阵”，降低用户使用程序的难度。
**2.无向图的连通判断以及分支的输出**
程序可以对用户输入的无向图进行连通性判断，倘若该图是连通图，则输出“此图是连通图”，反之输出“此图不是连通图”。
同时，程序要达到用户在选择输出无向图分支后能够清晰的看出图中的每一个分支，即使是连通图，也要把唯一的分支给输出到主界面。
**3.有向图连通性判断**   
弱连通图的判定
判断用户输入的图是否为弱连通图，倘若是弱连通图，则输出“此图是弱连通图”，倘若不是则输出“此图不是弱连通图”。
单向连通图的判定
判断用户输入的图形是否为单向连通图，倘若是单向连通图，则输出“此图是单向连通图”，倘若不是则输出“此图不是单向连通图”。
强连通图的判定
判断用户输入的图形是否为强连通图，倘若是强连通图，则输出“此图是强连通图”，倘若不是则输出“此图不是强连通图”。
**4.无向图的欧拉回路判断和输出**
程序可以对用户输入的无向图进行欧拉性判断，倘若该图是欧拉图，则告诉用户“此图是欧拉图”，并输出其欧拉回路，否则输出“此图不是欧拉图”
**5.	用户体验**
为了提高用户的使用体验，本程序设计结构非常完整。无论是输入无向图或有向图，都有撤回上一组输入数据的功能，避免用户误输入而得重启整个程序，并且在判别完有向图后，程序可以返回到主页无缝对无向图进行判定，反之亦然。

## 项目实现过程
![导图](https://img-blog.csdnimg.cn/20201011192943775.png#pic_center)
启动程序时，我们便可以看见如下欢迎界面：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201011193031664.png#pic_center)

```cpp
//伪代码
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
```

欢迎界面的主体是由switch（）构成，通过输入不同的编号，来执行相对应的函数，倘若输入的数字有误，会提示重新输入。
我们这里选择无向图，进入无向图的操作前，系统会提示您使用点边的输入方式对图形进行输入，效果如下：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201011193220619.png#pic_center)
该操作的源代码分为3部分：

```cpp
void enterUndigraph(){
        AMGraph G;
        CreateUDN(G);
        undigraph(G);
    }
```
第一步是创建一个图的对象，该对象里面有顶点表，整个图的邻接矩阵和图的点数和边数。

```cpp
class AMGraph{
public :
    int vexs[MVNum];//顶点表
    int arcs[MVNum][MVNum];//邻接矩阵
    int vexnum,arcnum;//图的点数和边数
};
```
第二步是创建无向图，计算机通过输入点和边的关系把这一系列关系转换成邻接矩阵，实现方法如下：
首先输入图的顶点数和边数，确定好有几个点几条边，并对输入的数据进行确认，倘若输入有误可重新输入。接着输入一条边所依附的两个顶点，如1 2，代表顶点1和顶点2有边相连，在判断完图中确实存在这两个点后，把顶点1 2通过计算机转为0 1，在无向图邻接矩阵中，把arcs[0][1]和arcs[1][0]都由0设置为1，接着重复上述过程，完成整个图形的输入。
第三步则是进入无向图功能选择界面的函数，该函数依旧使用switch（），把输入的编号做处理，转到其他对应功能的函数中去，处理完相对应的操作后，再return返回到无向图功能选择界面，直到输入4“返回主页”才退出该选择界面。

```cpp
while (true) {
            cout << "--------------------------------------" << endl;
            cout << "1.无向图的连通性判断" << endl;
            cout << "2.求无向图的所有分支" << endl;
            cout << "3.无向图的欧拉性判别及导出欧拉回路" << endl;
            cout << "4.返回主页"<<endl;
            cout << "请输入您所需功能的编号：";
            int n; cin >> n;
            switch (n) {
               .......
            }
            system("pause");
        }
```

**深度优先搜索（DFS）算法：**
DFS算法是整个项目的核心算法，该算法能有效的对图中的顶点以及顶点的分支进行遍历。在使用DFS算法时，需要传入要进行遍历的图形，算法默认是从第1个顶点对整个图进行遍历。在设计DFS函数前，需要提前建立好全局数组visited[]，来记录被访问过的顶点。假设从顶点1开始遍历，需要从邻接矩阵中获取与顶点1相邻接的顶点（设该点为顶点2），倘若该邻接点（顶点2）并没有访问过，则在此邻接点（顶点2）的基础上进行DFS，找到与顶点2相邻接的顶点，直到图中所有的顶点都被访问过，自动退出DFS递归。

```cpp
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
```
**无向图连通性判断：**
整个程序的运转离不开深度优先遍历搜索（DFS）算法，程序通过DFS算法，从顶点开始逐一扫描每一个邻接点，并记录一轮DFS算法中所访问过的顶点编号，第一轮DFS结束后，对记录下的顶点编号做遍历搜索，倘若发现图中存在顶点没有被DFS访问，则必定不是连通图，反之是连通图。
**求无向图的所有分支：**
该步骤实现原理也需运用深度优先搜索（DFS）算法，程序通过DFS算法，从顶点开始逐一扫描每一个邻接点，并把访问过的顶点编号做输出，打到控制台上，并在visited[]数组中记录访问过的顶点。第一轮DFS结束后，便对visited进行扫描，倘若图中还有点没被访问，则从那个点开始进行新一轮的DFS，重复上述步骤，直到图中所有的点都被访问。
**无向图的欧拉性判别及导出欧拉回路：**
根据佛罗来算法，利用深度优先搜索（DFS）为基础，对无向图进行遍历。从顶点1开始，通过对边的删除判断，判断此路是不是“桥”，整个欧拉判断遵从能不走桥就不要走桥的原则，把DFS扫描过的顶点依次记录在visited数组中，并把走过的边立马做删除处理，以免重复走同一条边。等待DFS结束后，倘若该图出现走死的现象（最后一个顶点和第一个顶点不一样），则判断为非欧拉图，否则为欧拉图。
**删除判断：**
删除判断的设计极其巧妙，假设从顶点1开始做深度优先搜索（DFS），在有多条路可走的情况下，先选择一条路，把它做删除处理，倘若删除完这条路后无向图不连通，则该路必定是桥，程序遵守能不走桥就不走桥的原则，所以把删除的路做复原处理，重新选择一条路做“删除判断”，直到找到非桥的路可走。倘若没能找到，则任选一个桥走，对下一个点进行DFS搜索。
导出欧拉回路：在上述DFS过程后，倘若该图是欧拉回路，则用foreach的方式对记录在visited[]中的顶点做遍历处理，依次输出到控制台上，从而完成欧拉回路的输出。
输入4返回主页后，我们就可以到主页选择对有向图的判别。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201011193537843.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTUyNTY1Mw==,size_16,color_FFFFFF,t_70#pic_center)
有向图的输入界面和原理和无向图一样，唯一的区别就在与有向图在对一条边所依附的两个顶点做输入时，是有区别方向的。
首先输入图的顶点数和边数，确定好有几个点几条边，并对输入的数据进行确认，倘若输入有误可重新输入。接着输入一条边所依附的两个顶点，如1 2，代表顶点1和顶点2有边相连，且方向为（1-->2），在判断完图中确实存在这两个点后，把顶点1 2通过计算机转为0 1，在有向图邻接矩阵中，把arcs[0][1]设置为1，接着重复上述过程，完成整个图形的输入。
图形输入完毕后，便进入有向图功能选择界面：

```cpp
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
                ......
            }
            system("pause");
        }
```
**判断有向图的弱连通性：**
先把有向图转成无向图，再通过无向图的深度优先搜索（DFS）算法判断此图是否连通，倘若连通则是弱连通图，反之则不是。
**判断有向图的单向连通性：**
判断有向图为弱连通图后，进行单向连通图的判断。倘若不是弱连通图，则必定不是单向连通图。
建立一个二维矩阵visited，该矩阵是用来记录任意两点之间的连通关系的。采用深度优先搜索（DFS）算法，对图上所有的顶点进行遍历，并记录下该顶点与其他顶点的连接关系。所有顶点遍历完后，对visited进行扫描，倘若发现有一点visited[x][y]=0，且visited[y][x]=0，则该图不是单向连通图。
**判断有向图的强连通性：**
建立一个二维矩阵visited，该矩阵是用来记录任意两点之间的连通关系的。采用深度优先搜索（DFS）算法，对图上所有的顶点进行遍历，并记录下该顶点与其他顶点的连接关系。所有顶点遍历完后，对visited进行扫描，倘若发现有一点visited[x][y]=0，则该图不是强连通图。

**获取源代码请移步到GitHub**
https://github.com/Ulrich2003/Neusoft-2020-Practical-Project
码农不易，需要鼓励，记得为我点亮Star哟。
![在这里插入图片描述](https://img-blog.csdnimg.cn/92f1e33456614b0c97bc1a7dc0508c89.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTUyNTY1Mw==,size_16,color_FFFFFF,t_70)

