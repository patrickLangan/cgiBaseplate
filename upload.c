#include "fcgi_stdio.h"
#include <stdlib.h>

int main (int argc, char **argv)
{
	unsigned int length;
	char *buffer;
	FCGI_FILE *file;

	while (1) {
		//The program will wait inside of FCGI_Accept untill it gets a new request
		FCGI_Accept ();

		//Writing the post request to a file
		length = atoi (getenv ("CONTENT_LENGTH"));
		buffer = malloc (length);
		FCGI_fread (buffer, length, 1, FCGI_stdin);
		file = FCGI_fopen ("uploadRequest.txt", "w");
		FCGI_fwrite (buffer, length, 1, file);
		FCGI_fclose (file);

		//Response
		FCGI_printf ("Content-type: text/html\r\n\r\n");
		FCGI_printf ("<p>Files have been uploaded.<p>\n");

		//Flush and free
		FCGI_Finish ();
		free (buffer);
	}
}

