//
// Created by fabie on 21/01/2020.
//

#include "contours.h"
#include "geom2d.h"
#include"types_macros.h"
#include <stdbool.h>
#include <math.h>

void init_sequence(tableau_point *tab_point){
    tab_point->longueur=0;
}

void init_sequence_tab_point(sequence_tab_point *seq_contour){
    seq_contour->tete = NULL;
    seq_contour->taille = 0;
}

void init_sequence_tab_segment(sequence_tab_seg *seq_contour){
    seq_contour->tete = NULL;
    seq_contour->taille = 0;
}

void init_sequence_tab_bezier2(sequence_tab_bezier2 *seq_contour){
    seq_contour->tete = NULL;
    seq_contour->taille = 0;
}

/*void memoriser_contour(sequence *seq_point,sequence_contour *seq_contour){
    cellule_contour *curr;
    cellule_contour *new =  (cellule_contour*) malloc(sizeof(cellule_contour));
    new->seq_point = seq_point;
    new->suivant=NULL;
    seq_contour->taille = (seq_contour->taille) + 1;

    if(seq_contour->tete == NULL) {
        seq_contour->tete = new;
    }
    else {
        curr = seq_contour->tete;
        while(curr->suivant != NULL){
            curr = curr->suivant;
        }
        curr->suivant = new;
    }
}*/

void memoriser_contour(sequence_tab_seg *seq_contour,tableau_seg *tab_seg){
    cellule_tab_seg *curr;
    cellule_tab_seg *new =  (cellule_tab_seg*) malloc(sizeof(cellule_tab_seg));
    new->tab_seg = tab_seg;
    new->suivant=NULL;
    seq_contour->taille = (seq_contour->taille) + 1;
    if(seq_contour->tete == NULL) {
        seq_contour->tete = new;
    }
    else {
        curr = seq_contour->tete;
        while(curr->suivant != NULL){
            curr = curr->suivant;
        }
        curr->suivant = new;
    }
}

void memoriser_contour_point(sequence_tab_point *seq_contour,tableau_point *tab_point){
    cellule_tab_point *curr;
    cellule_tab_point *new =  (cellule_tab_point*) malloc(sizeof(cellule_tab_point));
    new->tab_point = tab_point;
    new->suivant=NULL;
    seq_contour->taille = (seq_contour->taille) + 1;
    if(seq_contour->tete == NULL) {
        seq_contour->tete = new;
    }
    else {
        curr = seq_contour->tete;
        while(curr->suivant != NULL){
            curr = curr->suivant;
        }
        curr->suivant = new;
    }
}

/* faire avancer le robot d'une case */
void avancer(Robot * r){
    switch (r->o){
        case Nord:
            r->position.y = r->position.y-1;
            break;
        case Sud:
            r->position.y = r->position.y+1;
            break;
        case Est:
            r->position.x = r->position.x+1;
            break;
        case Ouest:
            r->position.x = r->position.x-1;
            break;
    }
}

/* faire tourner le robot à gauche */
void tourner_a_gauche(Robot * r){
    switch (r->o){
        case Nord:
            r->o = Ouest;
            break;
        case Sud:
            r->o = Est;
            break;
        case Est:
            r->o = Nord;
            break;
        case Ouest:
            r->o = Sud;
            break;
    }
}

/* faire tourner le robot à droite */
void tourner_a_droite(Robot * r){
    switch (r->o){
        case Nord:
            r->o = Est;
            break;
        case Sud:
            r->o = Ouest;
            break;
        case Est:
            r->o = Sud;
            break;
        case Ouest:
            r->o = Nord;
            break;
    }
}

