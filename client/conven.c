/*
 * Copyright 2012 the RedFish authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "client/fishc.h"

#include <stdio.h>

/* "Convenience" functions that are the same in any client implementation. */
void redfish_disconnect_and_free(struct redfish_client *cli)
{
	redfish_disconnect(cli);
	redfish_free_client(cli);
}

int redfish_close_and_free(struct redfish_file *ofe)
{
	int ret;

	ret = redfish_close(ofe);
	redfish_free_file(ofe);
	return ret;
}
