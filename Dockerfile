FROM debian

MAINTAINER Andreas Schedel <andreas.schedel@gmail.com>

ENV LANG C.UTF-8

RUN apt-get update -y && apt-get install -y --no-install-recommends \
        cmake \
        g++ \
        gcc \
        git \
        lcov \
        make \
        openssh-server \
        qt5-default \
        qtcreator \
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

RUN export uid=1000 gid=1000 && \
    mkdir -p /home/builder && \
    echo "builder:x:${uid}:${gid}:Developer,,,:/home/builder:/bin/bash" >> /etc/passwd && \
    echo "builder:x:${uid}:" >> /etc/group && \
    echo "builder ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/builder && \
    chmod 0440 /etc/sudoers.d/builder && \
    chown ${uid}:${gid} -R /home/builder

USER builder
ENV HOME /home/builder

RUN /bin/bash
