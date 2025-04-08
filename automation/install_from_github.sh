#!/bin/bash

# Example usage: 
# ./install_from_git.sh "yhirose/cpp-httplib" "-DHTTPLIB_TEST=OFF"
REPO=$1
OPTION_STRNG=$2

TEMP_DIR=$(mktemp -d)
echo "TEMP DIR: ${TEMP_DIR}"
cd ${TEMP_DIR}
rm -rf ${TEMP_DIR}/git_source
git clone "https://github.com/${REPO}.git" ${TEMP_DIR}/git_source
cd ${TEMP_DIR}/git_source/
mkdir build && cd build
cmake $OPTION_STRNG ..
mkdir -p /var/log/cmake

LOG_NAME="/var/log/install-${REPO//\//_}.log"
echo "Install log written to '${LOG_NAME}'"
make install VERBOSE=1 > ${LOG_NAME}
cd ~/ 
rm -rf ${TEMP_DIR}
