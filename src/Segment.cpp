#include "../include/Segment.h"
#include <armadillo>
#include <iostream>

using namespace std;
using namespace arma;
/*{
  if(approx_equal(x->pos, s2.x->pos, "absdiff", 0.001) && approx_equal(y->pos, s2.y->pos, "absdiff", 0.001))
    return true;
  if(approx_equal(x->pos, s2.y->pos, "absdiff", 0.001) && approx_equal(y->pos, s2.x->pos, "absdiff", 0.001))
    return true;
  return false;
}

ostream& operator<<(ostream& os, const Segment& obj)
{
  os<<"The x side of the segment is:"<<endl<<*obj.x<<endl;
  os<<"The y side of the segment is:"<<endl<<*obj.y<<endl;
  return os;
}

void Segment::der_energy(vec& d_x, vec& d_y)
{
  d_x = 2 * (x->pos - y->pos);
  d_y = 2 * (y->pos - x->pos);
}*/
