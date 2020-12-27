import errno
import numpy as np
import os
import sys
import json
import math
#traces = ["aditya", "dctcp", "datamining"]
#traces = ["aditya", 'dctcp']
traces = ["aditya"]
loads = [5, 6, 7, 8, 9]
#loads = [6]
ID = 0
SIZE = 1
START_TIME = 2
END_TIME = 3
RATIO = 4

bandwidth = 0

BDP = 0
FIRST_THRESHOLD = 0
SECOND_THRESHOLD = 0
THIRD_THRESHOLD = 0
FOURTH_THRESHOLD = 0
FIFTH_THRESHOLD = 0
bandwidth = 0

def get_oracle_fct(same_tor, flow_size):
    num_hops = 8
    if (same_tor == 1):
        num_hops = 4

    propagation_delay = num_hops * 0.00000065

    b = bandwidth * 1000000000.0
    # pkts = (float)(flow_size) / 1460.0
    # np = math.floor(pkts)
    # # leftover = (pkts - np) * 1460
    # incl_overhead_bytes = 1500 * np
    # incl_overhead_bytes = 1500 * np + leftover
    # if(leftover != 0): 
    #     incl_overhead_bytes += 40
    
    # bandwidth = 10000000000.0 #10Gbps
    transmission_delay = 0

    # transmission_delay = (incl_overhead_bytes + 40) * 8.0 / bandwidth
    transmission_delay = flow_size * 8.0 / b
    # if (num_hops == 4):
    #     # 1 packet and 1 ack
    #     # if (leftover != 1460 and leftover != 0):
    #     #     # less than mss sized flow. the 1 packet is leftover sized.
    #     #     transmission_delay += 2 * (leftover + 2 * 40) * 8.0 / (4 * bandwidth)
            
    #     # else:
    #     # # 1 packet is full sized
    #     #     transmission_delay += 2 * (1460 + 2 * 40) * 8.0 / (4 * bandwidth)
    #     transmission_delay += 1.5 * 1478 * 8.0 / bandwidth
    # # if (leftover != 1460 and leftover != 0):
    # #     # less than mss sized flow. the 1 packet is leftover sized.
    # #     transmission_delay += (leftover + 2 * 40) * 8.0 / (bandwidth)
        
    # # else:
    # #     # 1 packet is full sized
    # #     transmission_delay += (1460 + 2 * 40) * 8.0 / (bandwidth)
    # else:
    #     transmission_delay += 1 * 1478 * 8.0 / bandwidth
    if (num_hops == 8):
        # 1 packet and 1 ack
        # if (leftover != 1460 and leftover != 0):
        #     # less than mss sized flow. the 1 packet is leftover sized.
        #     transmission_delay += 2 * (leftover + 2 * 40) * 8.0 / (4 * bandwidth)
            
        # else:
        # # 1 packet is full sized
        #     transmission_delay += 2 * (1460 + 2 * 40) * 8.0 / (4 * bandwidth)
        transmission_delay += 1.5 * 1500 * 8.0 / b
#        transmission_delay += 2.5 * 40 * 8.0 / b
    # if (leftover != 1460 and leftover != 0):
    #     # less than mss sized flow. the 1 packet is leftover sized.
    #     transmission_delay += (leftover + 2 * 40) * 8.0 / (bandwidth)
        
    # else:
    #     # 1 packet is full sized
    #     transmission_delay += (1460 + 2 * 40) * 8.0 / (bandwidth)
    else:
        transmission_delay += 1 * 1500 * 8.0 / b
 #       transmission_delay += 2 * 40 * 8.0 / b
    return transmission_delay + propagation_delay

def read_homa_file(filename):
    output = []
    total_sent_packets = 0.0
    total_packets = 0.0
    finish_time = 0
    s_time = 1.0
    reach_check_point = 0
    with open(filename) as f:
        lines = f.readlines()
        for i in range(len(lines) - 1):
            line = lines[i]
            params = line.split()
            if params[0] == "##":
                total_unsent_packets = float(params[2])
                total_packets = float(params[3])
                reach_check_point += 1
            elif reach_check_point < 20:
                same_tor = int(params[0])
                size = float(params[1])
                start_time = float(params[2])
                end_time = float(params[3])
                fct = float(params[4])
                orct = get_oracle_fct(same_tor, size)
                ratio = fct / orct
                if(ratio <= 1.0):
                    ratio = 1.0
                #    print fct, orct
                
                # if fct < orct:
                #     print line
                #     print fct
                #     print orct
                # assert(fct > orct)
                # ratio = float(params[8])
                # if reach_check_point < 10:
                # assert(ratio > 1.0)
                output.append([0, size, start_time, end_time, ratio])
    return output, total_unsent_packets,total_packets

