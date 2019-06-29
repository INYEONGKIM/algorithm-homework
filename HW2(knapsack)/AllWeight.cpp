#include<queue>
#include<iostream>
#include<cstdlib>
#include<ctime>

#define MAXSIZE 40
#define TRIAL 100

using namespace std;

int cnt = 0;

struct Item {
	float weight;
	int value;
};

struct Node {
	int level, profit, bound;
	float weight;
	bool isPromising;
};

/*내림차순 정렬*/
struct cmpPQ {
	bool operator()(const Node t, const Node u) {
		return t.profit < u.profit;
	}
};

bool cmp(Item a, Item b) {
	double r1 = (double)a.value / a.weight;
	double r2 = (double)b.value / b.weight;
	return r1 > r2;
}

int bound(Node u, int n, int W, Item arr[]) {
	int j;
	int totweight;
	int res;

	if (u.weight >= W) {
		return 0;
	}
	else {
		res = u.profit;
		j = u.level + 1;
		totweight = u.weight;

		while ((j < n) && (totweight + arr[j].weight <= W)) {
			totweight += arr[j].weight;
			res += arr[j].value;
			j++;
		}

		if (j < n) {
			res += (W - totweight)*arr[j].value / arr[j].weight;
		}

		return res;
	}
}

int knapsack(int W, Item arr[], int n) {
	sort(arr, arr + n, cmp);

	priority_queue<Node, vector<Node>, cmpPQ> PQ;
	Node u, v;

	v.level = -1;
	v.profit = 0;
	v.weight = 0;
	v.isPromising = true;
	v.bound = bound(v, n, W, arr);;
	int maxProfit = v.profit;

	PQ.push(v);
	cout << "level\tprofit\tbound\n";
	cout << v.level + 1 << "\t" << v.profit << "\t" << v.bound << "\n";
	cnt++;

	while (!PQ.empty()) {
		v = PQ.top();
		PQ.pop();

		if (v.bound > maxProfit) {

			if (v.level == n - 1)
				continue;

			u.level = v.level + 1;
			u.isPromising = true;

			/*집어 넣는 경우*/
			u.weight = v.weight + arr[u.level].weight;
			u.profit = v.profit + arr[u.level].value;

			if (u.weight <= W && u.profit > maxProfit) {
				maxProfit = u.profit;
			}

			u.bound = bound(u, n, W, arr);
			if (u.bound == 0) {
				u.isPromising = false;
			}
			if (u.bound > maxProfit && u.isPromising == true) {
				PQ.push(u);
			}
			cout << u.level + 1 << "\t" << u.profit << "\t" << u.bound << "\n";
			cnt++;

			/*안집어 넣은 경우*/
			u.weight = v.weight;
			u.profit = v.profit;
			u.bound = bound(u, n, W, arr);
			if (u.bound == 0) {
				u.isPromising = false;
			}
			if (u.bound > maxProfit && u.isPromising == true) {
				PQ.push(u);
			}
			cout << u.level + 1 << "\t" << u.profit << "\t" << u.bound << "\n";
			cnt++;
		}
	}

	return maxProfit; //maxprofit이 return값
}

int main() {
	int W, n;
	Item arr[MAXSIZE];
	int cntNode[MAXSIZE*10];

	do {
		printf("n(maxsize = %d, MAX TRIAL = %d) = ", MAXSIZE, MAXSIZE * 10); cin >> n;
	} while (n>MAXSIZE);

	srand((unsigned int)time(NULL)); //set seed
	
	int totMAX = -1;
	for (int k = 0; k < TRIAL; k++) {

		/*Item Init*/
		cout << "\n===setItem===\ni\tvalue\tweight\n";
		for (int i = 0; i < n; i++) {
			arr[i].value = rand() % 49 + 1; //1~50
			arr[i].weight = rand() % 9 + 1; //1~10

			cout << i << "\t" << arr[i].value << "\t" << arr[i].weight << "\n";
		}
		cout << "\n===============================\n";

		double mean = 0;
		int max = -1;
		int idx = 0;
		for (int i = n; i <= 10 * n; i++) {
			cnt = 0;
			W = i;

			cout << "Maximum possible profit = " << knapsack(W, arr, n) << "\n";
			cout << "cnt = " << cnt << " , W = " << i << "\n\n";
			cntNode[i] = cnt;

			if (max < cntNode[i]) {
				max = cntNode[i];
				idx = i;
			}
		}

		if (totMAX < max) totMAX = max;
	}
	printf("\n=========<RESULT>==========\n", totMAX);
	printf("totMAX VISIT is %d\n", totMAX);
	cout << "n is " << n;

	return 0;
}
