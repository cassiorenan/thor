
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
ifeq ($(PLATFORM),windows)
install: build/thor.exe check_install_path
else
install: check_platform build/thor check_install_path
endif
	@echo Installing...
ifeq ($(PLATFORM),windows)
	@copy build\thor.exe $(INSTALL_PATH) > NUL
else
	@cp build/thor $(INSTALL_PATH)
endif

include settings_validators.mk