# meteo-zone
Meteo-zone weather service.<br>
<h2>Raspberry Pi client</h2><br>
<img src="http://s017.radikal.ru/i417/1601/c3/d44363bc983a.png" /><br>
<b>Depedencies:</b>
````
apt-get install cmake clang libboost-thread1.55.0 libboost-thread1.55-dev libboost-system1.55.0 libboost-system1.55-dev wiringpi
````
<b>DHT22 library</b>
````
git clone https://github.com/LittleBuster/pi-dht22.git
cd pi-dht22
mkdir build && cd build
cmake .. && make
make install
````
<b>Installation:</b>
````
git clone https://github.com/LittleBuster/meteo-zone.git
cd meteo-zone
cd pi-client
mkdir build && cd build
cmake .. && make
make install
nano /etc/meteo.cfg
#add to autorun /usr/share/meteo/mzclient and "chmod +x mzclient"
````
<h2>Meteo server</h2><br>
<b>Depedencies (CentOS):</b>
````
yum install clang cmake boost-system boost-devel mariadb mariadb-devel
````
<b>Installation:</b>
````
git clone https://github.com/LittleBuster/meteo-zone.git
cd meteo-zone
cd server
mkdir build && cd build
cmake .. && make
make install
nano /etc/meteo-users.cfg #add users id in column
nano /etc/meteosrv.cfg
#add to autorun /usr/share/meteosrv/mzserver and "chmod +x mzserver"
````
<br>
Developed by: <b>Sergey Denisov</b>
<br>
Email: <b>DenisovS21@gmail.com</b>
