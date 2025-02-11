/*
 * MsgSizeDistributions.h
 *
 *  Created on: May 22, 2015
 *      Author: neverhood
 */

#ifndef MSGSIZEDISTRIBUTIONS_H_
#define MSGSIZEDISTRIBUTIONS_H_

#include <omnetpp.h>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <random>
#include <exception>
#include "common/Minimal.h"

class MsgSizeDistributions {

  PUBLIC:
    enum DistributionChoice {
        SIZE_IN_FILE = 0,
        DCTCP,
        GOOGLE_SEARCH_RPC,
        GOOGLE_ALL_RPC,
        FACEBOOK_KEY_VALUE,
        FACEBOOK_WEB_SERVER_INTRACLUSTER,
        FACEBOOK_CACHE_FOLLOWER_INTRACLUSTER,
        FACEBOOK_HADOOP_ALL,
        FABRICATED_HEAVY_MIDDLE,
        FABRICATED_HEAVY_HEAD,
        TEST_DIST,
	IMC10,
	DataMining,
        NO_SIZE_DIST_SPECIFIED //Should always remain the last

    };

    enum InterArrivalDist {
        INTERARRIVAL_IN_FILE = 0,
        EXPONENTIAL,
        GAUSSIAN,
        FACEBOOK_PARETO,
        CONSTANT,
        NO_INTERARRIAVAL_DIST_SPECIFIED //Should always remain the last
    };


    MsgSizeDistributions(const char* distFileName, int maxDataBytesPerPkt,
            InterArrivalDist interArrivalDist,
            DistributionChoice sizeDistSelector, double avgRate = 5.0,
            int callerHostId = -1);
    ~MsgSizeDistributions() {};
    void getSizeAndInterarrival(int &nextMsgSize, int& destHostId,
        double &nextInterarrivalTime);

  PRIVATE:
    std::vector<std::pair<int, double>> msgSizeProbDistVector;
    std::queue<std::tuple<int, int, double>> msgSizeDestInterarrivalQueue;

    // The value of this variable will determine which distribution should be
    // used for generating new messages in the sizeGenratorWrapper()
    DistributionChoice sizeDistSelector;
    InterArrivalDist interArrivalDist;

    // Average message size from the constructed distribution. This value is
    // read from the first line of the file 'distFileName'.
    double avgMsgSize;
    double avgInterArrivalTime;

    // Max number of data bytes that one packet can carry.
    int maxDataBytesPerPkt;

  PRIVATE:
    void getInfileSizeInterarrivalDest(int &msgSize, int &destHostId,
        double &nextInterarrivalTime);
    void getFacebookSizeInterarrival(int &msgSize,
            double &nextInterarrivalTime);
    void getInterarrivalSizeFromVec(int &msgSize, double &nextInterarrivalTime);
    double facebookParetoInterGap();
    double getInterarrivalTime();
    double interpolate(double x, double x1, double y1, double x2, double y2); 
};

struct MsgSizeDistException : std::exception {
    std::string msg;
    MsgSizeDistException(const char* msg)
        : msg(msg)
    {
    }

    const char* what() const noexcept
    {
        return msg.c_str();
    }
};

#endif /* MSGSIZEDISTRIBUTIONS_H_ */
