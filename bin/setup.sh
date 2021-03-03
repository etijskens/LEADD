#!/bin/bash

# This script does the project setup on Leibniz. It must be executed only once.
# if it is sourced,

#-------------------------------------------------------------------------------
# create workspace on scratch and clone the github repo
mkdir -p $VSC_SCRATCH/workspace
cd $VSC_SCRATCH/workspace
module load git
echo 'Cloning https://github.com/etijskens/LEADD.git ...'
git clone https://github.com/etijskens/LEADD.git

#-------------------------------------------------------------------------------
# Creates the Python virtual environment .venv and activate it
module load IntelPython3-Packages
cd LEADD
echo 'Creating virtual environment LEADD/.venv ...'
python -m venv .venv --system-site-packages
. .venv/bin/activate

#-------------------------------------------------------------------------------
# Install the necessary Python packages
echo 'Installing micc-build ...'
pip install et_micc_build


#-------------------------------------------------------------------------------
# Final comments
if [[ $_ != $0 ]]
then
  # script was sourced
  module list
  echo 'You can now build the python module from the C++ code. Run:'
  echo '  (.venv) > micc-build'
else
  # script was not sourced
  echo 'Source the LEADD/bin/leibniz.sh script to prepare your environment'
  echo 'for building the Python module form the C++ code using micc-build.'
  echo '  > . $VSC_SCRATCH/workspace/LEADD/bin/leibniz.sh'
  echo '  (.venv) > micc-build'
fi
