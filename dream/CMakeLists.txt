project(dream)

set(
        HEADER_FILES
        include/dream/Log.h
)

set(
        SOURCE_FILES
        src/Log.cpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include/${PROJECT_NAME})