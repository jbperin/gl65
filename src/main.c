
/*
 *	main.c
 *	gl65 3D
 *
 *	Created by Jean-Baptiste PERIN, June 2020.
 *
 */
#include <cc65.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "gl65.h"

#include "globals.h"
#include "plat.h"

/*
 *  SCREEN MEMORY //BB80
 */
#define ADR_BASE_LORES_SCREEN 48040  
#define SCREEN_WIDTH 40 
#define SCREEN_HEIGHT 26

extern void glProject (char *tabpoint2D, char *tabpoint3D, unsigned char nbPoints, unsigned char opts);
extern void AdvancedPrint(unsigned char Xpos,unsigned char Ypos, char *message);
extern void project ();


#define TEXTURE_1 ','
#define TEXTURE_2 '.'
#define TEXTURE_3 'u'
#define TEXTURE_4 '*'
#define TEXTURE_5 'o'
#define TEXTURE_6 '+'
#define TEXTURE_7 'x'

signed char geomHouse []= {
/* Nb Coords = */ 10,
/* Nb Faces = */ 11,
/* Nb Segments = */ 14,
/* Nb Particules = */ 0,
// Coord List : X, Y, Z, unused
 1, 1, 0, 0, 
-1, 1, 0, 0,
-1,-1, 0, 0,
 1,-1, 0, 0,
 1, 1, 2, 0, 
-1, 1, 2, 0,
-1,-1, 2, 0,
 1,-1, 2, 0,
 1, 0, 3, 0,
-1, 0, 3, 0,
// Face List : idxPoint1, idxPoint2, idxPoint3, character 
 0, 1, 5, TEXTURE_6,
 0, 4, 5, TEXTURE_6,
 3, 2, 6, TEXTURE_6,
 6, 3, 7, TEXTURE_6,
 1, 2, 6, TEXTURE_5,
 1, 6, 5, TEXTURE_5,
 5, 6, 9, TEXTURE_5,
 4, 5, 9, TEXTURE_3,
 4, 9, 8, TEXTURE_3,
 7, 6, 9, TEXTURE_3,
 7, 9, 8, TEXTURE_3,
// Segment List : idxPoint1, idxPoint2, character , unused
0, 1, '-', 0,
1, 2, '-', 0,
2, 3, '-', 0,
4, 5, '-', 0,
6, 7, '-', 0,
0, 4,'|', 0,
1, 5,'|', 0,
2, 6,'|', 0,
3, 7,'|', 0,
4, 8,'/', 0,
7, 8,'/', 0,
5, 9,'/', 0,
6, 9,'/', 0,
9, 8,'-', 0,

// Particule List : idxPoint1, character 
};

#define NB_POINTS_TRAJ 64
#define SIZE_POINTS_TRAJ 3

char traj[] = {
    24, 0, 128,
    24, 2, -125,
    24, 5, -120,
    23, 7, -116,
    22, 9, -112,
    21, 11, -108,
    20, 13, -105,
    19, 15, -101,
    17, 17, -96,
    15, 19, -91,
    13, 20, -87,
    11, 21, -84,
    9, 22, -80,
    7, 23, -76,
    5, 24, -72,
    2, 24, -67,
    0, 24, -64,
    -2, 24, -61,
    -5, 24, -56,
    -7, 23, -52,
    -9, 22, -48,
    -11, 21, -44,
    -13, 20, -41,
    -15, 19, -37,
    -17, 17, -32,
    -19, 15, -27,
    -20, 13, -23,
    -21, 11, -20,
    -22, 9, -16,
    -23, 7, -12,
    -24, 5, -8,
    -24, 2, -3,
    -24, 0, 0,
    -24, -2, 3,
    -24, -5, 8,
    -23, -7, 12,
    -22, -9, 16,
    -21, -11, 20,
    -20, -13, 23,
    -19, -15, 27,
    -17, -17, 32,
    -15, -19, 37,
    -13, -20, 41,
    -11, -21, 44,
    -9, -22, 48,
    -7, -23, 52,
    -5, -24, 56,
    -2, -24, 61,
    0, -24, 64,
    2, -24, 67,
    5, -24, 72,
    7, -23, 76,
    9, -22, 80,
    11, -21, 84,
    13, -20, 87,
    15, -19, 91,
    17, -17, 96,
    19, -15, 101,
    20, -13, 105,
    21, -11, 108,
    22, -9, 112,
    23, -7, 116,
    24, -5, 120,
    24, -2, 125};


