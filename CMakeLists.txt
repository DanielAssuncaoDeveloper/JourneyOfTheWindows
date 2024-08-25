cmake_minimum_required(VERSION 3.29)
project(JourneyOfTheWindows C)

set(CMAKE_C_STANDARD 11)

add_executable(JourneyOfTheWindows main.c
        src/lab/display/mapService.c
        src/lab/display/mapService.h
        src/lab/gameplay/gameplayService.c
        src/lab/gameplay/gameplayService.h
        src/lab/display/structs/Actor.h
        src/lab/display/structs/Map.h
)
