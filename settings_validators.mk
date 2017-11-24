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