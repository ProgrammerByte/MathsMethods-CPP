#include <iostream>
#include <iomanip>
//#include <vector>
//#include <string>
//#include <time.h>

using namespace std;

const double PI = 3.14159265358979323846;
const double e = 2.71828182845904523536;

int factorial(int num) {
    int result = 1;
    for (int i = 2; i <= num; i++) {
        result *= i;
    }
    return result;
}

int sumX(int start, int end) {
    int result = 0;
    for (int i = start; i <= end; i++) {
        result += i;
    }
    return result;
}

double binomialExpansion(double x, double n, int iterations) { // |x| < 1 is assumed to be true, calculates (1 + x)^n
    double result = 1;
    double currentVal = 1;
    for (int i = 0; i < iterations; i++) {
        currentVal *= (double)(x * (n - i)) / (i + 1);
        if (currentVal == 0) {
            break;
        }
        result += currentVal;
    }



    return result;
}

double intPow(double base, int exponent) { //for integer exponents
    double result = 1;
    int exponentModulus = (exponent > 0) ? exponent:-exponent;
    for (int i = 0; i < exponentModulus; i++) {
        result *= base;
    }
    if (exponent > 0) {
        return result;
    }
    else {
        return (double)1 / result;
    }   
}

double root(double value, int exponent, int iterations) { //in this case exponent refers to the nth root
    double x = value - 1;
    int multiplier = 1;
    int exponentModulus = (exponent > 0) ? exponent:-exponent;
    while (x < -1 || x > 1) {
        multiplier *= 10;
        x = ((double)value / (intPow(multiplier, exponentModulus))) - 1;
    }
    double result = binomialExpansion(x, (double)1 / exponentModulus, iterations) * multiplier;
    if (exponent > 0) {
        return result;
    }
    else {
        return (double)1 / result;
    }
}

double ln(double value, int iterations) { //value > 0 is assumed
    int multiplier = 1;
    while (value > 2) { //until valid
        multiplier *= 2;
        value = root(value, 2, iterations);
    }

    double result = 0;
    if (value != 1) {
        double x = value - 1;
        double currentX = -1;
        for (int i = 1; i <= iterations; i++) { //applying Maclaurin series
            currentX *= -x;
            result += (double)currentX / i;
        }
    }
    return result * multiplier;
}

void simplifyFraction(int numerator, int denominator) {
    //int minVal = (numerator < denominator) ? numerator:denominator;
    cout << numerator << " / " << denominator << " simplifies to: " << endl;

    if (numerator % denominator == 0) {
        cout << numerator / denominator << endl;
    }
    else if (denominator % numerator == 0) {
        cout << "1 / " << denominator / numerator << endl;
    }

    else {
        int i = 2;
        while (i <= denominator) {
            if (numerator % i == 0 && denominator % i == 0) {
                numerator /= i;
                denominator /= i;
            } else {
                i += 1;
            }
        }
        cout << numerator << " / " << denominator << endl;
    }
}

//isSin is true whenever sin or sinh are called
//multiplier is -1 for sin and cos, and 1 for everything else (using Maclaurin series)
double exp(double x, int iterations, bool skip, bool isSin, int multiplier) { //skip is used for trigonometric and hyperbolic functions
    double result = 0;
    double currentVal = 1;
    for (int i = 1; i <= iterations; i++) {
        if (skip == false || (i + isSin) % 2 == 1) {
            result += currentVal;
            currentVal *= multiplier;
        }

        currentVal *= (double)x / i;
        if (currentVal == 0) {
            break;
        }
    }
    return result;
}

double calcExp(double x, int iterations) { //calculates e^x and is used for other methods
    return exp(x, iterations, false, false, 1);
}

double reduce(double x) { //reduces the value of x by 2PI until it can no longer be done, done in order to keep calculations accurate in trigonometric functions
    double period = 2 * PI;
    while (x >= period) {
        x -= period;
    }
    while (x <= -period) {
        x += period;
    }
    return x;
}

double sin(double x, int iterations) {
    return exp(reduce(x), iterations, true, true, -1);
}

double cos(double x, int iterations) {
    return exp(reduce(x), iterations, true, false, -1);
}

double tan(double x, int iterations) {
    return (double)sin(reduce(x), iterations) / cos(reduce(x), iterations);
}

double sinh(double x, int iterations) {
    return exp(x, iterations, true, true, 1);
}

double cosh(double x, int iterations) {
    return exp(x, iterations, true, false, 1);
}

double tanh(double x, int iterations) {
    return (double)sinh(x, iterations) / cosh(x, iterations);
}

//base^exponent = e^exponent*ln(base)
double doublePow(double base, double exponent, int iterations) { //when the exponent is a decimal value
    return calcExp(exponent * ln(base, iterations), iterations);
}

int main() {
    cout << std::setprecision(10);

    //the following are all test lines
    //cout << factorial(5) << endl;
    //cout << sumX(10, 100) << endl;
    //cout << intPow(4, -5) << endl;
    //cout << (double)binomialExpansion(0.5, 0.5, 10) << endl;

    //cout << root(1564, -7, 10000000) << endl; //many iterations are performed to give a very high level of accuracy

    //simplifyFraction(intPow(2, 5), intPow(2, 8));

    //cout << calcExp(5.6, 10000) << endl;
    //cout << sin(-PI / 2, 1000000) << endl;
    //cout << cos(-0.6, 1000000) << endl;
    //cout << tan(17 * e, 1000000) << endl; //as the value of x increases, the accuracy of this calculation decreases
    //cout << sinh(7 * PI, 1000000) << endl;
    //cout << cosh(-PI, 1000000) << endl;
    //cout << tanh(-15, 1000000) << endl;

    //cout << ln(50 * e, 1000000) << endl;

    //cout << doublePow(25, 0.5, 1000000) << endl;
    return 0;
}