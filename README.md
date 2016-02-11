# meteo-zone
Meteo-zone weather service.<br><br>
<h2>Raspberry Pi client</h2><br>
<img src="http://s017.radikal.ru/i417/1601/c3/d44363bc983a.png" /><br>
<b>Depedencies:</b>
````
apt-get install libboost-thread1.55.0 libboost-thread1.55-dev libboost-system1.55.0 libboost-system1.55-dev
````
<b>DHT22 library</b>
````
git clone https://github.com/LittleBuster/pi-dht22.git
cd pi-dht22
make
sudo make install
````
<b>Installation:</b>
````
git clone https://github.com/LittleBuster/meteo-zone.git
cd meteo-zone
cd pi-client
make
sudo make install
nano /etc/meteo.cfg
#add to autorun /usr/share/meteo/mzclient
````
<h2>Meteo server</h2><br>
<b>Depedencies (CentOS):</b>
````
yum install gcc-c++ boost boost-devel mariadb mariadb-devel
````
<b>Installation:</b>
````
git clone https://github.com/LittleBuster/meteo-zone.git
cd meteo-zone
cd server
make
sudo make install
sudo nano /etc/meteo-users.cfg #add users id in column
sudo nano /etc/meteosrv.cfg
#add to autorun /usr/share/meteosrv/mzsrv
````
<br>
Developed by: <b>Sergey Denisov</b>
<br>
Email: <b>DenisovS21@gmail.com</b>
