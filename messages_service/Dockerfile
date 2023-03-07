FROM apz_micro_basics:latest
COPY . /usr/src/messages_service
WORKDIR /usr/src/messages_service

RUN mkdir build && cd build && cmake .. . -DIN_DOCKER=1 && make && cd .. && \
    /sbin/ldconfig -v

CMD ["./build/messages_service"]