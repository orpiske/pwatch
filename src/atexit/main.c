/**
 Copyright 2015 Otavio Rodolfo Piske
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "main.h"

static void messenger_function(message_level_t level, const char *msg, ...)
{
	va_list ap;
	char *ret = NULL;

	va_start(ap, msg);
	vasprintf(&ret, msg, ap);

	switch (level) {
	case TRACE:
	{
		fprintf(stderr, "[TRACE]: %s\n", ret);
		break;
	}
	case DEBUG:
	{
		const options_t *options = get_options_object();

		if (options && options->debug) {
			fprintf(stderr, "[DEBUG]: %s\n", ret);
		}
		break;
	}
	case INFO:
	{
		fprintf(stderr, "[INFO]: %s\n", ret);
		break;
	}
	case WARNING:
	{
		fprintf(stderr, "[WARNING]: %s\n", ret);
		break;
	}
	case ERROR:
	{
		fprintf(stderr, "[ERROR]: %s\n", ret);
		break;
	}
	case FATAL:
	{
		fprintf(stderr, "[FATAL]: %s\n", ret);
		break;
	}
	default:
	{
		fprintf(stderr, "[MSG]: %s\n", ret);
		break;
	}
	}

	va_end(ap);
	free(ret);
}

int main(int argc, char **argv)
{
	int c;
	int option_index = 0;

	options_t *options = options_new();

	if (!options) {
		return EXIT_FAILURE;
	}

	pid_t pid = 0;

	set_options_object(options);
	set_messenger(messenger_function);
	while (1) {

		static struct option long_options[] = {
			{ "pid", true, 0, 'p'},
			{ "debug", false, 0, 'd'},
			{ "trace", false, 0, 't'},
			{ "command", true, 0, 'c'},
			{ "help", false, 0, 'h'},
			{ 0, 0, 0, 0}
		};

		c = getopt_long(argc, argv, "p:dc:H", long_options, &option_index);
		if (c == -1) {
			if (optind == 1) {
				fprintf(stderr, "Not enough options\n");
				return EXIT_FAILURE;
			}
			break;
		}

		switch (c) {
		case 'p':
		{
			options->pid = strtol(optarg, NULL, 10);
			break;
		}
		case 'd':
		{
			options->debug = true;
			break;
		}
		case 'c':
		{
			strncpy(options->command, optarg, sizeof(options->command) - 1);
			break;
		}
		case 't':
		{
			options->trace = true;
			break;
		}
		}
	}


	trace_start();

	return EXIT_SUCCESS;
}