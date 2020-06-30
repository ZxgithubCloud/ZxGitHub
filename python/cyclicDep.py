import sys
import re
import os
import networkx as nx
import matplotlib.pyplot as plt

def getAllCmakeLists(path):
	commandOutput = os.popen("find {} -name CMakeLists.txt".format(path)).read()
	return commandOutput.split('\n')


def grepRawModuleName(cmakeLists):
	moduleNameRe = re.compile('set\(MODULE_NAME *(.*)\)[\s\S]*add_library\((.*).*ALIAS.*\).*', re.MULTILINE)
	m = moduleNameRe.match(cmakeLists)
	if m is None:
		return 'not found'

	return m.group(2).replace('${MODULE_NAME}', m.group(1)).strip()

def grepDependencies(cmakelists):
	dependenciesRe = re.compile('[\s\S]*target_link_libraries\(.*\n([\s\S]*?)\)', re.MULTILINE)
	m = dependenciesRe.match(cmakelists)
	if m is None:
		return []
	return m.group(1).replace(" ", "").split('\n')

def constructDependenceChart(path):
	cmakeLists = getAllCmakeLists(path)
	libs = []
	depChart = {}
	variablesInDep = {}

	for cmake in cmakeLists:
		try:
			with open(cmake) as fd:
				moduleName = grepRawModuleName(fd.read())
				if (moduleName == "not found"):
					continue
				libs.append(moduleName)
		except:
			None
	for cmake in cmakeLists:
		try:
			with open(cmake) as fd:
				lines = fd.read()
				moduleName = grepRawModuleName(lines)
				if (moduleName == "not found"):
					continue
				dependencies = grepDependencies(lines)
				validDependencies = filter(lambda x: x in libs, dependencies)
				depChart[moduleName] = validDependencies

				variables = filter(lambda x: "$" in x, dependencies)
				if variables:
					variablesInDep[moduleName] = variables
		except:
			None

	return depChart, variablesInDep

def getCylicDependencies(path, cycleSize):
	depChart, variablesInDep = constructDependenceChart(sys.argv[1])
	G = nx.DiGraph(depChart)
	return filter(lambda x: len(x) <= cycleSize or cycleSize == 0, list(nx.simple_cycles(G))), variablesInDep


cycles, variablesInDep = getCylicDependencies(sys.argv[1], int(sys.argv[2]))
for cycle in cycles:
	print cycle
print len(cycles)

if variablesInDep:
	print ("WARNING: there are variables in dependence list which may cause this cyclic dependence detect script failed to detect the concerned dependencies")
	print variablesInDep