Point trouver_depart(Image I)
{
    Point p;
    for(int j=0;j<hauteur_image(I);j++){
        for(int i=0;i<largeur_image(I);i++){
            if(I.tab[i+I.L*j]==1 && (j==0 || I.tab[i+I.L*(j-1)]==0)){
                p = set_point((double) i+1, (double) j+1) ;
                return p;
            }
        }
    }
    p = set_point(0.0, 0.0) ;
    return p;
}
void nouvelle_orientation(Image I, Robot * r){
    Point pixelG;
    Point pixelD;
    switch (r->o){
        case Nord:
            pixelG = add_point(r->position,(Point){0.0, 0.0});
            pixelD = add_point(r->position,(Point){1.0, 0.0});
            break;
        case Sud:
            pixelG = add_point(r->position,(Point){1.0, 1.0});
            pixelD = add_point(r->position,(Point){0.0, 1.0});
            break;
        case Est:
            pixelG = add_point(r->position,(Point){1.0, 0.0});
            pixelD = add_point(r->position,(Point){1.0, 1.0});
            break;
        case Ouest:
            pixelG = add_point(r->position,(Point){0.0, 1.0});
            pixelD = add_point(r->position,(Point){0.0, 0.0});
            break;
    }
    if(get_pixel_image(I,pixelG.x,pixelG.y)== NOIR) tourner_a_gauche(r);
    else if (get_pixel_image(I,pixelD.x,pixelD.y)==BLANC) tourner_a_droite(r);
}

void contour(Image I){
    Point p = trouver_depart(I);
    if(egal_point(p,(Point){0.0, 0.0})) ERREUR_FATALE("Image vide \n");
    double x0 = p.x - 1.0;
    double y0 = p.y - 1.0;
    Robot r;
    r.position = set_point(x0, y0);
    r.o = Est;
    bool boucle = true;
    while (boucle){
        afficher_point(r.position);
        avancer (&r);
        nouvelle_orientation(I, &r);
        if (r.position.x==x0 && r.position.y==y0 && r.o==Est){
            boucle=false;
        }
    }
    afficher_point(r.position);
}

void ecrire_fichier (tableau_point *tab_point, FILE *f)
{
    Point p;
    fprintf(f,"%d\n\n",1);
    fprintf(f,"%d\n",tab_point->longueur);
    for(int i=0;i<tab_point->longueur;i++){
        p = tab_point->tab[i];
        fprintf(f, " %.1f %.1f\n", p.x, p.y);
    }
}

void memoriser_position(tableau_point *tab_point, Point p){
    if(tab_point->longueur<LMAX){
        tab_point->tab[tab_point->longueur] = p;
        tab_point->longueur++;
    }
}

void stocker_contour(Image I, tableau_point *tab_point){
    Point p = trouver_depart(I);
    if(egal_point(p,(Point){0.0, 0.0})) ERREUR_FATALE("Image vide \n");
    double x0 = p.x - 1.0;
    double y0 = p.y - 1.0;
    Robot r;
    r.position = set_point(x0, y0);
    r.o = Est;
    bool boucle = true;
    while (boucle){
        memoriser_position(tab_point,r.position);
        avancer (&r);
        nouvelle_orientation(I, &r);
        if (r.position.x==x0 && r.position.y==y0 && r.o==Est){
            boucle=false;
        }
    }
    memoriser_position(tab_point, r.position);

}

int tout_propre(Image I){

    for(int j=0;j<hauteur_image(I);j++){
        for(int i=0;i<largeur_image(I);i++){
            if ((I.tab[i+I.L*j])== 1){
                return false;
            }
        }
    }
    return true;
}

void stocker_pls_contours(Image I, sequence_tab_point *res) {
    Point p;
    Image calque = creer_calque(I);
    while (!tout_propre(calque)) {
        tableau_point *tab_point = (tableau_point*) malloc(sizeof(tableau_point));
        tab_point->longueur = 0;
        p = trouver_depart(calque);
        if (egal_point(p, (Point) {0.0, 0.0})) ERREUR_FATALE("Image vide \n");
        double x0 = p.x - 1.0;
        double y0 = p.y - 1.0;
        Robot r;
        r.position = set_point(x0, y0);
        r.o = Est;
        bool boucle = true;
        while (boucle) {
            memoriser_position(tab_point,r.position);
            if (r.o == Est) set_pixel_image(calque, r.position.x + 1, r.position.y + 1, 0);
            avancer(&r);
            nouvelle_orientation(I, &r);
            if (r.position.x == x0 && r.position.y == y0 && r.o == Est) {
                boucle = false;
            }
        }
        memoriser_position(tab_point,r.position);
        set_pixel_image(calque, r.position.x + 1, r.position.y + 1, 0);
        memoriser_contour_point(res,tab_point);
    }
}

