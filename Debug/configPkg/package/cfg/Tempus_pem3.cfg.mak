# invoke SourceDir generated makefile for Tempus.pem3
Tempus.pem3: .libraries,Tempus.pem3
.libraries,Tempus.pem3: package/cfg/Tempus_pem3.xdl
	$(MAKE) -f C:\Users\Karl\workspace_v6_2\Tempus/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\Karl\workspace_v6_2\Tempus/src/makefile.libs clean

