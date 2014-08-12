#include "fcgi_stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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

	char fileName[255];
	char fileType[255];
	char filePath[255];
	char fileHash[255];
	char fileSize[255];

	char newFilePath[255];

	struct stat statBuf;

	while (1) {
		//The program will wait inside of FCGI_Accept untill it gets a new request
		FCGI_Accept ();

		//Response
		FCGI_printf ("Content-type: text/html\r\n\r\n");
		FCGI_printf ("UPLOADED\n");

		//Read file info and move file to permanent location
		while  (readPostMultipart (fileName)) {
			readPostMultipart (fileType);
			readPostMultipart (filePath);
			readPostMultipart (fileHash);
			readPostMultipart (fileSize);

			FCGI_printf ("<p>File name: %s</p>\n", fileName);
			FCGI_printf ("<p>File type: %s</p>\n", fileType);
			FCGI_printf ("<p>File path: %s</p>\n", filePath);
			FCGI_printf ("<p>File hash: %s</p>\n", fileHash);
			FCGI_printf ("<p>File size: %s</p>\n", fileSize);

			sprintf (newFilePath, "/www/dump/%s", fileName);
			FCGI_printf ("Moving file to %s\n", newFilePath);

			if (!stat(newFilePath, &statBuf)) {
				remove (newFilePath);
				FCGI_puts ("<p>Replaced existing file</p>");
			}

			rename (filePath, newFilePath);
		}

		//Flush and free
		FCGI_Finish ();
	}
}

