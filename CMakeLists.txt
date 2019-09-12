cmake_minimum_required(VERSION 3.13)
project(Five_Crowns_CPP)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(
        Five_Crowns_CPP main.cpp
        Cards.hpp
        Cards.cpp
        Deck.hpp
        Deck.cpp
        Player.hpp
        Player.cpp
        Human.hpp
        Human.cpp
        Computer.hpp
        Computer.cpp
        Game.hpp
        Game.cpp
        FiveCrowns.hpp
        FiveCrowns.cpp
        Round.cpp Round.hpp)