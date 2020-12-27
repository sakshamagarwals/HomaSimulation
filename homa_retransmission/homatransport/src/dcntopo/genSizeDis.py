import os
import argparse

# senderNum = 32
# msgSize = 128000

parser = argparse.ArgumentParser(description="gen size distribution")
parser.add_argument('--senderNum', type=int, default=32)
parser.add_argument('--msgSize', type=int, default=32000)
args = parser.parse_args()
senderNum = args.senderNum
msgSize = args.msgSize

receiverId = "0"
deltaTime = "0"

os.chdir ("../../sizeDistributions/")
fileName = "HostidSizeInterarrival.txt"


file = open (fileName, "w+")
for i in range(senderNum):
    line = "\t".join ([str(i+1), receiverId, str(msgSize), deltaTime, "\n"])
    file.write (line)

file.close

