#include<algorithm>
#include<queue>
#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>

using namespace std;

void bfs(unordered_map<int, vector<int>> & graph, unordered_set<int> & visited, vector<int> & dist, queue<int> & q) {
  int curr_dist = 0; 
  while (!q.empty()) {
    int size = q.size();
    for (int i = 0; i < size; i++) {
      int curr = q.front(); 
      if (visited.find(curr) == visited.end()) {
        visited.insert(curr);
        dist[curr] = curr_dist; 
        for (int neighbour : graph[curr]) {
          if (visited.find(neighbour) == visited.end()) {
            q.push(neighbour);
          }
        }
      }
      q.pop();
    }
    curr_dist++;
  }
}

void solve() {
  int n, m, v; 
  cin >> n >> m >> v;
  unordered_map<int, vector<int>> graph;
  vector<int> dist(n, -1);
  
  for (int i = 0; i < m; i++) {
    int a, b; 
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  for (int i = 0; i < n; i++) {
    sort(graph[i].begin(), graph[i].end());
  }
  
  queue<int> q; 
  q.push(v);
  unordered_set<int> visited;
  bfs(graph, visited, dist, q);
  
  // sort(dist.begin(), dist.end());
  for (int d : dist) {
    cout << d << " ";
  }
  cout << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t) {
    solve();
    t--;
  }

  return 0;
}