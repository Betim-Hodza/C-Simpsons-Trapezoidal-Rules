// to compile: gcc main.c tinyexpr-master/tinyexpr.c -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "tinyexpr-master/tinyexpr.h"

#define MAX_FUNC_SIZE 100

// double parseFunction(char *function, double x);
double simpsonsApprox(int N, int b, int a, char* function, double deltaX);
double trapezoidalApprox(int N, int b, int a, char* function, double deltaX);

/* 
Deprecated function, my attempt at parsing math (just didnt work how i wanted it to)

function looks through the string and parses out computational information
e.g. if the function was x+x^2+5 it would take that and return 
// double parseFunction(char *function, double x)
// {
//     double result = 0.0;
//     double prevValue = 0.0;
//     int prevValSet = 0;
//     char op = '+';

//     char *token = function;

//     while (*token)
//     {
//         double value = 1.0;

//         // Skip whitespace characters
//         while (*token == ' ')
//             token++;

//         if (*token == 'x')
//         {
//             value = x;
//             token++;
//         }
//         else if (isdigit(*token))
//         {
//             char *endptr;
//             value = strtod(token, &endptr);
//             token = endptr;
//         }

//         if (*token == '^')
//         {
//             token++;
//             char *endptr;
//             double exponent = strtod(token, &endptr);
//             token = endptr;
//             prevValue = pow(prevValue, exponent);
//         }
//         else
//         {
//             switch (op)
//             {
//                 case '+':
//                     result += prevValue;
//                     prevValue = value;
//                     break;
//                 case '-':
//                     result += prevValue;
//                     prevValue = -value;
//                     break;
//                 case '*':
//                     prevValue *= value;
//                     break;
//                 case '/':
//                     prevValue /= value;
//                     break;
//                 default:
//                     prevValue = value;
//                     break;
//             }

//             prevValSet = 1;
//             op = *token;
//             token++;
//         }
//     }

//     result += prevValue;

//     return result;
// }
*/



double simpsonsApprox(int N, int b, int a, char* function, double deltaX)
{
    double sum = 0.0;
    double x = a;

    int err;
    te_variable vars1[] = {{"x", &x}};

    //compile expression 1
    te_expr *expr1 = te_compile(function, vars1, 1, &err);

    double f_a = te_eval(expr1); //returns expression value
    x = b;

    te_variable vars2[] = {{"x", &x}};
    //compile expression 2
    te_expr *expr2 = te_compile(function, vars2, 1, &err);

    double f_b = te_eval(expr2);

    sum += f_a + f_b; // Add the first and last terms

    free(expr1);
    free(expr2);

    for (int i = 1; i < N; i++)
    {
        x = a + i * deltaX;
        te_variable vars3[] = {{"x", &x}};
        //compile expression 2
        te_expr *expr3 = te_compile(function, vars3, 1, &err);

        double f_x = te_eval(expr3);

        if (i == N - 1)
        {
            //second-to-last terms are multiplied by 4
            sum += 4 * f_x;
        }
        else if (i % 2 == 0)
        {
            // Even-indexed terms (except the second-to-last) are multiplied by 2
            sum += 2 * f_x;
        }
        else
        {
            // Odd-indexed terms (except the first) are multiplied by 4
            sum += 4 * f_x;
        }
        free(expr3);
    }

    // Combine the terms
    sum = (deltaX / 3) * sum;

    return sum;
}

double trapezoidalApprox(int N, int b, int a, char* function, double deltaX)
{
    //initialize
    double sum = 0.0;
    int err;

    //compile expression 1
    double x = a;
    te_variable vars1[] = {{"x", &x}};
    te_expr *expr1 = te_compile(function, vars1, 1, &err);
    double f_a = te_eval(expr1); //returns expression value
    
    //compile expression 2
    x = b;
    te_variable vars2[] = {{"x", &x}};
    te_expr *expr2 = te_compile(function, vars2, 1, &err);
    double f_b = te_eval(expr2);

    printf("f_a: %f, f_b: %f\n", f_a, f_b);

    sum += f_a + f_b; // Add the first and last terms
    
    printf("current sum: %f\n", sum);

    //free expressions
    free(expr1);
    free(expr2);

    for (int i = 1; i < N; i++)
    {
        x = a + i * deltaX;
        te_variable vars3[] = {{"x", &x}};
        //compile expression 2
        te_expr *expr3 = te_compile(function, vars3, 1, &err);

        double f_x = te_eval(expr3);

        if (i > 1 || i < (N-1))
        {
            // multiply inner terms by 2 (except the second-to-last and first)
            sum += 2 * f_x;
        }
        // free the expression
        free(expr3);
    }

    // Combine the terms
    sum = (deltaX / 2) * sum;

    return sum;
}

void printMenu()
{
    printf("Simpsons & Trapezoidal Algorithm\n");
    printf("choose a number out of the list:\n");
    printf("1. Simpsons\n");
    printf("2. Trapezoidal\n");
    printf("Please input the algorithm you want to use: \n");
}

void printingNote()
{
    printf("\nNote, when inputting a function you can write it like this: e.g. x + x^2 or (x*5)^2 or (x * 5) / 2. \n");
    printf("Parenthesis work as intented\n");
    printf("Factorials work fac 5 == 120\n");
    printf("the following constants work pi, e\n");
}

int main()
{
    //initialization
    int N, b, a;
    char function[MAX_FUNC_SIZE];
    char choice;
    int loop = 1;
    
    //Starter menu
    printMenu();

    scanf("%c", &choice);

    //error checking on the choice
    if (choice == '1' || choice == '2')
    {
        loop = 0;
        //grab newline
        scanf("%c");
    }
    else
    {
        while (loop)
        {
            scanf("%c");
            if (choice == '1' || choice == '2')
            {
                loop = 0;
                break;
            }
            else
            {
                printf("Please reinput your choice\n");
                scanf("%c", &choice);
            }
        }
    }

    printingNote();

    printf("\nPlease input the function you want to integrate (max chars = %d)\n", MAX_FUNC_SIZE);

    //get function with whitespace
    scanf("%[^\n]s", function);

    printf("Please input the number of intervals (N): \n");
    scanf("%d", &N);
    
    printf("Please input the lower bound (a): \n");
    scanf("%d", &a);

    printf("Please input the upper bound (b): \n");
    scanf("%d", &b);

    //calculate deltaX
    double deltaX = (double)(b-a) / (double)N;
    
    // simpsons rule or trapezoidal
    if (choice == '1') 
    {
        double sum = simpsonsApprox(N, b, a, function, deltaX); 
        printf("Simpsons Aproximation of the integral from %d-%d of %s = %f\n", a, b, function, sum);
    }
    else 
    {
        double sum = trapezoidalApprox(N, b, a, function, deltaX); 
        printf("Trapizoidal Aproximation of the integral from %d-%d of %s = %f\n", a, b, function, sum);
    }

    return 0;
}