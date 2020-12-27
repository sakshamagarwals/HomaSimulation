import os
import sys

incast_degree = [10, 20, 40, 60, 80, 100, 160, 200, 300, 320]

for i in range(len(incast_degree)):
  filename = "HostidSizeInterarrival_" + str(incast_degree[i]) + "_to_1.txt"
  f= open(filename,"w+")
  for j in range(incast_degree[i]):
    f.write("%d %d 50000 0\n" % ( j , incast_degree[i]) )
  f.close()



