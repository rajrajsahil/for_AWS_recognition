#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;


int main( int argc, char** argv )
{
  Mat src, src_gray, dst,final;
  int kernel_size = 3;
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;

  int c;

  // Load an image
  src = imread("face.jpg");

  if( !src.data )
    { return -1; }

  /// Remove noise by blurring with a Gaussian filter
  GaussianBlur( src, src, Size(7,7), 0, 0, BORDER_DEFAULT );

  src_gray = src;

  /// Create window
  namedWindow("improved_image", CV_WINDOW_AUTOSIZE );

  /// Apply Laplace function
  Mat abs_dst;
  Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( dst, abs_dst );
  Mat abs_src_gray;
  convertScaleAbs( src_gray, abs_src_gray );

  //Adding original and Laplacian image
  addWeighted( abs_src_gray, 1, abs_dst, 1, 0.0, final);

  /// Show what you got
  imwrite("improved.jpg",final);
  imshow("improved_image", final);

  waitKey(0);

  return 0;
  }