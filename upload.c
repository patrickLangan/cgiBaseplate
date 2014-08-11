#include "fcgi_stdio.h"
#include <stdlib.h>
#include <string.h>

/* todo
 * Error checking, handling, and prevention
 */

int readPostMultipart (char *postVal)
{
	char line[255];
	size_t length;

	//Read and ignore the first line
	FCGI_fgets (line, 255, FCGI_stdin);

	//Check the header type
	FCGI_fread (line, 38, 1, FCGI_stdin);
	line[38] = '\0';
	if ((strcmp (line, "Content-Disposition: form-data; name=\"")))
		return 0;

	//Read and ignore up until the last line
	FCGI_fgets (line, 255, FCGI_stdin);
	FCGI_fgetc (FCGI_stdin);
	FCGI_fgetc (FCGI_stdin);

	//Read the value
	FCGI_fgets (postVal, 255, FCGI_stdin);

	//Remove the newline
	length = strlen (postVal) - 2;
	postVal[length] = '\0';

	return 1;
}

int main (int argc, char **argv)
{
	unsigned int length;
	FCGI_FILE *file;

	char *fileName = malloc (255);
	char *fileType = malloc (255);
	char *filePath = malloc (255);
	char *fileHash = malloc (255);
	char *fileSize = malloc (255);

	char *newFilePath = malloc (255);

	while (1) {
		//The program will wait inside of FCGI_Accept untill it gets a new request
		FCGI_Accept ();

		//Response
		FCGI_printf ("Content-type: text/html\r\n\r\n");

		//Read file info and move file to permanent location
		while  (readPostMultipart (fileName)) {
			readPostMultipart (fileType);
			readPostMultipart (filePath);
			readPostMultipart (fileHash);
			readPostMultipart (fileSize);

			sprintf (newFilePath, "/www/upload/%s", fileName);
			rename (filePath, newFilePath);
		}

		//Flush and free
		FCGI_Finish ();
		free (fileName);
		free (fileType);
		free (filePath);
		free (fileHash);
		free (fileSize);
		free (newFilePath);
	}
}

