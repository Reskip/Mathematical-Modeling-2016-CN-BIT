#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>  
#include<cstring>  
#include<algorithm>  
#include <iostream>  
#include <string>  
#include<stdio.h>
#include<cmath>

using namespace std;

double A = 150, Alef, Arig;
const int maxn = 53;
const int maxl = 3010;
int remain_parts[maxn + 5] = { 4, 216, 104, 38, 4, 60, 4, 8, 6, 10, 8, 2, 4, 8, 8, 2, 8, 301, 6, 38, 30, 8, 4, 4, 34, 18, 4, 4, 90, 30, 30, 212, 108, 482, 196, 8, 32, 4, 52, 42, 8, 8, 8, 60, 136, 4, 68, 286, 502, 286, 292, 57, 24 ,10000};
int data[maxn + 5] = { 1743, 1680, 1532, 1477, 1313, 1285, 1232, 1217, 1180, 1177, 1105, 1055, 1046, 1032, 1030, 975, 893, 882, 847, 845, 830, 795, 766, 745, 732, 719, 714, 690, 665, 633, 630, 600, 590, 588, 582, 578, 540, 488, 455, 434, 420, 415, 414, 411, 405, 328, 313, 290, 275, 265, 255, 184, 155 };

int days_barrier[maxn + 5] = { 0, 0, 0, 2, 1, 0, 1, 0, 1, 0, 2, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 2, 1, 0, 0, 1, 2, 0, 0, 2, 0, 0, 0, 1, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 1, 0, 2, 0, 0, 0 };
double bar_d[maxn + 5];

double barrier(int x)
{
	if (bar_d[x])
	{
		return bar_d[x];
	}

	double ret;
	if (days_barrier[x] == 1)
	{
		ret = sqrt(x + 5);
	}
	if (days_barrier[x] == 2)
	{
		ret = sqrt(x + 5) * A * 0.3;
	}
	if (days_barrier[x] == 0)
	{
		ret = sqrt(x + 5) * A;
	}
	bar_d[x] = ret;
	return ret;
}

class finds{
public:
	int data[55];
	int remain;
	double rank;

	double get_rank()//get rank
	{
		int usen = 0;
		double ranks = 0;
		for (size_t i = 0; i < maxn; i++)
		{
			usen += data[i];
			ranks += barrier(i) * data[i];
		}
		ranks /= usen + 1;
		ranks += remain;

		rank = ranks;
		return ranks;
	}
};


finds has[1000];
int hasn;

class dp{
public:
	finds dps[maxl + 5];

	finds temp;

	void init()
	{
		dps[0].remain = 0;
		memset(dps[0].data, 0, sizeof(dps[0].data));

		for (size_t i = 1; i <= maxl; i++)
		{
			memset(dps[i].data, 0, sizeof(dps[i].data));
			dps[i].remain = 100000000;
		}
	}

	void iter()
	{
		for (size_t i = 1; i <= maxl; i++)
		{
			//printf("%d\n", i);

			for (size_t s = 0; s <= maxn; s++)
			{
				if (i >= data[s] && remain_parts[s])
				{
					int d_remain = 0;
					for (int k = i - data[s]; k >= 0 && d_remain < 10; k--)
					{
						if (remain_parts[s] - dps[k].data[s] <= 0)
						{
							continue;
						}
						temp = dps[k];
						temp.data[s]++;
						temp.remain += d_remain;
						if (temp.get_rank() < dps[i].get_rank())
						{
							dps[i] = temp;
						}
						d_remain++;
					}
				}
			}

			//for (size_t s = 0; s < maxn; s++) //test
			//{
			//	cout << dps[i].data[s] << " ";
			//}
			//cout << "\n";
		}
	}

};

int main()
{
	FILE * file;
	file = fopen("datas.txt", "w");

	for (size_t i = 0; i < maxn; i++)
	{
		data[i] += 5;
	}
	int n = 0;
	int remains = 0;
	dp test;
	while (1)
	{
		int counter = 0;
		for (size_t i = 0; i < maxn; i++)
		{
			counter += remain_parts[i];
		}
		if (!counter)
		{
			break;
		}
		test.init();
		test.iter();

		int tar = 0;
		for (size_t i = 0; i < hasn; i++)
		{
			int k = 0;
			for (size_t s = 0; s < maxn; s++)
			{
				if (has[i].data[s] > remain_parts[s])
				{
					k = 1;
					break;
				}
			}
			if (k == 0 && has[i].rank <= test.dps[3005].rank*1.001)
			{
				test.dps[3005] = has[i];
				tar = 1;
			}
		}
		if (!tar)
		{
			has[hasn] = test.dps[3005];
			hasn++;
		}

		for (size_t i = 0; i < maxn; i++)
		{
			remain_parts[i] -= test.dps[3005].data[i];
		}
		remains += test.dps[3005].remain;
		fprintf(file, "%d %d\n", n, remains);
		//cout << n << " " << remains << "\n";
		for (size_t i = 0; i < maxn; i++)
		{
			fprintf(file, "%d ", test.dps[3005].data[i]);
			//cout << test.dps[3005].data[i] << " ";
		}
		fprintf(file, "\n");
		//cout << "\n";
		for (size_t i = 0; i < maxn; i++)
		{
			fprintf(file, "%d ", remain_parts[i]);
			printf("%d ", remain_parts[i]);
			//cout << remain_parts[i] << " ";
		}
		printf("\n");
		fprintf(file, "\n");
		//cout << "\n";
		n++;
	}
	fclose(file);
	cin >> n;
}