void ecrire_seq (sequence_tab_seg *seq_contour, FILE *f) {
    cellule_tab_seg *curr = NULL;
    curr = seq_contour->tete;
    fprintf(f, "%d\n\n", seq_contour->taille);
    while (curr != NULL){
        fprintf(f, "%d\n", curr->tab_seg->longueur);
        for(int i=0;i<curr->tab_seg->longueur;i++){
            fprintf(f, " [%.1f %.1f , %.1f %.1f] \n", curr->tab_seg->tab[i].a.x, curr->tab_seg->tab[i].a.y, curr->tab_seg->tab[i].b.x, curr->tab_seg->tab[i].b.y);
        }
        curr = curr -> suivant;
    }
}

void afficher_stats(sequence_tab_point *seq_tab_point){
    int n = 0;
    cellule_tab_point *curr;
    curr = seq_tab_point->tete;
    while (curr != NULL){
        n+=(curr->tab_point->longueur-1);
        curr = curr -> suivant;
    }
    printf("NOMBRE DE CONTOURS : %d\n", seq_tab_point->taille);
    printf("NOMBRE DE SEGMENTS : %d\n", n);
}

/*tableau_point sequence_point_to_tableau(sequence *seq_point){
    tableau_point tab_point;
    tab_point.longueur = seq_point->taille;
    cellule_t *curr;
    int i=0;
    if(seq_point->tete == NULL) {
        return tab_point;
    }
    else {
        curr = seq_point->tete;
        tab_point.tab[i] = set_point(curr->p.x,curr->p.y);
        i++;
        while(curr->suivant != NULL){
            curr = curr->suivant;
            tab_point.tab[i] = set_point(curr->p.x,curr->p.y);
            i++;
        }
    }
    if(i!=tab_point.longueur) ERREUR_FATALE("ERREUR CONVERSION LISTE CHAINEE EN TABLEAU\n");
    return tab_point;
}*/

tableau_seg *concat(tableau_seg *L1,tableau_seg *L2){
    int taille = L1->longueur + L2->longueur;
    int i = L1->longueur;
    int j=0;
    if(taille<LMAX){
        while(j<L2->longueur){
            L1->tab[i] = L2->tab[j];
            i++;
            j++;
        }
        if(i!=taille)ERREUR_FATALE("ERREUR CONCATENATION DE TABLEAUX\n");
    } else{
        ERREUR_FATALE("TAILLE INSUFFISANTE POUR CONCATENATION\n");
    }
    L1->longueur = taille;
    return L1;
}

tableau_seg *simplification_douglas_peucker (tableau_point *C,int j1,int j2,double d){
    double dmax = 0;
    int k = j1;
    double dj=0;
    tableau_seg *res = (tableau_seg *) malloc(sizeof(tableau_seg));
    res->longueur=0;
    segment seg_simple = { C->tab[j1], C->tab[j2]};
    for(int j = j1+1;j<j2;j++){
        dj = point_segment(C->tab[j],seg_simple);
        if (dj>dmax){
            dmax = dj;
            k=j;
        }
    }
    if(dmax<=d){
            res->tab[0]=seg_simple;
            res->longueur = 1;
    }else{
        tableau_seg *part1 = (tableau_seg *) malloc(sizeof(tableau_seg));
        tableau_seg *part2 = (tableau_seg *) malloc(sizeof(tableau_seg));
        part1->longueur=0;
        part2->longueur=0;
        part1 = simplification_douglas_peucker(C,j1,k,d);
        part2 = simplification_douglas_peucker(C,k,j2,d);
        res = concat(part1,part2);
    }
    return res;
}

