#include<stdio.h> /* printf,scanf,fscanf,fopen,fclose */
#include<stdlib.h> /*SRAND() */
#include<time.h> /* time(NULL) */
#include<math.h> /* sqrt */

char decrypt_numbers (int number){ /* first and second function's translate the number to character */
	switch(number){
		case 0:printf(" "); break;
		case 1:printf("-"); break;
		case 2:printf("_"); break;
		case 3:printf("|"); break;
		case 4:printf("/"); break;
		case 5:printf("\\"); break;
		case 6:printf("O"); break;
		default:printf("\n"); break;
	}
}
void decrypt_and_print (char* file_path){ /*encrypted1 */
	FILE *fps;
	fps=fopen(file_path,"r");
	int number;
	char a;
	while(!feof(fps)){
		fscanf(fps,"%c",&a); /* read the character */
		number = a - '0';  /* turn char to integer */
		decrypt_numbers(number); 
		if(a != '\n'){
			fscanf(fps,"%c",&a);
			number = a - '0';
			decrypt_numbers(number);
		}
		else{
			printf("\n"); /* arrengement the lines */
		}
	}
	fclose(fps);
}

void deep_decrypt_and_print (char* file_path){
	FILE *fps;
	char a,b,c;
	int n,i,number=0,num1,num2,num3,j,k;
	for(j=0; j<26; j++){ /* lines */
		for(n=0; n<148; n++){ /* characters of each line */ 
			fps=fopen(file_path,"r"); /* open the file each n variable */

			for(k=0; k<148*j; k++){
				fscanf(fps,"%c",&a);  /*determine the which line will read */ 
			}

			for(i=0; i<n; i++){
				fscanf(fps,"%c",&a);	/*determine the which character will read */ 
			}
			fscanf(fps,"%c",&a);
			fscanf(fps,"%c",&b);	/* read the character in file */
			fscanf(fps,"%c",&c);
			num1= a - '0'; /* return the character to decimal number */
			num2= b - '0';
			num3= c - '0';
			number= num1+num2+num3;
			number=(number%7);
			decrypt_numbers(number); /* return the result by character */
			fclose(fps);
		}
		
	}
	printf("\n");
}
void refresh_position (int *X,int *Y,double *D, double *R){
	int i,j;  
	i=*X; /* initial position */
	j=*Y;
	srand(time(NULL)); /* refresh the enemies position each start the programm */
	*X=rand()%11; /* put the x and y coordinate by random */
	*Y=rand()%11;
	*D = sqrt((*X-6)*(*X-6)+(*Y-6)*(*Y-6)); /* distance between two dots equation */
	*R = sqrt((*X-i)*(*X-i)+(*Y-j)*(*Y-j));
}
void track_machine (){
	int X=0,Y=0,i,j;
	double D,R;
	refresh_position(&X, &Y, &D, &R); 
	for(i=1; i<=11; i++){  /* 11*11 coordinate system */
		for(j=1; j<=11; j++){
			if((i==6)&&(j==6)){ /* our position */
				printf("O\t");
			}
			else if((i==X)&&(j==Y)){ /* enemy position */
				printf("E\t");
			}
			else{
				printf(".\t"); /* other coordinate dots */
			}
			
		}
		printf("\n");/* line arrengement*/
	}
	printf("Enemies x posittion: %d, Y position: %d, Displacement: %.2lf, Distance to our camp: %.2lf \n",X,Y,R,D);
	printf("Commond waiting...: \n");
}

int encrypt_A(char A){ /* for part 4 */
	char a;
	switch(A){  /* return the character to decimal */
		case ' ': a='0';  break;
		case '-': a='1';  break;
		case '_': a='2';  break;
		case '|': a='3';  break;
		case '/': a='4';  break;
		case '\\':a='5';  break;
		case 'O': a='6';  break;
		default:  ; break;
	}
	return a;
}
void encrypt_messages (char* file_path){
	FILE *fps;
	FILE *ofps;
	fps=fopen(file_path,"r");
	ofps=fopen("encrypted_p4.img","w");
	char A;
	int num1=0,num2=0,num3,n,a,c,x;
	for(x=0;x<5;x++){  /* for first 5 lines */
		fprintf(ofps,"%d",num1);
		fprintf(ofps,"%d",num2);
		for(n=0; n<179; n++){ /* each line */
			fscanf(fps,"%c",&A);/* read the first file */
			a=encrypt_A(A)-'0'; /* desired number */
			c=(num1+num2)%7; /* number at hand */
			if(a==c) num3=0; /* calculation for reach the desired number */
			else if(a==(c+1)%7) num3=1; 
		 	else if(a==(c+2)%7) num3=2; 
			else if(a==(c+3)%7) num3=3; 
			else if(a==(c+4)%7) num3=4; 
			else if(a==(c+5)%7) num3=5; 
			else if(a==(c+6)%7) num3=6; 	
			fprintf(ofps,"%d",num3); /* write in file */
			num1=num2;
			num2=num3;
		}
		fprintf(ofps,"\n");/* line arrengement*/
		num1=0;
		num2=0;
	}
	for(x=0; x<2; x++){ /* space */
		for(n=0; n<178; n++){
			fprintf(ofps,"0");
		}
		fprintf(ofps,"\n");/* line arrengement*/
	}
	for(x=0;x<5;x++){ /* after 5 lines */
		fprintf(ofps,"%d",num1);
		fprintf(ofps,"%d",num2);
		for(n=0; n<106; n++){ /* each line */
			fscanf(fps,"%c",&A);/*read the first file */
			a=encrypt_A(A)-'0';/* desired number */
			c=(num1+num2)%7;/*number at hand */
			if(a==c) num3=0; /*calculation for reach the desired number */
			else if(a==(c+1)%7) num3=1; 
		 	else if(a==(c+2)%7) num3=2; 
			else if(a==(c+3)%7) num3=3; 
			else if(a==(c+4)%7) num3=4; 
			else if(a==(c+5)%7) num3=5; 
			else if(a==(c+6)%7) num3=6; 	
			fprintf(ofps,"%d",num3); /* write in file */
			num1=num2;
			num2=num3;
		}
		fprintf(ofps,"\n");/* line arrengement*/
		num1=0;
		num2=0;
	}
	for(n=0; n<106; n++){ /*space */
		fprintf(ofps,"0");
	}
	fprintf(ofps,"\n"); /* line arrengement*/
	fclose(fps);
	fclose(ofps);
}
void menu(){
	int a;
	while(a!=5){
	printf("1-) Decrypt and print encrypted_p1.img \n"); /* menu for user */
	printf("2-) Decrypt and print encrypted_p2.img \n");
	printf("3-) Switch on the tracking machine \n");
	printf("4-) Encrypt the message \n"); 
	printf("5-) Switch off \n");
	printf("Please make your choice: \n");
	scanf("%d",&a);
	if(a==1)decrypt_and_print("encrypted_p1.img");
	if(a==2)deep_decrypt_and_print("encrypted_p2.img");
	if(a==3)track_machine();
	if(a==4) encrypt_messages("decrypted_p4.img");
	}
} 
void main(){
	menu(); /* call the menu */
}