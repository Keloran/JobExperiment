find_path(NordicEngine_Path
    NAMES
        NordicEngine/Engine.hpp
    PATHS
        ../
        ../NordicEngine
)

find_library(NordicEngine_Library 
    NAMES
        NordicEngine
    PATHS 
        ../
        ../NordicEngine
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(NordicEngine DEFAULT_MSG NordicEngine_Library NordicEngine_Path)

mark_as_advanced(NordicEngine_Path NordicEngine_Library)
