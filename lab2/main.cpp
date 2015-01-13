/*
  CPE 471 Lab 1 
  Base code for Rasterizer
  Example code using B. Somers' image code - writes out a sample tga
*/

#include <stdio.h>
#include <stdlib.h>
#include "Image.h"
#include "types.h"
#include <iostream>
#include <algorithm>
#include <cmath>

// Class to represent a 3D point
class Point {
  public:
    float x;
    float y;
    float z;
};

float min(float a, float b, float c){
  float low;
  low = a;
  if (b<low)
    low=b;
  if (c<low)
    low=c;

  return low;
}

float max(float a, float b, float c){
  float big;
  big = a;
  if (b>big)
    big=b;
  if (c>big)
    big=c;

  return big;
}

float determinant(Point a, Point b, Point c){
  return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);
}

bool inTriangle(float a, float b, float c){
  if (a<=1 && a>=0){
    if (b<=1 && b>=0){
      if(c<=1 && c>=0)
        return true;
    }
  }

  return false;
}

int main(void) {

  // make color vars for points A B and C
  color_t clrA;
  color_t clrB;
  color_t clrC;

  // Assign colors to color vars
  // Color A
  clrA.r = 1;
  clrA.b = 0;
  clrA.g = 0;
  // Color B
  clrB.r = 0;
  clrB.b = 1;
  clrB.g = 0;
  // Color C
  clrC.r = 0;
  clrC.b = 0;
  clrC.g = 1;

  // obtain all coordinates
  Point a;
  Point b;
  Point c;

  int maxX=0;
  int minX=0;
  int minY=0;
  int maxY=0;

  std::cout << "Enter 3 points (in the form: X Y Z X Y Z X Y Z):" << std::endl;
  std::cin >> a.x >> a.y >> a.z >> b.x >> b.y >> b.z >> c.x >> c.y >> c.z;
  
  minX = min(a.x,b.x,c.x);
  maxX = max(a.x,b.x,c.x);
  minY = min(a.y,b.y,c.y);
  maxY = max(a.y,b.y,c.y);

  // make a 640x480 image (allocates buffer on the heap)
  Image img(640, 480);

  // RASTA-Rizzeeeee
  color_t clr;
  Point p;
  float area = determinant(a,c,b);
  std::cout << area << std::endl;
  float alpha;
  float beta;
  float gamma;
  for (int i=minX; i < maxX; i++) {
    for (int j=minY; j < maxY; j++) {
      p.x = i;
      p.y = j;
      alpha = determinant(b, c, p) / area;
      beta = determinant(c, a, p) / area;
      gamma = determinant(a, b, p) / area;
      if (inTriangle(alpha, beta, gamma)){
        clr.r = 1; //clrA.r*alpha + clrB.r*beta + clrC.r*gamma;
        clr.b = 1; //clrA.b*alpha + clrB.b*beta + clrC.b*gamma;
        clr.g = 1; //clrA.g*alpha + clrB.g*beta + clrC.g*gamma;
        img.pixel(i, j, clr);
      }
    }
  }

  // write the targa file to disk
  img.WriteTga((char *)"baller.tga", true); 
  // true to scale to max color, false to clamp to 1.0

}
