#!/bin/bash
if [ $# -ne 2 ]
then
  echo "Usage: ./lsroot.sh <rootfile> <dirname>"
  exit 1
fi

root -b <<EOF
TFile *_file1 = TFile::Open("$1");
$2->cd()
.ls
.q
EOF

