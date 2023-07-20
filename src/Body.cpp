// openGL libraries
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

// my libraries
#include "../include/Body.h"

// c++ libraries
#include <vector>
#include <random>


// namespaces
using namespace std;
using namespace arma;

void Body::init()
{
  load_from_file();


}

void Body::move_randomly()
{
  for(int i=0;i<N_points;i++)
  {
    if(fixed[i]==0)
    {
      vec ran = arma::randu(3)-0.5;
      state.subvec(3*i,3*i+2)+=ran;
    }
  }
}

void Body::apply_force_1()
{
  vec n(3);
  n(0)=1;
  n(1)=0;
  n(2)=1;
  for(int i=0;i<N_points;i++)
  {
    if(fixed[i]==0)
    {
      n = state.subvec(3*i,3*i+2);
      n(1)=0;
      vec f = n / norm(n);
      state.subvec(3*i,3*i+2)+=f;
    }
  }
}
void Body::apply_force_2()
{
  vec n(3);
  n(0)=1;
  n(1)=0;
  n(2)=1;
  for(int i=0;i<N_points;i++)
  {
    if(fixed[i]==0)
    {
      n = state.subvec(3*i,3*i+2);
      n(1)=0;
      n(0) = -n(0);
      vec f = n / norm(n);
      state.subvec(3*i,3*i+2)+=f;
    }
  }
}
void Body::apply_force_3()
{
  vec c(3, fill::zeros);
  for(int i=0;i<N_points;i++)
  {
    c+=state.subvec(3*i,3*i+2);
  }
  c = c / N_points;
  cout<<endl<<c<<endl;
  for(int i=0;i<N_points;i++)
  {
    //if(fixed[i]==0)
    //{
    vec n = state.subvec(3*i,3*i+2) - c;
    vec f = n / norm(n);
    state.subvec(3*i,3*i+2)+=f;
    //}
  }
}
double Body::calculate_energy()
{
  /*double energy = 0;
  for(auto itr = segments.begin(); itr != segments.end(); itr++)
  {
    energy += itr->local_energy(state);
  }
  return energy;*/
}

void Body::calculate_der()
{
  /*for(auto itr = segments.begin(); itr != segments.end(); itr++)
  {
    vec d_x, d_y;
    vec Z(3, fill::zeros);
    itr->der_energy(d_x, d_y);
    cout<<"this is important"<<endl<<d_x<<endl;
    if(points[itr->id_x]->fixed)
      der.subvec(itr->id_x * 3, itr->id_x * 3 + 2) = Z;
    else
      der.subvec(itr->id_x * 3, itr->id_x * 3 + 2) = d_x;

    if(points[itr->id_y]->fixed)
      der.subvec(itr->id_y * 3, itr->id_y * 3 + 2) = Z;
    else
      der.subvec(itr->id_y * 3, itr->id_y * 3 + 2) = d_y;
  }*/
}
//==============================================================================

void Body::load_from_file()
{
  string load_out;
  ifstream reader("Generator/constraints_gen_mob.txt");
  cout<<"the load has started"<<endl;
  reader>>load_out;
  reader>>N_points;
  cout<<load_out<<N_points<<endl;
  reader>>load_out;
  reader>>N_constraints;
  cout<<load_out<<N_constraints<<endl;


  state = vec(3 * N_points, fill::zeros);
  vec Z(3, fill::zeros);
  fixed.resize(N_points);
  for(int i=0; i< N_constraints; i++)
  {
    int x, y;
    double d;
    int f;
    reader>> x >> y >> d;
    Segment temp(x, y, d);
    segments.push_back(temp);
  }
  cout<<"the fisrt part is done"<<endl;
  reader>>load_out;
  for(int i=0; i < N_points; i++)
  {
    double x, y, z, f;
    reader>>x>>y>>z>>f;
    vec p(3, fill::zeros);
    p(0) = x;
    p(1) = y;
    p(2) = z;
    fixed[i] = f;

    state.subvec(3 * i, 3 * i +2) = p;
  }
  cout<<"the second part is done"<<endl;
  reader.close();
}

