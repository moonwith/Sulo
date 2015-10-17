#pragma once

#include "ISuloPlugin.h"
#include "pin.H"

#include <fstream>
#include <map>

class ASMethodInfo;

class ASMTracePlugin : public ISuloPlugin
{
public:
	ASMTracePlugin();
	~ASMTracePlugin();

	bool beforeMethodCall(ASMethodInfo* mi, string methodName, UINT32 argc, UINT32* argv);
	void afterMethodCall(UINT32 retVal);

private:

	string format(char* fmt, ...);

	typedef struct CallEntry {
		string name;
		string params;
		string retval;
		vector<CallEntry*>* children;
	} CallEntry;

	// Log call trace to this stream
	ofstream m_traceFile;

	// This flag is used to prevent the logging of uninteresting method calls before the actual Flash file runs
	bool m_traceLoggingEnabled;

	ASMethodInfo* m_mi;
	int m_callDepth;
	map<int,vector<vector<CallEntry*>*>*> levelToList;
};