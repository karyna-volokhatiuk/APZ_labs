#https://devblogs.microsoft.com/cppblog/c-development-with-docker-containers-in-visual-studio-code/
FROM gcc:latest
COPY . /usr/src/apz_micro_basics
WORKDIR /usr/src/apz_micro_basics

#install meka and cmake
RUN apt -y update && \
    apt -y install make && \
    apt -y install cmake

#install httpserver lib dependencies
RUN apt -y install libmicrohttpd-dev

#install httpserver lib
RUN git clone https://github.com/etr/libhttpserver && \
    cd libhttpserver && \
    ./bootstrap && \
    mkdir build && \
    cd build && \
    ../configure && \
    make && \
    make install && \
    cd ../..

#install spdlog lib
RUN apt -y install libspdlog-dev
