#!/usr/bin/python
"""
This program is one place that the data for all plots will be parsed, packed,
and prepared. The plots themselves are generated by R scripts under PlotScripts
directory.
"""

from numpy import *
from glob import glob
from optparse import OptionParser
from pprint import pprint
from functools import partial
from xml.dom import minidom
import math
import os
import subprocess
import random
import re
import sys
import warnings
sys.path.insert(0, os.environ['HOME'] + '/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/analysis')
from parseResultFiles import *
from MetricsDashBoard import *

def roundLoadFactor(loadFactor):
    allLoads = [0.05, 0.1, 0.15, 0.2, 0.4, 0.5, 0.6, 0.7, 0.8]
    loadDiff = [abs(i - loadFactor) for i in allLoads]
    minDiff = min(loadDiff)
    loadFacInd = [i for i,j in enumerate(loadDiff) if j == minDiff][0]
    return allLoads[loadFacInd]

def prepE2EStretchVsSizeAndUnsched(resultDir = ''):
    """
    Parses the stretch data and generates colomnized text data of stretch versus
    the Unsched bytes for homatransport.
    """

    f = open(os.environ['HOME'] + "/HomaSimulation/RpcTransportDesign"+
        "/OMNeT++Simulation/analysis/PlotScripts/stretchVsUnsched.txt", 'w')
    tw_h = 40
    tw_l = 15
    f.write('LoadFactor'.center(tw_l) + 'WorkLoad'.center(tw_h) +
        'MsgSizeRange'.center(tw_l) + 'SizeCntPercent'.center(tw_l) +
        'BytesPercent'.center(tw_l) + 'UnschedBytes'.center(tw_l) +
        'MeanStretch'.center(tw_l) + 'MedianStretch'.center(tw_l) +
        '99PercentStretch'.center(tw_l) + '\n')
    for filename in glob(os.path.join(resultDir, '*.sca')):

        sp = ScalarParser(filename)
        parsedStats = AttrDict()
        parsedStats.hosts = sp.hosts
        parsedStats.tors = sp.tors
        parsedStats.aggrs = sp.aggrs
        parsedStats.cores = sp.cores
        parsedStats.generalInfo = sp.generalInfo


        xmlConfigFile =  os.environ['HOME'] + '/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/config.xml'
        xmlParsedDic = AttrDict()
        xmlParsedDic = parseXmlFile(xmlConfigFile,parsedStats.generalInfo)
        msgBytesOnWireDigest = AttrDict()
        msgBytesOnWire(parsedStats.hosts, parsedStats.generalInfo, xmlParsedDic, msgBytesOnWireDigest)
        e2eStretchAndDelayDigest = AttrDict()
        e2eStretchAndDelay(parsedStats, xmlParsedDic, msgBytesOnWireDigest, e2eStretchAndDelayDigest)
        loadFactor = float(parsedStats.generalInfo.rlf) * len(xmlParsedDic.senderIds) / len(xmlParsedDic.receiverIds)
        workLoad = parsedStats.generalInfo.workloadType
        avgStretch = 0.0

        try:
            UnschedBytes = int(parsedStats.generalInfo.defaultReqBytes) + int(parsedStats.generalInfo.defaultUnschedBytes)
        except Exception as e:
            print('No Unsched bytes in file: %s' % (filename))
            UnschedBytes = 'NA'

        for elem in e2eStretchAndDelayDigest.stretch:
            sizeUpBound = elem.sizeUpBound
            sizeProbability = elem.cntPercent
            bytesPercent = elem.bytesPercent
            meanStretch = float(elem.mean)
            medianStretch = float(elem.median)
            tailStretch = float(elem.ninety9Percentile)
            avgStretch += meanStretch * float(elem.cntPercent) / 100
            f.write('{0}'.format(loadFactor).center(tw_l) + '{0}'.format(workLoad).center(tw_h) +
                '{0}'.format(sizeUpBound).center(tw_l) + '{0:.5f}'.format(sizeProbability).center(tw_l) +
                '{0:.5f}'.format(bytesPercent).center(tw_l) + '{0}'.format(UnschedBytes).center(tw_l) +
                '{0}'.format(meanStretch).center(tw_l) + '{0}'.format('NA').center(tw_l) +
                '{0}'.format('NA').center(tw_l) + '\n')
            f.write('{0}'.format(loadFactor).center(tw_l) + '{0}'.format(workLoad).center(tw_h) +
                '{0}'.format(sizeUpBound).center(tw_l) + '{0:.5f}'.format(sizeProbability).center(tw_l) +
                '{0:.5f}'.format(bytesPercent).center(tw_l) + '{0}'.format(UnschedBytes).center(tw_l) +
                '{0}'.format('NA').center(tw_l) + '{0}'.format(medianStretch).center(tw_l) +
                '{0}'.format('NA').center(tw_l) + '\n')
            f.write('{0}'.format(loadFactor).center(tw_l) + '{0}'.format(workLoad).center(tw_h) +
                '{0}'.format(sizeUpBound).center(tw_l) + '{0:.5f}'.format(sizeProbability).center(tw_l) +
                '{0:.5f}'.format(bytesPercent).center(tw_l) + '{0}'.format(UnschedBytes).center(tw_l) +
                '{0}'.format('NA').center(tw_l) + '{0}'.format('NA').center(tw_l) +
                '{0}'.format(tailStretch).center(tw_l) + '\n')
        #f.write('{0}'.format(loadFactor).center(tw_l) + '{0}'.format(workLoad).center(tw_h) +
        #    '{0}'.format('overallsizes').center(tw_l) + '{0}'.format(1.00).center(tw_l) +
        #    '{0}'.format(100).center(tw_l) + '{0}'.format(unschedbytes).center(tw_l) +
        #    '{0}'.format(avgStretch).center(tw_l) + '{0}'.format('NA').center(tw_l) +
        #    '{0}'.format('NA').center(tw_l) + '\n')
    f.close()

