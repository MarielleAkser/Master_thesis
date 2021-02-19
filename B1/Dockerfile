FROM jansson/appnuc
LABEL authors="Marielle Aksér <marielle.akser@gmail.com>"

WORKDIR /project
COPY . .

SHELL ["/bin/bash", "-c", "-l"]

RUN apt-get update && \
    apt-get install -y mesa-utils libgl1-mesa-glx \
    xserver-xorg-video-nvidia-390 

RUN . /etc/profile.d/geant4.sh && \
    mkdir build && \
    cd build && \
    cmake -DGeant4_DIR=/usr/local/geant4.10.07.p01/lib/Geant4-10.7.1 .. && \
    make