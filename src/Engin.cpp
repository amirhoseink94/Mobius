// openGL libraries
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

// my libraries
#include "../include/Engin.h"

// c++ libraries
#include <vector>
#include <cmath>

// namespaces
using namespace std;
using namespace arma;

namespace ENG
{
  void Engin::init(Body& b)
  {

  }
  double Engin::calculate_energy(const vec& state,const vector<Segment>& con)
  {
    double energy = 0;
    for(auto itr = con.begin(); itr != con.end(); itr++)
    {
      vec x = state.subvec(3 * itr->id_x, 3* itr->id_x+2);
      vec y = state.subvec(3 * itr->id_y, 3* itr->id_y+2);
      double en = norm(y - x);
      double d = itr->dist;
      double t = (-d * d + en * en);
      if(t<0)
      {
        t = INFINITY;
      }
      energy += t;
    }

    return energy;
  }
  vec Engin::calculate_der(const vec& state,const vector<Segment>& con, const vector<int>& fixed)
  {
    vec der(state.size(), fill::zeros);
    //cout<<"the number of const: "<<con.size()<<endl;
    double e = calculate_energy(state, con);
    for(auto itr = con.begin(); itr != con.end(); itr++)
    {
      vec d_x, d_y;
      vec Z(3, fill::zeros);
      vec x = state.subvec(itr->id_x * 3, itr->id_x * 3 + 2);
      vec y = state.subvec(itr->id_y * 3, itr->id_y * 3 + 2);
      double s = (norm(x-y) - itr->dist)/ 16;
      d_x = s * (y - x)/norm(x-y);
      d_y = s * (x - y)/norm(y-x);

      /*if(e < 0)
      {
        d_x = -d_x;
        d_y = -d_y;

      }*/

      //cout<<"this is important"<<endl<<itr->id_x<<","<<itr->id_y<<endl<<d_x<<endl;
      if(fixed[itr->id_x] == 1)
        der.subvec(itr->id_x * 3, itr->id_x * 3 + 2) += Z;
      else
        der.subvec(itr->id_x * 3, itr->id_x * 3 + 2) += d_x;

      if(fixed[itr->id_y] == 1)
        der.subvec(itr->id_y * 3, itr->id_y * 3 + 2) += Z;
      else
        der.subvec(itr->id_y * 3, itr->id_y * 3 + 2) += d_y;
    }
    return der;
  }
}
