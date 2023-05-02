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

bool SetLimits(ldouble& leftLim, ldouble& rightLim, ldouble eps) {
    bool onGoing = true, resultIsFound = false;
    ldouble step{ (fabs(leftLim) + fabs(rightLim)) / 10 }, fX{ 0 }, fLeft{ 0 };

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
        }

        if(onGoing)
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

ldouble Get1D(ldouble x) {
    return (1 / (x * x + 1) - cos(x));
}

void ShowIterations(const ldouble current_x, const ldouble previous_x, const int number_of_iterations) {
    if (number_of_iterations == 1)
        cout << endl << endl << "Iterations method:" << endl << endl << "№\t\t" << "current x\t\t" << "previous x\t\t" << "difference\t\t" << endl;

    cout << number_of_iterations << "\t\t" << current_x << " \t\t" << previous_x << " \t\t" << fabs(current_x - previous_x) << endl;
}
void ShowNewton(const ldouble current_x, const ldouble previous_x, const int number_of_iterations) {
    if (number_of_iterations == 1)
        cout << endl << endl << "Newton method:" << endl << endl << "№\t\t" << "current x\t\t" << "previous x\t\t" << "difference\t\t" << endl;

    cout << number_of_iterations << "\t\t" << current_x << "\t\t" << previous_x << "    \t\t" << fabs(current_x - previous_x) << endl;
}

class Newton {
private:
    ldouble leftLim;
    ldouble rightLim;
    ldouble eps;
    SResult result;

    ldouble Get2D(ldouble x) {
        return sin(x) - 2 * x / ((x * x + 1) * (x * x + 1));
    }
    ldouble GetX(ldouble x) {
        return x - (f(x) / Get1D(x));
    }
public:
    Newton(ldouble leftLim, ldouble rightLim, ldouble eps) {
        this->leftLim = leftLim;
        this->rightLim = rightLim;
        this->eps = eps;
        result = { 0, NAN };
    }

    SResult Find() {
        bool resultIsFound = false;

        resultIsFound = SetLimits(leftLim, rightLim, eps);

        if (resultIsFound)
            result.result = leftLim;

        while ((Get1D(leftLim) * Get1D(rightLim) <= 0 || Get2D(leftLim) * Get2D(rightLim) <= 0)) {
            resultIsFound = SetLimits(leftLim, rightLim, eps);
            
            if (resultIsFound) {
                result.result = leftLim;
                break;
            }
        }

        if (!resultIsFound) {
            ldouble runLim = 0, prevLim = 0;

            if (Get2D(leftLim) > 0 && Get1D(leftLim) > 0) {
                runLim = rightLim;
            }
            else if (Get2D(leftLim) > 0 && Get1D(leftLim) < 0)
                runLim = leftLim;
            else if (Get2D(leftLim) < 0 && Get1D(leftLim) > 0)
                runLim = leftLim;
            else
                runLim = rightLim;

            while (fabs(runLim - prevLim) > eps) {
                result.iterations++;

                prevLim = runLim;
                runLim = GetX(runLim);

                ShowNewton(runLim, prevLim, result.iterations);
            }

            result.result = runLim;
        }

        return result;
    }
};

class SimpleIterations {
private:
    ldouble leftLim;
    ldouble rightLim;
    ldouble eps;

    SResult result;

    ldouble GetCloser(ldouble x, ldouble k) {
        return x - f(x)/k;
    }

    ldouble GetDerForFi(ldouble x, ldouble max_derivative) {
        return 1 - Get1D(x) / max_derivative;
    }
public:
    SimpleIterations(ldouble leftLim, ldouble rightLim, ldouble eps) {
        this->leftLim = leftLim;
        this->rightLim = rightLim;
        this->eps = eps;

        result = { 0, NAN };
    }

    SResult Find() {
        bool resultIsFound = false;

        resultIsFound = SetLimits(leftLim, rightLim, eps);

        result.result = leftLim;

        if (!resultIsFound){

            ldouble maxDerivative = 0, currentDerivative = 0, prevRes = leftLim;

            for (ldouble n = leftLim; n < rightLim; n += fabs(leftLim + rightLim) / 10)
                if (fabs(currentDerivative = Get1D(n)) > maxDerivative)
                    maxDerivative = currentDerivative;

            cout << "Derivatives of fi: " << endl;
            for (ldouble x = leftLim; x < rightLim; x += fabs(leftLim + rightLim) / 20) {
                cout << GetDerForFi(x, maxDerivative) << endl;
            }
            cout << endl;

            result.result = GetCloser(result.result, maxDerivative);
            while (!(fabs(result.result - prevRes) <= eps)) {
                result.iterations++;

                prevRes = result.result;
                result.result = GetCloser(result.result, maxDerivative);

                ShowIterations(result.result, prevRes, result.iterations);
            }
        }
        return result;
    }
};