#ifndef ENGIN_H
#define ENGIN_H

#include <set>
#include <iostream>
#include <stdio.h>
#include <armadillo>
#include <bits/stdc++.h>
#include <cmath>

#include "Particle.h"
#include "Segment.h"
#include "Face.h"
#include "Body.h"


using namespace std;
using namespace arma;


namespace ENG{
	class Engin
	{
		public:
		void init(Body&);
		double calculate_energy(const vec&, const vector<Segment>&);
		vec calculate_der(const vec&, const vector<Segment>&, const vector<int>&);
		private:
		vector<bool> fixed;
	};
}
#endif
