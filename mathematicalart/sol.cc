#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

//binary search for upperbound of xCoords, get compressed

struct FenwickTree{
   vector<int> bit;
   int n;

   FenwickTree(int n){
      this->n = n + 1;
      bit.assign(n + 1, 0);
   }

    int sum(int i) {
        int ret = 0;
        for (++i; i > 0; i -= i & -i)
            ret += bit[i];
        return ret;
    }

    void update(int i, int d){
      for (++i; i < n; i += i & -i)
          bit[i] += d;
    }

    int rangeSum(int l, int r){
      return sum(r) - sum(l-1);
    }
};

void mergeRanges(vector<pair<long long, long long>>& ranges){
  //ranges sorted
  sort(ranges.begin(), ranges.end());
  int j = 0;
  for(int i = 1; i < ranges.size(); i++){
    if(ranges[i].first <= ranges[j].second){
      ranges[j].second = max(ranges[j].second, ranges[i].second);
    }else{
      ranges[++j] = ranges[i];
    }
  }
  ranges.resize(j+1);
}


long long getPlusSignCount(int N, vector<int> L, string D) {
  // Write your code here
  
  long long x = 0, y = 0; //start position
  
  //Find lines O(n)

  //cout <<"create lines lists" <<endl;
  unordered_map<long long, vector<pair<long long, long long>>> V, H;
  //cout <<"(x: " << 0<< ", y: " << 0 <<")" <<endl;  
  for(int i = 0; i < N; i++){
    int len = L[i];
    switch(D[i]){
      case 'U':
        V[x].push_back({y, y+len});
        y += len;
        break;
      case 'D':
        V[x].push_back({y-len, y});
        y -= len;
        break;
      case 'R':
        H[y].push_back({x, x+len});
        x += len;
        break;
      case 'L':
        H[y].push_back({x-len, x});
        x-= len;
        break;
    }
    //cout <<"(x: " << x<< ", y: " << y <<")" <<endl;  

  }



  
  //Line Sweep
  vector<long long> xCoords;
  xCoords.reserve(V.size());

  vector<pair<long long, pair<long long, char>> > updates;  // {y, {x, delta}}

  for (auto& [x, ranges] : V) {
    xCoords.push_back(x);
    mergeRanges(ranges);
    for(const auto& range : ranges){
      updates.push_back({range.first+1, {x, 1}});
      updates.push_back({range.second, {x, -1}});
    }
  }
  sort(xCoords.begin(), xCoords.end());
  sort(updates.begin(), updates.end());

  //Compression Map
  unordered_map<long long, int> compX(xCoords.size());

  for(int i = 0; i < xCoords.size(); i++){
    compX[xCoords[i]] = i;
  }

  //cout <<"create Fenwick Tree" <<endl;
  FenwickTree lines(xCoords.size());

  //Find coordinates for range queries
  vector<long long> yCoords;
  yCoords.reserve(H.size());
  for (auto& pair : H) {
    yCoords.push_back(pair.first);
    mergeRanges(pair.second);
  }
  sort(yCoords.begin(), yCoords.end());

  int N = updates.size(), M = yCoords.size();

  long long count = 0;

  /*
  
  cout << "=== Vertical Lines===" <<endl;
  for(auto x: xCoords){
    cout << " x: " << x <<" ranges: [ ";
    for(auto& [l, r]: V[x]){
      cout << "("<<l <<", " << r <<") ";
    }
    cout <<"]"<<endl;
  }

  cout << "=== Horizontal Lines===" <<endl;
  for(auto y: yCoords){
    cout << " y: " << y << " ranges: [ ";
    for(auto& [l, r]: H[y]){
      cout << "("<<l <<", " << r <<") ";
    }
    cout<<"]" <<endl;
  }
  */
  

  //merge two indices
  for(int i = 0, j = 0; i < N || j < M;){
    if(i < N && (j== M || updates[i].first <= yCoords[j])){ //Update
      /*
      cout <<"=== y: " << updates[i].first <<" Update ===" <<endl;
      cout << " x: " << updates[i].second.first<< " delta: " << (int)updates[i].second.second<<endl;
      */
      lines.update(compX[updates[i].second.first], updates[i].second.second);
      i++;
    }else{ //Range Queries
      for(const auto& [l, r]: H[yCoords[j]]){
          /*
          cout <<"=== y: " << yCoords[j] <<" Query ===" <<endl;
          cout << "  Range: ( " << l << ", "<< r <<")" <<endl; 
          */
          auto itL = upper_bound(xCoords.begin(), xCoords.end(), l);
          int li = int(itL - xCoords.begin());

          // Find the first element >= r:
          auto itR = std::lower_bound(xCoords.begin(), xCoords.end(), r);

          // If that’s the very first element, there is no xCoords[i] < r:
          if (itR == xCoords.begin()) {
            // empty range
            continue;
          }
          // Otherwise back up one to get the last element < r:
          int ri = int(itR - xCoords.begin())-1;
          int crossCount = lines.rangeSum(li, ri);
          //cout << "Cross Count: " <<crossCount <<endl;
          count += crossCount;
      }
      j++;
    }
  }
  return count;
}

int main(){
  int N;
  cin >> N;
  vector<int> L(N);
  string D;
  for(int i = 0; i < N; i++){
    cin >> L[i];
  }
  cin >> D;
  cout << getPlusSignCount(N, L, D) << endl;
}
