#include <ntddk.h>
#include <wdf.h>
#include <ntintsafe.h>

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(FDO_DATA, FdoGetData)

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#endif

NTSTATUS DriverEntry(
   IN PDRIVER_OBJECT  a_DriverObject,
   IN PUNICODE_STRING a_RegistryPath
)
{
   NTSTATUS              l_status = STATUS_SUCCESS;
   WDF_DRIVER_CONFIG     l_config;
   WDF_OBJECT_ATTRIBUTES attrib;
   WDFDRIVER             l_driver;

   ExInitializeDriverRuntime(DrvRtPoolNxOptIn);

   WPP_INIT_TRACING(a_DriverObject, a_RegistryPath);

   WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&attrib, DRIVER_CONTEXT);


}