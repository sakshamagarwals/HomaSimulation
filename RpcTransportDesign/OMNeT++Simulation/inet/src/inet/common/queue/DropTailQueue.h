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

#ifndef __INET_DROPTAILQUEUE_H
#define __INET_DROPTAILQUEUE_H

#include "inet/common/INETDefs.h"

#include "inet/common/queue/PassiveQueueBase.h"

namespace inet {

/**
 * Drop-front queue. See NED for more info.
 */
class INET_API DropTailQueue : public PassiveQueueBase
{
  public:
  uint32_t getByteLength(){
  	return queue.getByteLength();
  };
  protected:
    // configuration
    int frameCapacity;

    // state
    cPacketQueue queue;
    cGate *outGate;

  protected:
    virtual void initialize();

    /**
     * Redefined from PassiveQueueBase.
     */
    virtual cMessage *enqueue(cMessage *msg);

    /**
     * Redefined from PassiveQueueBase.
     */
    virtual cMessage *dequeue();

    /**
     * Redefined from PassiveQueueBase.
     */
    virtual void sendOut(cMessage *msg);

    /**
     * Redefined from IPassiveQueue.
     */
    virtual bool isEmpty();

  protected:
    /**
     * Redefined from IPassiveQueue.
     * Throws an exceptions when called for a packet not already queued or if
     * called more than once for the same queued packet.
     */
    virtual void setTxPktDuration(int txPktBytes);

    /**
     * Redefined from IPassiveQueue.
     */
    cModule* getNextMacLayer();


};

} // namespace inet

#endif // ifndef __INET_DROPTAILQUEUE_H

