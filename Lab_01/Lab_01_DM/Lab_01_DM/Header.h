#pragma once

#include <iostream>
#include <cmath>

typedef long double ldouble;

using namespace std;

typedef struct {
	int iterations;
	ldouble result;
} SResult;

ldouble f(ldouble x) {
    return atan(x) - sin(x);
}

void Swap(ldouble& left, ldouble& right) {
    ldouble temp = left;
    left = right;
    right = temp;
}

bool SetLimits(ldouble& leftLim, ldouble& rightLim, ldouble eps) {
    bool onGoing = true, resultIsFound = false;
    ldouble step = (fabs(leftLim) + fabs(rightLim)) / 10, fX = 0, fLeft = 0;

    if (leftLim > rightLim)
        Swap(leftLim, rightLim);

    if (step >= 1)
        step = 1;

    fLeft = f(leftLim);
    if (fLeft == 0) {
        resultIsFound = true;
        rightLim = fLeft;
        onGoing = false;
    }

    while (onGoing) {

        for (ldouble x = leftLim + step; x < rightLim; x += step) {
            fX = f(x);

            if (fabs(fX) <= eps) {
                leftLim = x;
                rightLim = x;
                resultIsFound = true;
                onGoing = false;
                break;
            }

            if (fLeft * fX <= 0) {
                rightLim = x;
                leftLim = x -= step;
                onGoing = false;
                break;
            }

            fLeft = fX;
        }
        step /= 10;
    }

    return resultIsFound;
}

class Secant {

private:
	ldouble leftLim, rightLim, x, eps;
	SResult result;

	ldouble FindSecant(ldouble a, ldouble b) {

		return a - (f(a) * (b - a)) / (f(b) - f(a));
	}

public:
	Secant(ldouble a, ldouble b, ldouble eps) {
        this->leftLim = a;
        this->rightLim = b;
        this->eps = eps;
        result.iterations = 0;
        result.result = NAN;
        x = 0;

	}

	SResult Find() {
		x = FindSecant(leftLim, rightLim);

        bool resultIsFound = false;

        resultIsFound = SetLimits(leftLim, rightLim, eps);
        if (resultIsFound)
            x = leftLim;

        ldouble staticPoint = 0;
		ldouble xPrev = x;
        while (!resultIsFound) {
            result.iterations++;

            if (f(x) * f(leftLim) <= 0)
                staticPoint = leftLim;
            else
                staticPoint = rightLim;

            xPrev = x;
            x = FindSecant(x, staticPoint);

            if (fabs(x - xPrev) <= eps)
                resultIsFound = true;
        }
		result.result = x;

		return result;
	}

};

class Dichotomy {
private:
    ldouble leftLim, rightLim, eps;
    SResult result;

public:
    Dichotomy(ldouble leftLim, ldouble rightLim, ldouble eps) {
        this->leftLim = leftLim;
        this->rightLim = rightLim;
        this->eps = eps;
        result.iterations = 0;
        result.result = NAN;
    }

    SResult Find()
    {
        ldouble midLim = 0;
        bool BordersAreSetting = true, resultIsFound = false;

        resultIsFound = SetLimits(leftLim, rightLim, eps);

        if (resultIsFound)
            midLim = leftLim;
        else
            midLim = (leftLim + rightLim) / 2;
        while (!resultIsFound) {
            result.iterations++;

            if (f(leftLim) * f(midLim) <= 0) {
                rightLim = midLim;
            }
            else {
                leftLim = midLim;
            }

            midLim = (leftLim + rightLim) / 2;
            if (fabs(leftLim - rightLim) < eps)
                resultIsFound = true;

        }
        result.result = midLim;

        return result;
    }
};    