def prepE2EStretchVsTransport(resultDir, outputFileName, resultFiles=[]):
    f = open(os.environ['HOME'] +
        "/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/analysis/PlotScripts/" +
        outputFileName, 'w')
    tw_h = 40
    tw_l = 15
    f.write('TransportType'.center(tw_l) + 'LoadFactor'.center(tw_l) +
        'WorkLoad'.center(tw_h) + 'MsgSizeRange'.center(tw_l) +
        'SizeCntPercent'.center(tw_l) + 'BytesPercent'.center(tw_l) +
        'UnschedBytes'.center(tw_l) + 'MeanStretch'.center(tw_l) +
        'MedianStretch'.center(tw_l) + '99PercentStretch'.center(tw_l) + '\n')
    for dirFile in resultFiles:
        match = re.match('(\S+)/(\S+)', dirFile)
        transport = match.group(1)
        filename = resultDir + '/' + dirFile

        sp = ScalarParser(filename)
        parsedStats = AttrDict()
        parsedStats.hosts = sp.hosts
        parsedStats.tors = sp.tors
        parsedStats.aggrs = sp.aggrs
        parsedStats.cores = sp.cores
        parsedStats.generalInfo = sp.generalInfo

        xmlConfigFile =  os.environ['HOME'] + '/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/config.xml'
        xmlParsedDic = AttrDict()
        xmlParsedDic = parseXmlFile(xmlConfigFile,parsedStats.generalInfo)
        msgBytesOnWireDigest = AttrDict()
        msgBytesOnWire(parsedStats.hosts, parsedStats.generalInfo, xmlParsedDic, msgBytesOnWireDigest)
        e2eStretchAndDelayDigest = AttrDict()
        e2eStretchAndDelayDigest = AttrDict()
        e2eStretchAndDelay(parsedStats, xmlParsedDic, msgBytesOnWireDigest, e2eStretchAndDelayDigest)
        loadFactor = float(parsedStats.generalInfo.rlf) * len(xmlParsedDic.senderIds) / len(xmlParsedDic.receiverIds)
        workLoad = parsedStats.generalInfo.workloadType
        avgStretch = 0.0
        try:
            UnschedBytes = int(parsedStats.generalInfo.defaultReqBytes) + int(parsedStats.generalInfo.defaultUnschedBytes)
        except Exception as e:
            print('No Unsched bytes in file: %s' % (filename))
            UnschedBytes = 'NA'
        for elem in e2eStretchAndDelayDigest.stretch:
            sizeUpBound = elem.sizeUpBound
            sizeProbability = elem.cntPercent
            bytesPercent = elem.bytesPercent
            meanStretch = float(elem.mean)
            medianStretch = float(elem.median)
            tailStretch = float(elem.ninety9Percentile)
            avgStretch += meanStretch * float(elem.cntPercent) / 100
            f.write('{0}'.format(transport).center(tw_l) + '{0}'.format(loadFactor).center(tw_l) +
                '{0}'.format(workLoad).center(tw_h) + '{0}'.format(sizeUpBound).center(tw_l) +
                '{0:.5f}'.format(sizeProbability).center(tw_l) + '{0:.5f}'.format(bytesPercent).center(tw_l) +
                '{0}'.format(UnschedBytes).center(tw_l) + '{0}'.format(meanStretch).center(tw_l) +
                '{0}'.format('NA').center(tw_l) + '{0}'.format('NA').center(tw_l) + '\n')
            f.write('{0}'.format(transport).center(tw_l) + '{0}'.format(loadFactor).center(tw_l) +
                '{0}'.format(workLoad).center(tw_h) + '{0}'.format(sizeUpBound).center(tw_l) +
                '{0:.5f}'.format(sizeProbability).center(tw_l) + '{0:.5f}'.format(bytesPercent).center(tw_l) +
                '{0}'.format(UnschedBytes).center(tw_l) + '{0}'.format('NA').center(tw_l) +
                '{0}'.format(medianStretch).center(tw_l) + '{0}'.format('NA').center(tw_l) + '\n')
            f.write('{0}'.format(transport).center(tw_l) + '{0}'.format(loadFactor).center(tw_l) +
                '{0}'.format(workLoad).center(tw_h) + '{0}'.format(sizeUpBound).center(tw_l) +
                '{0:.5f}'.format(sizeProbability).center(tw_l) + '{0:.5f}'.format(bytesPercent).center(tw_l) +
                '{0}'.format(UnschedBytes).center(tw_l) + '{0}'.format('NA').center(tw_l) +
                '{0}'.format('NA').center(tw_l) + '{0}'.format(tailStretch).center(tw_l) + '\n')
        #f.write('{0}'.format(transport).center(tw_l) + '{0}'.format(loadFactor).center(tw_l) +
        #        '{0}'.format(workLoad).center(tw_h) + '{0}'.format('OverAllSizes').center(tw_l) +
        #        '{0}'.format(1.00).center(tw_l) + '{0}'.format(100).center(tw_l) +
        #        '{0}'.format(UnschedBytes).center(tw_l) + '{0}'.format(avgStretch).center(tw_l)  +
        #        '{0}'.format('NA').center(tw_l) + '{0}'.format('NA').center(tw_l) + '\n')
    f.close()

