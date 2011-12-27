/*
 * The RedFish distributed filesystem
 *
 * Copyright 2011, Colin Patrick McCabe <cmccabe@alumni.cmu.edu>
 *
 * This is licensed under the Apache License, Version 2.0.  See file COPYING.
 */

#include "util/username.h"
#include "util/string.h"

#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int get_current_username(char *out, size_t out_len)
{
	int ret;
	char *buf = NULL;
	struct passwd pwd, *p;
	long buf_len;
	uid_t euid;

	/* It would be nice to use cuserid here, but that function does
	 * different things on different systems and has a lot of weird
	 * limitations.  Even its own man page says that it sucks. */

	/* First get UID */
	euid = geteuid();

	/* How long of a buffer should we use to read password file entries? */
	buf_len = sysconf(_SC_GETPW_R_SIZE_MAX);
	if (buf_len == -1)
		buf_len = 1048576;
	buf = malloc(buf_len);
	if (!buf) {
		ret = -ENOMEM;
		goto done;
	}
	ret = getpwuid_r(euid, &pwd, buf, buf_len, &p);
	if (ret) {
		char *user_env;
		/* Ok, that failed.  Is the USER environment variable set,
		 * though? */
		user_env = getenv("USER");
		if (!user_env) {
			ret = -ENOSYS;
			goto done;
		}
		ret = zsnprintf(out, out_len, "%s", user_env);
	}
	else {
		/* Get the username from the pwd file entry */
		ret = zsnprintf(out, out_len, "%s", pwd.pw_name);
	}
done:
	free(buf);
	return ret;
}
