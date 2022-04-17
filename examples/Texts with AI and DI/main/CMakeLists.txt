# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS "main.cpp"
	System.cpp
	FtpServer.cpp
	WebService.cpp
	)
set(COMPONENT_ADD_INCLUDEDIRS ".")

register_component(SRCS COMPONENT_SRCS
                    INCLUDE_DIRS COMPONENT_ADD_INCLUDEDIRS)

#idf_component_register(SRCS COMPONENT_SRCS
#                    INCLUDE_DIRS COMPONENT_ADD_INCLUDEDIRS)