def prepQueueDigest(resultDir, outputFileName, resultFiles=[]):
    f = open(os.environ['HOME'] +
        "/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/analysis/PlotScripts/" +
        outputFileName, 'w')
    tw_h = 40
    tw_l = 15
    f.write('TransportType'.center(tw_l) + 'LoadFactor'.center(tw_l) +
        'WorkLoad'.center(tw_h) + 'UnschedBytes'.center(tw_l) +
        'PrioLevels'.center(tw_l) + 'SchedPrios'.center(tw_l) +
        'RedundancyFactor'.center(tw_l) + 'QueueLocation'.center(tw_l) +
        'Metric'.center(tw_l) + 'QueueLen'.center(tw_l) + '\n')
    for dirFile in resultFiles:
        match = re.match('(\S+)/(\S+)', dirFile)
        transport = match.group(1)
        filename = resultDir + '/' + dirFile
        print(filename)

        sp = ScalarParser(filename)
        parsedStats = AttrDict()
        parsedStats.hosts = sp.hosts
        parsedStats.tors = sp.tors
        parsedStats.aggrs = sp.aggrs
        parsedStats.cores = sp.cores
        parsedStats.generalInfo = sp.generalInfo

        xmlConfigFile =  os.environ['HOME'] + '/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/config.xml'
        xmlParsedDic = AttrDict()
        xmlParsedDic = parseXmlFile(xmlConfigFile,parsedStats.generalInfo)
        loadFactor = float(parsedStats.generalInfo.rlf) * len(xmlParsedDic.senderIds) / len(xmlParsedDic.receiverIds)
        workLoad = parsedStats.generalInfo.workloadType
        schedPrios = int(eval(parsedStats.generalInfo.adaptiveSchedPrioLevels))
        prioLevels = int(eval(parsedStats.generalInfo.prioLevels))
        redundancyFac = int(eval(parsedStats.generalInfo.numSendersToKeepGranted))
        queueLen = computeQueueLength(parsedStats, xmlParsedDic)
        try:
            unschedBytes = int(parsedStats.generalInfo.defaultReqBytes) + int(parsedStats.generalInfo.defaultUnschedBytes)
        except Exception as e:
            print('No Unsched bytes in file: %s' % (filename))
            unschedBytes = 'NA'

        keys = ['meanCnt', 'meanBytes', 'minCnt', 'minBytes', 'maxCnt', 'maxBytes', 'empty', 'onePkt']
        for key in keys:
            queueStats = queueLen.tors.down.nic.queueLenDigest
            f.write('{0}'.format(transport).center(tw_l) + '{0}'.format(loadFactor).center(tw_l) +
                '{0}'.format(workLoad).center(tw_h) + '{0}'.format(unschedBytes).center(tw_l) +
                '{0}'.format(prioLevels).center(tw_l) + '{0}'.format(schedPrios).center(tw_l) +
                '{0}'.format(redundancyFac).center(tw_l) + '{0}'.format('TorDown').center(tw_l) +
                '{0}'.format(key).center(tw_l) + '{0}'.format(queueStats.access(key)).center(tw_l) + '\n')

            queueStats = queueLen.tors.up.nic.queueLenDigest
            f.write('{0}'.format(transport).center(tw_l) + '{0}'.format(loadFactor).center(tw_l) +
                '{0}'.format(workLoad).center(tw_h) + '{0}'.format(unschedBytes).center(tw_l) +
                '{0}'.format(prioLevels).center(tw_l) + '{0}'.format(schedPrios).center(tw_l) +
                '{0}'.format(redundancyFac).center(tw_l) + '{0}'.format('TorUp').center(tw_l) +
                '{0}'.format(key).center(tw_l) + '{0}'.format(queueStats.access(key)).center(tw_l) + '\n')

            queueStats = queueLen.aggrs.nic.queueLenDigest
            f.write('{0}'.format(transport).center(tw_l) + '{0}'.format(loadFactor).center(tw_l) +
                '{0}'.format(workLoad).center(tw_h) + '{0}'.format(unschedBytes).center(tw_l) +
                '{0}'.format(prioLevels).center(tw_l) + '{0}'.format(schedPrios).center(tw_l) +
                '{0}'.format(redundancyFac).center(tw_l) + '{0}'.format('Aggr').center(tw_l) +
                '{0}'.format(key).center(tw_l) + '{0}'.format(queueStats.access(key)).center(tw_l) + '\n')

    f.close()

