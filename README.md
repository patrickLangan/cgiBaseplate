cgiBaseplate
============

Setup on ubuntu 12.04 LTS 64bt
------------------------------
apt-get install git <br>
apt-get install gcc <br>
apt-get install libpcre3-dev <br>
apt-get install zlib1g-dev <br>
apt-get install make <br>
apt-get install libssl-dev <br>
<br>
wget nginx.org/download/nginx-1.6.0.tar.gz <br>
git clone https://github.com/masterzen/nginx-upload-progress-module.git <br>
git clone -b 2.2 git://github.com/vkholodkov/nginx-upload-module.git nginx-upload-module-2.2m <br>
<br>
./configure --add-module=../nginx-upload-module-2.2m --add-module=../nginx-upload-progress-module <br>
make <br>
make install <br>
<br>
apt-get install libfcgi-dev <br>
apt-get install spawn-fcgi <br>
<br>
git clone https://github.com/patrickLangan/cgiBaseplate.git <br>
make <br>
./startup.sh <br>
./linkage.sh <br>
./runCGI.sh <br>

