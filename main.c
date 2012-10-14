#include <system.h>

/* You will need to code these up yourself*/
unsigned char *memcpy(unsigned char *dest, const unsigned cahr *src, int count) {
    /* Add code here to copy 'count' bytes of data
     * from 'src' to 'dest', finally return 'dest'
     * */
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count) {
    /* Add code here to set 'count' bytes in 'dest' to
     * 'val'. Again, return 'dest'
     * */
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count) {
    /* Same as above, but this time, we're working
     * with a 16-bit 'val' and dest pointer.
     * Your code can be an exact copy of the above,
     * provided that your local variables if any, 
     * are unsigned short */
}

int strlen(const char *str) {
    /* This loops through character array 'str'
     * returning how many chars it needs to check 
     * before it finds a 0.
     * In simple words, it returns the length in bytes
     * of a string.*/
}

/* We will use this later on for reading from 
 * the I/O ports to get data from devices such
 * as the keyboard. We are using what is called
 * 'inline assembly' in these routines to actually
 *  do the work */
unsigned char inport (unsigned short _port) {
    unsigned char rv;
    /*"N" : Const in range 0 to 255(for out instruction) */
    __asm__ __volatile__("inb %1, %0" : "=a" (rv): "dN"(_port));
    return rv;
}
