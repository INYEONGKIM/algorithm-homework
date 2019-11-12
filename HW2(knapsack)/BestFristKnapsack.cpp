#include<queue>
#include<iostream>
#include <vector>
#include <cstdio>

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

//내림차순 정렬
struct cmpPQ {
	bool operator()(const Node t, const Node u) {
		return t.bound < u.bound;
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
	int W = 16;   // Weight of knapsack 
	Item arr[] = { { 2, 40 },{ 5, 30 },{ 10, 50 },{ 5, 10 } };
	//Item arr[] = { { 2, 20 },{ 5, 30 },{ 7, 35 },{ 3, 12 },{ 1,3 } };
	int n = sizeof(arr) / sizeof(arr[0]);
	
	cout << "\nMaximum possible profit = " << knapsack(W, arr, n);
	
	cout << "\ncnt = " << cnt << "\n";

	return 0;
}
