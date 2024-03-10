#include <stdio.h>
#include <math.h>

/*Program to approximate an integral using the trapazodial rule/algorithm */
/* To compile run: gcc Trapezodial.c -lm */

double f(double x)
{
    //e^(x^2)
    return exp(pow(x, 2));
}

int main()
{
    //initializing vars
    int N = 4; //number of points we use
    int b = 2; //where integral stops
    int a = 0; //where integral starts
    double deltaX = (b-a)/(double)N; //calculation of deltaX /\X
    double sum = 0; //our summation 

    for(int i = 1; i <= N; i++)
    {
        double x1 = a + (i-1) * deltaX; //we calculate our first x value
        double x2 = a + (i) * deltaX; //calculate second value
        
        //this summation is deltaX/2 * (e^(i-1)^2 + e^(i)^2) + ...   
        sum += (deltaX / 2) * ((f(x1)) + f(x2)); 
    }

    printf("Aproximation of the integral from %d-%d of e^(x^2) = %f\n", a, b, sum);

    return 0;
}