def prepE2EStretchVsPrioCutoff(resultDir, outputFileName, resultFiles=[]):
    f = open(os.environ['HOME'] +
        "/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/analysis/PlotScripts/" +
        outputFileName, 'w')
    tw_h = 40
    tw_l = 15
    f.write('TransportType'.center(tw_l) + 'LoadFactor'.center(tw_l) +
        'PrioLevels'.center(tw_l) + 'SchedPrios'.center(tw_l) +
        'WorkLoad'.center(tw_h) + 'MsgSizeRange'.center(tw_l) +
        'SizeCntPercent'.center(tw_l) + 'BytesPercent'.center(tw_l) +
        'UnschedBytes'.center(tw_l) + 'MeanStretch'.center(tw_l) +
        'MedianStretch'.center(tw_l) + '99PercentStretch'.center(tw_l) + '\n')
    for dirFile in resultFiles:
        #match = re.match('(\S+)/(\S+)', dirFile)
        #transport = match.group(1)
        transport = "Homa"
        filename = resultDir + '/' + dirFile

        sp = ScalarParser(filename)
        parsedStats = AttrDict()
        parsedStats.hosts = sp.hosts
        parsedStats.tors = sp.tors
        parsedStats.aggrs = sp.aggrs
        parsedStats.cores = sp.cores
        parsedStats.generalInfo = sp.generalInfo

        xmlConfigFile =  os.environ['HOME'] + '/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/config.xml'
        xmlParsedDic = AttrDict()
        xmlParsedDic = parseXmlFile(xmlConfigFile,parsedStats.generalInfo)
        msgBytesOnWireDigest = AttrDict()
        msgBytesOnWire(parsedStats.hosts, parsedStats.generalInfo, xmlParsedDic, msgBytesOnWireDigest)
        e2eStretchAndDelayDigest = AttrDict()
        e2eStretchAndDelayDigest = AttrDict()
        e2eStretchAndDelay(parsedStats, xmlParsedDic, msgBytesOnWireDigest, e2eStretchAndDelayDigest)
        loadFactor = float(parsedStats.generalInfo.rlf) * len(xmlParsedDic.senderIds) / len(xmlParsedDic.receiverIds)
        schedPrios = int(eval(parsedStats.generalInfo.adaptiveSchedPrioLevels))
        prioLevels = int(eval(parsedStats.generalInfo.prioLevels))
        workLoad = parsedStats.generalInfo.workloadType
        avgStretch = 0.0
        try:
            UnschedBytes = int(parsedStats.generalInfo.defaultReqBytes) + int(parsedStats.generalInfo.defaultUnschedBytes)
        except Exception as e:
            print('No Unsched bytes in file: %s' % (filename))
            UnschedBytes = 'NA'
        for elem in e2eStretchAndDelayDigest.stretch:
            sizeUpBound = elem.sizeUpBound
            sizeProbability = elem.cntPercent
            bytesPercent = elem.bytesPercent
            meanStretch = float(elem.mean)
            medianStretch = float(elem.median)
            tailStretch = float(elem.ninety9Percentile)
            avgStretch += meanStretch * float(elem.cntPercent) / 100
            f.write('{0}'.format(transport).center(tw_l) + '{0}'.format(loadFactor).center(tw_l) +
                '{0}'.format(prioLevels).center(tw_l) + '{0}'.format(schedPrios).center(tw_l) +
                '{0}'.format(workLoad).center(tw_h) + '{0}'.format(sizeUpBound).center(tw_l) +
                '{0:.5f}'.format(sizeProbability).center(tw_l) + '{0:.5f}'.format(bytesPercent).center(tw_l) +
                '{0}'.format(UnschedBytes).center(tw_l) + '{0}'.format(meanStretch).center(tw_l) +
                '{0}'.format('NA').center(tw_l) + '{0}'.format('NA').center(tw_l) + '\n')

            f.write('{0}'.format(transport).center(tw_l) + '{0}'.format(loadFactor).center(tw_l) +
                '{0}'.format(prioLevels).center(tw_l) + '{0}'.format(schedPrios).center(tw_l) +
                '{0}'.format(workLoad).center(tw_h) + '{0}'.format(sizeUpBound).center(tw_l) +
                '{0:.5f}'.format(sizeProbability).center(tw_l) + '{0:.5f}'.format(bytesPercent).center(tw_l) +
                '{0}'.format(UnschedBytes).center(tw_l) + '{0}'.format('NA').center(tw_l) +
                '{0}'.format(medianStretch).center(tw_l) + '{0}'.format('NA').center(tw_l) + '\n')

            f.write('{0}'.format(transport).center(tw_l) + '{0}'.format(loadFactor).center(tw_l) +
                '{0}'.format(prioLevels).center(tw_l) + '{0}'.format(schedPrios).center(tw_l) +
                '{0}'.format(workLoad).center(tw_h) + '{0}'.format(sizeUpBound).center(tw_l) +
                '{0:.5f}'.format(sizeProbability).center(tw_l) + '{0:.5f}'.format(bytesPercent).center(tw_l) +
                '{0}'.format(UnschedBytes).center(tw_l) + '{0}'.format('NA').center(tw_l) +
                '{0}'.format('NA').center(tw_l) + '{0}'.format(tailStretch).center(tw_l) + '\n')

    f.close()

