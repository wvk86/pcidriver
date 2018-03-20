#include <ntddk.h>
#include <ntstatus.h>
#include <wdf.h>
#include <ntintsafe.h>
#include "PCIDRV.H"

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, PciDrvEvtDeviceAdd)
#pragma alloc_text (PAGE, PciDrvEvtDriverContextCleanup)
#endif

NTSTATUS DriverEntry(
   IN PDRIVER_OBJECT  a_DriverObject,
   IN PUNICODE_STRING a_RegistryPath
)
{
   NTSTATUS              l_status = STATUS_SUCCESS;
   WDF_DRIVER_CONFIG     l_config;
   WDF_OBJECT_ATTRIBUTES l_attrib;
   WDFDRIVER             l_driver;

   ExInitializeDriverRuntime(DrvRtPoolNxOptIn);

   //WPP_INIT_TRACING(a_DriverObject, a_RegistryPath);

   WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&l_attrib, DRIVER_CONTEXT);

   l_attrib.EvtCleanupCallback = PciDrvEvtDriverContextCleanup;

   WDF_DRIVER_CONFIG_INIT(&l_config, PciDrvEvtDeviceAdd);

   //
   // Create a WDFDRIVER object.
   //
   l_status = WdfDriverCreate(a_DriverObject,
      a_RegistryPath,
      &l_attrib,
      &l_config,
      &l_driver
   );

   if (!NT_SUCCESS(l_status))
   {
      //WPP_CLEANUP(a_DriverObject);

      return l_status;
   }

   return STATUS_SUCCESS;
}

NTSTATUS PciDrvEvtDeviceAdd(
   IN WDFDRIVER a_Driver,
   IN PWDFDEVICE_INIT a_DeviceInit
)
{
   UNUSED(a_Driver);
   UNUSED(a_DeviceInit);

   return STATUS_SUCCESS;
}

VOID
PciDrvEvtDriverContextCleanup(
   IN WDFOBJECT Driver
)
{
   UNUSED(Driver);
}