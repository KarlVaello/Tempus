#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/packages;/Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/tidrivers_cc13xx_cc26xx_2_21_00_04/packages;/Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages;/Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/uia_2_01_00_01/packages;/Applications/ti/ccsv6/ccs_base;/Users/carlosvaellomartinez/workspace_v6_2/Tempus/.config
override XDCROOT = /Applications/ti/xdctools_3_32_01_22_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/packages;/Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/tidrivers_cc13xx_cc26xx_2_21_00_04/packages;/Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages;/Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/uia_2_01_00_01/packages;/Applications/ti/ccsv6/ccs_base;/Users/carlosvaellomartinez/workspace_v6_2/Tempus/.config;/Applications/ti/xdctools_3_32_01_22_core/packages;..
HOSTOS = MacOS
endif
