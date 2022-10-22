#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>
#include <algorithm> 

using namespace std;


struct Node {
  int val;
  int start;
  int end;
  bool reachable;
  Node(int v) : val(v), start(-1), end(-1), reachable(false) {}
  bool const operator==(const Node &node) const {
    return val == node.val;
  }
};




void print_node(Node * node) {
  cout << node -> val << " " << node -> start << " " << node -> end << endl;
}

void print_set(vector<Node*> s) {
  for (auto & it : s) {
    cout << it << " ";
  }
  cout << endl;
}

int iter = 0; 

void print_graph(unordered_map<int, vector<Node*>> & graph) {
    for (int i = 0; i < graph.size(); i++) {
        cout << i << " -> "; 
        for (Node* n : graph[i]) {
            cout << n -> val << " "; 
        }
        cout << endl;
    }
}

void print_start(Node* root, vector<Node*> & children,  unordered_map<int, Node*> & graph, int max_node) {
  for (int i = 0; i < max_node; i++) {
    if (graph[i] -> reachable) {
      cout << graph[i] -> start << " ";
    } else {
      cout << "-1" << " ";
    }
  }
  cout << endl;
}


void print_end(Node* root, vector<Node*> & children,  unordered_map<int, Node*> & graph, int max_node) {
  for (int i = 0; i < max_node; i++) {
    if (graph[i] -> reachable) {
      cout << graph[i] -> end << " ";
    } else {
      cout << "-1" << " ";
    }
  }
  cout << endl;
}


void dfs(Node* curr, unordered_map<int, vector<Node*>> &graph, unordered_map<int, Node*> & reachables, vector<bool> & visited) {
    visited[curr -> val] = true;
    if (curr -> start != -1) {
        return;
    }

    reachables[curr -> val] = curr;
    curr -> reachable = true;

    curr -> start = iter;
    iter++;
    
    for (Node* neighbour : graph[curr -> val]) {
        if (!visited[neighbour -> val]) {
            dfs(neighbour, graph, reachables, visited);
        } 
    }

    curr -> end = iter;
    iter++;
}




void solve() {
  int n, m, v;
  cin >> n >> m >> v;
  
  Node* root = new Node(v);
  // unordered_map<Node*, vector<Node*>> graph;
  unordered_map<int, vector<Node*>> graph;
//   unordered_set<Node*> nodes; 
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    Node* to = new Node(b);
    Node* from = new Node(a);
    // nodes.insert(to);
    // nodes.insert(from);
    graph[a].push_back(to);
    graph[b].push_back(from);
  }

  for (int i = 0; i < graph.size(); i++) {
    sort(graph[i].begin(), graph[i].end(), [](const Node* n1, const Node* n2) {
        return n1 -> val < n2 -> val; 
    });
  }

  vector<bool> visited(n, false);
  unordered_map<int, Node*> reachables;

  dfs(root, graph, reachables, visited);

  vector<Node*> children; 
  for (auto kv : graph) {
    for (auto v : kv.second) {
      children.push_back(v);  
    }
  }

  // unordered_map<int, Node*> reachables; 
  for (int i = 0; i < n; i++) {
    if (reachables.find(i) == reachables.end()) {
      reachables[i] = new Node(i); 
    }
  }
  
  print_start(root, children, reachables, n);
  print_end(root, children, reachables, n);
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t) {
    solve();
    iter = 0;
    t--;
  }

  return 0;
}