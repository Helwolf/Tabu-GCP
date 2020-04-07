#ifndef GCP_H
#define GCP_H

struct Move
{
  int u;
  int i;
  int j;
  int delt;
};

class Gcp
{
public:
  Gcp();
  virtual ~Gcp();
  void readGraph(const char *filename);
  int K;

  //Tabu Search
  void Init();
  void date_Init();
  Move FindMove();
  void Update_ACTable(int a, int vi, int vj);
  void SetMove(Move *move, int u, int i, int j, int delt);
  void MakeMove(Move a);
  void TabuSearch();
  void setParameter(float alpha, int A, int m_max);

protected:
private:
  static const int MAX = 1001;
  static const int MK = 150;
  static const int INF = 0xffff;

  int Sol[MAX];
  bool **graph;
  int **Table;
  int **ACTable;
  int *degree;
  int iter, f, MaxIter;
  int n, edgeNum;
  int bestf;
  float alpha;
  int A, m, m_max;
};

#endif // GCP_H
