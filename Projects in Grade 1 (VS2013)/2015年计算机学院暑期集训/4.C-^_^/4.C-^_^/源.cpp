#include "stdio.h"
#include "map"
#include "set"
#include "algorithm"


typedef long long LL;
using namespace std;
const int maxn = 1000000 + 5;

map<int, int> M;
set<int> S;
int a[maxn];

int main(){
	int p;
	while (scanf("%d", &p) != EOF){
		S.clear();
		M.clear();
		for (int i = 0; i < p; i++){
			scanf("%d", &a[i]);
			S.insert(a[i]);
		}
		int n = S.size();
		if (n == 1){
			printf("1\n");
			continue;
		}
		int ans = p;
		int s = 0, t = 0, sum = 0;
		while (s < p && t < p){
			if (M[a[t]] == 0) sum++;
			M[a[t]]++;
			while (M[a[s]] >= 2){
				M[a[s]]--;
				s++;
			}
			if (sum == n){
				ans = min(ans, t - s + 1);
				if (M[a[s]] == 1) sum--;
				M[a[s]]--;
				s++;
			}
			t++;
		}
		printf("%d\n", ans);
	}
	return 0;
}


//int main()
//{
//	const int MAX = 100001;
//
//	int P;
//
//	int Idea[MAX];
//	int Sign[10000];
//	int SignNum[10000];
//
//	int Ideahead;
//
//	int SignC;//Idea counter;
//	int PC;//P counter;
//	int end = 0;
//
//	for (int x = 0; x < MAX; x++)
//	{
//		Idea[x] = -1;
//		if (x<10000)
//		{
//			Sign[x] = -1;
//			SignNum[x] = -1;
//		}
//	}
//	
//	scanf("%d", &P);
//
//	for (PC = 0; PC < P; PC++)
//	{
//		scanf("%d", &Idea[PC]);
//
//		if (PC == 0)//Start Sign.
//		{
//			Sign[0] = Idea[PC];
//			SignNum[0] = 1;
//			Ideahead = 0;
//		}
//		else
//		{
//			for (SignC = 0; Sign[SignC] != -1; SignC++)
//			{
//				if (Sign[SignC] == Idea[PC])
//				{
//					SignNum[SignC]++;
//					break;
//				}
//			}
//			if (Sign[SignC] == -1)
//			{
//				Sign[SignC] = Idea[PC];
//				SignNum[SignC] = 1;
//				SignC++;
//				end = PC;
//			}
//		}
//
//	/*	if (Idea[PC] == Idea[Ideahead])
//		{*/
//			for (;;)
//			{
//				for (SignC = 0; Sign[SignC] != Idea[Ideahead]; SignC++);
//				if (SignNum[SignC] > 1)
//				{
//					SignNum[SignC]--;
//					Ideahead++;
//				}
//				else
//				{
//					break;
//				}
//			}
//		}
//	/*}*/
//	//if (end != 0)
//	//{
//	//	printf("%d\n", end - Ideahead + 1);
//	//}
//	//else
//	//{
//	//	printf("%d\n", PC - Ideahead + 1);
//	//}
//}