
#include "traiterimage.h"
#include <assert.h>
#include <iostream>
using namespace std;
#define min(a,b)    ((a<b) ? a : b)
#define max(a,b)    ((a<b) ? b : a)
#define abs(a)      ((a<0) ? -a : a)


int TraiterImage::Width(void )
{
    return m_nWidth;
}



int TraiterImage::Height(void )
{
    return m_nHeight;
}



TraiterImage::TraiterImage( ) : m_ppImage(NULL)
{

    cout << "+ construction"<<endl;

    m_nWidth = m_nHeight = 0;
}

TraiterImage::TraiterImage( int nHeight, int nWidth ) : m_ppImage(NULL)
{
    m_nWidth = nWidth;
    m_nHeight = nHeight;
    Allouer( );
}


TraiterImage::~TraiterImage( )
{
    Liberer( );
}

void TraiterImage::Allouer()
{


    if (  m_ppImage != NULL )
        return;

    m_ppImage = new byte* [m_nHeight];
    m_normex = new PIXEL* [m_nHeight];
    m_normey = new PIXEL* [m_nHeight];
    m_norme = new PIXEL* [m_nHeight];
    m_buffer = new byte* [m_nHeight];

    for ( int i=0 ;i< m_nHeight; i++ )
    {
        m_ppImage[i]= new byte[ m_nWidth];
        m_normex[i]= new PIXEL[ m_nWidth];
        m_normey[i]= new PIXEL[ m_nWidth];
        m_norme[i]= new PIXEL[ m_nWidth];
        m_buffer[i]= new byte[ m_nWidth];
    }
    return;
}

void TraiterImage::Liberer( )
{
    for ( int i=0 ;i< m_nHeight; i++ )
    {

        delete [] m_ppImage[i];
        delete [] m_normex[i];
        delete [] m_normey[i];
        delete [] m_norme[i];
        delete [] m_buffer[i];
    }

    delete [] m_ppImage;
    delete [] m_normex;
    delete [] m_normey;
    delete [] m_norme;
    delete [] m_buffer;
    return;
}




void TraiterImage::affiche()
{

    if ( ! (m_nWidth && m_nHeight && m_ppImage ) )
        return ;

    int i,j;

    for (i=0 ; i<m_nHeight ; i++)
    {
        for (j=0;j< m_nWidth; j++)
        {
            cout << " " << (int) m_buffer[i][j] << " "  ;
        }
        cout << endl;
    }
    return;
}


void TraiterImage::seuil(int tresh, int fact)
{
    int i,j,k;
    int som=0;
    int moy=0;

    for( i=0 ; i<m_nHeight ; i++)

    { for(j=fact ; j<m_nWidth-fact ; j=j+fact)
        {
            if (fact>1)
            {
                som=0;
                for(k=0;k<fact-1;k++)
                {
                    som=som+m_ppImage[i][j+k];

                }
                moy=som/(fact-1);

                if(moy<=tresh)
                {
                    for(k=0;k<fact-1;k++)
                    {
                        m_ppImage[i][j+k]=255;

                    }
                }
                else {
                    for(k=0;k<fact-1;k++)
                    {
                        m_ppImage[i][j+k]=0;
                    }
                }
            }
            else {
                if(m_ppImage[i][j]<=tresh)
                {
                    m_ppImage[i][j]=255;
                }
                else {
                    m_ppImage[i][j]=0;
                }
            }
        }
    }

}

void TraiterImage::rgb_to_lum( int fact)
{
    int i,j;

    unsigned char lum;

    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            lum=(min(min(m_ppImage[i][j],m_ppImage[i][j+1]),m_ppImage[i][j+2])+max(max(m_ppImage[i][j],m_ppImage[i][j+1]),m_ppImage[i][j+2]))/2;
            m_ppImage[i][j]=lum;
            m_ppImage[i][j+1]=lum;
            m_ppImage[i][j+2]=lum;
            m_ppImage[i][j+3]=0;
        }
    }
}

