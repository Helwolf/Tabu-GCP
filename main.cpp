#include "Gcp.h"
#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    Gcp test;
    test.readGraph("instance/DSJC125.1.col");
    test.setParameter(1, 11, 50000000);
    test.K = 5;
    test.TabuSearch();
    return 0;
}
