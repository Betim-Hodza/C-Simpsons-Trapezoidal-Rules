#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAX_FUNC_SIZE 100

double parseFunction(char *function, double x);
double simpsonsApprox(int N, int b, int a, char* function, double deltaX);
double trapezoidalApprox(int N, int b, int a, char* function, double deltaX);

/*function looks through the string and parses out computational information
e.g. if the function was x+x^2+5 it would take that and return */
double parseFunction(char *function, double x)
{
    double result = 0.0;
    double prevValue = 0.0;
    int prevValSet = 0;

    char *token, *rest = function;
    char op = '+';

    while ((token = strtok_r(rest, "+-", &rest)))
    {
        double value = 1.0;

        if (*token == 'x')
        {
            value = x;
            token++;
        }
        else if (isdigit(*token))
        {
            value = strtod(token, &token);
        }

        if (*token == '^')
        {
            token++;
            double exponent = strtod(token, &token);
            value = pow(value, exponent);
        }

        switch (op)
        {
            case '+':
                result += value;
                break;
            
            case '-':
                result -= value;
                break;
            
            case '*':
                if (prevValSet)
                {
                    result = prevValue * value;
                }
                else
                {
                    result *= value;
                }
                break;

            case '/':
                if (prevValSet)
                {
                    result = prevValue * value;
                }
                else
                {
                    result /= value;
                }
                break;

            default:
                break;
        }

        prevValue = value;
        prevValSet = 1;
        op = (*rest == ' ') ? '+' : *rest;
    }
    
    return result;
}

double simpsonsApprox(int N, int b, int a, char* function, double deltaX)
{
    //initialize the sum
    double sum = 0;
    
    //iterate over the intervals
    for (int i = 1; i < N; i++)
    {
        double x = a + i * deltaX;
        double fX = parseFunction(function, x);

        //first and last terms we multiply by 1
        if (i == 1 || i == N)
        {
            sum += fX;
        }
        else if (i % 2 == 0)
        {
            //even index terms are multiplied by 2
            sum += 2 * fX;
        }
        else if (i % 2 == 1 || (i == N-1))
        {
            //odd index terms are multiplied by 4
            //the second to last term is multiplied by 4
            sum += 4 *fX;
        }
    }

    //combine and return sum
    sum = (deltaX / 3) * (sum);
    return sum;

}

double trapezoidalApprox(int N, int b, int a, char* function, double deltaX)
{

}

void printMenu()
{
    printf("Simpsons & Trapezoidal Algorithm\n");
    printf("1. Simpsons\n");
    printf("2. Trapezoidal\n");
    printf("Please input the algorithm you want to use: (i.e. 1 for simpsons)\n");
}

int main()
{
    //initialization
    int N, b, a;
    char function[MAX_FUNC_SIZE];
    char choice;
    
    //Starter menu
    printMenu();

    scanf("%c", &choice);

    //error checking on the choice
    while (1)
    {
        if (choice == '1' || choice == '2')
        {
            break;
        }
        else
        {
            printf("Please reinput your choice\n");
            scanf("%c", &choice);
        }
    }

    printf("Please input the function you want to integrate (max chars = %d)\n", MAX_FUNC_SIZE);
    printf("Note, function cannot be exponential, logrithmic: \n");
    scanf("%s", function);

    printf("Please input the number of intervals (N): \n");
    scanf("%d", &N);
    
    printf("Please input the lower bound (a): \n");
    scanf("%d", &a);

    printf("Please input the upper bound (b): \n");
    scanf("%d", &b);

    //calculate deltaX
    double deltaX = (double)(b-a) / (double)N;
    
    // simpsons rule or trapezoidal
    if (choice == 1) 
    {
        double sum = simpsonsApprox(N, b, a, function, deltaX); 
        printf("Aproximation of the integral from %d-%d of %s = %f\n", a, b, function, sum);
    }
    else 
    {
        double sum = trapezoidalApprox(N, b, a, function, deltaX); 
        printf("Aproximation of the integral from %d-%d of %s = %f\n", a, b, function, sum);
    }

    return 0;
}