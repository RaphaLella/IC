#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a) for (int i = 0; i < (int)a; i++)
#define PB push_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define F first
#define S second

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int INF = 0x3f3f3f3f;
const int MAX = 1e5 + 7;
const int SQ = sqrt(MAX);

unordered_map<int, string> vertexIndices;
vector<pair<int, int>> graph[int(1e6)];

void addVertice(int indice, string nome) {
  vertexIndices[indice] = nome;
}

void addAresta(int u, int v, int wt) {
  graph[u].PB(make_pair(v, wt));
}

void printGrafo(int V, ofstream &out) {
  int v, w;
  for (int u = 0; u < V; u++) {
    out << "Vertice " << u << " tem aresta com \n";
    for (auto it = graph[u].begin(); it != graph[u].end(); it++) {
      v = it->F;
      w = it->S;
      out << "\tVertice " << v << " com aresta de peso =" << w << "\n";
    }
    out << "\n";
  }
}

void Dijkstra(int G, int *d, int *pi, int s) {
  set<int> Set;
  vector<int> Q;
  int u;
  FOR(i, G) {
    d[i] = INF;
    pi[i] = -1;
  }
  d[s] = 0;
  FOR(i, G) {
    Q.PB(i);
  }

  while (!Q.empty()) {
    vector<int>::iterator i;
    i = min_element(all(Q));
    u = *i;
    Q.erase(i);
    Set.insert(u);

    vector<pair<int, int>>::iterator it;
    for (it = graph[u].begin(); it != graph[u].end(); it++) {
      if (d[it->F] > d[u] + it->S) {
        d[it->F] = (d[u] + it->S);
        pi[it->F] = u;
      }
    }
  }
}

void printPath(int *prev, int start, int end, int D, ofstream &out) {
    vector<int> path;
    
    // Remonta o caminho inversamente, começando do fim até o início
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    // Para cada vértice no caminho, imprime o nome do vértice original
    for (int i = 0; i < path.size(); i++) {
        int originalIndex;

        // Se for o primeiro ou último nó, imprime diretamente
        if (i == path.size() - 1 || i == 0) {
            originalIndex = path[i];  // Imprime o índice final ou inicial
        } else {
            // Caso seja um nó intermediário, calcula o índice original
            originalIndex = (path[i] - 1) % D + 1;  // Mapeia de volta para 1 a D
        }

        // Imprime o nome do vértice original (indexado por originalIndex)
        out << vertexIndices[originalIndex] << " (" << originalIndex << ")";

        // Imprime o separador se não for o último vértice
        if (i < path.size() - 1) {
            out << " -> ";
        }
    }
    out << endl;
}


void clearData(int T) {
  for (int i = 0; i < T; ++i) {
    graph[i].clear();
  }
  vertexIndices.clear();
}

int main() {
  ifstream in("in");
  ofstream out("out");

  if (!in.is_open() || !out.is_open()) {
    cerr << "Erro ao abrir arquivos." << endl;
    return 1;
  }

  int V, D, start, T, a, b, n, C;
  string s, c;
  in >> n; // número de testes
  FOR(i, n) {
    start = 0;
    in >> D; // número de vértices
    in >> s; // string que quer ler
    V = s.size();
    T = D * V + 2;
    int dist[T], prev[T];

    addVertice(0, "I"); // início
    for (int i = 1; i <= D; i++) {
      in >> c;
      addVertice(i, c);
      if (vertexIndices[i][0] == s[0])
        addAresta(0, i, 0);
      else
        addAresta(0, i, 1);
      addAresta(i + D * V - D, T - 1, 0);
    }
    addVertice(T - 1, "F"); // fim

    in >> C; // número de conexões
    FOR(i, C) {
      in >> a >> b;
      FOR(i, V - 1) {
        if (vertexIndices[b][0] == s[i + 1]) {
          addAresta(a + i * D, b + (i + 1) * D, 0);
        } else {
          addAresta(a + i * D, b + (i + 1) * D, 1);
        }
      }
    }
    //printGrafo(D+1, out);
    Dijkstra(T, dist, prev, start);

    out << "Caminho: ";
    printPath(prev, start, T - 1, D, out);
    out << " Custo: " << dist[T - 1] << endl;

    clearData(T);
  }

  in.close();
  out.close();

  return 0;
}
