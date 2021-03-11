#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void select_2(int Time,int year,float general[2000][50],char name[2000][100]){
	int i=0;
	if(Time==0){
		while(i!=2001){
			if(general[i][3]<year){   // less than entered year
				printf("%s\n",name[(int)general[i][0]]);
			}
			i++;
		}
	}
	else if(Time==1){
		i=0;
		while(i!=2001){
			if(general[i][3]>year){ // greater than entered year
				printf("%s\n",name[(int)general[i][0]]);
			}
			i++;
		}
	}
}
void select_3(char game[100],float general[2000][50],char platform[20][20],char genre[30][20],char name[2000][100]){
	int i;
	for(i=0; i<2000; i++){                // call the every information and print
		if(strcmp(game,name[i])==0){
			printf("Name: %s\n",name[i]);
			printf("Genre: %s\n",genre[(int)general[i][1]]);
			printf("Platform: %s\n",platform[(int)general[i][2]]);
			printf("Year: %d\n",(int)general[i][3]);
			printf("Sales in NA: %.2f\n",general[i][4]);
			printf("Sales in EU: %.2f\n",general[i][5]);
			if(general[i][6]!=0.0) printf("Total Sales: %.2f\n",general[i][6]);
			else if(general[i][6]==0.0) printf("Total Sales: not_available\n");
			printf("User Score: %.2f\n\n\n",general[i][7]);
		}
	}
}
void select_4(float general[2000][50]){
	int i;
	float sum=0.0;
	for(i=0; i<2000; i++){
		sum += general[i][7];   //add the all user scores
	}
	sum=sum/2000.0;   //calculate the average
	printf("%f\n",sum);
}
void select_5(char game[100],char name[2000][100],float general[2000][50]){
	int i=0;
	while(strcmp(game,name[i])==0){  // find the game
		i++;
	}
	if(general[i][4]>general[i][5]){   //if na greater than eu
		printf("This game was more popular in North America.\n\n");
	}
	else if(general[i][4]<general[i][5]){  //if eu greater than na
		printf("This game was more popular in Europe.\n\n");
	}
	else if(general[i][4]==general[i][5]){ // if na and eu equal
		printf("This game's popularity is equal in North America and Europe.\n\n");
	}

}
void select_6(float general[2000][50],char genre[30][20]){
	int i,j,a=0;
	for(j=0; j<12; j++){   
		for(i=0; i<2000; i++){  
			if(general[i][1]==j) a++;  //counter
		}
		printf("%s: %d\n",genre[j],a);
		a=0;
	}
	printf("\n\n");
}
void select_7(float general[2000][50],char platform[20][20]){
	int i,j,a=0;
	for(j=0; j<10; j++){
		for(i=0; i<2000; i++){
			if(general[i][2]==j) a++; //counter
		}
		printf("%s: %d\n",platform[j],a);
		a=0;
	}
	printf("\n\n");
}

