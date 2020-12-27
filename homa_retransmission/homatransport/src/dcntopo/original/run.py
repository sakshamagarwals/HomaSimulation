import os
import sys


iniFolder = "original/"

# workLoad = "WorkloadDCTCP"
# workLoad = "WorkloadHadoop"
# workLoad = "WorkloadWebServer"
workLoad = "WorkloadCacheFollower"


# for i in range (len(loadList)):
i = 0
    
os.chdir ("../")
cmd = "cp ./original/spinleaf.ini ./tmp2.ini"
print(cmd)
os.system(cmd)
cmd = "../homatransport -u Cmdenv -c " + workLoad + " -r " + str(i) + " -n ..:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET " + "./tmp2.ini"
print(cmd)
os.system(cmd)








