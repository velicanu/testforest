#!/bin/bash
if [ $# -lt 1 ]
then
  echo "Usage: ./getl1rates.sh <rootfile> [justone]"
  exit 1
fi

now=$(date +%s%N)

echo "{" > ${now}_getThisEntries.C
echo "  TFile * _file0 = new TFile(\"$1\");" >> ${now}_getThisEntries.C

~/testforest/lsroot.sh $1 > ${now}_tmproot.txt
for i in ` cat tmproot.txt | grep TDirectoryFile | sed 's@;.*@@g' | awk '{print $3}' ` 
do 
  ~/testforest/lsdir.sh $1 $i >  ${now}_tmpdir.txt
  cat ${now}_tmpdir.txt | grep TTree |  sed 's@;.*@@g' | awk '{print $3}' > ${now}_tmptree.txt
  for j in `cat ${now}_tmptree.txt | sort | uniq `
  do
    echo "TTree * $i$j = (TTree*) _file0->Get(\"$i/$j\");" >> ${now}_getThisEntries.C
    echo "std::cout<<\"$i/$j entries = \"<<$i$j->GetEntries()<<std::endl;" >> ${now}_getThisEntries.C
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
echo "}" >> ${now}_getThisEntries.C

root -b -q ${now}_getThisEntries.C

rm ${now}_*
#rm tmpdir.txt tmptree.txt tmproot.txt 

