#!/bin/bash
if [ $# -lt 1 ]
then
  echo "Usage: ./getl1rates.sh <rootfile> [justone]"
  exit 1
fi

echo "{" > getThisEntries.C
echo "  TFile * _file0 = new TFile(\"$1\");" >> getThisEntries.C

./lsroot.sh $1 > tmproot.txt
for i in ` cat tmproot.txt | grep TDirectoryFile | sed 's@;1@@g' | awk '{print $3}' ` 
do 
  ./lsdir.sh $1 $i >  tmpdir.txt
  cat tmpdir.txt | grep TTree |  sed 's@;1@@g' | awk '{print $3}' > tmptree.txt
  for j in `cat tmptree.txt`
  do
    echo "TTree * $i$j = (TTree*) _file0->Get(\"$i/$j\");" >> getThisEntries.C
    echo "std::cout<<\"$i/$j entries = \"<<$i$j->GetEntries()<<std::endl;" >> getThisEntries.C
    if [[ "${2}" ]]
    then
      break
    fi
  done
  if [[ "${2}" ]]
  then
    break
  fi
done
echo "}" >> getThisEntries.C

root -b -q getThisEntries.C

#rm tmpdir.txt tmptree.txt tmproot.txt 