double Body::generateRandomNumber(double x)
{
    // Set up random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0, x);

    // Generate a random number between 0 and x
    double randomNumber = dis(gen);
    return randomNumber;
}

void Body::mob_generator()
{
  //w = 4;
  //l = 40;
  w = 7;
  l = 28;
  double w_u = 0.3*2;
  double l_u = 0.4*2;
  double d_u = 0.5*2;
  ofstream writer("Generator/constraints_gen_mob.txt");
  writer<<"NUMBER_OF_POINTS: "<<w*l<<endl;
  writer<<"NUMBER_OF_CONSTRAINTS: "<<w-1 + ((w-2)*4 + 5) * (l-1) + 1 + (w-1) * 3 + l*(w)*(w-1)/2<<endl;
  for(int j=0;j<=w-2;j++)
  {
    int i=0;
    writer<<(i)*w+(j)<<" "<<(i)*w+(j+1)<<" "<<w_u<<endl;
    writer<<(i)*w+(j)<<" "<<(i+1)*w+(j)<<" "<<l_u<<endl;
    writer<<(i)*w+(j)<<" "<<(i+1)*w+(j+1)<<" "<<d_u<<endl;
  }
  writer<<(0)*w+(w-1)<<" "<<(1)*w+(w-1)<<" "<<l_u<<endl;
  for(int i=1;i<l-1;i++)
  {

    //writer<<(i)*w+(j)<<" "<<(i)*w+(j+1)<<" "<<w_u<<endl;
    //writer<<(i+1)*w+(j)<<" "<<(i+1)*w+(j)<<" "<<l_u<<endl;
    //writer<<(i+1)*w+(j+1)<<" "<<(i+1)*w+(j+1)<<" "<<d_u<<endl;
    for(int j=0;j<=w-2;j++)
    {
      writer<<(i)*w+(j)<<" "<<(i-1)*w+(j+1)<<" "<<d_u<<endl;
      writer<<(i)*w+(j)<<" "<<(i)*w+(j+1)<<" "<<w_u<<endl;
      writer<<(i)*w+(j)<<" "<<(i+1)*w+(j)<<" "<<l_u<<endl;
      writer<<(i)*w+(j)<<" "<<(i+1)*w+(j+1)<<" "<<d_u<<endl;
    }
    writer<<(i)*w+(w-1)<<" "<<(i+1)*w+(w-1)<<" "<<l_u<<endl;
  }
  for(int j=0;j<=w-2;j++)
  {
    int i=l-1;
    writer<<(i)*w+(j)<<" "<<(i)*w+(j+1)<<" "<<w_u<<endl;
    writer<<(i)*w+(j)<<" "<<(i-1)*w+(j+1)<<" "<<w_u<<endl;
  }
  writer<<(0)*w+(0)<<" "<<(l-1)*w+(w-1 -0)<<" "<<l_u<<endl;
  writer<<(0)*w+(0)<<" "<<(l-1)*w+(w-1 -1)<<" "<<d_u<<endl;

  writer<<(0)*w+(w-1)<<" "<<(l-1)*w+(w-1 - w +1)<<" "<<l_u<<endl;
  writer<<(0)*w+(w-1)<<" "<<(l-1)*w+(w-1 - (w-2) )<<" "<<d_u<<endl;
  for(int j=1;j<w-1;j++)
  {
    writer<<(0)*w+(j)<<" "<<(l-1)*w+(w-1 -j)<<" "<<l_u<<endl;
    writer<<(0)*w+(j)<<" "<<(l-1)*w+(w-1 -(j+1))<<" "<<d_u<<endl;
    writer<<(0)*w+(j)<<" "<<(l-1)*w+(w-1 -(j-1))<<" "<<d_u<<endl;
  }
  for(int i=0;i<l;i++)
  {
    for(int j=0;j<w;j++)
    {
      for(int k=j+1;k<w;k++)
      {
        writer<<(i)*w+(j)<<" "<<(i)*w+(k)<<" "<<(k-j)*3<<endl;
      }
    }
  }
  writer<<"END_CONSTRAINTS_STARTING_POINTS"<<endl;\
  /*for(int j=0;j<w;j++)
  {
    writer<<0+2<<" "<<j+2<<" "<<2<<" "<<1<<endl;
  }*/
  for(int i=0;i<l;i++)
  {
    for(int j=0;j<w;j++)
    {
      writer<<generateRandomNumber(10)<<" "<<generateRandomNumber(10)<<" "<<generateRandomNumber(10)<<" "<<0<<endl;
    }
  }
  writer.close();
}

