include(FetchContent)
FetchContent_Declare(
  lib-thread-messenger
  GIT_REPOSITORY git@github.com:vvvar/lib-thread-messenger.git
)
FetchContent_MakeAvailable(lib-thread-messenger)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		lib-thread-messenger
)
