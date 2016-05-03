#include <netdb.h>
#include <stdio.h>
#include <string.h>

int
getservbyport_r(int port, const char *proto, struct servent *se,
    struct servent_data *sd)
{
	int error;

	setservent_r(sd->stayopen, sd);
	while ((error = getservent_r(se, sd)) == 0) {
		if (se->s_port != port)
			continue;
		if (proto == 0 || strcmp(se->s_proto, proto) == 0)
			break;
	}
	if (!sd->stayopen && sd->fp != NULL) {
		fclose(sd->fp);
		sd->fp = NULL;
	}
	return (error);
}

struct servent *
getservbyport(int port, const char *proto)
{
	extern struct servent_data _servent_data;
	static struct servent serv;

	if (getservbyport_r(port, proto, &serv, &_servent_data) != 0)
		return (NULL);
	return (&serv);
}