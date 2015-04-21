// demonstrates some anomalies in the compiled code
// for integer arithmetic

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

int main (int argc, char **argv)
{
    int     x = 3;
    int     y = 2;
    int     signed16MaxValue =                  0x7FFF;
    int     signed32MaxValue =              0x7FFFFFFF;
    int     val;

    unsigned int    unsigned32MaxValue =    0xFFFFFFFF;
    unsigned int    unsignedDivisor =             0x10;
    unsigned int    uval;
    
    // a normal multiplication that works correctly
    val = x * y;
    
    // signed 16-bit multiplication that works correctly
    val = signed16MaxValue * signed16MaxValue;
    
    // signed 32-bit multiplication - does this work correctly?
    val = signed32MaxValue * signed32MaxValue;
    
    // the variables being used are unsigned,
    // so this statement should compile as unsigned multiplication
    uval = unsigned32MaxValue * unsigned32MaxValue;
    
    // a normal division that works correctly
    val = x / y;

    // the variables being used are unsigned,
    // so this statement should compile as unsigned division
    uval = unsigned32MaxValue / unsignedDivisor;
    
    return 0;
}

