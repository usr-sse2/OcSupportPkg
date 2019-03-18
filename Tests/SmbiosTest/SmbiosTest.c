/** @file
  Test smbios support.

Copyright (c) 2018, vit9696. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>
#include <PiDxe.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/OcDevicePropertyLib.h>
#include <Library/DevicePathLib.h>
#include <Library/OcMiscLib.h>
#include <Library/OcProtocolLib.h>
#include <Library/OcAppleBootPolicyLib.h>
#include <Library/OcSmbiosLib.h>
#include <Library/OcCpuLib.h>

#include <Protocol/AppleBootPolicy.h>
#include <Protocol/DevicePathPropertyDatabase.h>


#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/SimpleTextInEx.h>
#include <Protocol/SimpleFileSystem.h>

STATIC GUID SystemUUID = {0x44454C4C, 0x4800, 0x104D, {0x80, 0x44, 0xB7, 0xC0, 0x4F, 0x5A, 0x59, 0x31}};
STATIC UINT8 BoardType = 0xA; // Motherboard (BaseBoardTypeMotherBoard)
STATIC UINT8 MemoryFormFactor = 0xD; // SODIMM, 0x9 for DIMM (MemoryFormFactorSodimm)
STATIC UINT8 ChassisType = 0xD; // All in one (MiscChassisTypeAllInOne)
STATIC OC_SMBIOS_DATA Data = {
  .BIOSVendor = NULL, // Do not change BIOS Vendor
  .BIOSVersion = "281.0.0.0.0",
  .BIOSReleaseDate = "09/17/2018",
  .SystemManufacturer = "Apple Inc.", // Do not change System Manufacturer
  .SystemProductName = "iMac13,2",
  .SystemVersion = "1.0",
  .SystemSerialNumber = "C02JB041DNCW",
  .SystemUUID = &SystemUUID,
  .SystemSKUNumber = "Mac-FC02E91DDD3FA6A4",
  .SystemFamily = "iMac",
  .BoardManufacturer = "Apple Inc.", // Do not change Board Manufacturer
  .BoardProduct = "Mac-FC02E91DDD3FA6A4",
  .BoardVersion = "iMac13,2",
  .BoardSerialNumber = "C02140302D5DMT31M",
  .BoardAssetTag = "",
  .BoardLocationInChassis = "Part Component",
  .BoardType = &BoardType,
  .MemoryFormFactor = &MemoryFormFactor,
  .ChassisType = &ChassisType,
  .ChassisManufacturer = "Apple Inc.", // Do not change Chassis Manufacturer
  .ChassisVersion = "Mac-FC02E91DDD3FA6A4",
  .ChassisSerialNumber = NULL,
  .ChassisAssetTag = "iMac-Aluminum",
  .FirmwareFeatures = 0xE00FE137,
  .FirmwareFeaturesMask = 0xFF1FFF3F,
  .ProcessorType = NULL, // Will be calculated automatically
  .PlatformFeature = 1
};

EFI_STATUS
EFIAPI
TestSmbios (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  OC_CPU_INFO  CpuInfo;
  OcCpuScanProcessor (&CpuInfo);
  CreateSmbios (&Data, OcSmbiosUpdateAuto, &CpuInfo);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  UINTN  Index;

  WaitForKeyPress (L"Press any key...");

  for (Index = 0; Index < SystemTable->NumberOfTableEntries; ++Index) {
    Print (L"Table %u is %g\n", (UINT32) Index, &SystemTable->ConfigurationTable[Index].VendorGuid);
  }

  Print (L"This is test app...\n");

  TestSmbios (ImageHandle, SystemTable);

  return EFI_SUCCESS;
}
