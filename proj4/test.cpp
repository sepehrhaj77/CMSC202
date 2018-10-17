#include "Monster.h"
#include "Ben.h"
#include "Pyronite.h"
#include "Crystalsapien.h"
#include "Game.h"
using namespace std;

int main(){
  srand(time(NULL));
  Ben *b1 = new Crystalsapien("Sapien", 100, "energy", "laser", 0.25, 25, 0, 1, 25, 30, 10);
  delete b1;


  //  G.SetBen(100);


  return 0;
}
