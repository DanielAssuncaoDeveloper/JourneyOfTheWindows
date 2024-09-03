cmake_minimum_required(VERSION 3.29)
project(JourneyOfTheWindows C)

set(CMAKE_C_STANDARD 11)

add_executable(JourneyOfTheWindows main.c
        src/lab/display/map/mapService.c
        src/lab/display/map/mapService.h
        src/lab/gameplay/gameplayService.c
        src/lab/gameplay/gameplayService.h
        src/lab/display/structs/Entity.h
        src/lab/display/position/positionService.c
        src/lab/display/position/positionService.h
        src/lab/display/stage/stageService.c
        src/lab/display/stage/stageService.h
        src/lab/display/entity/entityService.c
        src/lab/display/entity/entityService.h
)
