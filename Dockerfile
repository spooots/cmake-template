FROM debian

MAINTAINER Andreas Schedel <andreas.schedel@gmail.com>

ENV LANG C.UTF-8

RUN useradd andi \
    && usermod -aG sudo andi \
    && apt-get update -y \
    && apt-get install -y  --no-install-recommends \
        cmake \
        g++ \
        gcc \
        git \
        lcov \
        make \
        openssh-server \
        qt5-default \
        sudo \
        tig \
        tmux \
        unzip \
        valgrind \
        vim \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

RUN sed -i 's/PermitRootLogin without-password/PermitRootLogin yes/' /etc/ssh/sshd_config
EXPOSE 22

RUN /bin/bash