/*void memoriser_contours_simple(sequence_tab_seg *seq, tableau_seg *contour_simple){
    cellule_tab_seg *curr;
    cellule_tab_seg *new =  (cellule_tab_seg*) malloc(sizeof(cellule_tab_seg));
    new->tab_seg = contour_simple;
    new->suivant=NULL;
    seq->taille = (seq->taille) + 1;
    if(seq->tete == NULL) {
        seq->tete = new;
    }
    else {
        curr = seq->tete;
        while(curr->suivant != NULL){
            curr = curr->suivant;
        }
        curr->suivant = new;
    }
}*/

sequence_tab_seg *simplif_pls_contours (sequence_tab_point *seq_contours, double d) {
    cellule_tab_point *curr;
    curr = seq_contours->tete;
    sequence_tab_seg *seq_tab_seg = (sequence_tab_seg *) malloc(sizeof(sequence_tab_seg));
    seq_tab_seg->taille=0;
    seq_tab_seg->tete=NULL;
    int i = 1;
    while (curr != NULL){
        tableau_seg *res = (tableau_seg *) malloc(sizeof(tableau_seg));
        i++;

        res = simplification_douglas_peucker(curr->tab_point,0,curr->tab_point->longueur-1,d);

        memoriser_contour(seq_tab_seg,res);
        curr = curr -> suivant;
    }
    return seq_tab_seg;
}

void afficher_contours_simple(sequence_tab_seg *seq_contours,FILE *f){
    int n = 0, i = 1;
    cellule_tab_seg *curr = seq_contours->tete;
    while (curr != NULL){
        n+=(curr->tab_seg->longueur);
        fprintf(f,"NOMBRE DE SEGMENT(S) DU CONTOUR %d : %d\n", i, curr->tab_seg->longueur);
        i++;
        curr = curr -> suivant;
    }
    fprintf(f,"NOMBRE DE CONTOURS : %d\n", n);
}

void afficher_contours_bezier2_simple(sequence_tab_bezier2 *seq_contours,FILE *f){
    int n = 0, i = 1;
    cellule_tab_bezier2 *curr = seq_contours->tete;
    while (curr != NULL){
        n+=(curr->tab_bezier2->longueur);
        fprintf(f,"NOMBRE DE COURBE(S) DU CONTOUR %d : %d\n", i, curr->tab_bezier2->longueur);
        i++;
        curr = curr -> suivant;
    }
    fprintf(f,"NOMBRE DE CONTOURS : %d\n", n);
}

tableau_bezier2 *concat_bezier(tableau_bezier2 *L1,tableau_bezier2 *L2){
    int taille = L1->longueur + L2->longueur;
    int i = L1->longueur;
    int j=0;
    if(taille<LMAX){
        while(j<L2->longueur){
            L1->tab[i] = L2->tab[j];
            i++;
            j++;
        }
        if(i!=taille)ERREUR_FATALE("ERREUR CONCATENATION DE TABLEAUX\n");
    } else{
        ERREUR_FATALE("TAILLE INSUFFISANTE POUR CONCATENATION\n");
    }
    L1->longueur = taille;
    return L1;
}

void memoriser_bezier2(sequence_tab_bezier2 *seq_bezier2,tableau_bezier2 *tab_bezier2){
    cellule_tab_bezier2 *curr;
    cellule_tab_bezier2 *new =  (cellule_tab_bezier2*) malloc(sizeof(cellule_tab_bezier2));
    new->tab_bezier2 = tab_bezier2;
    new->suivant=NULL;
    seq_bezier2->taille = (seq_bezier2->taille) + 1;
    if(seq_bezier2->tete == NULL) {
        seq_bezier2->tete = new;
    }
    else {
        curr = seq_bezier2->tete;
        while(curr->suivant != NULL){
            curr = curr->suivant;
        }
        curr->suivant = new;
    }
}

double dist_point_bezier2(double ti, Point pj, bezier2 courbe2){
    Point a = pointBezier2(ti, courbe2);
    //printf ( "d((%f,%f) , (%f,%f)) = %f\n", a.x, a.y, pj.x, pj.y,dist_point(a,pj));
    return dist_point(a,pj);
}

