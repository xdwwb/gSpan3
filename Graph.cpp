#include"Graph.h"
void Graph::addVertex(int eLabel){
    vector<int> temp;
    vertexLabel.push_back(eLabel);
    edgeTo.push_back(temp);
    edgeLabel.push_back(temp);
}

void Graph::addEdge(int from, int to, int eLabel){
    edgeTo[from].push_back(to);
    edgeLabel[from].push_back(eLabel);
}

void Graph::show(){
    /*
        if(!supporter.empty()){
            cout<<"Support Count: "<<supporter.size()<<endl;
            cout<<"Supporter: ";
            for(size_t i=0;i<supporter.size();i++){
                cout<<supporter[i]<<" ";
            }
            cout<<endl;
        }
        */
    for(size_t i=0;i<vertexLabel.size();i++){
        cout<<i<<"/"<<vertexLabel[i]<<": ";
        for(size_t j=0;j<edgeTo[i].size();j++){
            cout<<edgeTo[i][j]<<"/"<<edgeLabel[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

bool Graph::hasEdge(int fromLabel, int eLabel, int toLabel){
    for(size_t i=0;i<vertexLabel.size();i++){

        int opposite;//还没有匹配的另外一条边
        if(vertexLabel[i]==fromLabel)
            opposite=toLabel;
        else if(vertexLabel[i]==toLabel)
            opposite=fromLabel;
        else
            continue;

        for(size_t j=0;j<edgeLabel[i].size();j++){
            if(edgeLabel[i][j]==eLabel&&vertexLabel[edgeTo[i][j]]==opposite)
                return true;
        }//end for
    }//end for
    return false;
}

void Graph::removeEdge(int fromLabel, int eLabel, int toLabel){
    for(size_t i=0;i<vertexLabel.size();i++){

        int opposite;//还没有匹配的另外一条边
        if(vertexLabel[i]==fromLabel)
            opposite=toLabel;
        else if(vertexLabel[i]==toLabel)
            opposite=fromLabel;
        else
            continue;

        for(size_t j=0;j<edgeLabel[i].size();j++){
            if(edgeLabel[i][j]==eLabel&&vertexLabel[edgeTo[i][j]]==opposite){
                edgeLabel[i][j]=edgeLabel[i].back();//使用了一个巧妙的方法，将末尾的元素提前，然后删除末尾的元素
                edgeLabel[i].pop_back();
                edgeTo[i][j]=edgeTo[i].back();
                edgeTo[i].pop_back();
                j--;
            }
        }//end for
    }//end for
}
