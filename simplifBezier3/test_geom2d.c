//
// Created by fabie on 16/01/2020.
//

#include <stdio.h>
#include "geom2d.h"

int main(){
    Point A, B, C;
    Vecteur U, V, Nul, UnitaireAbs, UnitaireOrd, Test;
    double d;

    A = set_point( 1.0 , -3.0 ) ;
    B = set_point ( 4.0 , 1.0 ) ;
    UnitaireOrd = set_vect(0.0,1.0) ;
    UnitaireAbs = set_vect(1.0,0.0) ;
    Nul = set_vect(0.0,0.0) ;
    C = add_point (A,B) ;
    V = vect_bipoint (C,A) ;
    U = set_vect (12.0,3.0) ;

    afficher_vect(Nul);
    afficher_vect(UnitaireOrd);
    afficher_vect(V);

    Test = add_vect(UnitaireAbs,UnitaireOrd);
    printf("(1.0 , 0.0) + (0.0 , 1.0) : ");
    afficher_vect(Test);

    d = scalar_product(UnitaireAbs,UnitaireAbs);
    afficher_vect(UnitaireAbs);
    printf("Produit scalaire : %f\n",d);
    d = scalar_product(V,UnitaireAbs);
    afficher_vect(V);
    afficher_vect(UnitaireAbs);
    printf("Produit scalaire : %f\n",d);
    d = scalar_product(U,V);
    afficher_vect(U);
    afficher_vect(V);
    printf("Produit scalaire : %f\n",d);

    printf("(0.0 , 1.0) * 12.0 : ");
    Test = multiply_vect(UnitaireOrd,12.0);
    afficher_vect(Test);
    printf("(1.0 , 0.0) * 0.0 : ");
    Test = multiply_vect(UnitaireOrd,0.0);
    afficher_vect(Test);
    Test = multiply_vect(Nul,30.0);
    printf("(0.0 , 0.0) * 30.0 : ");
    afficher_vect(Test);

    d = norm_vect(Nul);
    printf("Norme Nul : %f\n",d);
    d = norm_vect(V);
    printf("Norme (-4.0 , -1.0) : %f\n",d);

    d = dist_point(A,B);
    printf("Distance A et B : %f\n",d);
    d = norm_vect(vect_bipoint (A,B));
    printf("Norme AB : %f\n",d);

    if (egal_point(A,B)) printf("A est égal à B\n");
    if (egal_point(B,B)) printf("B est égal à B\n");

    if (egal_vect(add_vect(U,V),add_vect(V,U))) printf("U+V est égal à V+U\n");

}
