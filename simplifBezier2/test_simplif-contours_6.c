#include "image.h"
#include "contours.h"
#include "fichier_EPS.h"

int main(int argc,char *argv[]){
    Image I;
    sequence_tab_bezier2 *res = (sequence_tab_bezier2 *) malloc(sizeof(sequence_tab_bezier2));
    init_sequence_tab_bezier2(res);
    sequence_tab_point tab_contours;
    init_sequence_tab_point(&tab_contours);
    FILE *f;

    if(argc != 4 ) ERREUR_FATALE("Utilisation commande : ./test_simplif-bezier3 fichier_image fichier_resultat distanceSeuil\n");

    double d = atof(argv[3]);
    printf("Seuil : %f\n",d);
    I = lire_fichier_image(argv[1]);
    stocker_pls_contours(I,&tab_contours);
    afficher_stats(&tab_contours);
    f = fopen(argv[2],"w");
    if(f==NULL) ERREUR_FATALE("Impossible d'ouvrir le fichier résultat en écriture.\n");

    res = simplif_pls_contours_bezier2(&tab_contours,d);

    afficher_contours_bezier2_simple(res,stdout);
    dessiner_pls_bezier2(res,I.L,I.H,f);
    fclose(f);
}

/**/

/*Point C0 = set_point(0,4);
    Point C1 = set_point(8,2);
    Point C2 = set_point(0,0);
    //Point C3 = set_point();

    bezier2 courbe2 = set_bezier2(C0,C1,C2);
    printf("La courbe de bézier 2 correspondant : C0 : (%f,%f) C1: (%f,%f) C2 : (%f,%f)\n",
           courbe2.C0.x, courbe2.C0.y, courbe2.C1.x, courbe2.C1.y, courbe2.C2.x, courbe2.C2.y);

    double t = 1;
    Point Ct = pointBezier2(t,courbe2);
    printf("C_2(t) = (%f,%f) \n",Ct.x,Ct.y);

    bezier3 courbe3 = conv_bezier2_bezier3(courbe2);
    printf("La courbe de bézier 3 correspondant : C0 : (%f,%f) C1: (%f,%f) C2 : (%f,%f) C3 : (%f,%f)\n",
            courbe3.C0.x, courbe3.C0.y, courbe3.C1.x, courbe3.C1.y, courbe3.C2.x, courbe3.C2.y, courbe3.C3.x, courbe3.C3.y);

    Ct = pointBezier3(t,courbe3);
    printf("C_3(t) = (%f,%f) \n",Ct.x,Ct.y);*/

/*tableau_point tab_point;
    tab_point.longueur=9;
    tab_point.tab[0] = set_point(0,0);
    tab_point.tab[1] = set_point(1,0);
    tab_point.tab[2] = set_point(1,1);
    tab_point.tab[3] = set_point(1,2);
    tab_point.tab[4] = set_point(2,2);
    tab_point.tab[5] = set_point(3,2);
    tab_point.tab[6] = set_point(3,3);
    tab_point.tab[7] = set_point(4,3);
    tab_point.tab[8] = set_point(5,3);

    bezier2 courbe2 = approx_contour(&tab_point,0,tab_point.longueur-1);
    printf("La courbe de bézier 2 correspondant : C0 : (%f,%f) C1: (%f,%f) C2 : (%f,%f)\n",
           courbe2.C0.x, courbe2.C0.y, courbe2.C1.x, courbe2.C1.y, courbe2.C2.x, courbe2.C2.y);
    for(int i=1;i<tab_point.longueur-1;i++){
        double lambda = dist_point_bezier2(i,&tab_point,courbe2);
        printf("\nd(P_i , c(t_i)) = %f \n",lambda);
    }*/