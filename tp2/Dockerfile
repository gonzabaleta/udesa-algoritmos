FROM ubuntu
RUN apt-get update -y
RUN apt update -y && apt upgrade -y
RUN apt install gcc valgrind make -y
COPY . /tp
WORKDIR /tp
CMD make local
