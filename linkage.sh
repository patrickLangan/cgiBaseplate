#!/bin/bash
rm /usr/local/nginx/conf/nginx.conf
cp nginx.conf /usr/local/nginx/conf

rm /usr/local/nginx/conf/fastcgi_params
cp fastcgi_params /usr/local/nginx/conf

rm /www/index.html
cp index.html /www

/usr/local/nginx/sbin/nginx -s reload

