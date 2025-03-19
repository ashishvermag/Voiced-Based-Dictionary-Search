
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
	while(1)
	{
		printf("\nEnter \n1:Universe Creation \n2:Codebook Creation \n3:Train Model \n4:Test Model Prerecorded \n5:Live Recording Test \n0:Exit\n");
		scanf("%d",&x);
		switch(x)
		{
			case 1:
				create_universe();
				break;
			case 2:
				create_codebook();
				break;
			case 3:
				training();
				break;
			case 4:
				testing();
				break;
			case 5:
				live_testing();
				break;
			case 0:
				return 0;
			default:
				printf("Invalid input\n");
		}
	}
	getch();
	return 0;
}

