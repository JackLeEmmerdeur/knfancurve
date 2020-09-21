FROM debian:buster-slim

RUN apt-get update && apt-get install -y cmake g++ make libqt5charts5 libqt5charts5-dev qt5-default

CMD ["/bin/bash"]
WORKDIR .
COPY dockercmake.sh /usr/local/bin/dockercmake.sh
WORKDIR /usr/local/bin
RUN chmod ug+x ./dockercmake.sh
CMD "./dockercmake.sh"