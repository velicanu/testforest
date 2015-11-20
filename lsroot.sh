#!/bin/bash
if [ $# -ne 1 ]
then
  echo "Usage: ./lsroot.sh <rootfile>"
  exit 1
fi

root -b <<EOF
TFile *_file1 = TFile::Open("$1");
.ls
.q
EOF

