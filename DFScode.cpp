#include"DFScode.h"

Graph &DFScode::toGraph(Graph &g){
    DFScode &gc=*this;//为了使用方便
    if (gc.empty())
        return g;//如果为空则返回

    g.addVertex(gc[0].fromLabel);//初始化第一个顶点
    //遍历每一个五元组
    for(size_t i=0;i<gc.size();i++){
        if(gc[i].forward())
            g.addVertex(gc[i].toLabel);//加入新的顶点

        g.addEdge(gc[i].from,gc[i].to,gc[i].eLabel);//加入边
        g.addEdge(gc[i].to,gc[i].from,gc[i].eLabel);//反向加入边

    }
    //顺便copy一遍没问题吧？
    //this->g=g;
    return g;
}

bool DFScode::isMin(Graph &g){
    return isMin(g,*this);
}

bool DFScode::isMin(const Graph &g, const DFScode &gc){
    assert(!(gc.empty()));
    is_min=true;
    //DFScode &gc=*this;
    pgraph2code=new vector<int>();
    pgraph2code->resize(0);
    pgraph2code->resize(g.vertexLabel.size(),-1);
    vector<int> &graph2code=*pgraph2code;
    pedgeVisited=new vector<vector<bool>>;
    vector<vector<bool>> &edgeVisited=*pedgeVisited;
    edgeVisited.resize(g.vertexLabel.size());
    for(size_t i=0;i<g.vertexLabel.size();i++){
        edgeVisited[i].resize(0);
        edgeVisited[i].resize(g.vertexLabel.size(),false);
    }//init edgeVisited data struct;

    for(size_t i=0;i<g.vertexLabel.size();i++){
        int x=g.vertexLabel[i];

        //第一种剪枝方式
        if(x > gc[0].fromLabel)
            continue;

        assert(x==gc[0].fromLabel);
        //if(x < s[0].fromLabel)
        //	return false;//这样肯定不是最小的，但这种情况根本不可能出现！


        vector<int> v(1,(int)i);//size + init value
        graph2code[i]=0;
        DFS(g,v,0,1);
        graph2code[i]=-1;
    }

    delete pedgeVisited;
    delete pgraph2code;

    return is_min;
}

void DFScode::DFS(const Graph &g, vector<int> &v, int current, int next){
    DFScode &s=*this;
    vector<int> &graph2code=*pgraph2code;
    vector<vector<bool>> &edgeVisited=*pedgeVisited;
    //current表示当前比较的是第几条边
    if(current >= (int)s.size())
        return;

    vector<int>bak;//当回溯失败时用于恢复栈

    while(!v.empty()){
        bool flag = false;
        int x = v.back();//获取当前所在的图中的顶点位置

        for(size_t i=0;i<g.edgeTo[x].size();i++){
            int y=g.edgeTo[x][i];
            if(edgeVisited[x][y])//边已经被访问过了
                continue;

            //新找到一条未经访问的边
            flag=true;

            //这条边和DFScode中的一样大，则需要继续比较
            if(graph2code[y]==-1){//没有访问过

                Edge5 e(graph2code[x],next,g.vertexLabel[x],g.edgeLabel[x][i],g.vertexLabel[y]);

                if(s[current]<e)
                    continue;

                //这条边太小，程序可以结束了
                if(e<s[current]){
                    is_min=false;
                    return;
                }
                graph2code[y]=next;//赋予新的标号
                v.push_back(y);

				edgeVisited[x][y]=true;
				edgeVisited[y][x]=true;
                
				DFS(g,v,current+1,next+1);
                //从后面的比较结果中返回
                if(!is_min)
                    return;

				edgeVisited[x][y]=false;
				edgeVisited[y][x]=false;

                v.pop_back();
                graph2code[y]=-1;

            }else{

                Edge5 e(graph2code[x],graph2code[y],g.vertexLabel[x],g.edgeLabel[x][i],g.vertexLabel[y]);
                if(s[current]<e)
                    continue;

                //这条边太小，程序可以结束了
                if(e<s[current]){
                    is_min=false;
                    return;
                }

				edgeVisited[x][y]=true;
				edgeVisited[y][x]=true;

                DFS(g,v,current+1,next);
                //从后续的比较结果中返回
                if(!is_min)
                    return;
				edgeVisited[x][y]=false;
				edgeVisited[y][x]=false;
            }//对面的顶点已经访问过了

            
        }//end for
        //当栈顶节点所邻接的边访问完毕的时候

        if(flag)//说明找到了匹配的边，但是测试失败
            break;
        //没有找到匹配的边，考虑回溯,接着尝试匹配
        bak.push_back(v.back());
        v.pop_back();

    }//end while
    //运行到这里，肯定已经找到匹配的边了，但是比较结果是失败的
    //恢复栈的结果，使之不影响上一层的运行
    while(!bak.empty()){
        v.push_back(bak.back());
        bak.pop_back();
    }//栈v这样使用是为了减少空间的浪费，否则可以不使用bak栈。
}

void DFScode::show(){
    cout<<"DFS code:"<<endl;
    for(vector<Edge5>::iterator itr=this->begin();itr<this->end();itr++){
        itr->show();
    }
    cout<<endl;
}
