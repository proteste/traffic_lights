#!/usr/bin/env python

import serial
import time
import sys
from jenkinsapi import jenkins
from pprint import pprint


JENKINS = 'http://10.7.1.221:8080/'
DEVICE  = '/dev/ttyUSB0'
BYTE    = 9600

FAILURE = '1'
PENDING = '2'
SUCCESS = '3'
SERVER_ERROR = '4'
BUILDING = '5'


QUERY_FREQUENCY = 1

print 'Connected with hardware in ' + DEVICE
ser = serial.Serial(DEVICE, BYTE)

time.sleep(2)

print 'Connected jenkins-ci in ' + JENKINS
j = jenkins.Jenkins(JENKINS)


def light(state):
    print str(state)
    ser.write(state)

def check_jenkins():
    try:
        jobs = j.get_jobs()
        for (name, job) in jobs:

            if not j[name]._data['lastBuild']:
                # If a job has never been built, skip it.
                continue
            last_build = j[name].get_last_build()
            if last_build and last_build.is_running():
                print 'BUILDING - ' + name
                light(BUILDING)
                return
            elif not j[name].get_last_build().is_good():
                print 'FAILURE - ' + name
                light(FAILURE)
                return
        print 'SUCCESS'
        light(SUCCESS)
    except:
        print 'SERVER_ERROR'
        light(SERVER_ERROR)
        print "Unable to query jenkins:", sys.exc_info()[0]


if __name__ == "__main__":

    print 'Started...'
    while(1):
        check_jenkins()
        time.sleep(QUERY_FREQUENCY)
