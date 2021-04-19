//
// Created by fabie on 21/01/2020.
//

#ifndef TACHE3_ROBOT_H
#define TACHE3_ROBOT_H

#define LMAX 50000

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "geom2d.h"
#include "image.h"

typedef enum { Nord, Est, Sud, Ouest } Orientation;

typedef struct {
    Point position;
    Orientation o;
} Robot;

typedef struct tableau_point{
    int longueur;
    Point tab[LMAX];
} tableau_point;

struct cellule_tab_point {
    tableau_point *tab_point;
    struct cellule_tab_point *suivant;
};
typedef struct cellule_tab_point cellule_tab_point;

struct sequence_tab_point {
    int taille;
    cellule_tab_point *tete;
};
typedef struct sequence_tab_point sequence_tab_point;

typedef struct tableau_seg{
    int longueur;
    segment tab[LMAX];
} tableau_seg;

struct cellule_tab_seg {
    tableau_seg *tab_seg;
    struct cellule_tab_seg *suivant;
};
typedef struct cellule_tab_seg cellule_tab_seg;

struct sequence_tab_seg {
    int taille;
    cellule_tab_seg *tete;
};
typedef struct sequence_tab_seg sequence_tab_seg;

typedef struct tableau_bezier2{
    int longueur;
    bezier2 tab[LMAX];
} tableau_bezier2;

struct cellule_tab_bezier2 {
    tableau_bezier2 *tab_bezier2;
    struct cellule_tab_bezier2 *suivant;
};
typedef struct cellule_tab_bezier2 cellule_tab_bezier2;

struct sequence_tab_bezier2 {
    int taille;
    cellule_tab_bezier2 *tete;
};

typedef struct sequence_tab_bezier2 sequence_tab_bezier2;

typedef struct tableau_bezier3{
    int longueur;
    bezier3 tab[LMAX];
} tableau_bezier3;

struct cellule_tab_bezier3 {
    tableau_bezier3 *tab_bezier3;
    struct cellule_tab_bezier3 *suivant;
};
typedef struct cellule_tab_bezier3 cellule_tab_bezier3;

struct sequence_tab_bezier3 {
    int taille;
    cellule_tab_bezier3 *tete;
};

typedef struct sequence_tab_bezier3 sequence_tab_bezier3;

//initialise un tableau de point alias un contour
void init_sequence(tableau_point *tab_point);

//initialise une liste chainee de contours
void init_sequence_tab_point(sequence_tab_point *seq_contour);

//initialise une liste chainee de contours ( sous forme de couple de point a.k.a segment)
void init_sequence_tab_segment(sequence_tab_seg *seq_contour);

//initialise une liste chainee de contours ( sous forme de tableau bézier 2)
void init_sequence_tab_bezier2(sequence_tab_bezier2 *seq_contour);

//initialise une liste chainee de contours ( sous forme de tableau bézier 3)
void init_sequence_tab_bezier3(sequence_tab_bezier3 *seq_contour);

//rajoute le contour (tab_seg) dans la liste chainee de contours (seq_contour)
void memoriser_contour(sequence_tab_seg *seq_contour,tableau_seg *tab_seg);

//rajoute le contour (tab_point) dans la liste chainee de contours (seq_contour)
void memoriser_contour_point(sequence_tab_point *seq_contour,tableau_point *tab_point);

/* faire avancer le robot d'une case */
void avancer(Robot * r);

/* faire tourner le robot à gauche */
void tourner_a_gauche(Robot * r);

/* faire tourner le robot à droite */
void tourner_a_droite(Robot * r);

//Trouve un pixel de depart noir avec son voisin nord blanc
Point trouver_depart(Image I);

//affiche le contour que le robot detecte sur l'image
void contour(Image I);

//écrit les contours dans le fichier f
void ecrire_fichier (tableau_point *tab_point, FILE *f);

//memorise la position du point dans le tableau tab_point
void memoriser_position(tableau_point *tab_point, Point p);

