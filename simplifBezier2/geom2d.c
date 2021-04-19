//
// Created by fabie on 16/01/2020.
//

#include <stdio.h>
#include <math.h>
#include "geom2d.h"

Point set_point (double x , double y )
{
Point P = {x , y } ;
return P;
}
Vecteur set_vect (double x , double y )
{
    Vecteur V = {x , y } ;
    return V;
}
segment set_segment (Point p1 , Point p2 )
{
    segment S = {p1 , p2 } ;
    return S;
}
bezier2 set_bezier2(Point C0, Point C1, Point C2){
    bezier2 courbe2 = {C0 , C1 , C2 };
    return  courbe2;
}
bezier3 set_bezier3(Point C0, Point C1, Point C2, Point C3){
    bezier3 courbe3 = {C0 , C1 , C2 , C3};
    return  courbe3;
}
Vecteur vect_bipoint ( Point A, Point B)
{
    Vecteur V = {B.x - A.x , B.y - A.y } ;
    return V;
}
Point add_point ( Point P1 , Point P2 )
{
    return set_point (P1.x + P2.x , P1.y + P2.y ) ;
}
Vecteur add_vect ( Vecteur V1 , Vecteur V2 )
{
    return set_vect(V1.x + V2.x , V1.y + V2.y ) ;
}
Vecteur multiply_vect ( Vecteur V, double lambda )
{
    Vecteur V0 = {lambda * V.x, lambda * V.y } ;
    return V0;
}
double scalar_product ( Vecteur V1 , Vecteur V2)
{
    return (V1.x * V2.x + V1.y *  V2.y ) ;
}

double norm_vect ( Vecteur V )
{
    return sqrt ( (V.x * V.x) + (V.y * V.y) );
}

double dist_point ( Point P1 , Point P2 ){
    return norm_vect(vect_bipoint(P1,P2));
}

bool egal_vect ( Vecteur V1 , Vecteur V2){
    return (V1.x == V2.x && V1.y == V2.y);
}

bool egal_point ( Point P1 , Point P2 ){
    return (P1.x == P2.x && P1.y == P2.y);
}

void afficher_point ( Point P ){
    printf("Coordonnées du point : %f %f\n",P.x, P.y);
    return ;
}

void afficher_vect ( Vecteur V ){
    printf("Coordonnées du vecteur : %f %f\n",V.x, V.y);
    return ;
}

double point_segment (Point P, segment S) {
	Point Q;
	Vecteur V1;
	Vecteur V2;
	double D;
	double L;
	if (S.a.x == S.b.x && S.a.y == S.b.y){
		D=dist_point(S.a,P);
	}
	else {
		V1=vect_bipoint ( S.a ,  P );
		V2=vect_bipoint ( S.a ,  S.b );
		L= (scalar_product (V1,V2))/( scalar_product (V2,V2));
		if (L<0){
			D=dist_point(S.a,P);
		}
		if (L>1){
			D=dist_point(S.b,P);
		}
		if ((L<=1)&&(L>=0)){
			Q.x=S.a.x+L*(S.b.x - S.a.x);
			Q.y=S.a.y+L*(S.b.y - S.a.y);
			D=dist_point(Q,P);
		}
	}
	
	return D;
}

Point pointBezier2(double t, bezier2 courbe2){
    Point res;
    res.x = courbe2.C0.x * (1-t) * (1-t) + courbe2.C1.x * 2*t*(1-t) + courbe2.C2.x * t * t;
    res.y = courbe2.C0.y * (1-t) * (1-t) + courbe2.C1.y * 2*t*(1-t) + courbe2.C2.y * t * t;
    return res;
}

Point pointBezier3(double t, bezier3 courbe3){
    Point res;
    res.x = courbe3.C0.x * pow(1-t,3) + courbe3.C1.x * 3*t*pow(1-t,2) + courbe3.C2.x * 3*pow(t,2)*(1-t) + courbe3.C3.x * pow(t,3);
    res.y = courbe3.C0.y * pow(1-t,3) + courbe3.C1.y * 3*t*pow(1-t,2) + courbe3.C2.y * 3*pow(t,2)*(1-t) + courbe3.C3.y * pow(t,3);
    return res;
}

bezier3 conv_bezier2_bezier3(bezier2 courbe2){
    bezier3 res;

    res.C0 = set_point(courbe2.C0.x, courbe2.C0.y);
    res.C3 = set_point(courbe2.C2.x, courbe2.C2.y);

    res.C1 = set_point( (courbe2.C0.x + 2*courbe2.C1.x) / 3 , (courbe2.C0.y + 2*courbe2.C1.y) / 3 );

    res.C2 = set_point( (2*courbe2.C1.x + courbe2.C2.x) / 3 , (2*courbe2.C1.y + courbe2.C2.y) / 3);

    return res;
}