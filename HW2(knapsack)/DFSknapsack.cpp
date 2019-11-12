#include<iostream>
#define SIZE 5
using namespace std;

int p[5] = {0,40,30,50,10}; //profit
int w[5] = {0,2,5,10,5}; // weight
//int p[6] = { 0,20,30,35,12,3 }; //profit
//int w[6] = { 0,2,5,7,3,1 }; // weight


int W = 16; //ÃÖ´ë weight

int maxprofit = 0;
int cnt=0;

void knapsack(int i, int profit, int weight);
bool promising(int i, int profit, int weight);

int main(){
	cout << "level\tprofit\tbound\n";
	knapsack(0, p[0], w[0]);

	
	cout << "\nMaximum possible profit = " << maxprofit << "\n";

	cout << "\ncnt = " << cnt << "\n";

	return 0;

}

void knapsack(int i, int profit, int weight){
	
	cnt++;
	if (weight <= W && profit > maxprofit) {
		maxprofit = profit;
	}

	if (promising(i, profit, weight)) {
		knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		knapsack(i + 1, profit, weight);
	}
}

bool promising(int i, int profit, int weight) {
	int j, k;
	int totweight;
	float bound;

	if (weight >= W){
		cout << i << "\t" << profit << "\t" << "Weight over" << "\n";
		return false;
	}	

	else {
		j = i + 1;
		totweight = weight;
		bound = profit;
		
		while ((j <= SIZE) && (totweight + w[j] <= W)) {
			totweight = totweight + w[j];
			bound = bound + p[j];
			j++;
		}
		k = j;

		if (k <= SIZE) {
			bound = bound + (W - totweight)*(p[k] / w[k]);

		}
		cout << i << "\t" << profit << "\t" << bound << "\n";

		if (bound > maxprofit){
			return true;
		}
		else{
			return false;
		}
	}
}
