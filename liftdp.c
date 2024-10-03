#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int fw(int a, int b, int *dests, int nrid)
{
	int fw_sum = 0;
	for(int i=0; i<nrid; i++){					
		if((*(dests+i) - a) < (b - *(dests+i))){
			if((*(dests+i) - a) >= 0)
				fw_sum += (*(dests+i) - a);
		}
		else
			if((b - *(dests+i)) >= 0)
				fw_sum += (b - *(dests+i));
	}
	return fw_sum;
}

int Mdp(int nst, int nrid, int nfl, int *dests, int **dp)
{
	int m, m1, min_k, last_stop, prev_stop;
	int **stops;

	stops = (int**) malloc((nst+1) * sizeof(int*)); // desmeuw dynamika mnhmh gia ta stops
	if(stops == NULL){
		printf("ERROR:NOT AVAILABLE MEMORY(in 1st if in solve)\n");
		exit(EXIT_FAILURE);
	}
	for(int i=0; i<=nst; i++){
		stops[i] = (int*) malloc((nfl+1) * sizeof(int));
		if(stops[i] == NULL){
			printf("ERROR:NOT AVAILABLE MEMORY(in 2nd if in solve)\n");
			exit(EXIT_FAILURE);
		}
	}

	m1 = INT_MAX;
	for(int i=0; i<=nst; i++){
		for(int j=0; j<=nfl; j++){
			if(i==0 || j==0){
				dp[i][j] = fw(0, INT_MAX, dests, nrid);
				m = dp[i][j];
				printf(" %3d", m);
			}
			else{
				m = INT_MAX;
				for(int k=0; k<j; k++){
					dp[i][j] = (dp[i-1][k] - fw(k, INT_MAX, dests, nrid) + fw(k, j, dests, nrid) + fw(j, INT_MAX, dests, nrid));
					if(dp[i][j] < m){
						m = dp[i][j];
						min_k = k;
					}
				}
				stops[i][j] = min_k;
				dp[i][j] = m;
				printf(" %3d", m);
			}			
			if(m < m1){
				m1 = m;
				last_stop = j;
			}
		}
		printf("\n");
	}

	printf("Lift stops are:");
	printf(" %d", last_stop);
	prev_stop = 0;
	for(int i=nst; i>1; i--){
		prev_stop = stops[i][last_stop];
		printf(" %d", prev_stop);
	}
	printf("\n");

	for(int i=0; i<=nst; i++)
		free(stops[i]);
	free(stops);

	return m;
}

int solve(int nrid, int nst, int *dests)
{
	int nfl, mc;
	int **dp;

	nfl = *dests;
	for(int i=0; i<nrid; i++)
		if(*(dests+i) > nfl)
			nfl = *(dests+i);

	dp = (int**) malloc((nst+1) * sizeof(int*));
	if(dp == NULL){
		printf("ERROR:NOT AVAILABLE MEMORY(in 1st if in solve)\n");
		exit(EXIT_FAILURE);
	}
	for(int i=0; i<=nst; i++){
		dp[i] = (int*) malloc((nfl+1) * sizeof(int));
		if(dp[i] == NULL){
			printf("ERROR:NOT AVAILABLE MEMORY(in 2nd if in solve)\n");
			exit(EXIT_FAILURE);
		}
	}

	mc = Mdp(nst, nrid, nfl, dests, dp);

	for(int i=0; i<=nst; i++)
		free(dp[i]);
	free(dp);

	return mc;
}