def prepE2EStretchVsUnschedPrioMode(resultDir, outputFileName, resultFiles=[]):
    f = open(os.environ['HOME'] +
        "/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/analysis/PlotScripts/" +
         outputFileName, 'w')
    tw_h = 40
    tw_l = 15
    f.write('TransportType'.center(tw_l) + 'LoadFactor'.center(tw_l) +
        'UnschedPrioCutoff'.center(tw_l) + 'ExponentIncFactor'.center(tw_l) +
        'ExplicitUnschedPrioCutoff'.center(tw_h) +
        'WorkLoad'.center(tw_h) + 'MsgSizeRange'.center(tw_l) +
        'SizeCntPercent'.center(tw_l) + 'BytesPercent'.center(tw_l) +
        'UnschedBytes'.center(tw_l) + 'MeanStretch'.center(tw_l) +
        'MedianStretch'.center(tw_l) + '99PercentStretch'.center(tw_l) + '\n')
    for dirFile in resultFiles:
        #match = re.match('(\S+)/(\S+)', dirFile)
        #transport = match.group(1)
        transport = 'Homa'
        filename = resultDir + '/' + dirFile

        sp = ScalarParser(filename)
        parsedStats = AttrDict()
        parsedStats.hosts = sp.hosts
        parsedStats.tors = sp.tors
        parsedStats.aggrs = sp.aggrs
        parsedStats.cores = sp.cores
        parsedStats.generalInfo = sp.generalInfo

        xmlConfigFile =  os.environ['HOME'] + '/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/config.xml'
        xmlParsedDic = AttrDict()
        xmlParsedDic = parseXmlFile(xmlConfigFile,parsedStats.generalInfo)
        msgBytesOnWireDigest = AttrDict()
        msgBytesOnWire(parsedStats.hosts, parsedStats.generalInfo, xmlParsedDic, msgBytesOnWireDigest)
        e2eStretchAndDelayDigest = AttrDict()
        e2eStretchAndDelayDigest = AttrDict()
        e2eStretchAndDelay(parsedStats, xmlParsedDic, msgBytesOnWireDigest, e2eStretchAndDelayDigest)
        loadFactor = float(parsedStats.generalInfo.rlf) * len(xmlParsedDic.senderIds) / len(xmlParsedDic.receiverIds)
        unschedPrioCutoffMode = parsedStats.generalInfo.unschedPrioResolutionMode
        exponentIncFac = parsedStats.generalInfo.unschedPrioUsageWeight
        workLoad = parsedStats.generalInfo.workloadType
        explicitUnschedPrioCutoff = ','.join(map(str, parsedStats.generalInfo.explicitUnschedPrioCutoff.split()))
        if explicitUnschedPrioCutoff == '':
            explicitUnschedPrioCutoff = '_'
        avgStretch = 0.0
        try:
            UnschedBytes = int(parsedStats.generalInfo.defaultReqBytes) + int(parsedStats.generalInfo.defaultUnschedBytes)
        except Exception as e:
            print('No Unsched bytes in file: %s' % (filename))
            UnschedBytes = 'NA'
        for elem in e2eStretchAndDelayDigest.stretch:
            sizeUpBound = elem.sizeUpBound
            sizeProbability = elem.cntPercent
            bytesPercent = elem.bytesPercent
            meanStretch = float(elem.mean)
            medianStretch = float(elem.median)
            tailStretch = float(elem.ninety9Percentile)
            avgStretch += meanStretch * float(elem.cntPercent) / 100
            f.write('{0}'.format(transport).center(tw_l) + '{0}'.format(loadFactor).center(tw_l) +
                '{0}'.format(unschedPrioCutoffMode).center(tw_l) + '{0}'.format(exponentIncFac).center(tw_l) +
                '{0}'.format(explicitUnschedPrioCutoff).center(tw_h) +
                '{0}'.format(workLoad).center(tw_h) + '{0}'.format(sizeUpBound).center(tw_l) +
                '{0:.5f}'.format(sizeProbability).center(tw_l) + '{0:.5f}'.format(bytesPercent).center(tw_l) +
                '{0}'.format(UnschedBytes).center(tw_l) + '{0}'.format(meanStretch).center(tw_l) +
                '{0}'.format('NA').center(tw_l) + '{0}'.format('NA').center(tw_l) + '\n')
            f.write('{0}'.format(transport).center(tw_l) + '{0}'.format(loadFactor).center(tw_l) +
                '{0}'.format(unschedPrioCutoffMode).center(tw_l) + '{0}'.format(exponentIncFac).center(tw_l) +
                '{0}'.format(explicitUnschedPrioCutoff).center(tw_h) +
                '{0}'.format(workLoad).center(tw_h) + '{0}'.format(sizeUpBound).center(tw_l) +
                '{0:.5f}'.format(sizeProbability).center(tw_l) + '{0:.5f}'.format(bytesPercent).center(tw_l) +
                '{0}'.format(UnschedBytes).center(tw_l) + '{0}'.format('NA').center(tw_l) +
                '{0}'.format(medianStretch).center(tw_l) + '{0}'.format('NA').center(tw_l) + '\n')
            f.write('{0}'.format(transport).center(tw_l) + '{0}'.format(loadFactor).center(tw_l) +
                '{0}'.format(unschedPrioCutoffMode).center(tw_l) + '{0}'.format(exponentIncFac).center(tw_l) +
                '{0}'.format(explicitUnschedPrioCutoff).center(tw_h) +
                '{0}'.format(workLoad).center(tw_h) + '{0}'.format(sizeUpBound).center(tw_l) +
                '{0:.5f}'.format(sizeProbability).center(tw_l) + '{0:.5f}'.format(bytesPercent).center(tw_l) +
                '{0}'.format(UnschedBytes).center(tw_l) + '{0}'.format('NA').center(tw_l) +
                '{0}'.format('NA').center(tw_l) + '{0}'.format(tailStretch).center(tw_l) + '\n')

    f.close()

