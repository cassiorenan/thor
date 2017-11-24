
include SETTINGS

ifeq ($(PLATFORM),windows)
build/thor.exe: src/main.cpp | build
else
build/thor: src/main.cpp check_platform | build
endif
	@echo Compiling thor...
	@$(CXX) $(CXX_FLAGS) src/main.cpp -o build/thor

build:
	@mkdir build

install: check_platform check_install_path
	@echo Installing...
ifeq ($(PLATFORM),windows)
	@copy build\thor.exe $(INSTALL_PATH) > NUL
else
	@cp build/thor $(INSTALL_PATH)
endif

# SETTINGS validators
.PHONY: check_platform
ifeq ($(PLATFORM),)
check_platform:
	$(error No platform specified. Please specify a platform in SETTINGS file)
else
check_platform:
endif

.PHONY: check_install_path
ifeq ($(INSTALL_PATH),)
check_install_path:
	$(error No installation path specified. Please specify an INSTALL_PATH in SETTINGS file)
else
check_install_path:
endif