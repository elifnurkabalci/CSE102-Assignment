#include "codeps.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Figure Figureee(){
	Figure *fig= start_figure(500,500);
	set_thickness_resolution(fig,20,0.8);
	Color c;
	c.red=0;
	c.green=0;
	c.blue=0;
	set_color(fig,c);

	return *fig;
}
 void main(){
 	int size1=10;
 	int size2=20;
 	int i;
 	Point2D * width_height;
 	Figure *figures=(Figure*)malloc(size1*sizeof(Figure));
 	Point2D *poly_line= (Point2D*)malloc(size2*sizeof(Point2D));

 	
 	//draw_fx
 	figures[0]=Figureee();
 	draw_fx(&figures[0],sin,0.0,10.0,3);
 	export_eps(&figures[0],"draw_fx.eps");
	
 	//draw_polyline
 	figures[1]=Figureee();
 	for(i=0; i<size2; i++){
 		poly_line[i].x=i;
 		poly_line[i].y=i;
 	}
 	draw_polyline(poly_line,size2);
 	export_eps(&figures[1],"draw_polyline.eps");
	

 	//draw_polygon
 	figures[2]=Figureee();
 	draw_polygon(poly_line);
 	export_eps(&figures[2],"draw_polygon.eps");
	
 	//draw_ellips
 	figures[3]=Figureee();
 	Point2D *center=(Point2D*)malloc(sizeof(Point2D));
 	center->x=0.0;
 	center->y=0.0;
 	width_height->x=80.0;
 	width_height->y=40.0;
 	draw_ellipse(center,width_height,&figures[3]);
 	export_eps(&figures[3],"draw_ellips.eps");

 	//scale_figure in draw_fx
 	scale_figure(30.0,30.0,&figures[0]);
 	export_eps(&figures[0],"scale_fx.eps");

 	//resize_figure
 	Point2D ur,ll;
 	ur.x = 60;
 	ur.y = 30;
 	ll.x =-60;
 	ll.y =-30;
 	resize_figure(ur,ll,&figures[3]);
 	export_eps(&figures[3],"resize_figure.eps");

 	//append_figure
 	figures[4]=Figureee();
 	Point2D *center1=(Point2D*)malloc(sizeof(Point2D));
 	center1->x=0.0;
 	center1->y=0.0;
 	width_height->x=160.0;
 	width_height->y=40.0;
 	draw_ellipse(center,width_height,&figures[4]);
 	append_figures(&figures[4],&figures[3]);
 	export_eps(&figures[4],"append.eps");
	

 }