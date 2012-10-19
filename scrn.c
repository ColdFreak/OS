#include <system.h>

unsigned short *textmemptr;

/* '1111' is 15: White */
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;

/* Scrools the screen */
void scroll(void) {
	/* unsigned is 4 byte long */
	unsigned blank, temp;

	/* I think the result is 0010 backcolor green  */
	blank = 0x20 | (attrib << 8);

	/* Row 25 is the end, this means we need to scroll up */
	if(csr_y >= 25 ) {
		/* Move the current text chunk that makes up the screen 
		 * back in the buffer by a line*/
		temp = csr_y -25 + 1;
		memcpy(textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);

		/* Finally, we set the chunk of memory that occupies
		 * the last line of text to our 'blank' character */
		memsetw(textmemptr + (25 - temp) * 80, blank, 80);
		csr_y = 25 -1;
	}
}