void TraiterImage::normey(int fact)
{
    int i,j,k;
    int moy[8];

    for(i=0;i<8;i++)
    { moy[i]=0;}

    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            if (fact>1)
            {
                for(k=0;k<fact-1;k++)
                {
                    m_normey[i][j+k]=min(m_ppImage[i-1][j+k-fact]+2*m_ppImage[i-1][j+k]+m_ppImage[i-1][j+fact+k]-m_ppImage[i+1][j+k-fact]-2*m_ppImage[i+1][j+k]-m_ppImage[i+1][j+fact+k],255);
                }
            }
            else
            {
                m_normey[i][j]=min(m_ppImage[i-1][j-1]+2*m_ppImage[i-1][j]+m_ppImage[i-1][j+1]-m_ppImage[i+1][j-1]-2*m_ppImage[i+1][j]-m_ppImage[i+1][j+1],255);
            }
        }
    }
}

void TraiterImage::normex(int fact)
{
    int i,j,k;
    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            if (fact>1)
            {
                for(k=0;k<fact-1;k++)
                {
                    m_normex[i][j+k]=min(m_ppImage[i-1][j+k-fact]+2*m_ppImage[i][j+k-fact]+m_ppImage[i+1][j+k-fact]-m_ppImage[i-1][j+fact+k]-2*m_ppImage[i][j+fact+k]-m_ppImage[i+1][j+fact+k],255);
                }
            }
            else
            {
                m_normex[i][j]=min(m_ppImage[i-1][j-1]+2*m_ppImage[i][j-1]+m_ppImage[i+1][j-1]-m_ppImage[i-1][j+1]-2*m_ppImage[i][j+1]-m_ppImage[i+1][j+1],255);
            }
        }
    }
}

void TraiterImage::gaussian(int fact)
{
    int i,j,k;
    for(i=2;i<m_nHeight-2;i++)
    {
        for(j=2*fact;j<m_nWidth-2*fact;j=j+fact)
        {
            if(fact>1)
            {
                for(k=0;k<fact-1;k++)
                {
                    m_ppImage[i][j+k]=min(255,(2*m_ppImage[i-2][j+k-2*fact]+4*m_ppImage[i-2][j+k-fact]+5*m_ppImage[i-2][j+k]+4*m_ppImage[i-2][j+k+fact]+2*m_ppImage[i-2][j+k+2*fact]+
                                               4*m_ppImage[i-1][j+k-2*fact]+9*m_ppImage[i-1][j+k-fact]+12*m_ppImage[i-1][j+k]+9*m_ppImage[i-1][j+k+fact]+4*m_ppImage[i-1][j+k+2*fact]+
                                               5*m_ppImage[i][j+k-2*fact]+12*m_ppImage[i][j+k-fact]+15*m_ppImage[i][j+k]+12*m_ppImage[i][j+k+fact]+5*m_ppImage[i][j+k+2*fact]+
                                               4*m_ppImage[i+1][j+k-2*fact]+9*m_ppImage[i+1][j+k-fact]+12*m_ppImage[i+1][j+k]+9*m_ppImage[i+1][j+k+fact]+4*m_ppImage[i+1][j+k+2*fact]+
                                               2*m_ppImage[i+2][j+k-2*fact]+4*m_ppImage[i+2][j+k-fact]+5*m_ppImage[i+2][j+k]+4*m_ppImage[i+2][j+k+fact]+2*m_ppImage[i+2][j+k+2*fact])/157);
                }
            }
            else
            {
                m_ppImage[i][j]=min(255,(2*m_ppImage[i-2][j-2*fact]+4*m_ppImage[i-2][j-fact]+5*m_ppImage[i-2][j]+4*m_ppImage[i-2][j+fact]+2*m_ppImage[i-2][j+2*fact]+
                                         4*m_ppImage[i-1][j-2*fact]+9*m_ppImage[i-1][j-fact]+12*m_ppImage[i-1][j]+9*m_ppImage[i-1][j+fact]+4*m_ppImage[i-1][j+2*fact]+
                                         5*m_ppImage[i][j-2*fact]+12*m_ppImage[i][j-fact]+15*m_ppImage[i][j]+12*m_ppImage[i][j+fact]+5*m_ppImage[i][j+2*fact]+
                                         4*m_ppImage[i+1][j-2*fact]+9*m_ppImage[i+1][j-fact]+12*m_ppImage[i+1][j]+9*m_ppImage[i+1][j+fact]+4*m_ppImage[i+1][j+2*fact]+
                                         2*m_ppImage[i+2][j-2*fact]+4*m_ppImage[i+2][j-fact]+5*m_ppImage[i+2][j]+4*m_ppImage[i+2][j+fact]+2*m_ppImage[i+2][j+2*fact])/157);
            }
        }
    }
}

