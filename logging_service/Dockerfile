FROM apz_micro_basics:latest
COPY . /usr/src/logging_service
WORKDIR /usr/src/logging_service

RUN apt -y install libtbb-dev

RUN mkdir build && cd build && cmake .. . -DIN_DOCKER=1 && make && cd .. && \
    /sbin/ldconfig -v

CMD ["./build/logging_service"]