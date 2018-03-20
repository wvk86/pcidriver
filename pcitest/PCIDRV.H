#if !defined(_PCIDRV_H_)
#define _PCIDRV_H_
#endif

#include <ntddk.h>
#include <wdf.h>

#define PCIDRV_POOL_TAG (ULONG) 'DICP'
#define _DRIVER_NAME_ "PCIDRV"

#define UNUSED(x) (x)

typedef struct _DRIVER_CONTEXT
{
   WDFLOOKASIDE   RecvLookaside;

} DRIVER_CONTEXT, *PDRIVER_CONTEXT;
WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DRIVER_CONTEXT, GetDriverContext)

typedef struct _FDO_DATA
{
   BUS_INTERFACE_STANDARD  BusInterface;
} FDO_DATA, *PFDO_DATA;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(FDO_DATA, FdoGetData)

//
// Function prototypes
//
DRIVER_INITIALIZE DriverEntry;

EVT_WDF_DRIVER_DEVICE_ADD PciDrvEvtDeviceAdd;
EVT_WDF_OBJECT_CONTEXT_CLEANUP PciDrvEvtDriverContextCleanup;
EVT_WDF_DEVICE_CONTEXT_CLEANUP PciDrvEvtDeviceContextCleanup;
