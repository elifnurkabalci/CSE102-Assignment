#include<stdio.h>
#include<stdlib.h> /* srand() */
#include<time.h> /* time(NULL) */
#include<string.h> /* strcpy */
struct Hospital
{
	char* name;
	char citiesServed[3];  // store the hospital location that working on
};
struct card
{
	const char *face;  // string array
	const char *suit;
};
void thirdFunc(){    
	char suits[4][12]={{'H','e','a','r','t','s'},{'D','i','a','m','o','n','d','s'},{'C','l','u','b','s'},{'S','p','a','d','e','s'}};
	char faces[13][10]={{'A','c','e'},{'D','e','u','c','e'},{'T','h','r','e','e'},{'F','o','u','r'},{'F','i','v','e'},{'S','i','x'},{'S','e','v','e','n'},{'E','i','g','h','t'},{'N','i','n','e'},{'T','e','n'},{'J','a','c','k'},{'Q','u','e','e','n'},{'K','i','n','g'}};
	int i,j;
	struct card x;  // for using data from struct
	srand(time(NULL));  // for random choose by cards
	for(i=0; i<26; i++){	// faces*suits
		for(j=0; j<2; j++){  // print the data between other data
			x.face=faces[rand()%12]; // random choose from faces
			x.suit=suits[rand()%3];  // random choose from suits
			printf("%s of %s          ",x.suit,x.face); // print the struct's
		}
		printf("\n");
	}
}
int canOfferCovidCoverage(char _cities[6], char _location[4][3], int _numHospitals, struct Hospital results[4]){
	struct Hospital x;
	int i;
	if(_numHospitals<=4 && _numHospitals>0){
		strcpy(x.citiesServed,_location[_numHospitals-1]);
		for(i=0; i<3; i++){                // I didnt read string, this 'for' for read like string
			if(x.citiesServed[i]=='A') _cities[0]='1'; // is this city covered ?  
			if(x.citiesServed[i]=='B') _cities[1]='1'; // if covered turn the 1
			if(x.citiesServed[i]=='C') _cities[2]='1'; 
			if(x.citiesServed[i]=='D') _cities[3]='1';
			if(x.citiesServed[i]=='E') _cities[4]='1';
			if(x.citiesServed[i]=='F') _cities[5]='1';	
		}
		return canOfferCovidCoverage(_cities,_location,_numHospitals-1,results); // recursive
	}
}
int numPathHome(int street, int avenue){  // for calculate the combination with recursive function
	int result;
	if(street==1) result=avenue;                       // if street=1, (avenue)!/1*(avenue-1)! = avenue
	else if(avenue==street) result=1;                  // if avenue=steet,  (avenue)!/(street)!*(0)! => 1/1*1 = 1
	else result= numPathHome(street-1,avenue-1)+numPathHome(street,avenue-1);  // example numpath(2,3) =>=>  1,2 => street=1 so 2 and  <=> 2,2=> avenue=street -> 1 ==3 
	return result;
}
void menu(){
	char _cities[6]={'A','B','C','D','E','F'};
	char _location[4][3]={{'A'},{'C','D'},{'B','F'},{'F','E','C'}};
	struct Hospital results[4];
	int a,street,avenue,_numHospitals,b,x=0,i;
	printf("1) Part 1\n2) Part 2\n3) Part 3\n4) Exit\n");
	scanf("%d",&a);
	switch(a){
		case 1:{
			printf("Enter the street number:");
			scanf("%d",&street);
			printf("steet: %d\n",street);
			printf("Enter the avenue number:");
			scanf("%d",&avenue);
			printf("avenue: %d\n",avenue);
			if(avenue>street) b=numPathHome(street,avenue);  //combination(avenue,street)
			else b=numPathHome(avenue,street);               //combination(street,avenue)
			printf("Number of optimal path to take back home:%d\n",b);
		}break;
		case 2:{
			printf("Enter the maximum number of hospitals that can be constructed:\n");
			scanf("%d",&_numHospitals);
			canOfferCovidCoverage(_cities,_location,_numHospitals,results);
			for(i=0; i<6; i++){
				x+=(int)(_cities[i]-'0'); // translate the char to int
			}
			if(x==6){  // if _numhospital choose covered the all cities
				printf("Yes can offer health care to all!\n");
				for(i=0; i<_numHospitals; i++){  // print the hospital locations
					printf("Hospital- %d\nHospital location: %c%c%c\n",i+1,_location[i][0],_location[i][1],_location[i][2]);
				}
			} 
			else printf("No some cities are not covered\n");
		}break;
		case 3:{
			thirdFunc(); // call the cards function
		}break;
		case 4:{
			printf("EXIT\n"); // for exit the program
		}break;
		default: printf("İnvalid operation\n"); break;
	}
}
void main(){
	menu();
}