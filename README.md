# 최적화 알고리즘을 이용한 회귀식 추정

## Simulated Annealing (모의 담금질 기법)

>모의 담금질 기법은 액체 상태의 물질이 온도가 점차 낮아지면서 결정채로 변화는 과정에서의 물질의 분자의 상태를 모방한 해 탐색 알고리즘으로, 물질의 분자는 온도가 높은 상태에서는 비교적으로 자유로운 상태인 반면 온도가 낮아질수록 자유도는 낮아지게 되며 결국 결정채를 이루게 된다. 모의 담금질 기법 또한 초기값에서는 이웃해 중 최적해와 가깝지 않은 방향으로의 이동(현재 해보다 나쁜 방향으로의 이동)하는 자유로움을 보이다가 점차 자유도가 낮아지며 최적해에 가까운 방향으로의 이동만 보이게 된다. 그러나 모의 담금질 기법은 어느 최적해 탐색 알고리즘과 마찬가지로 항상 전역(Global) 최적해를 찾아준다는 보장은 없다.  

### Simulated Annealing에 대한 이해

>담금질 기법의 설명만으로는 작동 과정에 대한 이해가 쉽지 않았다. Simulated Annealing에 대한 이해를 위해 작동 방식을 따라가 보았다.

#### 1. 가능한 해의 후보를 구한다.

Simulated Annealing은 최적해를 찾기 위해서 최적해에 가까울 것 같은 현재값에 인접해 있는 일부 지역을 탐색하여 해의 후보를 구하게 된다. 
이를 위해서는 인접 상태에 대해 정의해 주어야 하는데, 이때 인접상태를 너무 크게 잡거나 현재값으로 부터 너무 많이 변하게 되면 결국 최적점으로의 도달이 너무 오래 걸리기 때문에 결국 국소적인 공간을 잡아야 한다. 

#### 2. 후보해를 평가한다.

현재 값에 대한 후보해들을 구했으면 그 후보해들이 얼마나 최적해에 가까운지에 대한 평가가 필요하고, 이를 위해 평가함수를 정의해 주어야 한다. 일반적으로 최소화 또는 최대화 하고 싶은 그 값이 평가함수가 되지만 제약 조건을 만족시키며 최적화 시켜야 한다면 이를 만족하도록 평가함수를 만들어야 한다.

#### 3. 이동시킨다.

평가 함수가 정의 되었으면, 이 후보해들의 등장 확률에 따라 이동확률이 결정되게 된다. 0~1에서 랜덤하게 선택한 수 q와 확률 p를 비교하여 p보다 작으면 이동시킨다.

#### 4. 온도의 감소

모의 담금질 기법의 핵심은 바로 온도 감소에 있다. 모의 담금질 기법은 온도 T가 높을 때부터 점차 낮아지는 것을 확률 p에 반영하여 온도가 낮아질 수록 탐색의 자유도를 낮춘다. 이로 인해 해 탐색은 점차 세밀한 탐색을 진행하게 된다.

```c++
임의의 후보해 S를 선택한다.
초기 T를 정한다.
repeat
    for i=1 to K{
        s의 이웃해 중에서 랜덤한 s`을 선택한다.
        d = s`-s
        if(d<0)
        {
            s=s`;
        } 
        else
        {
            q=rand(0~1);
            if(q<p)
                s=s`;
        }
    }
    T*= aT;
untile(종료조건 만족될 때 까지)
return s;
```

### 알고리즘의 구현1

[문제](https://www.acmicpc.net/problem/2582)
nxn 개의 행렬을 이루는 동전에 대하여 초기 상태가 주어진다. H는 앞면 T 는 뒤집어진 모양이고, 한 행 또는 한 열에 놓은 동전을 모두 뒤집는 작업을 수행할 때 뒤집어진 동전의 개수의 최솟값을 구하는 알고리즘을 구현했다.

```c++
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

double t = 1, d = 0.9999, lim = 0.09;
std::mt19937_64 seed(9999);
std::uniform_real_distribution<double> rng(0, 1);

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
```
### 알고리즘의 구현2

2021년도 월간 최저 기온에 대하여 모의 담금질 알고리즘을 통해 최고기온을 구해 보았다.
[날씨 데이터 출처](https://data.kma.go.kr/data/rmt/rmtList.do?code=420&pgmNo=572)


데이터에 대하여 matlab 프로그램을 이용하여 함수를 구하고 데이터에 대한 그래프의 모양을 그려보았다.
![월간 최저 기온](https://user-images.githubusercontent.com/98035175/174315740-b550225b-145a-479a-9589-337ff75e5f8a.png)
