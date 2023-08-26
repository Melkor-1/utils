#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

int my_strcasecmp1 (const char *restrict s, const char *restrict t) 
{
	assert (s && t);

	int p, q;

	do {
		p = * ((unsigned char *) s++);
		q = * ((unsigned char *) t++);

		p = tolower (toupper (p));
		q = tolower (toupper (q));
	} while (p == q && p != '\0');

	return p - q;
}

int my_strcasecmp2 (const char *restrict s, const char *restrict t)
{
	assert (s && t);

	int p, q;
	
	do {
		p = *s++;
		if (islower (p)) {
			p = toupper ( (unsigned char) p);
		}
		q = *t++;
		if (islower (q)) {
			q = toupper ( (unsigned char) p);
		}
	} while (p == q && q != '\0');
	
	return p - q;
}

int main (void) 
{
	static const char s[] = "aPple";
	static const char t[] = "APPLE";

    !my_strcasecmp2 (s, t) ? puts ("Compared equal.") : puts ("Failed.");
#if 0    
	if (!my_strcasecmp2 (s, t)) {
		puts ("Compared equal.");
	} else {
		puts ("Failed");
	}
#endif
	return EXIT_SUCCESS;
}


