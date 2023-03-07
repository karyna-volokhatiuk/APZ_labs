FROM apz_micro_basics:latest
COPY . /usr/src/facade_service
WORKDIR /usr/src/facade_service

#install cpr lib
RUN git clone https://github.com/libcpr/cpr.git && \
    cd cpr && mkdir build && cd build && \
    cmake .. -DCPR_USE_SYSTEM_CURL=ON && \
    cmake --build . && \
    cmake --install . && \
    cd ../..

#inctall boost/uuid
RUN apt -y install libboost-dev

RUN mkdir build && cd build && cmake .. . -DIN_DOCKER=1 && make && cd .. && \
    /sbin/ldconfig -v

CMD ["./build/facade_service"]