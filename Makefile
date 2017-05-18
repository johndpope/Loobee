.PHONY: default
default: all

include Makefile.in.$(shell uname -s)
-include Makefile.in.$(shell whoami)

SWIFTC_COMMON_FLAGS = -j 8 -num-threads 8 -warnings-as-errors
SWIFTC_RELEASE_FLAGS += -Ounchecked -gnone -whole-module-optimization -static-stdlib $(SWIFTC_COMMON_FLAGS)
SWIFTC_SAFE_RELEASE_FLAGS += -O -gline-tables-only -whole-module-optimization -static-stdlib $(SWIFTC_COMMON_FLAGS)
SWIFTC_DEBUG_FLAGS += -Onone -g $(SWIFTC_COMMON_FLAGS)

CC_COMMON_FLAGS = -Wextra
CC_DEBUG_FLAGS += $(CC_COMMON_FLAGS)
CC_RELEASE_FLAGS += -Ofast -march=native -ffast-math -$(CC_COMMON_FLAGS)

#generatePassFlags = $(shell echo $(2) | sed -e "s/[^ ][^ ]*/-$(1) \"&\"/g")
generatePassFlags = $(patsubst %,-$(1) "%",$(2))

.PHONY: all release
all: clean build test
safe-release: clean build-safe-release test-safe-release
release: clean build-release test-release

.PHONY: build build-release
build:
	swift build $(SWIFT_FLAGS) $(call generatePassFlags,Xswiftc,$(SWIFTC_DEBUG_FLAGS)) $(call generatePassFlags,Xcc,$(CC_DEBUG_FLAGS)) $(call generatePassFlags,Xlinker,$(LINKER_DEBUG_FLAGS))
build-safe-release:
	swift build --configuration release $(SWIFT_FLAGS) $(call generatePassFlags,Xswiftc,$(SWIFTC_SAFE_RELEASE_FLAGS)) $(call generatePassFlags,Xcc,$(CC_RELEASE_FLAGS)) $(call generatePassFlags,Xlinker,$(LINKER_RELEASE_FLAGS))
build-release:
	swift build --configuration release $(SWIFT_FLAGS) $(call generatePassFlags,Xswiftc,$(SWIFTC_RELEASE_FLAGS)) $(call generatePassFlags,Xcc,$(CC_RELEASE_FLAGS)) $(call generatePassFlags,Xlinker,$(LINKER_RELEASE_FLAGS))

.PHONY: test test-release test-docker
test:
	swift test $(SWIFT_FLAGS) $(call generatePassFlags,Xswiftc,$(SWIFTC_DEBUG_FLAGS)) $(call generatePassFlags,Xcc,$(CC_DEBUG_FLAGS)) $(call generatePassFlags,Xlinker,$(LINKER_DEBUG_FLAGS))
test-safe-release:
	swift test --configuration release $(SWIFT_FLAGS) $(call generatePassFlags,Xswiftc,$(filter-out -whole-module-optimization,$(SWIFTC_SAFE_RELEASE_FLAGS)) -g -enable-testing) $(call generatePassFlags,Xcc,$(CC_RELEASE_FLAGS)) $(call generatePassFlags,Xlinker,$(LINKER_RELEASE_FLAGS))
test-release:
	swift test --configuration release $(SWIFT_FLAGS) $(call generatePassFlags,Xswiftc,$(filter-out -whole-module-optimization,$(SWIFTC_RELEASE_FLAGS)) -g -enable-testing) $(call generatePassFlags,Xcc,$(CC_RELEASE_FLAGS)) $(call generatePassFlags,Xlinker,$(LINKER_RELEASE_FLAGS))
test-docker: docker-env
	$(DOCKER_ENV) && docker-compose run test

.PHONY: clean
clean:
	swift package clean

.PHONY: xcode
xcode:
	swift package generate-xcodeproj
