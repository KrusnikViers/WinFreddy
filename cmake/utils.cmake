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
