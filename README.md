testforest
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
