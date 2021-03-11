#include "codeps.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void new_point(Point2D *strtp,double x, double y); //definition for new function

Figure * start_figure(double width, double height){
	Figure *fig=(Figure*)malloc(sizeof(Figure));

	fig->urx=width/2.0;  // for find the center of figure
	fig->ury=height/2.0;
	fig->llx=-width/2.0; 
	fig->lly=-height/2.0;
}
void set_thickness_resolution(Figure *fig, double thickness, double resolution){
	fig->resolution=resolution;
	fig->thickness=thickness;
}
void set_color(Figure * fig, Color c){
	fig->color.red=c.red;
	fig->color.green=c.green;
	fig->color.blue=c.blue;
}
void draw_fx(Figure * fig, double f(double x), double start_x, double end_x, double step_size){
	Point2D *strtp =(Point2D*)malloc(sizeof(Point2D));  // start point the figure
	strtp->x=start_x;
	strtp->y=f(start_x);
	strtp->next=NULL;
	while(start_x!=(end_x+1.0)){
		new_point(strtp,start_x,f(start_x));
		start_x+=1.0;
	}
	fig->point=strtp;
}
void new_point(Point2D *strtp,double x, double y){
	Point2D *p1;
	Point2D *p2;

	for(p1 = strtp; p1!= NULL; p1=p1->next){   // go to last inserted point
	}
	p2 = (Point2D*)malloc(sizeof(Point2D));
	p1->next=p2;
	p2->x=x;  // connect two node
	p2->y=y;
	p2->next=NULL;
}
void draw_polyline(Point2D * poly_line, int n){
	int i;
	Point2D *point=(Point2D*)malloc(sizeof(Point2D));
	point->x=poly_line[0].x;  // head point
	point->y=poly_line[0].y;
	for(i=0; i<n; i++){
		point->next->x=poly_line[i].x;
		point->next->y=poly_line[i].y;
		point=point->next;
	}
}

void draw_polygon(Point2D *poly_line){
	int i;
	Point2D *point=(Point2D*)malloc(sizeof(Point2D));
	Point2D *temp=(Point2D*)malloc(sizeof(Point2D));
	point->x=poly_line[0].x;  // head point
	point->y=poly_line[0].y;
	temp=point;
	while(poly_line[i-1].x=='\0' || poly_line[i-1].y=='\0'){
		temp->next->x=poly_line[i].x;
		temp->next->y=poly_line[i].y;
		temp=temp->next;
		i++;
	}
	temp->next=point;
}

void draw_ellipse(Point2D *center,Point2D * width_height,Figure *fig){  // point2d array for width and height
	double a,b;
	int i;
	Point2D *temp;
	Figure *negFig=(Figure*)malloc(sizeof(Figure));
	a=(double)width_height->x/2.0;
	b=(double)width_height->y/2.0;
	double f1(double x){  // positive side
		sqrt((1-(pow(x,2)/pow(a,2)))*pow(b,2));  // (x^2 / a^2)+(y^2 / b^2) = 1 // ellips equation
	}											 // we will find the y variable in this functions
	double f2(double x){ // negative side
		-sqrt((1-(pow(x,2)/pow(a,2)))*pow(b,2));  
	}

	fig->thickness=negFig->thickness;
	fig->urx=negFig->urx;
	fig->ury=negFig->ury;
	fig->llx=negFig->llx;
	fig->lly=negFig->lly;

	draw_fx(fig,f1,-a,a,1);
	draw_fx(negFig,f2,-a,a,1);
	append_figures(fig,negFig);
	//if center coordinates are (0,0), we must shift the ellips to figures center
	temp=fig->point;
}

void draw_binary_tree(Tree *root){
}																		//			posY	
void scale_figure(double scale_x, double scale_y, Figure *fig){    	 	//           |    
	double posX,negX,posY,negY,centerX,centerY;							//		     |
	Point2D *temp;	//	for not lose fig->point data		            //	negX-----------posX	
	posX=temp->x;													    //			 |
	posY=temp->y;													    //			 |
	negX=temp->x;													    //          negY
	negY=temp->y;
	for(temp=fig->point; temp!= NULL; temp= temp->next){
		if(temp->x > posX){					// found the extreme points of the shape from all directions
			posX=temp->x;
		}
		if(temp->y > posY){
			posY=temp->y;
		}
		if(temp->x < posX){
			negX=temp->x;
		}
		if(temp->y < posY){
			negY=temp->y;
		}
	}
	// after the found the extreme points of the shape, find the center 
	// scaling the figure according to center of figure because of become regular scaling
	centerX=(posX+negX)/2.0;
	centerY=(posY+negY)/2.0;

	for(temp=fig->point; temp!=NULL; temp=temp->next){
		temp->x=((temp->x-centerX)*scale_x)+centerX;
		temp->y=((temp->y-centerY)*scale_y)+centerY;
	}
}

void resize_figure(Point2D start_roi, Point2D end_roi,Figure *fig){
	fig->urx=end_roi.x;
	fig->ury=end_roi.y;
	fig->llx=start_roi.x;
	fig->lly=start_roi.y;
}

void append_figures(Figure *fig1,Figure *fig2){
	Point2D *p1,*p2;
	p1=fig1->point;
	p2=fig2->point;
	for(; p1!=NULL; p1=p1->next){
	}
	if(p1->x==p2->x && p1->y==p2->y){  // merge to two figure 
	}
	else if(p1->next!=p2){  // we want to p1 go to figure 2's point
		for(; p1->x!=p2->x; p1->x+=0.1){
		}
	}
	p1->next=p2;
}

void export_eps(Figure * fig, char * file_name){
	FILE *fp=fopen(file_name,"wt");
	Point2D *temp;

	fprintf(fp,"%%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf(fp,"%%%%BoundingBox: %d %d %d %d\n",(int)fig->llx,(int)fig->lly,(int)fig->urx,(int)fig->ury);
	fprintf(fp,"%d setlinewidth\n",(int)fig->thickness);
	fprintf(fp,"%.1f %.1f %.1f setrgbcolor",fig->color.red,fig->color.green,fig->color.blue);
	fprintf(fp,"%.1f %.1f moveto\n",fig->point->x,fig->point->y);  // starting point

	for(temp=fig->point; temp!=NULL; temp=temp->next){
		if(temp->next==NULL){
			fprintf(fp,"%.1f %.1f moveto\n",temp->x,temp->y);
		}
		else if(temp->next!=NULL){
			fprintf(fp,"%.1f %.1f lineto\n",temp->x,temp->y);
		}
	}
	fprintf(fp,"stroke\n");
	fclose(fp);
}