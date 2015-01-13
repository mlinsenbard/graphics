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

int main(void) {

  // make a color
  color_t clr;

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

  // set a square to be the color above
  for (int i=minX; i < maxX; i++) {
    for (int j=minY; j < maxY; j++) {
      clr.r = (maxX-i)%256;
      clr.g = (maxY-j)%256;
      clr.b = (maxX+maxY)%256;
      img.pixel(i, j, clr);
    }
  }

  // write the targa file to disk
  img.WriteTga((char *)"baller.tga", true); 
  // true to scale to max color, false to clamp to 1.0

}
