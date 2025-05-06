#include <bits/stdc++.h>
using namespace std;

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


//In-place sort and merge overlapping intervals algorithm
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
  long long x = 0, y = 0; //start position  
  
  //Find lines O(n)
  unordered_map<long long, vector<pair<long long, long long>>> V, H; //Vertical and Horizontal lines

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
  }

  //Line Sweep
  vector<long long> xCoords;
  xCoords.reserve(V.size());

  vector<pair<long long, pair<long long, char>> > updates;  // {y, {x, delta}} | y, y-value to apply this update

  for (auto& [x, ranges] : V) {
    xCoords.push_back(x);
    mergeRanges(ranges);
    for(const auto& range : ranges){
      updates.push_back({range.first+1, {x, 1}});
      updates.push_back({range.second, {x, -1}});
    }
  }
  sort(updates.begin(), updates.end());

  //X Value compression
  sort(xCoords.begin(), xCoords.end());
  unordered_map<long long, int> compX(xCoords.size());
  for(int i = 0; i < xCoords.size(); i++){
    compX[xCoords[i]] = i;
  }

  //Initialize Fenwick Tree
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

  //Line Sweep
  for(int i = 0, j = 0; i < N || j < M;){
    if(i < N && (j== M || updates[i].first <= yCoords[j])){
      //Update
      lines.update(compX[updates[i].second.first], updates[i].second.second);
      i++;
    }else{ 
      //Range Query
      for(const auto& [l, r]: H[yCoords[j]]){
          auto itL = upper_bound(xCoords.begin(), xCoords.end(), l);
          if(itL == xCoords.end()) continue; //Out of Bounds
          int li = int(itL - xCoords.begin());

          auto itR = std::lower_bound(xCoords.begin(), xCoords.end(), r);
          if (itR == xCoords.begin()) continue; //Out of Bounds
          int ri = int(itR - xCoords.begin())-1;

          int crossCount = lines.rangeSum(li, ri);
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