void TraiterImage::fenetrage(int fact,int a, int b, int L, double teta)
{
    int i,j,k;
    for(i=0;i<m_nHeight;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            if (fact>1)
            {
                for(k=0;k<fact-1;k++)
                {


                    if (m_ppImage[i][j+k]<=a)
                    {

                        m_ppImage[i][j+k]=0;

                    }
                    else if(m_ppImage[i][j+k]>a && m_ppImage[i][j+k]<b)
                    {
                        m_ppImage[i][j+k]=teta*m_ppImage[i][j+k];
                    }
                    else
                    {
                        m_ppImage[i][j+k]=L;
                    }
                }
            }
            else
            {
                if (m_ppImage[i][j]<=a)
                {
                    m_ppImage[i][j]=0;
                }
                else if(m_ppImage[i][j]>a && m_ppImage[i][j]<b)
                {
                    m_ppImage[i][j]=teta*m_ppImage[i][j];
                }
                else
                {
                    m_ppImage[i][j]= L;
                }
            }
        }
    }
}



void TraiterImage::seuillage(int fact, int a,  double teta)
{
    int i,j,k;
    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            if (fact>1)
            {
                for(k=0;k<fact-1;k++)
                {
                    if (m_ppImage[i][j+k]<=a)
                    {
                        m_ppImage[i][j+k]=0;
                    }
                    else
                    {
                        m_ppImage[i][j+k]=teta*(m_ppImage[i][j+k]+a);
                    }

                }
            }
            else
            {
                if (m_ppImage[i][j]<=a)
                {
                    m_ppImage[i][j]=0;
                }
                else
                {
                    m_ppImage[i][j]=teta*(m_ppImage[i][j]+a);
                }
            }
        }
    }
}


void TraiterImage::binarisation(int fact, int a,  int L)
{
    int i,j,k;
    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            for(k=0;k<fact-1;k++)
            {
                if (m_ppImage[i][j+k]<=a)
                {
                    m_ppImage[i][j+k]=0;
                }
                else
                {
                    m_ppImage[i][j+k]=L;
                }
            }
        }

    }
}


void TraiterImage::seuillage_par_intervalle(int fact,int a, int b, int L, double teta)
{
    int i,j,k;
    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            for(k=0;k<fact-1;k++)
            {
                if (m_ppImage[i][j+k]<=a)
                {
                    m_ppImage[i][j+k]=0;
                }
                else if(m_ppImage[i][j+k]>a && m_ppImage[i][j+k]<b)
                {
                    m_ppImage[i][j+k]=teta*(m_ppImage[i][j+k]+a);
                }
                else
                {
                    m_ppImage[i][j+k]= 0;
                }
            }
        }
    }
}


void TraiterImage::binarisation_par_intervalle(int fact,int a, int b, int L)
{
    int i,j,k;
    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            for(k=0;k<fact-1;k++)
            {
                if (m_ppImage[i][j+k]<=a)
                {
                    m_ppImage[i][j]=0;
                }
                else if(m_ppImage[i][j+k]>a && m_ppImage[i][j+k]<b)
                {
                    m_ppImage[i][j+k]=L;
                }
                else
                {
                    m_ppImage[i][j+k]= 0;
                }
            }
        }
    }
}


void TraiterImage::inversion(int fact)
{
    int i,j,k;
    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            for(k=0;k<fact-1;k++)
            {

            m_ppImage[i][j+k]=255- m_ppImage[i][j+k];
            }
        }
    }
}


void TraiterImage::norme(int fact)
{
    int i,j,k;

    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            if (fact>1)
            {
                for(k=0;k<fact-1;k++)
                {
                    m_ppImage[i][j+k]=255-min(abs(m_normex[i][j+k])+abs(m_normey[i][j+k]),255);
                }
            }
            else
            {
                m_ppImage[i][j]=255-min(255, abs(m_normex[i][j])+abs(m_normey[i][j]));
            }
        }
    }
}

void TraiterImage::transfertx()
{   int i,j;

    for(i=0;i<m_nHeight;i++)
    {
        for(j=0;j<m_nWidth;j++)
        {
            m_ppImage[i][j]=255-min(255,abs(m_normex[i][j]));
        }
    }
}

void TraiterImage::transferty()
{   int i,j;

    for(i=0;i<m_nHeight;i++)
    {
        for(j=0;j<m_nWidth;j++)
        {
            m_ppImage[i][j]=255-min(255,abs(m_normey[i][j]));
        }
    }
}

