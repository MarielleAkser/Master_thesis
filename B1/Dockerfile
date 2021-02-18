FROM jansson/appnuc
LABEL authors="Marielle Aksér <marielle.akser@gmail.com>"

WORKDIR /project
COPY . .

# ENV LD_LIBRARY_PATH="/usr/local/geant4.10.07.p01/lib:/usr/local/geant4.10.07.p01/lib"
SHELL ["/bin/bash", "-c", "-l"]
RUN . /etc/profile.d/geant4.sh && \
    mkdir build && \
    cd build && \
    cmake -DGeant4_DIR=/usr/local/geant4.10.07.p01/lib/Geant4-10.7.1 .. && \
    make