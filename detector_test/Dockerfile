FROM jansson/appnuc
LABEL authors="Marielle Aksér <marielle.akser@gmail.com>"

WORKDIR /project
COPY . .

RUN gcc -o d_test main.cpp
RUN ./d_test

