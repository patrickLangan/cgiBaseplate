#include "fcgi_stdio.h"
#include <stdlib.h>

int main (int argc, char **argv)
{
	while (FCGI_Accept() >= 0)
		printf("Content-type: text/html\r\n\r\n"
		       "%s", getenv("REMOTE_ADDR"));
}