void TraiterImage::transfert_to_exim(QImage * pqImg)
{
    float fact;
    int w, h;
    byte * pLine;

    fact=pqImg->depth()/8;
    w=pqImg->width();
    h=pqImg->height() ;

    for ( int i = 0 ; i< h ; i++ )
    {
        pLine = pqImg->scanLine(i);
        memcpy ( m_ppImage[i],  pLine , w*fact*sizeof(byte ));
        assert(m_ppImage[i] != NULL);
    }

}

void TraiterImage::transfert_to_qim(QImage * pqImg)
{
    int w,h;
    float fact;
    byte* pLine;
    w=m_nWidth;
    h=m_nHeight;
    fact=pqImg->depth()/8;

    for ( int i=0 ; i<h ; i++ )
    {
        pLine=pqImg->scanLine(i);
        memcpy ( pLine, m_ppImage[i] , w*sizeof(byte ));
    }
}

byte* TraiterImage::get_buffer()
{
    return m_ppImage[0];
}
bool TraiterImage::isNULL()
{
    if(m_ppImage ==NULL || m_nWidth==0 || m_nHeight==0 )
        return true;
    else
        return false;
}


void TraiterImage::moyenneur(int fact)
{
    int i,j,k;
    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            if (fact>1)
            {
                for(k=0;k<fact-1;k++)
                {
                    m_ppImage[i][j]=min((m_ppImage[i-1][j-1+k-fact]+m_ppImage[i-1][j+k-fact]+m_ppImage[i-1][j+1+k-fact]+m_ppImage[i][j-1+k-fact]+m_ppImage[i][j+k-fact]+m_ppImage[i][j+1+k-fact]+m_ppImage[i+1][j-1+k-fact]+m_ppImage[i+1][j+k-fact]+m_ppImage[i+1][j+1+k-fact])/9,255);
                }
            }
            else
            {
                m_ppImage[i][j]=min((m_ppImage[i-1][j-1]+m_ppImage[i-1][j]+m_ppImage[i-1][j+1]+m_ppImage[i][j-1]+m_ppImage[i][j]+m_ppImage[i][j+1]+m_ppImage[i+1][j-1]+m_ppImage[i+1][j]+m_ppImage[i+1][j+1])/9,255);
            }
        }
    }
}


void TraiterImage::mediane(int fact, int n)
{
    int i,j,k;
    byte tab[n*n];

    for(i=1;i<m_nHeight-1;i++)
    {
        for(j=fact;j<m_nWidth-fact;j=j+fact)
        {
            if (fact>1)
            {
                for(k=0;k<fact-1;k++)
                {
                    for(int ii=0;ii<n;ii++)
                    {
                        for(int jj=0;jj<n;jj++)
                        {
                            tab[(ii)*n+jj]=m_ppImage[i+ii-(n-1)/2][j+(jj-((n-1)/2))*fact+k];
                         //   cout<<(int)tab[(ii)*n+jj]<< "  ";
                        }
                       //   cout<< "  "<<endl;
                    }
                    m_ppImage[i][j+k]=min(tri(tab, n*n),255);

                }
            }
            else
            {
                m_normex[i][j]=min((m_ppImage[i-1][j-1]+m_ppImage[i-1][j]+m_ppImage[i-1][j+1]+m_ppImage[i][j-1]+m_ppImage[i][j]+m_ppImage[i][j+1]+m_ppImage[i+1][j-1]+m_ppImage[i+1][j]+m_ppImage[i+1][j+1])/9,255);
            }
        }
    }
}

byte TraiterImage::tri(byte vect[], int taille)
{
    int i,j;
    byte tmp=vect[0];
//    for(i=0;i<taille; i++)
//    {
//        cout<<(int)vect[i]<<endl;
//     }
    for(i=0; i, i<taille;i++)
    {
        for(j=i;j<taille; j++)
        {
            if(vect[i]>vect[j])
            {
                tmp=vect[i];
                vect[i]=vect[j];
                vect[j]=tmp;
            }
        }
    }
//    for(i=0;i<taille; i++)
//    {
//        cout<<(int)vect[i]<<endl;
//     }
    if(taille%2==0)
    {
        return vect[taille/2];
    }
    else
    {
        return vect[(taille+1)/2];
    }
}
