#ifndef SEGMENT_H
#define SEGMENT_H

// c++ libraries
#include <vector>
#include <armadillo>
// my libraries


// namespasec
using namespace std;
using namespace arma;




class Segment
{
  public:
  int id_x;
  int id_y;
  double dist;


  Segment(int x, int y, double d)
  {
    this->id_x = x;
    this->id_y = y;
    dist = d;
  }


  //void der_energy(vec&, vec&);

  //bool operator==(const Segment& rhs) const;
  //void print();
  //friend ostream& operator<<(ostream& os, const Segment& obj);

  Segment& operator= (const Segment& obj)
	{
		this->id_x = obj.id_x;
		this->id_y = obj.id_y;
    return *this;
	}

};

#endif
