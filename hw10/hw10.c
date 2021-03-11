#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.1415926
typedef struct point   // A point have x and y coordinate
{
	float x;
	float y;
}point;
//**********************
typedef struct line  // A line must have a start and finish point
{
	point startPoint;
	point finishPoint;
}line;
//**********************
struct polygon  // A polygon form of some points or some lines, sometimes both of them
{
	point P1,P2,P3,P4;
	line L12,L23,L34,L41;
}PG1,PG2;
//*************************
double CalArea(point P1,point P2,point P3,point P4){// calculation area of the given polygon
	return abs(P1.x*P2.y+P2.x*P3.y+P3.x*P4.y+P4.x*P1.y-(P1.y*P2.x+P2.y*P3.x*P3.y*P4.x+P4.y*P1.x))/2;
}
double CalDistance(point p1,point p2){  //calculation distance between two dots
	return sqrt(pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2));
}
double CalAngle(line L12,line L23){  // calculation angle betwwen two lines
	 float a=0,b=0,c=0,x;
	 if(L12.finishPoint.x==L23.startPoint.x && L12.finishPoint.y==L23.startPoint.y){  // if start and finish points are equal
	 	b=CalDistance(L12.finishPoint,L12.startPoint);
	 	c=CalDistance(L23.finishPoint,L23.startPoint);
	 	a=CalDistance(L12.startPoint,L23.finishPoint);
	 	x=(pow(b,2)+pow(c,2)-pow(a,2))/(2*b*c);   // cosinus theorem
	 	return acos(x)*180.0/PI;
	 }
	 else if(L12.startPoint.y==L23.finishPoint.y && L12.startPoint.x==L23.finishPoint.x){
	 	b=CalDistance(L12.finishPoint,L12.startPoint);
	 	c=CalDistance(L23.finishPoint,L23.startPoint);
	 	a=CalDistance(L12.finishPoint,L23.startPoint);
	 	x=(pow(b,2)+pow(c,2)-pow(a,2))/(2*b*c);
	 	return acos(x)*180.0/PI;
	 }
	 else{   // if these lines doesnt intersect anywhere
	 	return 0.0;
	 }
	 
}

double CalLenght(point P1,point P2,point P3,point P4){   // calculation the perimeter of polygon
	return CalDistance(P1,P2)+CalDistance(P2,P3)+CalDistance(P3,P4)+CalDistance(P4,P1);
}
void PrintinFile(float x, float y, float z, float t, float m,float n){  // print in output.txt file, every data
	FILE *fp=fopen("output.txt","w");
	fprintf(fp,"Distance(P1,P2) = %.1f\n",x);
	fprintf(fp,"Distance(P1,P3) = %.1f\n",y);
	fprintf(fp,"Angle(L12,L23) = %.1f\n",z);
	fprintf(fp,"Angle(L12,L34) = %.1f\n",n);
	fprintf(fp,"Length(PG1) = %.1f\n",t);
	fprintf(fp,"Area(PG1) = %.1f\n",m);
	fclose(fp);
}
void control(point P1,point P2,point P3,point P4,line L12,line L23,line L34,line L41){   // calculation function
	float x,y,z,t,m,n;   // for easy using, I gave a character for every variable
	x=CalDistance(P1,P2); //calculation distance between two dots
	y=CalDistance(P1,P3);
	z=CalAngle(L12,L23);  // calculation angle betwwen two lines
	n=CalAngle(L12,L34);
	t=CalLenght(P1,P2,P3,P4); // calculation the perimeter of polygon
	m=CalArea(P1,P2,P3,P4);  // calculation area of the given polygon
	PrintinFile(x,y,z,t,m,n);
}
void EqualizeLine(point P1,point P2,point P3,point P4){   // using point data, define the lines start and finish points
	line L12,L23,L34,L41;
	L12.startPoint=P1;  // define the given lines with point values
	L12.finishPoint=P2;
	L23.startPoint=P2;
	L23.finishPoint=P3;
	L34.startPoint=P3;
	L34.finishPoint=P4;
	L41.startPoint=P4;
	L41.finishPoint=P1;
	control(P1,P2,P3,P4,L12,L23,L34,L41);

}

void EqualizePoint(char arr[55][20]){  // carry data from arr to struct variables
	point P1,P2,P3,P4;  
	char *ptr;
	P1.x= strtof(arr[2],&ptr);   // read string in arr and transform the string to float variable
	P1.y= strtof(arr[3],&ptr);
	P2.x= strtof(arr[5],&ptr);
	P2.y= strtof(arr[6],&ptr);
	P3.x= strtof(arr[8],&ptr);
	P3.y= strtof(arr[9],&ptr);
	P4.x= strtof(arr[11],&ptr);
	P4.y= strtof(arr[12],&ptr);
	EqualizeLine(P1,P2,P3,P4); 
}
void ReadFile(char *FileName,char arr[55][20]){
	FILE *fp=fopen(FileName,"r");
	int x=0,y=0;
	char a;
	char str[100][100],str1[5]={'/','/'};  // read every line until '//' 
	while(x!=61){
		fscanf(fp,"%s",str[x]); 
		if(strcmp(str[x],str1)!=0){  // if readed data isnt equal '//'
			strcpy(arr[y],str[x]);
			y++;   // for arr
		}
		else if(strcmp(str[x],str1)==0){  // if read '//' starts the reading empty
			fscanf(fp,"%c",&a);
			while(a!='\n'){       // read empty until reach end of the line
				fscanf(fp,"%c",&a);
			}
		}
		x++;   // for str
	}
	fclose(fp);
	
}
void main(){
	char arr[55][20];     // for using data from file
	ReadFile("commands.txt",arr);
	EqualizePoint(arr);
}