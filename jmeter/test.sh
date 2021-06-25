#!/bin/bash
now=$(date '+%Y_%m_%d-%H:%M')
/opt/apache-jmeter/bin/jmeter -Jjmeter.reportgenerator.overall_granularity=10000 -el JMeterRun_$now/jmeter.log -nt PerformanceTests.jmx -o JMeterRun_$now