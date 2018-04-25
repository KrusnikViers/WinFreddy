# Sets strict compilation flags for target.
macro (set_target_strict_compilation_params TARGET_NAME)
  if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # -Wall: Enable all warnings.
    # -Wextra: Enable extra warnings.
    # -Werror: Treat warnings as errors.
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Werror )
  elseif(MSVC)
    # -W4: Enable all warnings.
    # -WX: Treat warnings as errors.
    target_compile_options(${TARGET_NAME} PRIVATE -W4 -WX)
    # Disable warnings about Microsoft-specific alternative functions.
    target_compile_definitions(${TARGET_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
  else()
    message(WARNING
            "Unknown compiler! Strict compilation not set for ${TARGET_NAME}.")
  endif()
endmacro()

# Creates C resources file from files in given directory
macro (make_embedded_resources resources_directory output_filename)
  file(WRITE ${output_filename}.cpp
       "#include \"${output_filename}.h\"\n"
       "// This file is generated automatically. Do not edit!\n"
       "// Content is taken from ${resources_directory}\n\n")
  file(WRITE ${output_filename}.h
       "#pragma once\n"
       "// This file is generated automatically. Do not edit!\n"
       "// Content is taken from ${resources_directory}\n\n")
  file(GLOB resource_files ${resources_directory}/*)
  foreach(resource_file ${resource_files})
    # Read and convert filename to C identifier.
    string(REGEX MATCH "([^/]+)$" filename ${resource_file})
    string(REGEX REPLACE "\\.| |-" "_" filename ${filename})
    # Read and convert file data to C compatible format.
    file(READ ${resource_file} hex_data HEX)
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," hex_data ${hex_data})
    # Append data to output file.
    file(APPEND ${output_filename}.cpp
         "unsigned char ${filename}[] = {${hex_data}0x00};\n"
         "unsigned ${filename}_size = sizeof(${filename});\n")
    file(APPEND ${output_filename}.h
         "extern unsigned char ${filename}[];\n"
         "extern unsigned ${filename}_size;\n\n")
  endforeach()
endmacro()