char tampon[256];

void change_char(char c, unsigned char patt01, unsigned char patt02, unsigned char patt03, unsigned char patt04, unsigned char patt05, unsigned char patt06, unsigned char patt07, unsigned char patt08) {
    unsigned char* adr;
    adr      = (unsigned char*)(0xB400 + c * 8);
    *(adr++) = patt01;
    *(adr++) = patt02;
    *(adr++) = patt03;
    *(adr++) = patt04;
    *(adr++) = patt05;
    *(adr++) = patt06;
    *(adr++) = patt07;
    *(adr++) = patt08;
}

void addGeom2(
    signed char   X,
    signed char   Y,
    signed char   Z,
    unsigned char sizeX,
    unsigned char sizeY,
    unsigned char sizeZ,
    unsigned char orientation,
    signed char          geom[]) {

    int kk=0;
    int ii;
    int npt,nfa, nseg, npart;
    npt = geom[kk++];
    nfa = geom[kk++];
    nseg = geom[kk++];
    npart = geom[kk++];
    for (ii = 0; ii < npt; ii++){
        if (orientation == 0) {
            points3dX[nbPoints] = X + sizeX * geom[kk++];
            points3dY[nbPoints] = Y + sizeY * geom[kk++];
        } else {
            points3dY[nbPoints] = X + sizeY * geom[kk++];
            points3dX[nbPoints] = Y + sizeX * geom[kk++];
        }
        points3dZ[nbPoints] = Z + sizeZ * geom[kk++];
        nbPoints ++;
        kk++; // skip unused byte
    }
    for (ii = 0; ii < nfa; ii++){
        facesPt1[nbFaces] = nbPoints - (npt-geom[kk++]);  // Index Point 1
        facesPt2[nbFaces] = nbPoints - (npt-geom[kk++]);  // Index Point 2
        facesPt3[nbFaces] = nbPoints - (npt-geom[kk++]);  // Index Point 3
        facesChar[nbFaces] = geom[kk++];  // Character
        nbFaces++;
    }
    for (ii = 0; ii < nseg; ii++){
        segmentsPt1[nbSegments] = nbPoints - (npt-geom[kk++]);  // Index Point 1
        segmentsPt2[nbSegments] = nbPoints - (npt-geom[kk++]);  // Index Point 2
        segmentsChar[nbSegments] = geom[kk++]; // Character
        nbSegments++;
        kk++; // skip unused byte
    }
    for (ii = 0; ii < npart; ii++){
        particulesPt[nbParticules] = nbPoints - (npt-geom[kk++]);  // Index Point
        particulesChar[nbParticules] = geom[kk++]; // Character
        nbParticules++;        
    }
}    



void init (){
 
    // printf ("coucou \n");

    
    nbPoints     = 0;
    nbSegments   = 0;
    nbFaces      = 0;
    nbParticules = 0;

    change_char(36, 0x80, 0x40, 020, 0x10, 0x08, 0x04, 0x02, 0x01);
    addGeom2(0, 0, 0, 12, 8, 4, 0, geomHouse);

}



extern void glProjectArrays();


void main (){

    int i, j;
    CamPosX = -20;
    CamPosY = 16;
    CamPosZ = 6;

    CamRotZ = -23;
    CamRotX = 0;

    init ();

    i = 0;
    for (j = 0; j < 64; j++) {
        CamPosX = traj[i++];
        CamPosY = traj[i++];
        CamRotZ = traj[i++];
        i       = i % (NB_POINTS_TRAJ * SIZE_POINTS_TRAJ);

//     snprintf(tampon, 256, "j = %d coord = [%d, %d, %d]"
//             , j, CamPosX, CamPosY, CamRotZ );

//     AdvancedPrint(j%26, 0 ,tampon);

        glProjectArrays();
        // // listPoints2D();

        initScreenBuffers();

        glDrawFaces();

        glDrawSegments();

        glDrawParticules();

        buffer2screen((char *)ADR_BASE_LORES_SCREEN);
    }
    printf ("Fin\n");


}