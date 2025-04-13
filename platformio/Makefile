# This Makefile contain rules for typical command line task you may want to perform

# You can do "make help" to get a list of rules

PLATFORMIO := ~/.platformio/penv/bin/platformio

EMBEDDED_ENVIRONMENT := nucleo_l432kc
TEST_EMBEDDED_ENVIRONMENT := nucleo_l432kc
NATIVE_ENVIRONMENT := native

monitor:
	picocom -b 115200 -r -l /dev/ttyACM0

default: build_embedded

build_embedded:  ## (default) Compiles the code for the embedded system
	${PLATFORMIO} run --environment ${EMBEDDED_ENVIRONMENT}

build_embedded_verbose:  ## Compiles the code for the embedded system with extra output
	${PLATFORMIO} run -vv --environment ${EMBEDDED_ENVIRONMENT}

build_embedded_for_debug:  ## Compiles the code for the embedded system with debugging symbols
	${PLATFORMIO} debug --environment ${EMBEDDED_ENVIRONMENT}

build_embedded_for_debug_verbose:  ## Compiles the code for the embedded system with debugging symbols with extra output
	${PLATFORMIO} debug -vv --environment ${EMBEDDED_ENVIRONMENT}

make build_and_run:
	${PLATFORMIO} run --target upload --target monitor --environment ${EMBEDDED_ENVIRONMENT} 

flash_embedded: build_embedded  ## Builds and flashes the firmware into the embedded system
	${PLATFORMIO} run --target upload --environment ${EMBEDDED_ENVIRONMENT}

test_led:
	${PLATFORMIO} test -v --environment ${TEST_EMBEDDED_ENVIRONMENT} -f embedded/components/test_led

test_debug:
	${PLATFORMIO} test -v --environment ${TEST_EMBEDDED_ENVIRONMENT} -f embedded/components/test_debug

test_bt:
	${PLATFORMIO} test -v --environment ${TEST_EMBEDDED_ENVIRONMENT} -f embedded/components/test_bt

test_ina219:
	${PLATFORMIO} test -v --environment ${TEST_EMBEDDED_ENVIRONMENT} -f embedded/components/test_ina219

test_ppm_in:
	${PLATFORMIO} test -v --environment ${TEST_EMBEDDED_ENVIRONMENT} -f embedded/components/test_ppm_in

test_pwm:
	${PLATFORMIO} test -v --environment ${TEST_EMBEDDED_ENVIRONMENT} -f embedded/components/test_pwm

test_motor_controller_factory:
	${PLATFORMIO} test -v --environment ${TEST_EMBEDDED_ENVIRONMENT} -f embedded/factories/test_motor_controller_factory

test_stepper_controller_factory:
	${PLATFORMIO} test -v --environment ${TEST_EMBEDDED_ENVIRONMENT} -f embedded/factories/test_stepper_controller_factory

test_gpio_controller_factories:
	${PLATFORMIO} test -v --environment ${TEST_EMBEDDED_ENVIRONMENT} -f embedded/factories/test_gpio_controller_factories

test_ina219_factory:
	${PLATFORMIO} test -v --environment ${TEST_EMBEDDED_ENVIRONMENT} -f embedded/factories/test_ina219_factory

test_ppm_in_factories:
	${PLATFORMIO} test -v --environment ${TEST_EMBEDDED_ENVIRONMENT} -f embedded/factories/test_ppm_in_factories

test_native:  ## Launches tests for the native environment
	${PLATFORMIO} test --environment ${NATIVE_ENVIRONMENT}

test_native_verbose:  ## Launches tests for the native environment (verbose output)
	${PLATFORMIO} test -vvv --environment ${NATIVE_ENVIRONMENT}

cleanall_embedded:  ## Cleans embedded build
	${PLATFORMIO} run --target cleanall --environment ${EMBEDDED_ENVIRONMENT}

cleanall_embedded_tests:  ## Cleans embedded build
	${PLATFORMIO} run --target cleanall --environment ${TEST_EMBEDDED_ENVIRONMENT}

cleanall_native:  ## Cleans native build
	${PLATFORMIO} run --target cleanall --environment ${NATIVE_ENVIRONMENT}

CLANG_CALL_JUST_CHECK := clang-format-14 -style=file --dry-run -Werror {}
CLANG_CALL_DO_FORMAT := clang-format-14 -style=file -i {}
CLANG_FIND_FILE_FILTER := -iname "*.cpp" -or -iname "*.c" -or -iname "*.h"

format_check: ## Checks code format
	find src/ ${CLANG_FIND_FILE_FILTER} | xargs -P0 -I{} ${CLANG_CALL_JUST_CHECK}
	find test/ ${CLANG_FIND_FILE_FILTER} | xargs -P0 -I{} ${CLANG_CALL_JUST_CHECK}
	find lib/ ${CLANG_FIND_FILE_FILTER} | xargs -P0 -I{} ${CLANG_CALL_JUST_CHECK}

format_src: ## Formats code in src
	@echo "This can update files you are not touching in this commit. You should better format with your IDE."
	@echo "Anyway, if you want to do it, you can use the following line:"
	@echo "find src/ ${CLANG_FIND_FILE_FILTER} | xargs -P0 -I{} ${CLANG_CALL_DO_FORMAT}"

format_lib: ## Formats code in lib
	@echo "This can update files you are not touching in this commit. You should better format with your IDE."
	@echo "Anyway, if you want to do it, you can use the following line:"
	@echo "find lib/ ${CLANG_FIND_FILE_FILTER} | xargs -P0 -I{} ${CLANG_CALL_DO_FORMAT}"

lint:
	${PLATFORMIO} check --verbose --fail-on-defect high --json-output --skip-packages

find_unused_functions:
	@find $(shell pwd)/lib \( -name "*.cpp" -o -name "*.h" \) xargs cppcheck --enable=all --language=c++
	@find $(shell pwd)/src \( -name "*.cpp" -o -name "*.h" \) xargs cppcheck --enable=all --language=c++
	# @find $(shell pwd)/test \( -name "*.cpp" -o -name "*.h" \) xargs cppcheck --enable=unusedFunction

.PHONY: help
help: ## show this help.
	@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##//'
