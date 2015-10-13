add_definitions(-D_GNU_SOURCE -D_POSIX_C_SOURCE)

if (${CMAKE_SYSTEM_NAME} EQUAL "Linux") 
 add_definitions(-DLINUX_BUILD) 
endif (${CMAKE_SYSTEM_NAME} EQUAL "Linux") 

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





