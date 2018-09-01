/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

#include<stdio.h>

#include<conio.h>

#include<iostream>

using namespace std;
//int p[5],wt[5];
int C, n;
void knapsack01_DP(int p[], int wt[]);
int max(int a, int b);




/**
* @param args the command line arguments
*/
int main() {

	cout << "Enter the number of items in a Knapsack:";

	// int n, C;

//	cin >> n;
	n = 5;
	int p[5], wt[5];

	for (int i = 0; i < n; i++)

	{

		cout << "Enter value and weight for item " << i << ":";

		cin >> p[i];


		cin >> wt[i];


	}
	cout << "\n------------\n";
	for (int i = 0; i < n; i++)

	{
		cout << p[i];
		cout << wt[i];
	}


	//    int val[] = { 60, 100, 120 };

	//    int wt[] = { 10, 20, 30 };

	//    int W = 50;

	cout << "Enter the capacity of knapsack";

	//cin >> C;
	C = 5;
	cout << "\n0/1 Knapsack using dynamic programming";
	knapsack01_DP(p, wt);





	return 0;

}
int max(int a, int b) {
	return(a>b) ? a : b;
}

void knapsack01_DP(int p[], int wt[]) {

	int i, j, w;
	cout << C << n;
	cout << "\n------------\n";
	for (int i = 0; i < n; i++)

	{
		cout << p[i];
		cout << wt[i];
	}
	int K[5 + 1][5 + 1];
	for (i = 0; i <= n; i++) {
		for (w = 0; w <= C; w++) {
			if (i == 0 || w == 0) {
				K[i][w] = 0;
			}
			else if (wt[i] <= w) {
				cout << " " << max(p[i] + K[i - 1][w - wt[i]], K[i - 1][w]);
				K[i][w] = max(p[i] + K[i - 1][w - wt[i]], K[i - 1][w]);

			}
			else {
				K[i][w] = K[i - 1][w];
				cout << " " << K[i - 1][w];
			}
		}
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= C; j++)
		{
			cout << " " << K[i][j];
		}
		cout << "\n";
	}
	cout << "The selected items are:\n";
	int c = C;
	int m = n;
	cout << "\nm" << m << "\nc" << c << "\n";
	while (m>0)
	{
		if (K[m][c] != K[m - 1][c]) {
			cout << "Item" << m << "(weight:" << wt[m] << ",profit:" << p[m] << ")";
			c = c - wt[m];

		}m--;
	}
	cout << "The total profit of the items added to knapsack=" << K[n][C];
	cout << "\nIntermediate results\nCapacity: ";
	for (j = 0; j <= C; j++) {
		cout << j << "\t";

	}
	cout << "\n";

	for (i = 0; i <= n; i++) {
		cout << "Item" << i << " : ";
		for (j = 0; j <= C; j++) {
			cout << K[i][j] << "\t";
		}
		cout << "\n";



	}
}




// TODO code application logic here



