FROM jansson/appnuc
LABEL authors="Marielle Aksér <marielle.akser@gmail.com>"

WORKDIR /project
COPY . .

SHELL ["/bin/bash", "-c", "-l"]

RUN apt-get update && \
    apt-get install -y mesa-utils libgl1-mesa-glx \
    xserver-xorg-video-nvidia-390

RUN . /etc/profile && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make
