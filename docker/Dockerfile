FROM ubuntu:24.04

ENV TZ=Europe/Warsaw
ARG DEBIAN_FRONTEND=noninteractive

# apt
RUN apt update -y && apt upgrade -y && apt install -y \
    python3 \
    python3-pip \
    git \
    wget \
    cmake \
    unzip \
    build-essential \
    libc++-dev \
    rsync \
    openssh-server \
    gdb && \
    valgrind && \
    apt clean \

RUN apt install -y \
    libgtest-dev && \
    apt clean

#ssh for remote development
RUN mkdir /var/run/sshd && \
    echo 'root:pass1234' | chpasswd && \
    sed -i 's/#Port 22/Port 10023/' /etc/ssh/sshd_config && \
    sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config && \
    sed -i 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' /etc/pam.d/sshd
EXPOSE 10023

#ccache
ARG VERSION=4.10.2
ARG CCACHE_SRC=ccache-$VERSION
ARG CCACHE_TAR=$CCACHE_SRC.tar.gz
RUN wget https://github.com/ccache/ccache/releases/download/v$VERSION/$CCACHE_TAR && \
    tar -xzf $CCACHE_TAR && rm $CCACHE_TAR && \
    cd $CCACHE_SRC && \
    mkdir build && \
    cd build && cmake .. -DCMAKE_BULD_TYPE=Release && \
    make install -j`nproc` && \
    cd ../../ && \
    rm -r $CCACHE_SRC

