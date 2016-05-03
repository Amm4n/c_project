#include <netdb.h>
#include <stdio.h>
#include <string.h>

int
getservbyname_r(const char *name, const char *proto, struct servent *se,
    struct servent_data *sd)
{
	char **cp;
	int error;

	setservent_r(sd->stayopen, sd);
	while ((error = getservent_r(se, sd)) == 0) {
		if (strcmp(name, se->s_name) == 0)
			goto gotname;
		for (cp = se->s_aliases; *cp; cp++)
			if (strcmp(name, *cp) == 0)
				goto gotname;
		continue;
gotname:
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
getservbyname(const char *name, const char *proto)
{
	extern struct servent_data _servent_data;
	static struct servent serv;

	if (getservbyname_r(name, proto, &serv, &_servent_data) != 0)
		return (NULL);
	return (&serv);
}