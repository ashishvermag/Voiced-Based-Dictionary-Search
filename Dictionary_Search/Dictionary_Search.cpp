#include "stdafx.h"
#include<conio.h>
#include "string.h"
#include "stdio.h"
#include<stdlib.h>
#include<cstdlib>
#include<time.h>
#include<math.h>
#include<windows.h>
#include<iostream>
#pragma comment(lib,"Winmm.lib")
#include "create_universe.h"
#include "create_codebook.h"
#include "training.h"
#include "testing.h"
#include "live_testing.h"
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	int x;
	printf("1.Training  2.Searching  \n");
	scanf("%d",&x);
	switch(x)
	{
	case 1:
		// printf("Creating Universe...  ");
				create_universe();
		//	printf("Creating Codebook...  ");
				create_codebook();
		//	printf("Training...  ");
				training();
		//	printf("Testing Prerecorded...  ");
				testing();
				break;
	case 2:
		printf("Start searching...  \n\n");
		while(1)
	{
 		printf("Press any key to search ");
			getch();
				live_testing();
				
	}
		break;
	default:
		printf("Invalid Input");
		break;
	}

	    
			
	
	getch();
	return 0;
}

