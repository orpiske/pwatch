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
	
	const options_t *options = get_options_object();

	switch (level) {
	case TRACE:
		if (options && options->trace) { 
			fprintf(stderr, "[TRACE]: %s\n", ret);
		}
		break;
	case DEBUG:
		if (options && options->debug) {
			fprintf(stderr, "[DEBUG]: %s\n", ret);
		}
		break;
	case INFO:
		fprintf(stderr, "[INFO]: %s\n", ret);
		break;
	case WARNING:
		fprintf(stderr, "[WARNING]: %s\n", ret);
		break;
	case ERROR:
		fprintf(stderr, "[ERROR]: %s\n", ret);
		break;
	case FATAL:
		fprintf(stderr, "[FATAL]: %s\n", ret);
		break;
	default:
		fprintf(stderr, "[MSG]: %s\n", ret);
		break;
	}

	va_end(ap);
	free(ret);
	fflush(NULL);
}

static void show_help() {
	printf("Usage: ");
	printf("\t-p\t--pid=<pid> pid to trace\n");
	printf("\t-d\t--debug runs in debug verbose mode\n");
	printf("\t-t\t--trace runs in trace verbose mode\n");
	
	printf("\t-D\t--daemon runs in backgroup\n");
	printf("\t-c\t--command=<command> executes a command after the tracee has exited\n");
	
	printf("\t-L\t--logdir=<logdir> a directory to save the logs (mandatory for --daemon)\n");
	printf("\t-h\t--help show this help\n");
}

int main(int argc, char **argv)
{
	int c;
	int option_index = 0;

	options_t *options = options_new();

	if (!options) {
		return EXIT_FAILURE;
	}

	set_options_object(options);
	set_messenger(messenger_function);
	while (1) {

		static struct option long_options[] = {
			{ "pid", true, 0, 'p'},
			{ "debug", false, 0, 'd'},
			{ "daemon", false, 0, 'D'},
			{ "trace", false, 0, 't'},
			{ "command", true, 0, 'c'},
			{ "logdir", true, 0, 'L'},
			{ "help", false, 0, 'h'},
			{ 0, 0, 0, 0}
		};

		c = getopt_long(argc, argv, "p:dDc:L:h", long_options, &option_index);
		if (c == -1) {
			if (optind == 1) {
				fprintf(stderr, "Not enough options\n");
				show_help();
				return EXIT_FAILURE;
			}
			break;
		}

		switch (c) {
		case 'p':
			options->pid = strtol(optarg, NULL, 10);
			break;
		case 'd':
			options->debug = true;
			break;
		case 'D':
			options->daemon = true;
			break;
		case 'c':
			strncpy(options->command, optarg, sizeof(options->command) - 1);
			break;
		case 'L':
			strncpy(options->logdir, optarg, sizeof(options->logdir) - 1);
			break;
		case 't':
			options->trace = true;
			break;
		case 'h':
			show_help();
			return EXIT_SUCCESS;
		default:
			printf("Invalid or missing option\n");
			show_help();
			break;
		}
	}
	
	if (strlen(options->logdir) > 0) {
		remap_log(options->logdir, "atexit", options->pid, stderr);
	}
	
	if (options->daemon == true) {
		
		
		int child = fork();
		if (child == 0) {
			return trace_start();
		}
		else if (child < 0) {
			messenger_function(ERROR, 
				"Unable to create child process: %s", strerror(errno));

			return EXIT_FAILURE;
		}
		else {
			return EXIT_SUCCESS;
		}
	}
	
	return trace_start();
}