#!/bin/bash
WORKSPACE=$2
IMAGEID=$1
HOSTNAME=devcon
docker run -i -h ${HOSTNAME} -v /work -v ${WORKSPACE}:/workspace -t ${IMAGEID} /bin/bash
