//
// Created by fabie on 26/02/2020.
//

#include "geom2d.h"
#include "types_macros.h"

int main(int argc,char *argv[]){
    Point p;
    Point a;
    Point b;
    segment segAB;
    double res;

    if(argc != 7 ) ERREUR_FATALE("Utilisation commande : ./test_image Px Py Ax Ay Bx By\n");

    p.x = atof(argv[1]);
    p.y = atof(argv[2]);
    a.x = atof(argv[3]);
    a.y = atof(argv[4]);
    b.x = atof(argv[5]);
    b.y = atof(argv[6]);
    segAB = set_segment(a,b);
    printf("Calcul de la distance du segment [AB] { (%f, %f) , (%f, %f)} à P (%f, %f)\n",a.x,a.y,b.x,b.y,p.x,p.y);
    res = point_segment(p,segAB);
    printf("Distance de [AB] à P est : %f\n",res);
}