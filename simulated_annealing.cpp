#include <bits/stdc++.h>
#include <random>

using namespace std;
int n;
int coin[40][40]; // coin �� ����

void turn(int x, int y) { // ������ ������ �Լ�
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

int scoring() { // ���� ������ �������� �ִ� ������ ���� return
	int s = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			s += coin[i][j];
	return s;
}

double t = 1, d = 0.9999, k = 10, lim = 0.09; // t�� �µ�, d �� �µ��� ��ȭ��, lim�� �µ��� �Ѱ谪�̴�.
std::mt19937_64 seed(9999);
std::uniform_real_distribution<double> rng(0, 1); // 0���� 1������ ���� double ���� ��� �Լ���.

int ret = 999;

void simulated_annealing() {
	double e1, e2;
	int ori[40][40];
	while (t > lim) {
		e1 = scoring();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				ori[i][j] = coin[i][j];// �̵��� ���� ����
		int pos = rand() % n; // n �̸��� �������� pos �� ����
		turn(pos, 0); // ���� pos ������
		func();
		e2 = scoring(); // ������ �� �������� �ִ� ������ ���� e2�� ����
		if (e1 > e2)
		{
			ret = min(ret, (int)e2);
		}
		else
		{
			double p = exp((e1 - e2) / t); // Ȯ���Լ�
			if (p < rng(seed)) // Ȯ�������� ������ ���¸� �������� ����
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++)
						coin[i][j] = ori[i][j];
		}
		t *= d;// �µ��� ������
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
			coin[i][j] = (ch == 'H' ? 0 : 1); // ������ �ʱ� ���� �Է�
		}
	}
	simulated_annealing();
	printf("%d", ret); // ���� ����� �� ���� �ּڰ��� ���
	return 0;
}