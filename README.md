# 최적화 알고리즘을 이용한 회귀식 추정

## Simulated Annealing (모의 담금질 기법)

>모의 담금질 기법은 액체 상태의 물질이 온도가 점차 낮아지면서 결정채로 변화는 과정에서의 물질의 분자의 상태를 모방한 해 탐색 알고리즘으로, 물질의 분자는 온도가 높은 상태에서는 비교적으로 자유로운 상태인 반면 온도가 낮아질수록 자유도는 낮아지게 되며 결국 결정채를 이루게 된다. 모의 담금질 기법 또한 초기값에서는 이웃해 중 최적해와 가깝지 않은 방향으로의 이동(현재 해보다 나쁜 방향으로의 이동)하는 자유로움을 보이다가 점차 자유도가 낮아지며 최적해에 가까운 방향으로의 이동만 보이게 된다. 그러나 모의 담금질 기법은 어느 최적해 탐색 알고리즘과 마찬가지로 항상 전역(Global) 최적해를 찾아준다는 보장은 없다.  

### Simulated Annealing에 대한 이해

>담금질 기법의 설명만으로는 작동 과정에 대한 이해가 쉽지 않았다. Simulated Annealing에 대한 이해를 위해 작동 방식을 따라가 보았다.

#### 1. 가능한 해의 후보를 구한다.

Simulated Annealing은 최적해를 찾기 위해서 최적해에 가까울 것 같은 현재값에 인접해 있는 일부 지역을 탐색하여 해의 후보를 구하게 된다. 
이를 위해서는 인접 상태에 대해 정의해 주어야 하는데, 이때 인접상태를 너무 크게 잡거나 현재값으로 부터 너무 많이 변하게 되면 결국 최적점으로의 도달이 너무 오래 걸리기 때문에 결국 국소적인 공간을 잡아야 한다. 

#### 2. 후보해를 평가한다.





