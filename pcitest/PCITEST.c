#include <ntddk.h>
#include <ntstatus.h>
#include <wdf.h>
#include <ntintsafe.h>
#include "PCIDRV.H"
#include "PCIIOCTL.H"

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, PciDrvEvtDeviceAdd)
#pragma alloc_text (PAGE, PciDrvEvtDriverContextCleanup)
#pragma alloc_text (PAGE, PciDrvEvtDeviceContextCleanup)
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

   WDF_OBJECT_ATTRIBUTES           l_fdoAttributes;
   NTSTATUS l_status = STATUS_SUCCESS;

   PAGED_CODE();

   WdfDeviceInitSetIoType(a_DeviceInit, WdfDeviceIoBuffered);

   //
   // Specify the context type an size for the device we are about to create.
   //
   WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&l_fdoAttributes, FDO_DATA);

   l_fdoAttributes.EvtCleanupCallback = PciDrvEvtDeviceContextCleanup;

   if (!NT_SUCCESS(l_status))
   {
      return l_status;
   }

   return STATUS_SUCCESS;
}

VOID PciDrvEvtDriverContextCleanup(
   IN WDFOBJECT Driver
)
{
   UNUSED(Driver);
}

VOID PciDrvEvtDeviceCOntextCleanup(
   WDFOBJECT Device
)
{
   UNUSED(Device);
}

VOID PciDrvEvtIoDeviceControl(
   IN WDFQUEUE   a_Queue,
   IN WDFREQUEST a_Request,
   IN size_t     a_OutputBufferLength,
   IN size_t     a_InputBufferLength,
   IN ULONG      a_IoControlCode
)
{
   UNUSED(a_InputBufferLength);
   UNUSED(a_OutputBufferLength);

   NTSTATUS  l_status = STATUS_SUCCESS;
   WDFDEVICE l_hDevice = WdfIoQueueGetDevice(a_Queue);
   PFDO_DATA l_fdoData = FdoGetData(l_hDevice);

   UNUSED(l_fdoData);

   WDF_REQUEST_PARAMETERS l_params;

   WDF_REQUEST_PARAMETERS_INIT(&l_params);

   WdfRequestGetParameters(
      a_Request,
      &l_params
   );

   switch (a_IoControlCode)
   {
      case IOCTL_PCI_READ_CONFIG:
      case IOCTL_PCI_WRITE_CONFIG:

         // Do nothing for now.
         l_status = STATUS_ABANDONED;
         break;
   }
}
