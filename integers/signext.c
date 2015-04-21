// demonstrates sign extension (for signed values)
// and zero extension (for unsigned values)

#include <stdio.h>

int main (int argc, char **argv)
{
    short           s16 = -123;
    int             s32 = s16;
    
    unsigned short  u16 = 123;
    unsigned int    u32 = u16;
    
    printf("s16 %6hd, s32 %10d\n", s16, s32);
    printf("s16 0x%04hX, s32 0x%08X\n\n", s16, s32);
    printf("u16 %6hu, u32 %10u\n", u16, u32);
    printf("u16 0x%04hX, u32 0x%08X\n\n", u16, u32);

    return 0;
}
