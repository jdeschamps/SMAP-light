#include "mex.h"
#include <stdio.h>
#include <math.h>

/*
 * xtimesy.c - example found in API guide
 *
 * multiplies an input scalar times an input matrix and outputs a
 * matrix 
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2006 The MathWorks, Inc.
 */

/* $Revision: 1.10.6.2 $ */

/*void correlate(double *n1, double *G, mwSize lenG, mwSize lenn)*/
  //  cs(d list,d x,d y,l frames,d dX,l dT,mws maxactive,mws lenx);
void   findn(double *nb,double *x,double *y,double dx,long lenx)
{
double dx2,dtest,r2,dtest2,ry2,rx2;
long indx,this,testind;

dtest=dx*3;
dx2=dx*dx;
dtest2=dtest*dtest;

indx=0;
for(this=0;this<lenx;this++) 
{
    if (this%10000==0)
        {
        mexPrintf(" %i of %i k\n",this/1000,lenx/1000);
        mexEvalString("drawnow");
        }
    while((x[indx]<x[this]-dtest)&&(indx<lenx-1))
    {
        indx++;
    }
    testind=indx;
    while((x[testind]<x[this]+dtest)&&(testind<lenx-1))
    {
        ry2=(y[testind]-y[this])*(y[testind]-y[this]);
        if (ry2<dtest2)
            {
            rx2=(x[testind]-x[this])*(x[testind]-x[this]); 
            nb[this]+=exp(-(rx2+ry2)/(2*dx2));              
            }
        testind++;
        
        
    }
    
}
}

/* the gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
double *x,*y,*nb,dx;
long  lenx;

  
  /*  check for proper number of arguments */
  /* NOTE: You do not need an else statement when using mexErrMsgTxt
     within an if statement, because it will never get to the else
     statement if mexErrMsgTxt is executed. (mexErrMsgTxt breaks you out of
     the MEX-file) */
  if(nrhs!=3) 
    mexErrMsgTxt("3 inputs required.");
  if(nlhs!=1) 
    mexErrMsgTxt("1 output required.");
  

  /*  get the scalar input x */
 
  /*  create a pointer to the input matrix y */
 x = mxGetPr(prhs[0]);
 y = mxGetPr(prhs[1]);

  
  /*  get the dimensions of the matrix input y */
  lenx = mxGetM(prhs[0]);

 // printf("length of positons: %i\n",lenx);
  
dx=mxGetScalar(prhs[2]);


  /*  set the output pointer to the output matrix */
//  printf("inputs associated\n");
 
  plhs[0] = mxCreateNumericMatrix(lenx,1,mxDOUBLE_CLASS,mxREAL);


//     printf("outputmatrix created\n");
  
  
  /*  create a C pointer to a copy of the output matrix */
  nb = mxGetData(plhs[0]);

//    printf("outputmatrix created 2, call routine\n");
  /*  call the C subroutine */
  findn(nb,x,y,dx,lenx);

}