//stocke les contours de l'image I dans le tab_point
void stocker_contour(Image I,tableau_point *tab_point);

//Verifie si l'image généralement le calque est toute/tout blanche
int tout_propre(Image I);

//stocke une liste chainee de contours (donc 1 ou plusieurs contours) dans tabPoint
void stocker_pls_contours(Image I, sequence_tab_point *tabPoint);

//ecrit la sequence de contours dans le fichier f
void ecrire_seq (sequence_tab_seg *seq_contour, FILE *f);

//afficher le nombre de segment de chaque contour et le nombre total de segment
void afficher_stats(sequence_tab_point *seq_tab_point);

//Concatene les deux tableau de segment en un seul tableau
tableau_seg *concat(tableau_seg *L1,tableau_seg *L2);

//Algorithme de douglas peucker pour les segments
tableau_seg *simplification_douglas_peucker (tableau_point *C,int j1,int j2,double d);

//Memorise dans la prochaine case libre le contour (tableau_seg) dans la liste chainee de contour (seq)
void memoriser_contours_simple(sequence_tab_seg *seq, tableau_seg *contour_simple);

//Passe chaque contour de la liste chainee de sequence dans l'algorithme de Douglas-Peucker
sequence_tab_seg *simplif_pls_contours (sequence_tab_point *seq_contours, double d);

//Affiche le nombre de segment de chaque contour et le total (debug les courbe simplifié en segment)
void afficher_contours_simple(sequence_tab_seg *seq_contours,FILE *f);

//Affiche le nombre de courbe de bezier de chaque contour et le total (debug les courbe simplifié en bezier2)
void afficher_contours_bezier2_simple(sequence_tab_bezier2 *seq_contours,FILE *f);

//Concatene les deux tableaux de courbes de bezier2 en un seul tableau
tableau_bezier2 *concat_bezier(tableau_bezier2 *L1,tableau_bezier2 *L2);

//Calcul la distance approximatif entre la courbe de bézier 2 (courbe2) et le point (pj)
double dist_point_bezier2(double ti, Point pj, bezier2 courbe2);

//Calcul la distance approximatif entre la courbe de bézier 2 (courbe2) et le point (pj)
double dist_point_bezier3(double ti, Point pj, bezier3 courbe3);

//Calcul d'une approximation de contour de bezier 2 du contour (tab_point) restreint entre les indices j1 et j2 du tableau
bezier2 approx_contour(tableau_point *tab_point, int j1, int j2);

//Passe chaque contour (bezier 2) de la liste chainee de sequence dans l'algorithme de Douglas-Peucker
sequence_tab_bezier2 *simplif_pls_contours_bezier2 (sequence_tab_point *seq_contours, double d);

//Concatene les deux tableaux de courbes de bezier3 en un seul tableau
tableau_bezier3 *concat_bezier3(tableau_bezier3 *L1,tableau_bezier3 *L2);

//Memorise dans la prochaine case libre le tableau de bezier 3 (tab_bezier3) dans la liste chainee de contour (seq)
void memoriser_bezier3(sequence_tab_bezier3 *seq_bezier3,tableau_bezier3 *tab_bezier3);

//Affiche le nombre de courbe de bezier de chaque contour et le total (debug les courbe simplifié en bezier3)
void afficher_contours_bezier3_simple(sequence_tab_bezier3 *seq_contours,FILE *f);

//Calcul d'une approximation de contour de bezier 3 du contour (tab_point) restreint entre les indices j1 et j2 du tableau
bezier3 approx_contour_b3(tableau_point *tab_point, int j1, int j2);

//Algorithme de douglas peucker appliqués aux courbes de bézier 3
tableau_bezier3 *simplification_douglas_peucker_bezier3 (tableau_point *C,int j1,int j2,double d);

//Passe chaque contour (bezier 3) de la liste chainee de sequence dans l'algorithme de Douglas-Peucker
sequence_tab_bezier3 *simplif_pls_contours_bezier3 (sequence_tab_point *seq_contours, double d);

#endif //TACHE3_ROBOT_H