void Body::band_generator()
{
  int w = 5, l = 500*2;
  double w_u = 3;
  double l_u = 4;
  double d_u = 5;
  ofstream writer("Generator/constraints_gen.txt");
  writer<<"NUMBER_OF_POINTS: "<<w*l<<endl;
  writer<<"NUMBER_OF_CONSTRAINTS: "<<w-1 + ((w-2)*4 + 5) * (l-1)<<endl;
  for(int j=0;j<=w-2;j++)
  {
    int i=0;
    writer<<(i)*w+(j)<<" "<<(i)*w+(j+1)<<" "<<w_u<<endl;
    writer<<(i)*w+(j)<<" "<<(i+1)*w+(j)<<" "<<l_u<<endl;
    writer<<(i)*w+(j)<<" "<<(i+1)*w+(j+1)<<" "<<d_u<<endl;
  }
  writer<<(0)*w+(w-1)<<" "<<(1)*w+(w-1)<<" "<<l_u<<endl;
  for(int i=1;i<l-1;i++)
  {

    //writer<<(i)*w+(j)<<" "<<(i)*w+(j+1)<<" "<<w_u<<endl;
    //writer<<(i+1)*w+(j)<<" "<<(i+1)*w+(j)<<" "<<l_u<<endl;
    //writer<<(i+1)*w+(j+1)<<" "<<(i+1)*w+(j+1)<<" "<<d_u<<endl;
    for(int j=0;j<=w-2;j++)
    {
      writer<<(i)*w+(j)<<" "<<(i-1)*w+(j+1)<<" "<<d_u<<endl;
      writer<<(i)*w+(j)<<" "<<(i)*w+(j+1)<<" "<<w_u<<endl;
      writer<<(i)*w+(j)<<" "<<(i+1)*w+(j)<<" "<<l_u<<endl;
      writer<<(i)*w+(j)<<" "<<(i+1)*w+(j+1)<<" "<<d_u<<endl;
    }
    writer<<(i)*w+(w-1)<<" "<<(i+1)*w+(w-1)<<" "<<l_u<<endl;
  }
  for(int j=0;j<=w-2;j++)
  {
    int i=l-1;
    writer<<(i)*w+(j)<<" "<<(i)*w+(j+1)<<" "<<w_u<<endl;
    writer<<(i)*w+(j)<<" "<<(i-1)*w+(j+1)<<" "<<w_u<<endl;
  }
  writer<<"END_CONSTRAINTS_STARTING_POINTS"<<endl;
  for(int i=0;i<l;i++)
  {
    for(int j=0;j<w;j++)
    {
      writer<<i+2<<" "<<j+2<<" "<<2<<" "<<0<<endl;
    }
  }
  writer.close();
}

