add_definitions(-DPSSERVER -D_GNU_SOURCE -D_POSIX_C_SOURCE)

add_executable(
	atexit
        options.c
        messenger.c
        log.c
        sigutil.c
        trace.c
	main.c
)

install(TARGETS
            atexit 
	RUNTIME DESTINATION ${RUNTIME_DIR}
)





