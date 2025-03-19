void record_digit()
{
	//int choice;
	system("Live_testing\\Recording_Module.exe 2 Live_testing\\input_file.wav Live_testing\\input_file.txt");
	/*do
	{
	system("Live_testing\\Recording_Module.exe 2 Live_testing\\input_file.wav Live_testing\\input_file.txt");
	printf("Playing sound:\n");
	PlaySound(TEXT("Live_testing\\input_file.wav"),NULL,SND_SYNC);
	printf("Press 1:Proceed 2:Re-record digit\n");
	scanf("%d",&choice);
	printf("Recording completed\n");
	}while(choice==2);  */
	//printf("record function done\n");
}

int find_digit()
{
	lld probability=0,calc_probability=0;
	int index=0;
	for(int i=1;i<=10;i++)
	{
		read_lambda_values(i);
		calc_probability=forward_procedure();
		if(calc_probability>probability)
		{
			probability=calc_probability;
			index=i;
		}
	}
	return index;
}
void predict_digit()
{
	char filename[40];
	lld arr[40000],frame_arr[framesize+1];
	int index,framecount=0,predicted_digit;
	lld count;
	lld R[p+1],A[p+1],C[p+1];
	//printf("Codebook loading starts.... \n");
	load_codebook();
	//printf("Codebook loading eends.... \n");
	sprintf(filename,"Live_testing/input_file.txt");
	FILE *fp=fopen(filename,"r");
	
	if(fp==NULL)
	{
		printf("unable to access Live_testing file\n");
		return;
	}
	int k=0;
	while(fscanf(fp,"%Lf",&arr[k])!=EOF)
		k++;
	fclose(fp);
	//printf("recog starts\n");
	dc_shift(arr);
	normalisation(arr);
	framecount=0;
	for(int x=0;x+framesize<k;x+=280)
	{
		index=0;
		for(int y=x;y<x+framesize;y++)
		{
			frame_arr[index]=arr[y];
			index++;
		}
		
		hammingWindow(frame_arr);
		calculateRi(frame_arr,R);
		calculateAi(R,A);
		calculateCi(R,A,C);
		// printf("Ci Calculated\n");
		raisedsinewindow(C);
		framecount++;
		O[framecount]=tokhura_distance_index(C);
	}
	T=framecount;
	predicted_digit=find_digit();
	char wordname[40];
	int arrays[5]={1,4,7,3,8};
	sprintf(filename,"stored_words/%d.txt",predicted_digit);
	FILE *fptr=fopen(filename,"r");
	char ch[1000];
	printf("\n----------------------------------------------------------\n");
	while(!feof(fp))
	{
		fgets(ch,100,fptr);
		printf("%s",ch);
	}
	printf("\n----------------------------------------------------------\n");
	//printf("Predicted digit is: %d\n",predicted_digit);
}
void live_testing()
{
	record_digit();
	predict_digit();
}