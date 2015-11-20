#!/bin/bash
if [ $# -ne 1 ]
then
  echo "Usage: ./getl1rates.sh <rootfile>"
  exit 1
fi

echo "{" > getThisEntries.C
echo "  TFile * _file0 = new TFile(\"/data/velicanu/store/group/phys_heavyions/velicanu/forest/Run2015E/ExpressPhysics/Merged/ExpressHiForest_run262163-262172_100k.root\");" >> getThisEntries.C

./lsroot.sh $1 > tmproot.txt
for i in ` cat tmp | grep TDirectoryFile | sed 's@;1@@g' | awk '{print $3}' ` 
do 
  ./lsdir.sh /data/velicanu/store/group/phys_heavyions/velicanu/forest/Run2015E/ExpressPhysics/Merged/ExpressHiForest_run262163-262172_100k.root $i >  tmpdir.txt
  cat tmpdir.txt | grep TTree |  sed 's@;1@@g' | awk '{print $3}' > tmptree.txt
  for j in `cat tmptree.txt`
  do
    echo "TTree * $i$j = (TTree*) _file0->Get(\"$i/$j\");" >> getThisEntries.C
    echo "std::cout<<\"$i/$j entries = \"<<$i$j->GetEntries()<<std::endl;" >> getThisEntries.C
  done
done
echo "}" >> getThisEntries.C

root -b -q getThisEntries.C

rm tmpdir.txt tmptree.txt tmproot.txt 

