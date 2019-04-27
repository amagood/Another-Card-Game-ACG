project(lib CXX)
include_directories(nlohmann)

add_library(nlohmann_json nlohmann/json.hpp)
set_target_properties(nlohmann_json PROPERTIES LINKER_LANGUAGE CXX)