#include <stdio.h>
#include "geom2d.h"
#include "contours.h"

void en_tete(int xmin, int yymax, FILE *f);

void deplacer_curseur(Point d, FILE *f); 

void creer_ligne(Point l, FILE *f);

void creer_cercle(float r, Point c, FILE *f);

void creer_bezier2(bezier2 courbe2,FILE *f);

void dessiner_contour(tableau_point * tab_point, int Mode,int xmax, int ymax, FILE *f);

void dessiner_pls_contours(sequence_tab_point *seq,int xmax, int ymax, FILE *f);

void dessiner_pls_seg(sequence_tab_seg *seq, int xmax, int ymax, FILE *f);

void dessiner_pls_bezier2(sequence_tab_bezier2 *seq, int xmax, int ymax, FILE *f);