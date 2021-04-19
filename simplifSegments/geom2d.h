//
// Created by fabie on 16/01/2020.
//

#ifndef GEOM2D_H
#define GEOM2D_H

#include <stdbool.h>

typedef struct Vecteur {
double x , y ; /* coordonnees */
} Vecteur ;

typedef struct Point {
        double x , y ; /* coordonnees */
} Point ;

typedef struct segment {
	Point a , b ;
} segment ;

typedef struct Bezier2 {
    Point C0, C1, C2;
} bezier2;

typedef struct Bezier3 {
    Point C0, C1, C2, C3;
} bezier3;

/* cree le point de coordonnees ( x , y ) */
Point set_point (double x , double y ) ;
/* cree le vect de coordonnees ( x , y ) */
Vecteur set_vect (double x , double y ) ;
/* cree le segment d'extremites ( x , y ) */
segment set_segment (Point p1 , Point p2 );

bezier2 set_bezier2(Point C0, Point C1, Point C2);

bezier3 set_bezier3(Point C0, Point C1, Point C2, Point C3);
/* somme P1+P2 */
Point add_point ( Point P1 , Point P2 ) ;
/* somme V1+V2 */
Vecteur add_vect ( Vecteur V1 , Vecteur V2 );
/* vecteur correspondant au bipoint AB */
Vecteur vect_bipoint ( Point A, Point B ) ;
/* produit scalaire de V1 et V2 */
double scalar_product ( Vecteur V1 , Vecteur V2 );
/* produit v par le scalaire lambda */
Vecteur multiply_vect ( Vecteur v, double lambda );
/* produit v par le scalaire lambda */
double norm_vect ( Vecteur V );
/* distance entre P1 et P2 */
double dist_point ( Point P1 , Point P2 );
/* Test l'égalité entre V1 et V2 */
bool egal_vect ( Vecteur V1 , Vecteur V2);
/* Test l'égalité entre P1 et P2 */
bool egal_point ( Point P1 , Point P2 );

void afficher_vect ( Vecteur V );

void afficher_point ( Point P );

double point_segment (Point P, segment S) ;

Point pointBezier2(double t, bezier2 courbe2);

Point pointBezier3(double t, bezier3 courbe3);

bezier3 conv_bezier2_bezier3(bezier2 courbe2);

#endif //GEOM2D_H
