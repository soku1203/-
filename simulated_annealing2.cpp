#include <iostream>
#include <random>

using namespace std;
double pos;
double scoring() {
	double newpos = -0.8845 * pow(pos, 2) + 12.2868*pos - 22.3864;
	return newpos;
}

double t = 1, d = 0.9999, k = 10, lim = 0.09;
std::mt19937_64 seed(9999);
std::uniform_real_distribution<double> rng(0, 1);
std::uniform_real_distribution<double> rng2(0, 0.1);

double cdouble(double cur)
{
	int t = rand() % 2;
	if (t == 0)
	{
		return -cur;
	}
	else if (t == 1)
		return cur;
}
double ret = 0;
void simulated_annealing() {
	double e1, e2;
	int ori[40][40];
	while (t > lim) {
		e1 = scoring();
		double delval = rng2(seed);
		delval = cdouble(delval);
		pos += delval;
		e2 = scoring();
		double p = exp((e1 - e2) / (k * t));
		if (p < rng(seed))
			pos-= delval;
		t *= d;
		ret = max(ret, scoring());
	}
}

int main() {
	pos = rand() % 12;
	simulated_annealing();
	cout << ret;
	return 0;
}