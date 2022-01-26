#pragma once
double drvt(double (*f)(double), double x)
{
    double delta = 1e-2, x1 = x + delta * 10, x2 = x + delta, eps = 1e-6;
    while (abs(abs((f(x2) - f(x)) / (x2 - x)) - abs((f(x1) - f(x)) / (x1 - x))) > eps)
    {
        delta /= 10;
        x1 = x2;
        x2 = x + delta;
    }
    return ((f(x2) - f(x)) / (x2 - x));
}
double Newton(double (*f)(double), double x0)
{
    double xn = x0, xn1 = x0 - f(x0) / drvt(f, x0), eps = 1e-6;
    while (abs(xn - xn1) > eps)
    {
        xn = xn1;
        xn1 = xn - f(xn) / drvt(f, xn);
    }
    return (xn1);
}
double intg(double (*f)(double), double x1, double x2)
{
    int N = 100;  double dx1 = (x2 - x1) / N * 10, dx2 = (x2 - x1) / N, S1 = 0, S2 = 0, eps = 1e-6;
    for (int i = 0; i < N / 10; i++) S1 += f(x1 + dx1 * i) * dx1;
    for (int i = 0; i < N; i++) S2 += f(x1 + dx2 * i) * dx2;
    while (abs(S2 - S1) > eps)
    {
        S1 = S2;
        dx1 = dx2;
        N *= 10;
        dx2 = (x2 - x1) / N;
        S2 = 0;
        for (int i = 0; i < N; i++) S2 += f(x1 + dx2 * i) * dx2;
    }
    return S2;
}