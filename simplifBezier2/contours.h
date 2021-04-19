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

void init_sequence(tableau_point *tab_point);

void init_sequence_tab_point(sequence_tab_point *seq_contour);

void init_sequence_tab_segment(sequence_tab_seg *seq_contour);

void init_sequence_tab_bezier2(sequence_tab_bezier2 *seq_contour);

void memoriser_contour(sequence_tab_seg *seq_contour,tableau_seg *tab_seg);

void memoriser_contour_point(sequence_tab_point *seq_contour,tableau_point *tab_point);

/* faire avancer le robot d'une case */
void avancer(Robot * r);

/* faire tourner le robot à gauche */
void tourner_a_gauche(Robot * r);

/* faire tourner le robot à droite */
void tourner_a_droite(Robot * r);

Point trouver_depart(Image I);

void contour(Image I);

void ecrire_fichier (tableau_point *tab_point, FILE *f);

void memoriser_position(tableau_point *tab_point, Point p);

void stocker_contour(Image I,tableau_point *tab_point);

int tout_propre(Image I);

void stocker_pls_contours(Image I, sequence_tab_point *tabPoint);

void ecrire_seq (sequence_tab_seg *seq_contour, FILE *f);

void afficher_stats(sequence_tab_point *seq_tab_point);

tableau_seg *concat(tableau_seg *L1,tableau_seg *L2);

tableau_seg *simplification_douglas_peucker (tableau_point *C,int j1,int j2,double d);

void memoriser_contours_simple(sequence_tab_seg *seq, tableau_seg *contour_simple);

sequence_tab_seg *simplif_pls_contours (sequence_tab_point *seq_contours, double d);

void afficher_contours_simple(sequence_tab_seg *seq_contours,FILE *f);

void afficher_contours_bezier2_simple(sequence_tab_bezier2 *seq_contours,FILE *f);

tableau_bezier2 *concat_bezier(tableau_bezier2 *L1,tableau_bezier2 *L2);

double dist_point_bezier2(double ti, Point pj, bezier2 courbe2);

double dist_point_bezier3(int i, tableau_point *tab_point, bezier3 courbe3);

bezier2 approx_contour(tableau_point *tab_point, int j1, int j2);

sequence_tab_bezier2 *simplif_pls_contours_bezier2 (sequence_tab_point *seq_contours, double d);

#endif //TACHE3_ROBOT_H
