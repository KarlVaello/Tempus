#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#

unexport MAKEFILE_LIST
MK_NOGENDEPS := $(filter clean,$(MAKECMDGOALS))
override PKGDIR = configPkg
XDCINCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(XPKGPATH))))
XDCCFGDIR = package/cfg/

#
# The following dependencies ensure package.mak is rebuilt
# in the event that some included BOM script changes.
#
ifneq (clean,$(MAKECMDGOALS))
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/utils.js:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/utils.js
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/xdc.tci:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/xdc.tci
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/template.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/template.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/om2.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/om2.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/xmlgen.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/xmlgen.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/xmlgen2.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/xmlgen2.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/Warnings.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/Warnings.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/IPackage.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/IPackage.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/package.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/package.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/services/global/Clock.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/services/global/Clock.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/services/global/Trace.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/services/global/Trace.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/bld.js:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/bld.js
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/BuildEnvironment.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/BuildEnvironment.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/PackageContents.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/PackageContents.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/_gen.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/_gen.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/Library.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/Library.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/Executable.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/Executable.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/Repository.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/Repository.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/Configuration.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/Configuration.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/Script.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/Script.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/Manifest.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/Manifest.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/Utils.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/Utils.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/ITarget.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/ITarget.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/ITarget2.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/ITarget2.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/ITarget3.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/ITarget3.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/ITargetFilter.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/ITargetFilter.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/package.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/bld/package.xs
package.mak: config.bld
/Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/targets/ITarget.xs:
package.mak: /Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/targets/ITarget.xs
/Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/targets/C28_large.xs:
package.mak: /Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/targets/C28_large.xs
/Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/targets/C28_float.xs:
package.mak: /Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/targets/C28_float.xs
/Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/targets/package.xs:
package.mak: /Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/targets/package.xs
/Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/targets/arm/elf/IArm.xs:
package.mak: /Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/targets/arm/elf/IArm.xs
/Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/targets/arm/elf/package.xs:
package.mak: /Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/targets/arm/elf/package.xs
package.mak: package.bld
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/tools/configuro/template/compiler.opt.xdt:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/tools/configuro/template/compiler.opt.xdt
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/services/io/File.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/services/io/File.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/services/io/package.xs:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/services/io/package.xs
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/tools/configuro/template/compiler.defs.xdt:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/tools/configuro/template/compiler.defs.xdt
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/tools/configuro/template/custom.mak.exe.xdt:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/tools/configuro/template/custom.mak.exe.xdt
/Applications/ti/xdctools_3_32_01_22_core/packages/xdc/tools/configuro/template/package.xs.xdt:
package.mak: /Applications/ti/xdctools_3_32_01_22_core/packages/xdc/tools/configuro/template/package.xs.xdt
endif

ti.targets.arm.elf.M3.rootDir ?= /Applications/ti/ccsv6/tools/compiler/arm_15.12.3.LTS
ti.targets.arm.elf.packageBase ?= /Users/carlosvaellomartinez/ti/tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/targets/arm/elf/
.PRECIOUS: $(XDCCFGDIR)/%.oem3
.PHONY: all,em3 .dlls,em3 .executables,em3 test,em3
all,em3: .executables,em3
.executables,em3: .libraries,em3
.executables,em3: .dlls,em3
.dlls,em3: .libraries,em3
.libraries,em3: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,em3
	@$(ECHO) xdc .executables,em3
	@$(ECHO) xdc .libraries,em3
	@$(ECHO) xdc .dlls,em3


all: .executables 
.executables: .libraries .dlls
.libraries: .interfaces

PKGCFGS := $(wildcard package.xs) package/build.cfg
.interfaces: package/package.xdc.inc package/package.defs.h package.xdc $(PKGCFGS)

-include package/package.xdc.dep
package/%.xdc.inc package/%_configPkg.c package/%.defs.h: %.xdc $(PKGCFGS)
	@$(MSG) generating interfaces for package configPkg" (because $@ is older than $(firstword $?))" ...
	$(XSRUN) -f xdc/services/intern/cmd/build.xs $(MK_IDLOPTS) -m package/package.xdc.dep -i package/package.xdc.inc package.xdc

.dlls,em3 .dlls: Tempus.pem3

-include package/cfg/Tempus_pem3.mak
-include package/cfg/Tempus_pem3.cfg.mak
ifeq (,$(MK_NOGENDEPS))
-include package/cfg/Tempus_pem3.dep
endif
Tempus.pem3: package/cfg/Tempus_pem3.xdl
	@


ifeq (,$(wildcard .libraries,em3))
Tempus.pem3 package/cfg/Tempus_pem3.c: .libraries,em3
endif

package/cfg/Tempus_pem3.c package/cfg/Tempus_pem3.h package/cfg/Tempus_pem3.xdl: override _PROG_NAME := Tempus.xem3
package/cfg/Tempus_pem3.c: package/cfg/Tempus_pem3.cfg
package/cfg/Tempus_pem3.xdc.inc: package/cfg/Tempus_pem3.xdl
package/cfg/Tempus_pem3.xdl package/cfg/Tempus_pem3.c: .interfaces

