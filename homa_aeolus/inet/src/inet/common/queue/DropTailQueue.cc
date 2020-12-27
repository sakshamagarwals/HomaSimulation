//
// Copyright (C) 2005 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "inet/common/INETDefs.h"

#include "inet/common/queue/DropTailQueue.h"
#include "inet/linklayer/ethernet/EtherMACBase.h"
#include "inet/linklayer/ethernet/Ethernet.h"
#include "transport/HomaPkt.h"

namespace inet {

Define_Module(DropTailQueue);

void DropTailQueue::initialize()
{
    PassiveQueueBase::initialize();

    queue.setName(par("queueName"));

    // Configure the HomaPkt priority sort function
    if (par("transportType").stdstringValue() == "HomaTransport") {
        queue.setup(&HomaPkt::comparePrios);
    } else if (par("transportType").stdstringValue() == "PseudoIdealTransport") {
        queue.setup(&HomaPkt::compareSizeAndPrios);
    }

    //statistics
    emit(queueLengthSignal, queue.length());
    emit(queueByteLengthSignal, queue.getByteLength());

    outGate = gate("out");

    // configuration
    frameCapacity = par("frameCapacity");
    enableAeolus = par("enableAeolus"); 
    selectiveDropThres = par("selectiveDropThres");

    max_queue_length_recorded = 0;
    queue_length_sum = 0;
    queue_length_print_counter = 0;

    mac = getNextMacLayer();
    if (!mac) {
        EV_WARN << "Warning. No mac connected to queue module.\n";
    }

}

cMessage *DropTailQueue::enqueue(cMessage *msg)
{
    double txRate = 0.0; // transmit speed of the next mac layer 
    if (mac) {
        txRate = dynamic_cast<EtherMACBase*>(mac)->getTxRate();
    }

   // EV << "frameCapacity = "<< frameCapacity <<endl;

    if (frameCapacity && queue.length() >= frameCapacity) {
        EV << "Queue full, dropping packet.\n";
        // std::cout << "Queue full, dropping packet."<<frameCapacity<<endl;

        // cPacket* tempPkt = check_and_cast<cPacket*>(msg);
        // tempPkt = HomaPkt::searchEncapHomaPkt(tempPkt); 
        // if (tempPkt){
        //     HomaPkt* homaPkt = check_and_cast<HomaPkt*>(tempPkt);
        //     std::cout<<"type: "<<homaPkt->getPktType()<<endl;
        // }
        return msg;
    }

    EV<<"DropTailQueue::enqueue:  queue.length() = "<< queue.length()<<endl;

    // at the queueing time, we check how much of the previous transmitting
    // packet is remained to be serialized and trigger queueLength signals
    // with current queue length and the remainder of that packet.
    int pktOnWire = 0;
    int txPktBitsRemained = 0; 

    if (lastTxPktDuration.second > simTime()) {
        txPktBitsRemained =  (int)((lastTxPktDuration.second - simTime()).dbl() * txRate);
        pktOnWire = 1;
    }

    if (queue.length() == 0 && pktOnWire == 0) {
            queueEmpty++;
    } else if ((queue.length() == 0 && pktOnWire == 1) 
            || (queue.length() == 1 && pktOnWire == 0)) {
        queueLenOne++;
    }

    // The timeavg of queueLength queueByteLength will not be accurate if
    // the queue(Byte)LengthSignal is emitted before a packet is stored at
    // the queue (similar to the following line) however the average of
    // queueLength at the packet arrival time at the queue will be accurate.
    // If you want the timeavg of queueLength instead, comment out the
    // following line and decomment the other emit invokations of
    // queueLengthSignal in this file.
    emit(queueLengthSignal, queue.length() + pktOnWire);
    emit(queueByteLengthSignal, queue.getByteLength() + (txPktBitsRemained >> 3));

    if (enableAeolus){
      cPacket* tempPkt = check_and_cast<cPacket*>(msg);
      tempPkt = HomaPkt::searchEncapHomaPkt(tempPkt);
      if (tempPkt){
        HomaPkt* homaPkt = check_and_cast<HomaPkt*>(tempPkt);
        switch(homaPkt->getPktType()){
          case PktType::REQUEST:
          case PktType::UNSCHED_DATA:
            EV << "Receive unscheduled_data at drop_tail_queue.\n";
            //  std::cout << "Receive unscheduled_data at drop_tail_queue with msgId = "<< homaPkt->getMsgId() <<endl;
            EV << "queue.length() = " << queue.length() << "  selectiveDropThres = " <<selectiveDropThres<<endl;
            
            // std::cout<<"DropTailQueue(), queue length = "<<queue.length()<<endl;

            if (queue.length() >= selectiveDropThres){
                EV << "Reaching selective dropping threshold, dropping packet.\n";
              
                // std::cout<<"DropTailQueue(), drop pkt"<<endl;

                return msg;
            }
            break;
          case PktType::SCHED_DATA:
          //  std::cout << "Receive scheduled pkt at drop_tail_queue with msgId = "<< homaPkt->getMsgId() <<endl;
          case PktType::GRANT:
          case PktType::MSG_ACK:
            break;
          case PktType::UNSCHED_FIN_PROBE:
            EV << "Receive probe at drop_tail_queue.\n";
          //  std::cout << "Receive probe at drop_tail_queue with msgId = "<< homaPkt->getMsgId() <<endl;
            break;
          default:
            throw cRuntimeError("Received packet type(%d) is not valid.",
                homaPkt->getPktType());
        }
      }else {
        EV << "not HomaPkt.\n";
      }
    }

    cPacket* pkt = check_and_cast<cPacket*>(msg);
    queue.insert(pkt);

    queue_length_print_counter += 1;
    queue_length_sum += queue.length();

    if (queue.length() > max_queue_length_recorded){
      max_queue_length_recorded = queue.length();
    }

    if (queue_length_print_counter == 20000){
      std::cout<<"max_queue = "<<max_queue_length_recorded << " avg_queue = " << (queue_length_sum/20000)<< "\n";
      queue_length_print_counter = 0;
      queue_length_sum = 0;
    } 
    //emit(queueLengthSignal, queue.length());
    //emit(queueByteLengthSignal, queue.getByteLength());
    return NULL;
}

cMessage *DropTailQueue::dequeue()
{
    if (queue.empty())
        return NULL;

    cPacket* pkt = queue.pop();

    // statistics
    //emit(queueLengthSignal, queue.length());
    //emit(queueByteLengthSignal, queue.getByteLength());

    return (cMessage *)pkt;
}

void DropTailQueue::sendOut(cMessage *msg)
{
    send(msg, outGate);
}

bool DropTailQueue::isEmpty()
{
    return queue.empty();
}

void
DropTailQueue::setTxPktDuration(int txPktBytes)
{
    double txRate = 0.0; // transmit speed of the next mac layer

    if (txPktBytes == 0) {
        lastTxPktDuration.first = 0;
        lastTxPktDuration.second = simTime();
        return;
    }
    
    lastTxPktDuration.first = txPktBytes + (INTERFRAME_GAP_BITS >> 3) +
            PREAMBLE_BYTES + SFD_BYTES;
    double lastTxBits = 0.0;
    lastTxBits = lastTxPktDuration.first * 8.0;

    if (mac) {
        txRate = dynamic_cast<EtherMACBase*>(mac)->getTxRate();
    }

    if (txRate <= 0.0) {
        lastTxPktDuration.second = simTime();
        return;
    }

    lastTxPktDuration.second = simTime() + lastTxBits / txRate;
    return;
}

cModule*
DropTailQueue::getNextMacLayer()
{
    cModule* parentModule = getParentModule(); 
    if (!parentModule->hasGate("out")) {
        return NULL;
    }

    cGate* parentOutGate = parentModule->gate("out");
    cGate* destGate = parentOutGate->getNextGate();
    cModule* nextModule = destGate->getOwnerModule();

    if (strcmp(nextModule->getName(), "mac") != 0) {
        return NULL;
    }

    return nextModule;

}

} // namespace inet

