#include<queue>
#include<iostream>
using namespace std;

int cnt = 0;

struct Item{
	float weight;
	int value;
};

struct Node{
	int level, profit, bound;
	float weight;
};

bool cmp(Item a, Item b){
	double r1 = (double)a.value / a.weight;
	double r2 = (double)b.value / b.weight;
	return r1 > r2;
}


int bound(Node u, int n, int W, Item arr[]){
	if (u.weight >= W)
		return 0; 

	int profit_bound = u.profit; 

	int j = u.level + 1;
	int totweight = u.weight;

	while ((j < n) && (totweight + arr[j].weight <= W)){ 
		totweight += arr[j].weight; 
		profit_bound += arr[j].value;
		j++;
	}

	if (j < n) 
		profit_bound += (W - totweight) * arr[j].value / arr[j].weight; //넘어간 index = n = j = k

	return profit_bound; 
}


int knapsack(int W, Item arr[], int n){ 
	sort(arr, arr + n, cmp);

	queue<Node> Q;
	Node u, v;

	u.level = -1; 
	u.profit = u.weight = 0;
	u.bound = bound(u, n, W, arr);;
	Q.push(u);
	cout << "level\tprofit\tbound\n";
	cout << u.level + 1 << "\t" << u.profit << "\t" << u.bound << "\n";
	cnt++;

	int maxProfit = 0;

	while (!Q.empty()){
		u = Q.front();
		Q.pop();

		if (u.level == -1) //맨 처음 시작 이라면
			v.level = 0; //v level 은 0 부터 시작(맨처음)

		if (u.level == n - 1) //u가 끝까지내려 왔다면 끝
			continue;

		v.level = u.level + 1; // 맨 처음시 v.level = 0
		
		/*집어 넣은 경우*/
		v.weight = u.weight + arr[v.level].weight; //v.weight와 v.profit에 각 level의 맞는값을 더한 걸 저장
		v.profit = u.profit + arr[v.level].value;

		if (v.weight <= W && v.profit > maxProfit) //첫번째 promising function +a(?)
			maxProfit = v.profit; //만족하는 경우 maxprofit은 현재 계산중인 노드의 profit

		v.bound = bound(v, n, W, arr); //현재 계산중인 노드의 bound 계산
		if (v.bound > maxProfit) { //2번째 promising function을 만족하는 경우
			Q.push(v);
		}
		cout << v.level+1 << "\t" <<v.profit << "\t"<<v.bound << "\n";
		cnt++;
		
		/*안집어 넣은 경우*/ 
		v.weight = u.weight;
		v.profit = u.profit;
		v.bound = bound(v, n, W, arr);
		if (v.bound > maxProfit) {
			Q.push(v);
		}

		cout << v.level + 1 << "\t" << v.profit << "\t" << v.bound << "\n";
		cnt++;
	}

	return maxProfit;
}

int main(){
	int W = 16;   // Weight of knapsack 
	Item arr[] = { { 2, 40 },{ 5, 30 },{ 10, 50 },{ 5, 10 } };
	//Item arr[] = { { 2, 20 },{ 5, 30 },{ 7, 35 },{ 3, 12 },{1,3} };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << "\nMaximum possible profit = " << knapsack(W, arr, n);

	cout << "\ncnt = " << cnt << "\n";
	
	return 0;
}