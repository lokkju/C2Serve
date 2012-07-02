
cmake_minimum_required(VERSION 2.6)

find_package( C2Serve COMPONENTS server )

if ( C2Serve_FOUND )

  include_directories(
    ${C2Serve_INCLUDE_DIRS}
  )
  
  add_executable( c2s_example_server
  	C2SExampleServerMain
  	C2SExampleRestMethodPrototypeSayHello
  )
  
  target_link_libraries( c2s_example_server
    ${C2Serve_LIBRARIES}
    ${C2S_SYSLIBS}
  )
  
  install( TARGETS 
  	c2s_example_server
  	DESTINATION bin
  )

endif ( C2Serve_FOUND )
	