void menu(char name[2000][100], char genre[30][20], char platform[20][20], float general[2000][50]){
	int a,b,c,x;
	char game[100],game1[100];
	char m;
	while(a!=8){  // if you want to exit press the '8'
		printf("0: List of the Genres\n");
		printf("1: List of the Platforms\n");
		printf("2: List of the Games Through the Years\n");
		printf("3: All information of a Single Game\n");
		printf("4: Average of the User Scores\n");
		printf("5: Georographical information of a Single Game\n");
		printf("6: Freguence of the Genres\n");
		printf("7: Freguence of the Platforms\n");
		printf("8: EXIT\n");
		printf("Please select an operation: ");
		scanf("%d",&a);
		switch(a){
			case 0:{
				for(x=0; x<12; x++){   //read the genre array
					printf("%s\n",genre[x]);
				}
				printf("\n\n");
			}break;
			case 1:{
				for(x=0; x<10; x++){   //read the platform array
					printf("%s\n",platform[x]);
				}
				printf("\n\n");
			} break;
			case 2:{
				printf("Enter a year:\n");
				scanf("%d",&b);
				printf("Until (0) or Since (1) %d:",b);   //if press 0 until entered year, if press 1 since entered year
				scanf("%d",&c);
				switch(c){
					case 0: select_2(0,b,general,name); break;  // call the function by entered choice
					case 1: select_2(1,b,general,name); break;
					default: printf("TRY AGAİN.\n"); break;
				}
			} break;
			case 3:{ 
				printf("Please enter the name of the game:\n"); 
				scanf("%s",game);
				select_3(game,general,platform,genre,name);
			}break;
			case 4:{
				select_4(general);
			} break;
			case 5:{
				printf("Please enter the name of the game:\n");
				scanf("%s",game1);
				select_5(game1,name,general);
			} break;
			case 6:{
				select_6(general,genre);
			} break;
			case 7:{
				select_7(general,platform);
			} break;
			case 8: printf("EXIT\n"); break;  // if user want to exit
			default: printf("TRY AGAİN.\n"); break; // if user enter the invalid operation
		}
	}

}
void fill_arrays(char name[2000][100],char genre[30][20],char platform[20][20],float general[2000][50]){  // read the video game file and fill the arrays
	FILE *fp=fopen("Video_Games.txt","r");
	int i=0,j=0,k=0,m=0,n,x,y=0,result=1,t;
	char a;
	float b;
	char buf[30][20];
	char s2[20];
	char *ptr;
	while(a!='\n'){          // read first row but dont use
		fscanf(fp,"%c",&a);
	}
	while(i!=2000){  //row number
		n=m%8;   // readed string number in a row
		switch(n){
			case 0:{	// name is first string in a row
				fscanf(fp,"%[^,]",name[i]); // read until ','
				fscanf(fp,"%c",&a); // read ','
				general[i][y]=i;  // every general row's number shows the name 
				m++;  // total string number
				y++;  // in general array string number
			}break;
			case 1:{    // genre is second string in a row
				fscanf(fp,"%[^,]",buf[0]); // read until ','
				fscanf(fp,"%c",&a);	// read ','
				for(x=0; x<30; x++){
					if(strcmp(genre[x],buf[0])==0){  // if readed string already be in genre array
						general[i][y]=x;  // 
						result *=0;  // control variable
					}
					else{
						result *=1; //control variable
					}
				}
				if(result==1){
					general[i][y]=j;
					strcpy(genre[j],buf[0]);  // if readed string isnt in genre array , copy the string buffer to genre array
					j++;
				}
				m++;
				y++;
				for(x=0; x<30; x++){ // throw the buffer
					for(t=0; t<20; t++){
						buf[x][t]=0;
					}
				}
				result=1;
			}break;
			case 2:{     //platform is third string in a row
				fscanf(fp,"%[^,]",buf[0]);
				fscanf(fp,"%c",&a);
				for(x=0; x<20; x++){
					if(strcmp(platform[x],buf[0])==0){  //like 181. line 
						general[i][y]=x;
						result *=0;
					}
					else{
						result *=1;
					}
				}
				if(result==1){ // throw the buffer
					general[i][y]=k;
					strcpy(platform[k],buf[0]);
					k++;
				}
				m++;
				y++;
				for(x=0; x<30; x++){
					for(t=0; t<20; t++){
						buf[x][t]=0;
					}
				}
				result=1;
			}break;  
			case 3:{               // year of release
				fscanf(fp,"%f",&b);// float read from file
				fscanf(fp,"%c",&a);
				general[i][y]=b;
				m++;
				y++;
			}break;
			case 4:{              // north america sales
				fscanf(fp,"%f",&b); // float read from file
				fscanf(fp,"%c",&a);
				general[i][y]=b;
				m++;
				y++;
			}break;
			case 5:{             // europe sales
				fscanf(fp,"%f",&b);// float read from file
				fscanf(fp,"%c",&a);
				general[i][y]=b;    
				m++;
				y++;
			}break;
			case 6:{           //global sales
				fscanf(fp,"%[^,]",s2);
				fscanf(fp,"%c",&a);
				b=strtod(s2,&ptr);
				general[i][y]=b;
				m++;
				y++;
			}break;
			case 7:{            //user score
				fscanf(fp,"%f",&b);// float read from file
				fscanf(fp,"%c",&a);
				general[i][y]=b;
				i++;
				m++;
				y=0; //return the begining the after row
			}break;
		}	
	}
	fclose(fp);
	menu(name,genre,platform,general);
}

void main(){
	char name[2000][100];
	char genre[30][20];
	char platform[20][20];
	float general[2000][50];
	fill_arrays(name,genre,platform,general);  
}