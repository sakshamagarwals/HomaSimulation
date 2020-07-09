import os
import sys


iniFolder = "bursty/"
# workLoad = "InFileDist"
# workLoad = "WorkloadGoogleSearchRpc"

workLoad = "WorkloadDCTCP"
# workLoad = "WorkloadHadoop"
# workLoad = "WorkloadWebServer"
# workLoad = "WorkloadCacheFollower"

# loadList = [0.5, 0.6, 0.7, 0.8] # correspond to -r 0 1 2 3 
# **.realLoadFactor = ${rlf=0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.75, 0.8, 0.85, 0.9}
loadList = [0.5]

# for i in range (len(loadList)):
i = 3
    
os.chdir ("../")
cmd = "cp ./bursty/bursty.ini ./tmp.ini"
print(cmd)
os.system(cmd)
cmd = "../homatransport -u Cmdenv -c " + workLoad + " -r " + str(i) + " -n ..:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET " + "./tmp.ini"
print(cmd)
os.system(cmd)