clean:: clean,em3
	-$(RM) package/cfg/Tempus_pem3.cfg
	-$(RM) package/cfg/Tempus_pem3.dep
	-$(RM) package/cfg/Tempus_pem3.c
	-$(RM) package/cfg/Tempus_pem3.xdc.inc

clean,em3::
	-$(RM) Tempus.pem3
.executables,em3 .executables: Tempus.xem3

Tempus.xem3: |Tempus.pem3

-include package/cfg/Tempus.xem3.mak
Tempus.xem3: package/cfg/Tempus_pem3.oem3 
	$(RM) $@
	@$(MSG) lnkem3 $@ ...
	$(RM) $(XDCCFGDIR)/$@.map
	$(ti.targets.arm.elf.M3.rootDir)/bin/armcl -fs $(XDCCFGDIR)$(dir $@) -q -u _c_int00 --silicon_version=7M3 -z --strict_compatibility=on  -o $@ package/cfg/Tempus_pem3.oem3   package/cfg/Tempus_pem3.xdl  -w -c -m $(XDCCFGDIR)/$@.map -l $(ti.targets.arm.elf.M3.rootDir)/lib/libc.a
	
Tempus.xem3: export C_DIR=
Tempus.xem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/:$(PATH)

Tempus.test test,em3 test: Tempus.xem3.test

Tempus.xem3.test:: Tempus.xem3
ifeq (,$(_TESTLEVEL))
	@$(MAKE) -R -r --no-print-directory -f $(XDCROOT)/packages/xdc/bld/xdc.mak _TESTLEVEL=1 Tempus.xem3.test
else
	@$(MSG) running $<  ...
	$(call EXEC.Tempus.xem3, ) 
endif

clean,em3::
	-$(RM) $(wildcard .tmp,Tempus.xem3,*)


clean:: clean,em3

clean,em3::
	-$(RM) Tempus.xem3
%,copy:
	@$(if $<,,$(MSG) don\'t know how to build $*; exit 1)
	@$(MSG) cp $< $@
	$(RM) $@
	$(CP) $< $@
Tempus_pem3.oem3,copy : package/cfg/Tempus_pem3.oem3
Tempus_pem3.sem3,copy : package/cfg/Tempus_pem3.sem3

$(XDCCFGDIR)%.c $(XDCCFGDIR)%.h $(XDCCFGDIR)%.xdl: $(XDCCFGDIR)%.cfg $(XDCROOT)/packages/xdc/cfg/Main.xs | .interfaces
	@$(MSG) "configuring $(_PROG_NAME) from $< ..."
	$(CONFIG) $(_PROG_XSOPTS) xdc.cfg $(_PROG_NAME) $(XDCCFGDIR)$*.cfg $(XDCCFGDIR)$*

.PHONY: release,configPkg
ifeq (,$(MK_NOGENDEPS))
-include package/rel/configPkg.tar.dep
endif
package/rel/configPkg/configPkg/package/package.rel.xml: package/package.bld.xml
package/rel/configPkg/configPkg/package/package.rel.xml: package/build.cfg
package/rel/configPkg/configPkg/package/package.rel.xml: package/package.xdc.inc
package/rel/configPkg/configPkg/package/package.rel.xml: .force
	@$(MSG) generating external release references $@ ...
	$(XS) $(JSENV) -f $(XDCROOT)/packages/xdc/bld/rel.js $(MK_RELOPTS) . $@

configPkg.tar: package/rel/configPkg.xdc.inc package/rel/configPkg/configPkg/package/package.rel.xml
	@$(MSG) making release file $@ "(because of $(firstword $?))" ...
	-$(RM) $@
	$(call MKRELTAR,package/rel/configPkg.xdc.inc,package/rel/configPkg.tar.dep)


release release,configPkg: all configPkg.tar
clean:: .clean
	-$(RM) configPkg.tar
	-$(RM) package/rel/configPkg.xdc.inc
	-$(RM) package/rel/configPkg.tar.dep

clean:: .clean
	-$(RM) .libraries $(wildcard .libraries,*)
clean:: 
	-$(RM) .dlls $(wildcard .dlls,*)
#
# The following clean rule removes user specified
# generated files or directories.
#

ifneq (clean,$(MAKECMDGOALS))
ifeq (,$(wildcard package))
    $(shell $(MKDIR) package)
endif
ifeq (,$(wildcard package/cfg))
    $(shell $(MKDIR) package/cfg)
endif
ifeq (,$(wildcard package/lib))
    $(shell $(MKDIR) package/lib)
endif
ifeq (,$(wildcard package/rel))
    $(shell $(MKDIR) package/rel)
endif
ifeq (,$(wildcard package/internal))
    $(shell $(MKDIR) package/internal)
endif
endif
clean::
	-$(RMDIR) package

include custom.mak