void Body::draw_body()
{
  glColor3ub(255, 255, 255);
  for(auto itr = segments.begin(); itr != segments.end(); itr++)
  {
    vec p1 = state.subvec(3*itr->id_x, 3*itr->id_x+2);
    vec p2 = state.subvec(3*itr->id_y, 3*itr->id_y+2);
    glColor3ub(255, 255, 255);
    //glPointSize(5);
    glBegin(GL_POINTS);
    glVertex3f(p1(0), p1(1), p1(2));
    glEnd();
    glBegin(GL_POINTS);
    glVertex3f(p2(0), p2(1), p2(2));
    glEnd();
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex3f(p1(0), p1(1), p1(2));
    glVertex3f(p2(0), p2(1), p2(2));
    glEnd();
  }
  /*for(int i=0;i<N_points;i++)
  {
    int x =
  }*/
  /*glPointSize(5);
  int r = 1;
  auto itr = points.begin();
  glBegin(GL_POINTS);
  glVertex3f((*itr)->pos[0], (*itr)->pos[1], (*itr)->pos[2]);
  glEnd();
  itr++;
  for(; itr != points.end(); itr++)
  {
    //cout<<itr->pos_show<<endl;
    glColor3ub(((r+1)*15)%255, ((r+2)*100)%255, (r+100)%255);
    glBegin(GL_POINTS);
    glVertex3f((*itr)->pos[0], (*itr)->pos[1], (*itr)->pos[2]);
    glEnd();
    r+=10;
  }*/
  /*for(long unsigned int i=0; i<faces.size(); i++)
  {
    //glColor3ub(150, 150, 150);
    glColor3ub(0, 255, 0);
    glBegin(GL_POINTS);
    glVertex3f(this->faces[i].C[0], this->faces[i].C[1], this->faces[i].C[2]);
    glEnd();
    glColor3ub(0, 0, 255);
    glBegin(GL_POINTS);
    glVertex3f(this->faces[i].c[0], this->faces[i].c[1], this->faces[i].c[2]);
    glEnd();
  }
  for(long unsigned int i=0; i<segments.size(); i++)
  {
    //glColor3ub(150, 150, 150);
    if(abs(this->segments[i].x->pos_0[1])<1 || abs(this->segments[i].y->pos_0[1])<1)
      glColor3ub(255, 0, 0);
    else
      glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex3f(this->segments[i].x->pos[0], this->segments[i].x->pos[1], this->segments[i].x->pos[2]);
    glVertex3f(this->segments[i].y->pos[0], this->segments[i].y->pos[1], this->segments[i].y->pos[2]);
    glEnd();
  }*/

}

Body& Body::operator= (const Body& obj)
{
  //this->points = obj.points;
  //this->segments = obj.segments;
  //this->faces = obj.faces;

  return *this;
}

