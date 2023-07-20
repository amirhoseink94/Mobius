#ifndef BODY_H
#define BODY_H

#include <set>
#include <iostream>
#include <stdio.h>
#include <armadillo>
#include <bits/stdc++.h>

#include "Particle.h"
#include "Segment.h"
#include "Face.h"


using namespace std;
using namespace arma;



class Body
{
	public:
	// the state is the location of all points, the size is 3*N_of_points
	vec state;
	// the der is the derivitive of the potential function, again, its size is 3*N_of_points
	vec der;
	// in the segment we practically storing all the information about the constraints
	vector<Segment> segments;

	double energy;

	int N_points;
  int N_constraints;

	// this vector containts the information about if the point is fixed or not!
	vector<int> fixed;

	void init();

	void move_randomly();

	void calculate_der();

	void band_generator();
	void mob_generator();
	void apply_force_1();
	void apply_force_2();
	void apply_force_3();

	//============================================================================
	bool operator==(const Face& rhs) const;
	Body& operator= (const Body& obj);

	// drawing materials for now

	void draw_body();
	void print();
	//  Geometry
	void reshape();

	//private:

	double calculate_energy();
	Mat<double> PSPD(const Mat<double>&);

	// file handling
	void load_from_file();
	double generateRandomNumber(double x);

	void save_to_file();
private:
	int w;
	int l;


};

#endif
