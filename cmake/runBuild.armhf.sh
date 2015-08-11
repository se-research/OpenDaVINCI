#!/bin/bash

cat <<EOF > $HOME/run.sh
#!/bin/bash
apt-get -y install cmake python
cd GITHUB/Mini-Smart-Vehicles/sources/OpenDaVINCI-msv/build 
cmake -DPANDABOARD=YES .. && make && echo 'NATIVE_BUILD=SUCCESS' && make test && echo 'NATIVE_TEST=SUCCESS'
chown -R 1000:1000 ..
EOF
chmod 755 $HOME/run.sh


cd sources && cd OpenDaVINCI-msv && \
  rm -fr build data && \
  ./generateDataStructures.sh && \
  mkdir build && \
  docker run --rm -ti --net="host" -v $HOME/GITHUB:/GITHUB -v $HOME/run.sh:/run.sh seresearch/opendavinci-ubuntu-armhf:latest /run.sh
   
