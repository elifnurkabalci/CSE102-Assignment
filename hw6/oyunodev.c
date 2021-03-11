#include<stdio.h>
#include<stdlib.h> /* srand() */
#include<time.h> /* time(NULL) */
#include<string.h>

#define NUMCOLS 20 // table column
#define NUMROWS 20 // table row
#define WORDROW 100 // word row
#define WORDCOL 15 // word column
void movedir(int k,int *x,int *y){ // move in the chosen direction
	switch(k){
		case 0:{ // north
			*x -= 1;
		} break; 
		case 1:{ // north east
			*x -= 1;
			*y += 1;
		} break;
		case 2:{ // east
			*y += 1;
		} break;
		case 3:{ // south east
			*x += 1;
			*y += 1;
		} break;
		case 4:{ // south
			*x += 1;
		} break;
		case 5:{ // south west
			*x += 1;
			*y -= 1;
		} break;
		case 6:{ // west
			*y -= 1;
		} break;
		case 7:{ //north west
			*x -= 1;
			*y -= 1;
		} break;
		default:  break;
	}
}
void  chos_dir(int length,int x,int y,char words[WORDROW][WORDCOL],int a,char table[NUMROWS][NUMCOLS]){ //choose direction
	int k,i;
	if(x<10&&y<10) k = (rand()%2)+2; // chosen direction for dont confusion in the table
	if(x<10&&y>10) k = (rand()%2)+4;
	if(x>10&&y<10) k = (rand()%2);
	if(x>10&&y>10) k = ((rand()%2)+6)%8;

	for(i=0; i<length; i++){  // move in the table while word length
		table[x][y]=words[a-1][i];
		movedir(k,&x,&y);
	}
}
void chos_initl_loc(char table[NUMROWS][NUMCOLS],int length,char words[WORDROW][WORDCOL],int a){  // choose inital location
	int x,y;
	x = rand()%(NUMROWS-1)+1;  //row
	y = rand()%(NUMCOLS-1)+1;  // column
	if(y==10||x==10){
		x = rand()%(NUMROWS-1)-1;   // random coordinate 
		y = rand()%(NUMCOLS-1)-1;
	}
	chos_dir(length,x,y,words,a,table);
}
void chos_word(char words[WORDROW][WORDCOL],char table[NUMROWS][NUMCOLS]){ // choose 10 word from words[]
	int a,i,b;
	srand(time(NULL));
	for(i=0; i<10; i++){
		a = rand()%100; // random row number
		b = strlen(words[a-1])-1;  // word length
		printf("%s\n",words[a-1]);
		chos_initl_loc(table,b,words,a); 
	}
	printf("\n");
}
void ReadFromFile(char*FileName,int row,char buf[WORDROW][WORDCOL]){  //convert words.txt to word[]
	int count=0;
	FILE *fp=fopen(FileName,"r");
	while(fgets(buf[count],row,fp)){
		buf[count][strlen(buf[count])-1]='\0';
		count++;
	}
	fclose(fp);
}

void Play(char table[NUMROWS][NUMCOLS],char a[]){   // play the game :)
	char word[20],coli,colf;
	int rowi,rowf,m,i,length,k=0;
	int inx,iny,j,n,result=0,z=0,control;
	while(result!=1){
		printf("Please enter the word and their inital and final coordinates:(For Exit'exit bye'):\n");
		printf("Example: word 0a 0t \n");
		scanf("%s%d%c%d%c",word,&rowi,&coli,&rowf,&colf); // word, row inital, column initial, row final, column final
		if(word[0]=='e'&&word[1]=='x'&&word[2]=='i'&&word[3]=='t'){ // if user press the exit ,the game close
			result = 1;
			break;
		}
		m=(int)coli-97;  //char to int for calculation coordinate
		n=(int)colf-97;
		inx = rowi;   // initial value for row (constant)
		iny = m;      // initial value for column (constant)
		length=strlen(word);
		if(table[rowi][m]==word[0]){
				for(i=1; i<length; i++){
					movedir(k,&rowi,&m);
					if(table[rowi][m]!=word[i]){
						rowi=inx;  //return the initial values
						m = iny; 
						i=1;
						k++;
						length=0;
						for(j=0; j<NUMCOLS; j++)
							word[j]=0;
					}	
					else if(table[rowi][m]==word[i]){
						control=1;
						z++;
					}
				}
		}
		if(control==1){
			for(i=0;i<length;i++){
				table[inx][iny]=(int)table[inx][iny]-32;
				movedir(k,&inx,&iny);						
			}
		}
		while(z==10){
			printf("WELL DONE\n");
			break;
		}
		printf("    ");      //print the table again
		for(i=0;i<NUMCOLS;i++){
		printf("%c ",a[i]);
		}
		printf("\n");
		printf("    ");
		for(i=0;i<NUMCOLS;i++){  
			printf("--");
		}
		printf("\n");
		k=0;
		for(i=0;i<NUMROWS; i++){
			if(k<=9) printf("%d  |",k);
			if(k>9)  printf("%d |",k);
			for(j=0; j<NUMCOLS; j++){
				printf("%c ",table[i][j]);
			}
			k++;
			printf("\n");
		}
		
	}
}
void Fill_in(){   // fill the table from words array and random a[] 
	char a[]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	int i,j,k=0,z;
	char table[NUMROWS][NUMCOLS];
	char words[WORDROW][WORDCOL];
	for(i=0;i<NUMROWS; i++){
		for(j=0; j<NUMCOLS;j++){
			table[i][j]=0;
		}
	}
	ReadFromFile("words.txt",WORDROW,words);
	chos_word(words,table);
	printf("    ");
	for(i=0;i<NUMCOLS;i++){  // coordinate column 
		printf("%c ",a[i]);
	}
	printf("\n");
	printf("    ");
	for(i=0;i<NUMCOLS;i++){  
		printf("--");
	}
	printf("\n");
	for(i=0;i<NUMROWS; i++){
		if(k<=9) printf("%d  |",k);  // coordinate row
		if(k>9)  printf("%d |",k);
		for(j=0; j<NUMCOLS; j++){
			if(table[i][j]==0){ // if table[i][j]  is empty , fill with random word
				z=rand()%19;  
				table[i][j]=a[z];
			}
			printf("%c ",table[i][j]);
		}
		k++;
		printf("\n");
	}
	Play(table,a);  // if everything is okey, you can play the game
}
void main(){
	Fill_in(); 
}