def read_homa_queue_file(filename):
    mean_s = 0
    max_s = 0
    with open(filename) as f:
        lines = f.readlines()
        tors = lines[len(lines) - 1].split()[1:]
        aggs = lines[len(lines) - 2].split()[2:]

        for t in range(len(tors)):
            if t % 2 == 0:
                mean_s = max(mean_s, float(tors[t]))
            else:
                max_s = max(max_s, float(tors[t]))
        for a in range(len(aggs)):
            if a % 2 == 0:
                mean_s = max(mean_s, float(aggs[a]))
            else:
                max_s = max(max_s, float(aggs[a]))
    return mean_s, max_s

def get_mean_fct_oct_ratio(output):
    total = 0
    for line in output:
        total += line[RATIO]
    return total / float(len(output))

def get_99_fct_oct_ratio(output):
    data = []
    for line in output:
        data.append(line[RATIO])
        #if line[FCT] / line[ORCT] > 8.0:
         #   print line[SIZE] / 1460
    return np.percentile(data, 99)

def read_homa_files(file = "./"):
    # file = direc + "result_homa_{}.txt".format("load")
    output = {}
    with open(file) as json_file:
        output = json.load(json_file)
    if "DCTCP" in output:
        output['dctcp'] = output.pop("DCTCP")
    if "DataMining" in output:
        output['datamining'] = output.pop("DataMining")
    if "IMC10" in output:
        output['aditya'] = output.pop("IMC10")
    return output

def get_mean_fct_oct_ratio_size(output, segments):
    total = []
    for i in range(segments):
        total.append([])

    num_elements = [0] * segments
    for line in output:
        size = line[SIZE]
        ratio = line[RATIO]
        if size < FIRST_THRESHOLD:
            total[0].append(ratio)
            num_elements[0] += 1
        elif size < SECOND_THRESHOLD:
            total[1].append(ratio)
            num_elements[1] += 1
        elif size < THIRD_THRESHOLD:
            total[2].append(ratio)
            # if ratio > 10:
            #     print line 
            num_elements[2] += 1
        elif size < FOURTH_THRESHOLD:
            total[3].append(ratio)
            # if ratio > 30:
            #     print line 
            num_elements[3] += 1
        elif size < FIFTH_THRESHOLD:
            total[4].append(ratio)
            num_elements[4] += 1
        else:
            total[5].append(ratio)
            num_elements[5] += 1
    return total, num_elements

def read_homa_output(direc, stats):
    input_prefix = direc + "/result_homa_"
    queue_input_prefix = direc + "/queue_size_"
    for k in traces:
        if k not in stats:
            stats[k] = {}
        for j in loads:
            load = "{:.1f}".format(float(j) / 10)
            if load not in stats[k]:
                stats[k][load] = {}
            file = input_prefix + k + "_{}.txt.csv".format(j)
            queue_file = queue_input_prefix + k + "_{}.txt".format(j)
            output, total_unsent_packet, total_packets = read_homa_file(file)
            total, num_elements = get_mean_fct_oct_ratio_size(output, 6)
            print total_unsent_packet
	    stats[k][load]['util'] = 1 - total_unsent_packet  / float(total_packets)
            stats[k][load]['mean'] = get_mean_fct_oct_ratio(output)
	    print stats[k][load]['util']
	    print len(output)
            stats[k][load]['99'] = get_99_fct_oct_ratio(output)
           # stats[k][load]['switch_mean'],stats[k][load]['switch_max'] = read_homa_queue_file(queue_file)
            stats[k][load]['mean_flow_size'] = [ np.mean(total[j]) for j in range(len(total))]
            stats[k][load]['std'] =  [ np.percentile(total[j], 99) - np.mean(total[j]) for j in range(len(total))]
    return stats



def main():
    global bandwidth, FIRST_THRESHOLD, SECOND_THRESHOLD, THIRD_THRESHOLD, FOURTH_THRESHOLD,FIFTH_THRESHOLD
    date = str(sys.argv[1])
    bandwidth = int(sys.argv[2])
    queue = str(sys.argv[3])
    stats = {}
    b = bandwidth * 1e9
    rtt = (0.65 * 4 + 1500.0 * 8 / b * 1000000.0 * 2.5) * 2
    BDP = int(math.ceil(rtt / (1500.0 * 8 / b * 1000000.0)))
    BDP = 24
    print (BDP)
    FIRST_THRESHOLD = BDP * 1460 
    SECOND_THRESHOLD = BDP * 2 * 1460
    THIRD_THRESHOLD = BDP * 4 * 1460
    FOURTH_THRESHOLD = BDP * 8 * 1460
    FIFTH_THRESHOLD = BDP * 16 * 1460
    # queue = str(sys.argv[3])
    #stats = read_homa_files("result_homa_{}_load_{}.txt".format(queue, bandwidth))
    stats =  read_homa_output("./results/" + date, stats)
    # draw_graph(average, "FCT_OCT_Ratio" + "_" + workload + "_" + alg)
    # draw_graph(stats, num_elements, workload + " FCT_OCT_ratio")
    out = open("result_homa_{}_load_{}.txt".format(queue, bandwidth) , 'w')
    file = json.dumps(stats)
    out.write(file)
    out.close()
main()
