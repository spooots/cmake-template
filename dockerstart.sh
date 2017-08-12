#!/bin/bash
IMAGEID=$1
HOSTNAME=devcon
echo "docker run -i -h ${HOSTNAME} -v /work -v ${WORKSPACE}:/workspace -t ${IMAGEID} /bin/bash"
docker run -it --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -h ${HOSTNAME} -v ${PWD}/src:/workspace -v ${PWD}/build:/work -t ${IMAGEID}
#1: docker run -i -h ${HOSTNAME} -v ${PWD}/src:/workspace -v ${PWD}/build:/work -t ${IMAGEID}
#0: docker run -i -h ${HOSTNAME} -v /work -v ${WORKSPACE}:/workspace -t ${IMAGEID} /bin/bash
