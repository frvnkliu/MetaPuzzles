#include <bits/stdc++.h>
using namespace std;

//All relevant vertex properties
struct vProp {
    int index;
    int lowlink;
    int visitable;
    vProp() : index(0), lowlink(0), visitable(0) {}
};

/*Modified Tarjans
  Returns number of visitable pages for a given vertex v if it is the root of its scc
  Otherwise return the max visitable pages of it's children not in the scc
*/
int getVisitableWebpages(int v, int& index, vector<vProp>& vProps, stack<int>& S,  vector<unordered_set<int>>& adj){
  vProps[v].index = vProps[v].lowlink = index++; 
  
  int maxDesc = 0;   //max visitable of descendents of this SCC
  int start = S.size(); 
  S.push(v);
  for(int w : adj[v]){
    if(!vProps[w].index){ 
      //Completely Unexplored
      maxDesc = max(maxDesc, getVisitableWebpages(w, index, vProps, S, adj));
      vProps[v].lowlink = min(vProps[v].lowlink, vProps[w].lowlink);
    } else if(!vProps[w].visitable){ 
      //Equivalent to being on stack since vProps[w].index != 0
      vProps[v].lowlink = min(vProps[v].lowlink, vProps[w].lowlink);
    }else{
      maxDesc = max(maxDesc, vProps[w].visitable);
    }
  }

  //Update all nodes in SCC rooted at v
  if(vProps[v].lowlink == vProps[v].index){
    int currVisitable = maxDesc + (S.size()-start); //visitable from current cycle
    while(S.top() != v){
      vProps[S.top()].visitable =  currVisitable;
      S.pop();
    }
    S.pop();
    vProps[v].visitable = currVisitable;
    return vProps[v].visitable;
  }
  
  //return Max Visitable number of descendents of this node not in the SCC
  return maxDesc; 
}

int getMaxVisitableWebpages(int N, int M, vector<int> A, vector<int> B) {
  //1) Build Adjacent graph, dropping duplicate links
  vector<unordered_set<int>> adj(N);
  //Shift page numbering by 1 for better indexing
  for (int i = 0; i < M; i++) adj[A[i]-1].insert(B[i]-1);


  //2) Modified Tarjans Algorithm
  int res = 0;
  int index = 1;
  vector<vProp> vProps(N);
  stack<int> S;
  for(int v = 0; v < N; v++){
    if(!vProps[v].index){
      res = max(res, getVisitableWebpages(v, index, vProps, S, adj));
    }
  }
  return res;
} 

int main(){
  int N, M;
  cin >> N >> M;
  vector<int> A(M), B(M);
  for(int i = 0; i < M; i++){
    cin >> A[i];
  }

  for(int i = 0; i < M; i++){
    cin >> B[i];
  }

  cout << getMaxVisitableWebpages(N, M, A, B) <<endl;
}

