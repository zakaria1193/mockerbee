BUILD_DIR :=./build
GENERATOR :='Ninja Multi-Config'

configure:
	cmake --fresh -B ${BUILD_DIR} -G ${GENERATOR}

RELEASE ?= n
ifeq (${RELEASE},y)
CONFIG=Release
else
CONFIG=Debug
endif

DRY_RUN ?= n
ifeq (${DRY_RUN},y)
DRY_RUN_FLAG=-- -n
$(info Dry run)
else
DRY_RUN_FLAG=
endif

VERBOSE ?= n
ifeq (${VERBOSE},y)
VERBOSE_FLAG=--verbose
$(info Verbose)
else
VERBOSE_FLAG=
endif

$(info verbose = ${VERBOSE})

build_$(CONFIG):
	$(info Build Config = ${CONFIG})
	cmake --build ${BUILD_DIR} --config ${CONFIG} ${VERBOSE_FLAG} ${DRY_RUN_FLAG}

build: build_$(CONFIG)

%:
	cmake --build ${BUILD_DIR} -t $@ ${VERBOSE_FLAG} ${DRY_RUN_FLAG}

run: build_$(CONFIG)
	${BUILD_DIR}/$(CONFIG)/mockbee_test_bin

.PHONY: build build_$(CONFIG) configure run
