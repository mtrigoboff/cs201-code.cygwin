// demonstrates passing floating point arguments,
// returning a floating point value,
// and doing a calculation using the FPU register stack

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

double fn (double w, double x, double y, double z)
{
    return 3.0 * (w + x) / (y * z);
}

int main ()
{
    double  f;
    
    f = fn(213.0, 43.0, 20.0, 1.2);
    
    return 0;
}
