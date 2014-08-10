ALL:
	gcc post.c -lfcgi -o post
	gcc upload.c -lfcgi -o upload
