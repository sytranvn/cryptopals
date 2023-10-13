add_subdirectory(shared)
file(GLOB V_GLOB LIST_DIRECTORIES true "set-*")
foreach(item ${V_GLOB})
	if(IS_DIRECTORY ${item})
		add_subdirectory(${item})
	endif()
endforeach()

