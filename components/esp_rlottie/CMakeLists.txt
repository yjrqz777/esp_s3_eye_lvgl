cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-value")

idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/rlottie/inc"
                    )

# Set CMP0077 policy 必须
if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()
# 可通过环境变量强制覆盖子模块的配置
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)


set(LOTTIE_MODULE OFF)
set(LOTTIE_THREAD OFF)
set(BUILD_SHARED_LIBS OFF)
option(BUILD_TESTING OFF)


function(install)
endfunction()

function(export)
endfunction()

add_subdirectory(rlottie)
target_link_libraries(${COMPONENT_LIB} INTERFACE rlottie)

project(esp_rlottie)

if(ESP_PLATFORM)
    message(STATUS "Configuring for ESP platform")
    # Add your ESP-specific configuration here
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DESP_PLATFORM")
endif()