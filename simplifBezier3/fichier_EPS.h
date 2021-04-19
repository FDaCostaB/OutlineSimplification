#include <stdio.h>
#include "geom2d.h"
#include "contours.h"


//Ecrit l'entête du fichier EPS
void en_tete(int xmin, int yymax, FILE *f);

//Déplace le curseur au point d ( grâce a moveto)
void deplacer_curseur(Point d, FILE *f);

//Créer une ligne depuis le curseur vers l et déplace le curseur au point l ( grâce a lineto)
void creer_ligne(Point l, FILE *f);

//Créer un cercle de centre c, de rayon r
void creer_cercle(float r, Point c, FILE *f);

//Créer une bezier 2 correspondant à courbe2
void creer_bezier2(bezier2 courbe2,FILE *f);

//Créer une bezier 3 correspondant à courbe3
void creer_bezier3(bezier3 courbe3,FILE *f);

//Dessine les segments de tab_point ( en couplant chaque n pair avec n+1)
void dessiner_contour(tableau_point * tab_point, int Mode,int xmax, int ymax, FILE *f);

//Dessine les segments de chaque contours de la liste chainee de contours (seq)
void dessiner_pls_contours(sequence_tab_point *seq,int xmax, int ymax, FILE *f);

//Dessine les segments de tab_seg (en prenant un tableau de couple de point segment)
void dessiner_pls_seg(sequence_tab_seg *seq, int xmax, int ymax, FILE *f);

//Dessine les courbes de bezier2 de la liste chainee de courbe de bezier 2 (seq)
//en inversant les corrdonnees y de chaque point de chaque bezier puis en utilisant creer_bezier2
void dessiner_pls_bezier2(sequence_tab_bezier2 *seq, int xmax, int ymax, FILE *f);

//Dessine les courbes de bezier3 de la liste chainee de courbe de bezier 3 (seq)
//en inversant les corrdonnees y de chaque point de chaque bezier puis en utilisant creer_bezier3
void dessiner_pls_bezier3(sequence_tab_bezier3 *seq, int xmax, int ymax, FILE *f);