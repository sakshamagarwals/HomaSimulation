import sys

INPUT_FILE = sys.argv[1]
OUTPUT_FILE = INPUT_FILE + '.homa'
outfile = open(OUTPUT_FILE,'w')

print(INPUT_FILE)

flows = []

def Sort_Tuple(tup):  
  
    # reverse = None (Sorts in Ascending order)  
    # key is set to sort using second element of  
    # sublist lambda has been used  
    tup.sort(key = lambda x: x[3])  
    return tup

with open(INPUT_FILE) as f1:
    f1.readline()
    for line in f1:
        line_str = line.split()
        src = int(line_str[0])
        dst = int(line_str[1])
        size_b = int(line_str[3]) * 1460
        arrival_time = float(line_str[4])
        flows.append((src,dst,size_b,arrival_time))

flows_sorted = Sort_Tuple(flows)

outfile = open(OUTPUT_FILE,'w')
# outfile.write(str(len(flows_sorted)) + '\n')
last_arrival_time = 0.0
for i in range(len(flows_sorted)):
    flow = flows_sorted[i]
    arrival_time = float(flow[3])
    delta_time = arrival_time - last_arrival_time
    assert(delta_time >= 0)
    last_arrival_time = arrival_time
    line_to_write = str(flow[0]) + ' ' + str(flow[1]) + ' ' + str(flow[2]) + ' ' + str("%.12f" % delta_time) + '\n'
    outfile.write(line_to_write)

outfile.close()  

# with open(INPUT_FILE) as f1:
#     num_flows = int(f1.readline())
#     last_arrival_time = 0.0
#     count = 0
#     for line in f1:
#         line_str  = line.split()
#         src = int(line_str[0])
#         dst = int(line_str[1])
#         size_bytes = int(line_str[3]) * 1460
#         arrival_time = float(line_str[4])
#         delta_time = arrival_time - last_arrival_time
#         assert(delta_time >= 0)
#         last_arrival_time = arrival_time
#         line_to_write = str(src) + ' ' + str(dst) + ' ' + str(size_bytes) + ' ' + str("%.12f" % delta_time) + '\n'
#         outfile.write(line_to_write)
#         count += 1
#         if(count == num_flows):
#             break
