#include <stdio.h>
#include "fichier_EPS.h"

void en_tete(int xmax,int ymax, FILE *f){
	fprintf(f,"%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf(f,"%%%BoundingBox: 0 0 %d %d\n", xmax, ymax);
	}

void deplacer_curseur(Point d,FILE *f){
	fprintf(f,"%d %d moveto\n",(int)d.x, (int)d.y);
	}

void creer_ligne(Point l, FILE *f){
	fprintf(f,"%d %d lineto\n",(int)l.x, (int)l.y);
	}

void creer_cercle(float r, Point c, FILE *f){
	fprintf(f,"newpath\n %d %d 0.5 0 360 arc\nfill\nclosepath\n",(int)c.x,(int)c.y);
	}

void creer_bezier2(bezier2 courbe2,FILE *f){
    bezier3 courbe3 = conv_bezier2_bezier3(courbe2);
    fprintf(f,"%d %d %d %d %d %d curveto\n",(int)courbe3.C1.x,(int)courbe3.C1.y,(int)courbe3.C2.x,(int)courbe3.C2.y,(int)courbe3.C3.x,(int)courbe3.C3.y);
}

void dessiner_contour(tableau_point *tab_point, int Mode,int xmax, int ymax, FILE *f){
	Point p;
	en_tete(xmax,ymax,f);
    if(Mode ==2){
        p=tab_point->tab[0];
	    p.y=ymax - p.y;
	    creer_cercle(0.2,p,f);
	}
	fprintf(f,"%d %d moveto\n", (int)p.x, ymax - (int)p.y);
	for(int i = 1; i < tab_point->longueur; i++){
        p=tab_point->tab[i];
		p.y = ymax - p.y;
		if(Mode==2){
			creer_cercle(0.2,p,f);
			deplacer_curseur(p,f);
		}
		creer_ligne(p, f);
	}
	if (Mode==1||Mode==2) fprintf(f,"stroke\n");
	if (Mode==3) fprintf(f,"fill\n");
	fprintf(f,"showpage\n");
}

void dessiner_pls_contours(sequence_tab_point *seq, int xmax, int ymax, FILE *f){
    cellule_tab_point *curr=seq->tete;
    Point p=curr->tab_point->tab[0];
    en_tete(xmax,ymax,f);
    while (curr != NULL){
        fprintf(f,"%d %d moveto\n", (int)p.x, ymax - (int)p.y);
        for(int i = 1; i <curr->tab_point->longueur; i++){
            p=curr->tab_point->tab[i];
            p.y = ymax - p.y;
            creer_ligne(p, f);
        }
        curr = curr -> suivant;
        if(curr != NULL) p=curr->tab_point->tab[0];
    }
    fprintf(f,"fill\n");
    fprintf(f,"showpage\n");
}

void dessiner_pls_seg(sequence_tab_seg *seq, int xmax, int ymax, FILE *f){
    cellule_tab_seg *curr=seq->tete;
    Point p=curr->tab_seg->tab[0].a;
    en_tete(xmax,ymax,f);
    while (curr != NULL){
        fprintf(f,"%d %d moveto\n", (int)p.x, ymax - (int)p.y);
        for(int i = 1; i <curr->tab_seg->longueur; i++){
            p=curr->tab_seg->tab[i].a;
            p.y = ymax - p.y;
            creer_ligne(p, f);
        }
        p=curr->tab_seg->tab[curr->tab_seg->longueur-1].b;
        p.y = ymax - p.y;
        creer_ligne(p, f);
        curr = curr -> suivant;
        if(curr != NULL) p=curr->tab_seg->tab[0].a;
    }
    fprintf(f,"fill\n");
    fprintf(f,"showpage\n");
}

void dessiner_pls_bezier2(sequence_tab_bezier2 *seq, int xmax, int ymax, FILE *f){
    bezier2 courbe2;
    cellule_tab_bezier2 *curr=seq->tete;
    Point p= curr->tab_bezier2->tab[0].C0;
    en_tete(xmax,ymax,f);
    while (curr != NULL){
        fprintf(f,"%d %d moveto\n", (int)p.x, ymax - (int)p.y);
        for(int i = 0; i <curr->tab_bezier2->longueur; i++){
            courbe2=curr->tab_bezier2->tab[i];
            courbe2.C0.y = ymax - courbe2.C0.y;
            courbe2.C1.y = ymax - courbe2.C1.y;
            courbe2.C2.y = ymax - courbe2.C2.y;
            creer_bezier2(courbe2, f);
        }
        curr = curr -> suivant;
        if(curr != NULL) p=curr->tab_bezier2->tab[0].C0;
    }
    fprintf(f,"fill\n");
    fprintf(f,"showpage\n");
}