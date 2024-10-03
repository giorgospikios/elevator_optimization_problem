#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "liftrec.h"
#include "liftmem.h"
#include "liftdp.h"

int main(void)
{
	int nrid, nst, mincost;
	int *dests;

	printf("ENTER THE NUMBER OF PASSENGERS\n");
	scanf("%d", &nrid);

	printf("ENTER THE MAXIMUM NUMBER OF ELEVATOR STOPS\n");
	scanf("%d", &nst);

	dests = (int*) malloc(nrid * sizeof(int));
	if(dests == NULL){

		printf("ERROR: NOT AVAILABLE MEMORY\n");
		exit(EXIT_FAILURE);
	}

	printf("ENTER THE DESTINATIONS OF THE PASSENGERS\n");
	for(int i=0; i<nrid; i++)
		scanf("%d", &dests[i]);

	mincost = solve(nrid, nst, dests);
	printf("Cost is: %d\n", mincost);

	return 0;
}