void Body::save_to_file()
{
  ofstream writer("Generator/mob_saved_2.txt");
  writer<<w * l<<endl;
  int n_points = w*l;
  for(int i=0; i<n_points;i++)
  {
    vec p = state.subvec(3*i, 3*i+2);
    writer<<i<<" "<<p(0)<<" "<<p(1)<<" "<<p(2)<<endl;
  }
  //writer<< w-1 + ((w-2)*4 + 5) * (l-1) <<endl;
  vector<Segment> sg;
  for(int j=0;j<=w-2;j++)
  {
    int i=0;
    /*writer<<(i)*w+(j)<<" "<<(i)*w+(j+1)<<endl;
    writer<<(i)*w+(j)<<" "<<(i+1)*w+(j)<<endl;
    writer<<(i)*w+(j)<<" "<<(i+1)*w+(j+1)<<endl;*/

    Segment temp0((i)*w+(j), (i)*w+(j+1), 0);
    Segment temp1((i)*w+(j), (i+1)*w+(j), 0);
    Segment temp2((i)*w+(j), (i+1)*w+(j+1), 0);
    sg.push_back(temp0);
    sg.push_back(temp1);
    sg.push_back(temp2);
  }
  //writer<<(0)*w+(w-1)<<" "<<(1)*w+(w-1)<<endl;
  Segment t0((0)*w+(w-1), (1)*w+(w-1), 0);
  sg.push_back(t0);
  for(int i=1;i<l-1;i++)
  {
    for(int j=0;j<=w-2;j++)
    {
      /*writer<<(i)*w+(j)<<" "<<(i-1)*w+(j+1)<<endl;
      writer<<(i)*w+(j)<<" "<<(i)*w+(j+1)<<endl;
      writer<<(i)*w+(j)<<" "<<(i+1)*w+(j)<<endl;
      writer<<(i)*w+(j)<<" "<<(i+1)*w+(j+1)<<endl;*/

      Segment temp0((i)*w+(j), (i-1)*w+(j+1), 0);
      Segment temp1((i)*w+(j), (i)*w+(j+1), 0);
      Segment temp2((i)*w+(j), (i+1)*w+(j), 0);
      Segment temp3((i)*w+(j), (i+1)*w+(j+1), 0);
      sg.push_back(temp0);
      sg.push_back(temp1);
      sg.push_back(temp2);
      sg.push_back(temp3);
    }
    /*writer<<(i)*w+(w-1)<<" "<<(i+1)*w+(w-1)<<endl;*/

    Segment tm0((i)*w+(w-1), (i+1)*w+(w-1), 0);
    sg.push_back(tm0);
  }
  for(int j=0;j<=w-2;j++)
  {
    int i=l-1;
    /*writer<<(i)*w+(j)<<" "<<(i)*w+(j+1)<<endl;
    writer<<(i)*w+(j)<<" "<<(i-1)*w+(j+1)<<endl;*/

    Segment temp0((i)*w+(j), (i)*w+(j+1), 0);
    Segment temp1((i)*w+(j), (i-1)*w+(j+1), 0);
    sg.push_back(temp0);
    sg.push_back(temp1);
  }
  /*writer<<(0)*w+(0)<<" "<<(l-1)*w+(w-1 -0)<<endl;
  writer<<(0)*w+(0)<<" "<<(l-1)*w+(w-1 -1)<<endl;*/

  Segment t1((0)*w+(0), (l-1)*w+(w-1), 0);
  Segment t2((0)*w+(0), (l-1)*w+(w-1 - 1), 0);
  sg.push_back(t1);
  sg.push_back(t2);

  /*writer<<(0)*w+(w-1)<<" "<<(l-1)*w+(w-1 - w +1)<<endl;
  writer<<(0)*w+(w-1)<<" "<<(l-1)*w+(w-1 - (w-2) )<<endl;*/

  Segment t3((0)*w+(w-1), (l-1)*w+(w-1 - w +1), 0);
  Segment t4((0)*w+(w-1), (l-1)*w+(w-1 - w +2), 0);
  sg.push_back(t3);
  sg.push_back(t4);
  for(int j=1;j<w-1;j++)
  {
    /*writer<<(0)*w+(j)<<" "<<(l-1)*w+(w-1 -j)<<endl;
    writer<<(0)*w+(j)<<" "<<(l-1)*w+(w-1 -(j+1))<<endl;
    writer<<(0)*w+(j)<<" "<<(l-1)*w+(w-1 -(j-1))<<endl;*/


    Segment temp0((0)*w+(j), (l-1)*w+(w-1 -j), 0);
    Segment temp1((0)*w+(j), (l-1)*w+(w-1 -(j+1)), 0);
    Segment temp2((0)*w+(j), (l-1)*w+(w-1 -(j-1)), 0);
    sg.push_back(temp0);
    sg.push_back(temp1);
    sg.push_back(temp2);
  }

  writer<<sg.size()<<endl;
  for(auto itr = sg.begin(); itr != sg.end(); itr++)
  {
      writer<<(itr)->id_x<<" "<<(itr)->id_y<<endl;
  }

  vector<Face> fc;

  for(int i=0; i<l-1; i++)
  {
    for(int j=0; j<w-1; j++)
    {
      Face temp0((i)*w+(j), (i+1)*w+(j), (i+1)*w+(j+1));
      Face temp1((i)*w+(j), (i)*w+(j+1), (i+1)*w+(j+1));
      fc.push_back(temp0);
      fc.push_back(temp1);
    }
  }
  for(int j=0; j<w-1; j++)
  {
    int i = l-1;
    Face temp0((i)*w+(j), (0)*w+(w-1 - j), (0)*w+(w-1 - (j+1)));
    Face temp1((i)*w+(j), (i)*w+(j+1), (0)*w+(w-1 -(j+1) ) );
    fc.push_back(temp0);
    fc.push_back(temp1);
  }
  writer<<fc.size()<<endl;
  for(auto itr = fc.begin(); itr != fc.end(); itr++)
  {
      writer<<(itr)->id_x<<" "<<(itr)->id_y<<" "<<(itr)->id_z<<endl;
  }
  writer.close();
}
