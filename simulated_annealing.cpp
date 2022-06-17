#include <iostream>
#include <random>

using namespace std;
int n;
int grid[40][40];
int pos;
void turn(int x, int y) {
	if (y == 0) {
		for (int i = 0; i < n; i++)
			grid[x][i] = 1 - grid[x][i];
	}
	else {
		for (int i = 0; i < n; i++)
			grid[i][x] = 1 - grid[i][x];
	}
}

void func() {
	for (int i = 0; i < n; i++) {
		int s = 0;
		for (int j = 0; j < n; j++)
			s += grid[j][i];
		if (s > (n / 2)) turn(i, 1);
	}
}

double scoring() {
	double s = pow(pos, 2) -8504 * pos+ 18079531.2;
	return s;
}

double t = 1, d = 0.9999, lim = 0.0005;
std::mt19937_64 seed(1919);
std::uniform_real_distribution<double> rng1(0, 1);

double ret = 0;
double cald(double t)
{
	if (t > 0)
		return -t;
	else
		return t;
}
double rd(double val) // 양수인지 음수인지 랜덤으로 결정
{
	int t = rand() % 2;
	return (t == 0) ? val : -val;
}
void simulated_annealing() {
	double e1, e2;
	while (t > lim) {
		e1 = scoring(); // 현재 위치에서의 함숫값
		double val = rd(rng1(seed));
		pos += val;
		e2 = scoring(); // 나중 위치에서의 함숫값
		double p = exp(cald(e2 - e1) / t); // p는 확률이다. 
		if (p < rng1(seed))
		{
			pos -= val;
		}
		t *= d;
		ret = max(ret, scoring());
	}
}

int main() {
	pos = rand() % 8000;
	simulated_annealing();
	cout << ret;
	return 0;
}