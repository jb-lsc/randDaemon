/*
 * signalHandler.h
 *
 *  Created on: 28 Apr 2014
 *      Author: jb
 */
#ifndef SYSLOG_H_
#include <sys/syslog.h>
#endif

#ifndef SIGNAL_H_
#include <signal.h>
#endif

#ifndef BOOL_H_
#include "bool.h"
#endif

#ifndef SIGNALHANDLER_H_
#define SIGNALHANDLER_H_

extern d_terminated;


void signalHandler(int sig)
{
	switch(sig)
	{
	case SIGHUP:
		syslog(LOG_WARNING, "Received SIGHUP signal.", DAE_NAME);
		break;
	case SIGTERM:
		syslog(LOG_WARNING, "Received SIGHUP signal.", DAE_NAME);
		break;
	default:
		syslog(LOG_WARNING, "Unhandled Signal.", DAE_NAME);
		break;
	}

}


#endif /* SIGNALHANDLER_H_ */
