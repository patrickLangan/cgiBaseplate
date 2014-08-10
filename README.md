cgiBaseplate
============

Setup on ubuntu 12.04 LTS 64bt
------------------------------
apt-get install git
apt-get install gcc
apt-get install libpcre3-dev
apt-get install zlib1g-dev
apt-get install make
apt-get install libssl-dev

wget nginx.org/download/nginx-1.6.0.tar.gz
git clone https://github.com/masterzen/nginx-upload-progress-module.git
git clone -b 2.2 git://github.com/vkholodkov/nginx-upload-module.git nginx-upload-module-2.2m

./configure --add-module=../nginx-upload-module-2.2m --add-module=../nginx-upload-progress-module
make
make install

apt-get install libfcgi-dev
apt-get install spawn-fcgi

git clone https://github.com/patrickLangan/cgiBaseplate.git
make
./startup.sh
./linkage.sh
./runCGI.sh

