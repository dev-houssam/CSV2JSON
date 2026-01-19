cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté hello
project(csv2json)

# Crée des variables avec les fichiers à compiler
set(SRCS
    main.c
    )
# Mon executable
add_executable(csv2json ${SRCS})
