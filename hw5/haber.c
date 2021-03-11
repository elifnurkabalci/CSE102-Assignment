#include<stdio.h>

void append_file(char* file_path, char c){ /* add the readed news in readed_news_id.txt */
	FILE *fps;
	fps=fopen(file_path,"a+");
	fprintf(fps,"%c",c);
	fclose(fps);
}
void read_news(char buffer[500], char file_path[12], int is_Only_Title){ /* read the news */
	int i;
	char c;

	if(is_Only_Title==0){  /* read entire the news */
		for(i=0; i<500; i++){
			printf("%c",buffer[i]);
			if(buffer[i]=='\0'){
				break;
			}
		}
	}
	else if(is_Only_Title==1){
		for(i=0; i<82; i++){ /* read only title */
			printf("%c",buffer[i]);
			if(buffer[i]=='\n'){
				break;
			}
		}
	}
	printf("\n");
	c = file_path[5]; /* readed news id */
	append_file("news/readed_news_id.txt",c); /* add the readed news */
}

double g_func(double f(int x),int a){  /* call the f_func */
	return f(a)*f(a);
}
double f_func(int x){
	return (x*x*x)-(x*x)+2;
}
void read_magic_numbers(char buffer_magic[],char buffer_news[500]){ 
	int a,i;
	char c;
	double y=0.0;
	for(i=0; i<500; i++){
		if(buffer_news[i]=='#'){ /* find the '#' */
			c = buffer_news[i+1]; /* take the in front of number */
			a = c - 48; /* return character to integer */
			y +=g_func(f_func,a); /* call the g_func between f_func */
		}
	
	}
	switch(buffer_magic[0]){
		case 1: printf("Number of tests performed: %f \n",y); break;  /* print the result */
		case 2: printf("Number of sick people: %f \n",y); break;
		case 3: printf("Number of death: %f \n",y); break;
		case 4: printf("Expected number of sick people: %f \n",y); break;
		default: printf("ERROR\n"); break;
	}
}
void menu(){
	char b,c;
	int a,j,i,k,x;
	char buffer[500],buffer_news[500],buffer_magic[10];
	printf("**************Daily Press**************\n");
	printf("Today's news are listed for you:\n");
	printf("Title of 1. news: YENI TIP KORONAVIRUS SALGININDA SON 24 SAAT\n");
	printf("Title of 2. news: Fatih Terim'in kızı Merve Terim patladı! 'Inanılmaz sinirliyim...'\n");
	printf("Title of 3. news: Kapıkoy Gumruk Kapısı'ndaki yolcu giris ve çıkışları geçici süreyle durduruldu\n");
	printf("Title of 4. news: Son dakika… Bakan Selcuk: 7 milyar liraya yakın asgari ücret destegi vereceğiz\n");
	printf("What do you want to do?\n");
	printf("1.Read a new\n");
	printf("2.List the readed news\n");
	printf("3.Get decrypted information from the news\n");
	scanf("%d",&a);                                            
	if(a==1){               /* read the news */
		FILE *fp;
		FILE *fps;
		printf("Which news do you want to read?:\n");
		scanf("%d",&x);
		c = x +'0'; /* x is integer, c is character */
		switch(x){
			case 1: fp=fopen("news/1.txt","r");	break;
			case 2: fp=fopen("news/2.txt","r");	break;
			case 3: fp=fopen("news/3.txt","r");	break;
			case 4: fp=fopen("news/4.txt","r");	break;
			default: printf("This file does not find\n"); break;
		}
		while (fgets(buffer,500,fp)!=NULL){ /* get the characters in file and write in buffer */
	    }
		fps=fopen("news/readed_news_id.txt","r"); /* this news readed or not */
		for(i=0; i<4; i++){
			fscanf(fps,"%c",&b);
			if(b==c){                           /* if new is readed */
				printf("This new is readed. Do you want to read again? Yes(1)/No(0):\n"); 
				scanf("%d",&k);
				if(k==0){
					printf("Would you like to continue? Yes(1)/No(0)\n");
					scanf("%d",&i);
					if(i==0) printf("Good Bye! \n");
					else if(i==1) menu(); 
				}
				else if(k==1){
					printf("Read the entire news(0) or Read the only title(1)\n");
					scanf("%d",&i);
					switch(x){
						case 1:read_news(buffer,"news/1.txt",i); break;
						case 2:read_news(buffer,"news/2.txt",i); break;
						case 3:read_news(buffer,"news/3.txt",i); break;
						case 4:read_news(buffer,"news/4.txt",i); break;
						default: break;
					}
					break;
				}
			}
			else{                     /* if new isnt read */
				printf("Read the entire news(0) or Read the only title(1)\n");
					scanf("%d",&i);
					switch(x){
						case 1:read_news(buffer,"news/1.txt",i); break;
						case 2:read_news(buffer,"news/2.txt",i); break;
						case 3:read_news(buffer,"news/3.txt",i); break;
						case 4:read_news(buffer,"news/4.txt",i); break;
						default: break;
					}
					break;
			}      
		}
		fclose(fps);
		fclose(fp);
			
	}
	else if(a==2){ /* check the new is readed or not */
		FILE *fps;
		fps=fopen("news/readed_news_id.txt","r");
		printf("Readed news are listed below: \n");
		fscanf(fps,"%c",&b);
		while(b!='\n'){
			printf("%c new is readed\n",b);
			fscanf(fps,"%c",&b);
		}
		printf("Do you want to continue? Yes(1)/No(0):\n");
		scanf("%d",&x);
		if(x==1) menu();
		else if(x==0) printf("Good Bye! \n");
		fclose(fps);	
	}
	else if(a==3){     /* decrypt the magic number */
		FILE *fp;
		printf("Which news would you like to decrypt?:\n");
		scanf("%d",&x);
		switch(x){
			case 1: fp=fopen("news/1.txt","r");	break;
			case 2: fp=fopen("news/2.txt","r");	break;
			case 3: fp=fopen("news/3.txt","r");	break;
			case 4: fp=fopen("news/4.txt","r");	break;
			default: printf("This file does not find"); break;
		}
		while (fgets(buffer_news,500,fp)!=NULL)
	        printf("%s",buffer_news);  
	    printf("\n");
	    fclose(fp);		 
		buffer_magic[0] = x;	/* number of news */
		read_magic_numbers(buffer_magic,buffer_news);
	}
	else{
		printf("This commant is not defined \n");
	}
}
void main(){  /* call the menu */
	menu();
}