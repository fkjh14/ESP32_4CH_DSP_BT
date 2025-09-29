# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

# Check ESP-IDF version - only v4.2.0 is supported
if(DEFINED ENV{IDF_VER})
    if(NOT "$ENV{IDF_VER}" STREQUAL "v4.2.0")
        message(FATAL_ERROR
            "\n"
            "================================================================================\n"
            "ERROR: This project requires ESP-IDF v4.2.0 exactly!\n"
            "Current ESP-IDF version: $ENV{IDF_VER}\n"
            "================================================================================\n"
            "\n"
            "INSTALLATION INSTRUCTIONS:\n"
            "1. Download ESP-IDF v4.2.0 from:\n"
            "   https://github.com/espressif/esp-idf/releases/tag/v4.2\n"
            "\n"
            "2. Install using the official installer or manual installation:\n"
            "   https://docs.espressif.com/projects/esp-idf/en/v4.2/esp32/get-started/\n"
            "\n"
            "3. Set up the environment:\n"
            "   - Windows: Run install.bat then export.bat\n"
            "   - Linux/macOS: Run install.sh then source export.sh\n"
            "\n"
            "4. Verify installation:\n"
            "   idf.py --version\n"
            "\n"
            "5. Clean and rebuild your project:\n"
            "   idf.py fullclean\n"
            "   idf.py build\n"
            "\n"
            "================================================================================\n"
        )
    endif()
else()
    # If IDF_VER is not set, try to detect version from IDF_PATH
    if(DEFINED ENV{IDF_PATH})
        if(EXISTS "$ENV{IDF_PATH}/version.txt")
            file(READ "$ENV{IDF_PATH}/version.txt" IDF_VERSION_FILE)
            string(STRIP "${IDF_VERSION_FILE}" IDF_VERSION_FILE)
            if(NOT "${IDF_VERSION_FILE}" STREQUAL "v4.2.0")
                message(FATAL_ERROR
                    "\n"
                    "================================================================================\n"
                    "ERROR: This project requires ESP-IDF v4.2.0 exactly!\n"
                    "Detected ESP-IDF version: ${IDF_VERSION_FILE}\n"
                    "================================================================================\n"
                    "\n"
                    "INSTALLATION INSTRUCTIONS:\n"
                    "1. Download ESP-IDF v4.2.0 from:\n"
                    "   https://github.com/espressif/esp-idf/releases/tag/v4.2\n"
                    "\n"
                    "2. Install using the official installer or manual installation:\n"
                    "   https://docs.espressif.com/projects/esp-idf/en/v4.2/esp32/get-started/\n"
                    "\n"
                    "3. Set up the environment:\n"
                    "   - Windows: Run install.bat then export.bat\n"
                    "   - Linux/macOS: Run install.sh then source export.sh\n"
                    "\n"
                    "4. Verify installation:\n"
                    "   idf.py --version\n"
                    "\n"
                    "5. Clean and rebuild your project:\n"
                    "   idf.py fullclean\n"
                    "   idf.py build\n"
                    "\n"
                    "================================================================================\n"
                )
            endif()
        # Check if path contains "v4.2" - typical for ESP-IDF v4.2.0 installations
        elseif("$ENV{IDF_PATH}" MATCHES ".*[/\\\\]v4\\.2([/\\\\].*)?$")
            # Path contains v4.2, assume it's correct version
            message(STATUS "ESP-IDF v4.2.0 detected from installation path")
        # Check for common v4.2.0 files to verify it's the right version
        elseif(EXISTS "$ENV{IDF_PATH}/components/esp32/Kconfig" AND EXISTS "$ENV{IDF_PATH}/tools/cmake/project.cmake")
            # This is likely ESP-IDF v4.2.0 structure, allow it to proceed
            message(STATUS "ESP-IDF v4.2.0 structure detected - proceeding")
        else()
            # Cannot determine version reliably, show error
            message(FATAL_ERROR
                "\n"
                "================================================================================\n"
                "ERROR: Cannot verify ESP-IDF version!\n"
                "This project requires ESP-IDF v4.2.0 exactly.\n"
                "================================================================================\n"
                "\n"
                "Your ESP-IDF installation path: $ENV{IDF_PATH}\n"
                "\n"
                "INSTALLATION INSTRUCTIONS:\n"
                "1. Download ESP-IDF v4.2.0 from:\n"
                "   https://github.com/espressif/esp-idf/releases/tag/v4.2\n"
                "\n"
                "2. Install using the official installer or manual installation:\n"
                "   https://docs.espressif.com/projects/esp-idf/en/v4.2/esp32/get-started/\n"
                "\n"
                "3. Set up the environment:\n"
                "   - Windows: Run install.bat then export.bat\n"
                "   - Linux/macOS: Run install.sh then source export.sh\n"
                "\n"
                "4. Verify installation:\n"
                "   idf.py --version\n"
                "\n"
                "5. To bypass this check (NOT RECOMMENDED), set environment variable:\n"
                "   set IDF_VER=v4.2.0\n"
                "\n"
                "================================================================================\n"
            )
        endif()
    else()
        message(FATAL_ERROR
            "\n"
            "================================================================================\n"
            "ERROR: ESP-IDF environment not found!\n"
            "================================================================================\n"
            "\n"
            "INSTALLATION INSTRUCTIONS:\n"
            "1. Download ESP-IDF v4.2.0 from:\n"
            "   https://github.com/espressif/esp-idf/releases/tag/v4.2\n"
            "\n"
            "2. Install using the official installer or manual installation:\n"
            "   https://docs.espressif.com/projects/esp-idf/en/v4.2/esp32/get-started/\n"
            "\n"
            "3. Set up the environment:\n"
            "   - Windows: Run install.bat then export.bat\n"
            "   - Linux/macOS: Run install.sh then source export.sh\n"
            "\n"
            "4. Verify installation:\n"
            "   idf.py --version\n"
            "\n"
            "================================================================================\n"
        )
    endif()
endif()

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(a2dp_sink)
