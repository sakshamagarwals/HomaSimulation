import os

fileName = "oneRackIncast.xml"

serverNum = 301 # Num sender, 1 receiver, total Num+1

file = open (fileName, "w+")

par1 = [
"<topologyConfig>",
"\t<param>",
"\t</param>",
"\t<IPv4Configurator>",
"\t\t<config>"
]
par2 = []
if serverNum <= 255:
    partmp = [
    "\t\t\t<interface hosts='**.host[0.."+ str(serverNum) +"]' address='10.x.0.x' netmask='255.x.x.x'/>",
    "\t\t\t<interface hosts='**' address='10.x.x.x' netmask='255.x.x.x'/>"
    ]
    par2.extend (partmp)
elif serverNum > 255:
    partmp = [
    "\t\t\t<interface hosts='**.host[0..255]' address='10.x.0.x' netmask='255.x.x.x'/>",
    "\t\t\t<interface hosts='**.host[256.."+ str(serverNum-255) +"]' address='10.x.1.x' netmask='255.x.x.x'/>",
    "\t\t\t<interface hosts='**' address='10.x.x.x' netmask='255.x.x.x'/>"
    ]
    par2.extend (partmp)


par3 = [
"\t\t</config>",
"\t</IPv4Configurator>"
]
'''
par4 = [
"\t<hostConfig id="0">",
"\t\t<transportConfig>",
"\t\t</transportConfig>",
"\t\t<appConfig>",
"\t\t\t<!--if true, this host app will send messages as well-->",
"\t\t\t<isSender>false</isSender>",
"\t\t\t<!--One of the three patterns: 1) the space separated positive ids of the hosts that",
"\t\t\t\tthis app will send messages to. 2) If empty, it means the app will send randomly",
"\t\t\t\tto every possible host in the topology. 3) If -1, this app sends to all possible",
"\t\t\t\thosts except itself.-->",
"\t\t\t<!-- <destIds>-1</destIds> -->",
"\t\t</appConfig>",
"\t</hostConfig>"
]
'''
par4 = []
for i in range(serverNum+1):
    host = [
    "\t<hostConfig id=\""+ str(i) +"\">",
    "\t\t<transportConfig>",
    "\t\t</transportConfig>",
    "\t\t<appConfig>",
    "\t\t\t<isSender>true</isSender>",
    "\t\t\t<destIds>-1</destIds>",
    "\t\t</appConfig>",
    "\t</hostConfig>"
    ]
    par4 += host

par5 = [
"</topologyConfig>"
]

output = par1+par2+par3+par4+par5
output = "\n".join (output)
file.write (output)
file.close
