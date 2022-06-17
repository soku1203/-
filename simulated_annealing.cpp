#include <bits/stdc++.h>
#include <random>

using namespace std;
int n;
int coin[40][40]; // coin 의 상태

void turn(int x, int y) { // 코인을 뒤집는 함수
	if (y == 0) {
		for (int i = 0; i < n; i++)
			coin[x][i] = 1 - coin[x][i];
	}
	else {
		for (int i = 0; i < n; i++)
			coin[i][x] = 1 - coin[i][x];
	}
}

void func() {
	for (int i = 0; i < n; i++) {
		int s = 0;
		for (int j = 0; j < n; j++)
			s += coin[j][i];
		if (s > (n / 2)) turn(i, 1);
	}
}

int scoring() { // 현재 상태의 뒤집어져 있는 코인의 개수 return
	int s = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			s += coin[i][j];
	return s;
}

double t = 1, d = 0.9999, k = 10, lim = 0.09; // t는 온도, d 는 온도의 변화율, lim은 온도의 한계값이다.
std::mt19937_64 seed(9999);
std::uniform_real_distribution<double> rng(0, 1); // 0에서 1사이의 랜덤 double 값을 얻는 함수다.

int ret = 999;

void simulated_annealing() {
	double e1, e2;
	int ori[40][40];
	while (t > lim) {
		e1 = scoring();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				ori[i][j] = coin[i][j];// 이동전 값을 저장
		int pos = rand() % n; // n 미만의 랜덤값을 pos 에 지정
		turn(pos, 0); // 랜덤 pos 뒤집기
		func();
		e2 = scoring(); // 뒤집은 후 뒤집에져 있는 코인의 개수 e2에 저장
		if (e1 > e2)
		{
			ret = min(ret, (int)e2);
		}
		else
		{
			double p = exp((e1 - e2) / t); // 확률함수
			if (p < rng(seed)) // 확률적으로 코인의 상태를 기존으로 돌림
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++)
						coin[i][j] = ori[i][j];
		}
		t *= d;// 온도가 낮아짐
		if (ret == 0)
			break;
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			char ch;
			scanf(" %c", &ch);
			coin[i][j] = (ch == 'H' ? 0 : 1); // 코인의 초기 상태 입력
		}
	}
	simulated_annealing();
	printf("%d", ret); // 모의 담금질 후 구한 최솟값을 출력
	return 0;
}