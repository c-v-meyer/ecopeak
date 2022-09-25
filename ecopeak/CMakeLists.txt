# CMakeList.txt: CMake-Projekt für "ecopeak". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (ecopeak "main.c" "cpu.h" "cpu.c" "memory.h" "memory.c" "mmu.h" "mmu.c" "opcode.h" "opcode.c" "preprocess.h" "preprocess.c" "read_bin.h" "read_bin.c" "semaphore.h" "semaphore.c" "platform.h" "mutex.h" "mutex.c" "thread.h" "thread.c" "expect.h")

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
