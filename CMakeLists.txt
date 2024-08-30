find_library(PYTHIA_LIBRARIES NAMES Pythia8 pythia8 libpythia8 PATHS /usr/include/Pythia8 /usr/lib)

i3_project (pythia-wrapper
)

SET(LIB_${PROJECT_NAME}_SOURCEFILES
        private/pythia-wrapper/I3PythiaWrapperModule.cxx
)

SET(LIB_${PROJECT_NAME}_PYBINDINGS_SOURCEFILES
        private/pybindings/module.cxx
)

SET(LIB_${PROJECT_NAME}_PROJECTS
        serialization icetray dataclasses phys-services simclasses sim-services
)

SET(LIB_${PROJECT_NAME}_TOOLS python boost)

i3_add_library(${PROJECT_NAME}
        ${LIB_${PROJECT_NAME}_SOURCEFILES}
        USE_TOOLS ${LIB_${PROJECT_NAME}_TOOLS}
        USE_PROJECTS ${LIB_${PROJECT_NAME}_PROJECTS}
)
# else(PYTHIA_FOUND)
#         colormsg(CYAN "+-- pythia not found, skipping pythia-wrapper")