BUILD_DIR :=./build
GENERATOR :='Ninja Multi-Config'

configure:
	cmake --fresh -B ${BUILD_DIR} -G ${GENERATOR}

RELEASE ?= n
ifeq (RELEASE, y)
	CONFIG=Release
else
	CONFIG=Debug
endif

build: 
	$(info Build Config = ${CONFIG})
	cmake --build ${BUILD_DIR} --config ${CONFIG}

%:
	cmake --build ${BUILD_DIR} -t $@

.PHONY: build
