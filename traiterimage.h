
#include <iostream>
#include <fstream>
using namespace std;
#include <QImage>

typedef unsigned char byte;
typedef double PIXEL;

#ifndef TRAITERIMAGE_H
#define TRAITERIMAGE_H

class TraiterImage
{
protected:

 byte **m_ppImage;    // Matrice Image

 PIXEL **m_normex;    //
 PIXEL **m_normey;
 PIXEL **m_norme;
 byte **m_buffer;     // Buffer Image
 int m_nWidth ;
 int m_nHeight ;


 void Allouer( );
 void Liberer( );

public :

TraiterImage( ) ;

TraiterImage( int , int  );

~TraiterImage( );

bool isNULL();

int Width( ) ;
int Height( );
void affiche();



void seuil(int,int );



void maskvert(void);
void maskhori(void);



void normex(int);
void normey(int);
void norme(int);



void transfertx(void);
void transferty(void);
void transfert_n(void);


 byte* GetLine( int );




void transfert_to_qim(QImage*);
void transfert_to_exim(QImage*);



void rgb_to_lum(int);


void gaussian(int);
void fenetrage(int,int, int, int, double);
void seuillage(int,int,  double);
void binarisation(int,int, int);
void binarisation_par_intervalle(int,int, int, int);
void seuillage_par_intervalle(int,int, int , int, double);

void inversion(int);
void moyenneur(int);
void mediane(int,int);
byte tri(byte* , int);



byte* get_buffer(void) ;

};
#endif // TRAITERIMAGE_H