double dist_point_bezier3(int i, tableau_point *tab_point, bezier3 courbe3){
    Point a = pointBezier3((double) i / (double) (tab_point->longueur-1), courbe3);
    return dist_point(a,tab_point->tab[i]);
}

bezier2 approx_contour(tableau_point *tab_point, int j1, int j2){
    bezier2 res;
    res.C0 = tab_point->tab[j1];
    res.C2 = tab_point->tab[j2];
    res.C1 = set_point(0,0);
    double omega_i = 0;
    int taille=j2-j1;
    //printf("Longueur : %d\n\n",taille);

    if(taille <= 1) {
        res.C1 = set_point( (tab_point->tab[j1].x + tab_point->tab[j2].x) / 2 , (tab_point->tab[j1].y + tab_point->tab[j2].y) / 2 );
    }
    else{
        for(int i = 1; i<taille; i++){
            double ti = (double)i / (double)(taille);
            Point Ci = set_point(
                    tab_point->tab[j1+i].x - pow(1-ti,2) * res.C0.x - pow(ti,2) * res.C2.x,
                    tab_point->tab[j1+i].y - pow(1-ti,2) * res.C0.y - pow(ti,2) * res.C2.y);
            res.C1 =add_point(res.C1,Ci);
            omega_i = omega_i + 2*ti*(1-ti);
            //printf("c_i = (%f,%f) \n omega_i = %f\n\n", Ci.x/(2*ti*(1-ti)), Ci.y/(2*ti*(1-ti)), 2*ti*(1-ti));
        }
        res.C1 = set_point(res.C1.x / omega_i, res.C1.y / omega_i);
    }
    return res;
}

tableau_bezier2 *simplification_douglas_peucker_bezier2 (tableau_point *C,int j1,int j2,double d){
    int i=0;
    double ti=0;

    double dmax = 0;
    int taille = j2-j1;
    double dj=0;
    int k = j1;
    tableau_bezier2 *res = (tableau_bezier2 *) malloc(sizeof(tableau_bezier2));
    res->longueur=0;
    bezier2 courbe2 = approx_contour(C,j1,j2);

    for(int j = j1+1;j<j2;j++){
        i = j-j1;
        ti = (double) i /(double) taille ;
        dj = dist_point_bezier2(ti,C->tab[j],courbe2);
        if (dj>dmax){
            dmax = dj;
            k=j;
        }
    }
    if(dmax<=d){
        res->tab[0]=courbe2;
        res->longueur = 1;
    }else{
        tableau_bezier2 *part1 = (tableau_bezier2 *) malloc(sizeof(tableau_bezier2));
        tableau_bezier2 *part2 = (tableau_bezier2 *) malloc(sizeof(tableau_bezier2));
        part1->longueur=0;
        part2->longueur=0;
        part1 = simplification_douglas_peucker_bezier2(C,j1,k,d);
        part2 = simplification_douglas_peucker_bezier2(C,k,j2,d);
        res = concat_bezier(part1,part2);
    }
    return res;
}

sequence_tab_bezier2 *simplif_pls_contours_bezier2 (sequence_tab_point *seq_contours, double d) {
    cellule_tab_point *curr;
    curr = seq_contours->tete;
    sequence_tab_bezier2 *seq_tab_bez2 = (sequence_tab_bezier2 *) malloc(sizeof(sequence_tab_bezier2));
    seq_tab_bez2->taille=0;
    seq_tab_bez2->tete=NULL;
    int i = 1;
    while (curr != NULL){
        tableau_bezier2 *res = (tableau_bezier2 *) malloc(sizeof(tableau_bezier2));
        i++;

        res = simplification_douglas_peucker_bezier2(curr->tab_point,0,curr->tab_point->longueur-1,d);

        memoriser_bezier2(seq_tab_bez2,res);
        curr = curr -> suivant;
    }
    return seq_tab_bez2;
}
