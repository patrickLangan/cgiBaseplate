#!/bin/bash
rm /etc/nginx/nginx.conf
cp nginx.conf /etc/nginx

rm /etc/nginx/fastcgi_params
cp fastcgi_params /etc/nginx

rm /www/index.html
cp index.html /www

