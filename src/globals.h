/*
 *	globals.h
 *	gl65
 *
 *	Created by Jean-Baptiste Périn, June 2020.
 *
 */

#ifndef _GLOBALS_H_
#define _GLOBALS_H_


 // Camera Position use only low bytes
extern int              CamPosX;
extern int              CamPosY;
extern int              CamPosZ;

 // Camera Orientation
extern char             CamRotZ;  // -128 -> 127 unit : 2PI/(2^8 - 1)
extern char             CamRotX;

 // Geometry size
extern unsigned char    nbPoints;
extern unsigned char    nbFaces;
extern unsigned char    nbSegments;
extern unsigned char    nbParticules;

 // Geometry buffers
extern signed char      points3dX[];
extern signed char      points3dY[];
extern signed char      points3dZ[];

extern unsigned char    particulesPt[];
extern unsigned char    particulesChar[];

extern unsigned char    segmentsPt1[];
extern unsigned char    segmentsPt2[];
extern unsigned char    segmentsChar[];

extern unsigned char    facesPt1[];
extern unsigned char    facesPt2[];
extern unsigned char    facesPt3[];
extern unsigned char    facesChar[];

// Render buffer
extern char             fbuffer[];  // frame buffer SCREEN_WIDTH * SCREEN_HEIGHT

#endif //_GLOBALS_H_