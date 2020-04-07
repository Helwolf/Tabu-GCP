#ifndef INITFUNC_H
#define INITFUNC_H
#define MAX 1001

class InitFunc
{
public:
  InitFunc();
  InitFunc(int n, int k, int *Sol, bool **graph);
  virtual ~InitFunc();
  void DSATUR_Init(int *degree);
  void random_Init();

protected:
private:
  int n, k;
  int *Sol;
  bool **graph;

  //DASTUR
  bool **VCAvail;
  int *NAColors;
  int *VUDegree;

  void DSATUR_dataInit(int *degree);
  void DSATUR_datadel();
  void colorDot(int vi, int color);
};

#endif // INITFUNC_H