if __name__ == '__main__':
    parser = OptionParser(description='This scripts is inteded for parsing the simulation'
            ' result files, preparing the input files for plotting, and calling plotting'
            ' scripts.')
    parser.add_option('--resultDir', metavar='DIR',
            default = os.environ['HOME'] + '/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/results',
            dest='resultDir',
            help='Directory containing result files')

    parser.add_option('--plotType', metavar='TYPE_OF_PLOT', default = '',
            dest='plotType',
            help='Mandatory argument. Types are: StretchVsUnsched')
    parser.add_option('--outputFile', metavar='FILENAME',
        default = 'stretchVsTransport.txt', dest='outputFileName',
        help='Name of the output file')
    options, args = parser.parse_args()
    resultDir = options.resultDir
    plotType = options.plotType
    outputFileName = options.outputFileName
    if plotType == '':
        print("--plotType argument not provided.")
        sys.exit(prepE2EStretchVsSizeAndUnsched(resultDir))
    elif plotType == 'StretchVsUnsched':
        prepE2EStretchVsSizeAndUnsched(resultDir)
        plotPath = os.environ['HOME'] + "/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/analysis/PlotScripts/"
        print subprocess.Popen('cd {0}; Rscript PlotStretchVsUnsched.r'.format(plotPath),
            shell=True, stdout=subprocess.PIPE).stdout.read()
    elif plotType == 'StretchVsSize':
        prepE2EStretchVsSizeAndUnsched(resultDir)
        plotPath = os.environ['HOME'] + "/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/analysis/PlotScripts/"
        print subprocess.Popen('cd {0}; Rscript PlotStretchVsSize.r'.format(plotPath),
            shell=True, stdout=subprocess.PIPE).stdout.read()
    elif plotType == 'StretchVsTransport':
        f = open(resultDir + '/fileList.txt')
        resultFiles = [line.rstrip('\n') for line in f]
        f.close()
        """
        resultFiles=["1pktReq3PrioMidPrioForLessThanRTT/WorkloadKeyValue-46.sca",
            "1pktReq3PrioMidPrioForLessThanRTT/WorkloadFabricatedHeavyHead-46.sca",
            "1pktReq3PrioMidPrioForLessThanRTT/WorkloadFabricatedHeavyMiddle-46.sca",
            "3PrioDividedForBytes/WorkloadKeyValue-46.sca",
            "3PrioDividedForBytes/WorkloadFabricatedHeavyHead-46.sca",
            "3PrioDividedForBytes/WorkloadFabricatedHeavyMiddle-46.sca",
            "450BytesReq3PrioMidPrioForLessThanRTT/WorkloadKeyValue-46.sca",
            "450BytesReq3PrioMidPrioForLessThanRTT/WorkloadFabricatedHeavyHead-46.sca",
            "450BytesReq3PrioMidPrioForLessThanRTT/WorkloadFabricatedHeavyMiddle-46.sca",
            "pseudoIdeal_RawData/WorkloadKeyValue-2.sca",
            "pseudoIdeal_RawData/WorkloadFabricatedHeavyHead-2.sca",
            "pseudoIdeal_RawData/WorkloadFabricatedHeavyMiddle-2.sca"]
        """
        prepE2EStretchVsTransport(resultDir, outputFileName, resultFiles)
        plotPath = os.environ['HOME'] + "/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/analysis/PlotScripts/"
        print subprocess.Popen('cd {0}; Rscript PlotStretchVsTransport.r'.format(plotPath),
            shell=True, stdout=subprocess.PIPE).stdout.read()
    elif plotType == 'StretchVsUnschedPrioMode':
        f = open(resultDir + '/fileList.txt')
        resultFiles = [line.rstrip('\n') for line in f]
        f.close()
        prepE2EStretchVsUnschedPrioMode(resultDir, outputFileName, resultFiles)
        #plotPath = os.environ['HOME'] + "/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/analysis/PlotScripts/"
        #print subprocess.Popen('cd {0}; Rscript PlotStretchVsTransport.r'.format(plotPath),
        #    shell=True, stdout=subprocess.PIPE).stdout.read()

    elif plotType == 'StretchVsPrioCutoff':
        f = open(resultDir + '/fileList.txt')
        resultFiles = [line.rstrip('\n') for line in f]
        f.close()
        prepE2EStretchVsPrioCutoff(resultDir, outputFileName, resultFiles)
        #plotPath = os.environ['HOME'] + "/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/analysis/PlotScripts/"
        #print subprocess.Popen('cd {0}; Rscript PlotStretchVsTransport.r'.format(plotPath),
        #    shell=True, stdout=subprocess.PIPE).stdout.read()

    elif plotType == 'QueueLength':
        f = open(resultDir + '/fileList.txt')
        resultFiles = [line.rstrip('\n') for line in f]
        f.close()
        prepQueueDigest(resultDir, outputFileName, resultFiles)
        #plotPath = os.environ['HOME'] + "/HomaSimulation/RpcTransportDesign/OMNeT++Simulation/analysis/PlotScripts/"
        #print subprocess.Popen('cd {0}; Rscript PlotStretchVsTransport.r'.format(plotPath),
        #    shell=True, stdout=subprocess.PIPE).stdout.read()
