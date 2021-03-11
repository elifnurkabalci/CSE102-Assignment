#ifndef CODEPS_H
#define CODEPS_H

struct Point2D{
	double x,y;
	struct Point2D *next; 
};
typedef struct Point2D Point2D;
//**********************************
struct Color{
	double red,green,blue;  
};
typedef struct Color Color;
//**********************************
struct Figure{
	double urx, ury, llx, lly, resolution, thickness; 
	Color color;
	Point2D *point;
};
typedef struct Figure Figure;
//*********************************
struct Tree{
	int data;
	struct Tree *right;
	struct Tree *left;
};
typedef struct Tree Tree;
//*********************************

Figure * start_figure(double width, double height);

void set_thickness_resolution(Figure *fig, double thickness, double resolution);

void set_color(Figure * fig, Color c);

void draw_fx(Figure * fig, double f(double x), double start_x, double end_x, double step_size);

void draw_polyline(Point2D * poly_line, int n);

void draw_polygon(Point2D *poly_line);

void draw_ellipse(Point2D *center,Point2D * width_height, Figure *fig);

void draw_binary_tree(Tree *root);

void scale_figure(double scale_x, double scale_y, Figure *fig);

void resize_figure(Point2D start_roi, Point2D end_roi, Figure *fig);

void append_figures(Figure *fig1,Figure *fig2);

void export_eps(Figure * fig, char * file_name);

#endif 