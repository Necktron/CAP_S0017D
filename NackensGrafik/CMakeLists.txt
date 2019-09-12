#--------------------------------------------------------------------------
# NackensGrafik project
#--------------------------------------------------------------------------

PROJECT(NackensGrafik)
FILE(GLOB nackensgrafik_headers code/*.h)
FILE(GLOB nackensgrafik_sources code/*.cc)

SET(files_nackensgrafik ${nackensgrafik_headers} ${nackensgrafik_sources})
SOURCE_GROUP("nackensgrafik" FILES ${files_nackensgrafik})

ADD_EXECUTABLE(NackensGrafik ${files_nackensgrafik})
TARGET_LINK_LIBRARIES(NackensGrafik core render)
ADD_DEPENDENCIES(NackensGrafik core render)