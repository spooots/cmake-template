#!/bin/bash
IMAGEID=$1
HOSTNAME=devcon
echo "docker run -i -h ${HOSTNAME} -v /work -v ${WORKSPACE}:/workspace -t ${IMAGEID} /bin/bash"
docker run -i -h ${HOSTNAME} -v ${PWD}/src:/workspace -v ${PWD}/build:/work -t ${IMAGEID}
#docker run -i -h ${HOSTNAME} -v /work -v ${WORKSPACE}:/workspace -t ${IMAGEID} /bin/bash
