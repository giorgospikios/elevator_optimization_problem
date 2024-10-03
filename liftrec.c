#include <stdio.h>
#include <limits.h>

int fw(int a, int b, int *dests, int nrid)
{
	int fw_sum = 0;
	for(int i=0; i<nrid; i++){					
		if((*(dests+i) - a) < (b - *(dests+i))){ //analoga ta dedomena blepw poio einai pio mikro
			if((*(dests+i) - a) >= 0)            // wste na kserw an tha anebei h katebei o epibaths
				fw_sum += (*(dests+i) - a);
		}
		else
			if((b - *(dests+i)) >= 0)
				fw_sum += (b - *(dests+i));
	}
	return fw_sum;
}

int Mrec(int i, int j, int nrid, int *dests)
{
	int m1, m;


	m = INT_MAX;
	if(i == 0)
		return fw(0, INT_MAX, dests, nrid);
	else{
		for(int k=0; k<=j; k++){
			m1 = (Mrec(i-1, k, nrid, dests) - fw(k, INT_MAX, dests, nrid) + fw(k , j, dests, nrid) + fw(j, INT_MAX, dests, nrid));
			if(m1 < m) //sygkrinw kathe timh poy epistrefetai sto m1 gia na brw to min gia to iteration apo to k mexri to j
				m = m1;
		}
	}
	return m;

}

int solve(int nrid, int nst, int *dests)
{
	int nfl, mc, MC, last_stop;

	nfl = *dests;      //xrhsimopoiw to deikth(pinaka) gia nabrw to nfl
	for(int i=0; i<nrid; i++)
		if(*(dests+i) > nfl)
			nfl = *(dests+i);

	MC = INT_MAX;
	last_stop = 0;
	for(int j=0; j<=nfl; j++){
		mc = Mrec(nst, j, nrid, dests);
		if(mc < MC){
			MC = mc;
			last_stop = j;
		}
	}
	if(last_stop)
		printf("Last stop at floor: %d\n", last_stop);
	else
		printf("No lift stops\n");

	return MC;
}