# Homa

## Installation

1. Follow [Homa](https://github.com/PlatformLab/HomaSimulation/tree/omnet_simulations/RpcTransportDesign/OMNeT%2B%2BSimulation) to install omnetpp-4.6, patch and inet framwork. We modified `/homa_retransmission/inet/src/inet/common/queue/DropTailQueue.ned` to set finite switch buffer. By defalut, we set

   ```c++
   int frameCapacity = default(334);
   ```

2. make homa in `/homa_retransmission/homatransport`



## How to run

* path: `/homa_retransmission/homatransport/src/dcntopo`

  ```
  ../homatransport -u Cmdenv -c WorkloadDCTCP -r 0 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig.ini
  ```

  * -c WorkloadDCTCP: workload type
  * -r 0: iterator number in OMNET++
  * homaTransportConfig.ini: topology file



## File Description

* `/homa_retransmission/homatransport/sizeDistributions`: workload flow size distribution

* `/homa_retransmission/homatransport/src`: transport src folder
  * `dcntopo`: topology file
  * `transport/HomaTransport.cc`: main body of Homa
* Some options like `enableFileOutput` in `transport/HomaTransport.cc` & `application/WorkloadSynthesizer.cc`

* Timeout value `msgTimeoutValSender & msgTimeoutValReceiver` in `transport/HomaTransport.cc` 



## How Retransmission Works

We use two Timers to implement Homa retransmission mechanism. 

When transport receives a message from app, it will bind a SxTimer to this message. After timeout, the SxTimer will be triggered and a SelfMsg will be sent to this sender. Then the sender will resend this message. The SxTimer will be cancelled when this sender receives GRANT from the receiver. 

When receiver receives a packet from network, it will reset corresponding message's RxTimer. The RxTimer will be triggered after timeout and then this receiver will prepare and send a RESEND packet back to the sender. The sender will resend packets according to the RESEND information. Also, the RxTimer will be canceled after this message finished.


