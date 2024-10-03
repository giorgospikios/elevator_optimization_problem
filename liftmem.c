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

int Mmem(int i, int j, int nrid, int *dests, int **mem)
{
	int m, m1;


	m = INT_MAX;
	if(mem[i][j] == -1){
		if(i == 0)
			return fw(0, INT_MAX, dests, nrid);
		else{
			for(int k=0; k<=j; k++){
				m1 = (Mmem(i-1, k, nrid, dests, mem) - fw(k, INT_MAX, dests, nrid) + fw(k , j, dests, nrid) + fw(j, INT_MAX, dests, nrid));
				if(m1 < m)
					m = m1;
			}
			mem[i][j] = m;
			return m;
		}
	}
	else
		return mem[i][j];
}

int solve(int nrid, int nst, int *dests)
{
	int nfl, mc, MC, last_stop;
	int **mem;

	nfl = *dests;
	for(int i=0; i<nrid; i++)
		if(*(dests+i) > nfl)
			nfl = *(dests+i);

	mem = (int**) malloc((nst+1) * sizeof(int*));
	if(mem == NULL){
		printf("ERROR:NOT AVAILABLE MEMORY(in 1st if in solve)\n");
		exit(EXIT_FAILURE);
	}
	for(int i=0; i<=nst; i++){
		mem[i] = (int*) malloc((nfl+1) * sizeof(int));
		if(mem[i] == NULL){
			printf("ERROR:NOT AVAILABLE MEMORY(in 2nd if in solve)\n");
			exit(EXIT_FAILURE);
		}
	}
	for(int i=0; i<=nst; i++)
		for(int j=0; j<=nfl; j++)
			mem[i][j] = -1;

	MC = INT_MAX;
	last_stop = 0;
	for(int j=0; j<=nfl; j++){
		mc = Mmem(nst, j, nrid, dests, mem);
		if(mc < MC){
			MC = mc;
			last_stop = j;
		}
	}
	if(last_stop)
		printf("Last stop at floor: %d\n", last_stop);
	else
		printf("No lift stops\n");

	for(int i=0; i<=nst; i++)
		free(mem[i]);
	free(mem);

	return MC;
}