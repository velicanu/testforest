## testforest
==========
To run you need to have either a link or a clone of HiForestAnalysis in this direcotry:

```bash
ln -s /path/to/HiForestAnalysis
```
or
```bash
git clone git@github.com:CmsHI/HiForestAnalysis.git
```

Then to run either: 


```bash
g++ testforest.C $(root-config --cflags --libs) -std=c++11 -Werror -Wall -O2 -o testforest.exe
```
or in root
```c++
root [0] .L testforest.C+
```

## getentries
run the following script to getentries of the tree
```bash
# to get all the entries of every tree in the forest, for consistency checking
./getentries.sh <hiforest-file>
# to get entries of the first tree (faster) if you know they are consistent and want the number fast 
./getentries.sh <hiforest-file> 1
```

