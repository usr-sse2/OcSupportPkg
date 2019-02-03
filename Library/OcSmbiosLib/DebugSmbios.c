/** @file
  Copyright (C) 2016 - 2017, The HermitCrabs Lab. All rights reserved.

  All rights reserved.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
**/

#include <Base.h>

#include <IndustryStandard/AppleSmBios.h>

#include <Library/DebugLib.h>
#include <Library/UefiLib.h>

#include <Macros.h>

#include "DebugSmbios.h"
#include "OcSmbiosInternal.h"

// String Conversion Lookup Table

GLOBAL_REMOVE_IF_UNREFERENCED CONST CHAR8 *SlotDataWidthStrings[] = {
  "",
  "Other",
  "Unknown",
  "8Bit",
  "16Bit",
  "32Bit",
  "64Bit",
  "128Bit",
  "1X",
  "2X",
  "4X",
  "8X",
  "12X",
  "16X",
  "32X"
};

VOID
SmbiosDebugGeneric (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  DEBUG_SMBIOS ((
    DEBUG_INFO,
    "Handle 0x%02X Type %d Length 0x%02X\n",
    Record.Standard.Hdr->Handle,
    Record.Standard.Hdr->Type,
    Record.Standard.Hdr->Length
    ));
}

VOID
SmbiosDebugBiosInformation (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Vendor",
    SmbiosGetString (Record, Record.Standard.Type0->Vendor)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "BiosVersion",
    SmbiosGetString (Record, Record.Standard.Type0->BiosVersion)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "BiosReleaseDate",
    SmbiosGetString (Record, Record.Standard.Type0->BiosReleaseDate)
    ));
}

VOID
SmbiosDebugSystemInformation (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Manufacturer",
    SmbiosGetString (Record, Record.Standard.Type1->Manufacturer)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "ProductName",
    SmbiosGetString (Record, Record.Standard.Type1->ProductName)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Version",
    SmbiosGetString (Record, Record.Standard.Type1->Version)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "SerialNumber",
    SmbiosGetString (Record, Record.Standard.Type1->SerialNumber)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %g\n",
    "Uuid",
    Record.Standard.Type1->Uuid
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "SKUNumber",
    SmbiosGetString (Record, Record.Standard.Type1->SKUNumber)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Family",
    SmbiosGetString (Record, Record.Standard.Type1->Family)
    ));
}

VOID
SmbiosDebugBaseboardInformation (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Manufacturer",
    SmbiosGetString (Record, Record.Standard.Type2->Manufacturer)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "ProductName",
    SmbiosGetString (Record, Record.Standard.Type2->ProductName)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Version",
    SmbiosGetString (Record, Record.Standard.Type2->Version)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "SerialNumber",
    SmbiosGetString (Record, Record.Standard.Type2->SerialNumber)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Location",
    SmbiosGetString (Record, Record.Standard.Type2->LocationInChassis)
    ));
}

VOID
SmbiosDebugSystemEnclosure (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Manufacturer",
    SmbiosGetString (Record, Record.Standard.Type3->Manufacturer)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Version",
    SmbiosGetString (Record, Record.Standard.Type3->Version)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "SerialNumber",
    SmbiosGetString (Record, Record.Standard.Type3->SerialNumber)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "AssetTag",
    SmbiosGetString (Record, Record.Standard.Type3->AssetTag)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "SKUNumber",
    SmbiosGetString (Record, *(PTR_OFFSET(Record.Raw,
                                          MultU64x32 (
                                            Record.Standard.Type3->ContainedElementCount,
                                            Record.Standard.Type3->ContainedElementRecordLength) + 0x15,
                                          UINT8 *)))
    ));
}

VOID
SmbiosDebugProcessorInformation (
  IN  SMBIOS_TABLE_ENTRY_POINT       *Smbios,
  IN  APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Socket",
    SmbiosGetString (Record, Record.Standard.Type4->Socket)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Manufacturer",
    SmbiosGetString (Record, Record.Standard.Type4->ProcessorManufacture)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Version",
    SmbiosGetString (Record, Record.Standard.Type4->ProcessorVersion)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d MHz\n",
    "External Clock",
    Record.Standard.Type4->ExternalClock
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d MHz\n",
    "Max Speed",
    Record.Standard.Type4->MaxSpeed
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d MHz\n",
    "Current Speed",
    Record.Standard.Type4->CurrentSpeed
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a 0x%02X\n",
    "Family",
    Record.Standard.Type4->ProcessorFamily
    ));

  // Not present before 2.7 specifications
  if (((Smbios->MajorVersion == 2) && (Smbios->MinorVersion >= 7)) ||
       (Smbios->MajorVersion == 3))
  {
    DEBUG_SMBIOS ((
      DEBUG_INFO,
      " %-16a 0x%02X\n",
      "Family2",
      Record.Standard.Type4->ProcessorFamily2
    ));
  }
}

VOID
SmbiosDebugSystemPorts (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Internal",
    SmbiosGetString (Record, Record.Standard.Type8->InternalReferenceDesignator)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %X\n",
    "Type",
    Record.Standard.Type8->InternalConnectorType
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "External",
    SmbiosGetString (Record, Record.Standard.Type8->ExternalReferenceDesignator)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %X\n",
    "Type",
    Record.Standard.Type8->ExternalConnectorType
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %X\n",
    "Port Type",
    Record.Standard.Type8->PortType
    ));
}

VOID
SmbiosDebugCacheInformation (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Socket",
    SmbiosGetString (Record, Record.Standard.Type7->SocketDesignation)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d KB\n",
    "Maximum Size",
    Record.Standard.Type7->MaximumCacheSize
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d KB\n",
    "Installed Size",
    Record.Standard.Type7->InstalledSize
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d\n",
    "Associativity",
    Record.Standard.Type7->Associativity
    ));
}

VOID
SmbiosDebugSystemSlots (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Designation",
    SmbiosGetString (Record, Record.Standard.Type9->SlotDesignation)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %X\n",
    "Type",
    Record.Standard.Type9->SlotType
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "DataBus Width",
    SlotDataWidthStrings[Record.Standard.Type9->SlotDataBusWidth]
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Current Usage",
    (Record.Standard.Type9->CurrentUsage == SlotUsageAvailable ? "Free" : "InUse")
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Length",
    (Record.Standard.Type9->SlotLength == SlotLengthShort ? "Short" : "Long")
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %X\n",
    "Id",
    Record.Standard.Type9->SlotID
    ));
}

VOID
SmbiosDebugPhysicalMemoryArray (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d\n",
    "Location",
    Record.Standard.Type16->Location
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d\n",
    "Use",
    Record.Standard.Type16->Use
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d\n",
    "ErrorCorrection",
    Record.Standard.Type16->MemoryErrorCorrection
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d GB\n",
    "Maximum Capacity",
    (Record.Standard.Type16->MaximumCapacity >> 20)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d\n",
    "No Of Devices",
    Record.Standard.Type16->NumberOfMemoryDevices
    ));
}

VOID
SmbiosDebugMemoryDevice (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "DeviceLocator",
    SmbiosGetString (Record, Record.Standard.Type17->DeviceLocator)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "BankLocator",
    SmbiosGetString (Record, Record.Standard.Type17->BankLocator)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d Bits\n",
    "TotalWidth",
    Record.Standard.Type17->TotalWidth
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d Bits\n",
    "DataWidth",
    Record.Standard.Type17->DataWidth
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d MB\n",
    "Size", Record.Standard.Type17->Size
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d MHz\n",
    "Speed", Record.Standard.Type17->Speed
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Manufacturer",
    SmbiosGetString (Record, Record.Standard.Type17->Manufacturer)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "SerialNumber",
    SmbiosGetString (Record, Record.Standard.Type17->SerialNumber)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "AssetTag",
    SmbiosGetString (Record, Record.Standard.Type17->AssetTag)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "PartNumber",
    SmbiosGetString (Record, Record.Standard.Type17->PartNumber)
    ));
}

VOID
SmbiosDebugType19Device (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a 0x%08X\n",
    "Starting Address",
    Record.Standard.Type19->StartingAddress
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a 0x%08X\n",
    "Ending Address",
    Record.Standard.Type19->EndingAddress
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a 0x%04X\n",
    "Array Handle",
    Record.Standard.Type19->MemoryArrayHandle
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d\n",
    "Partition Width",
    Record.Standard.Type19->PartitionWidth
    ));
}

VOID
SmbiosDebugType20Device (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a 0x%08X\n",
    "Starting Address",
    Record.Standard.Type20->StartingAddress
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a 0x%08X\n",
    "Ending Address",
    Record.Standard.Type20->EndingAddress
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a 0x%02X\n",
    "Device Handle",
    Record.Standard.Type20->MemoryDeviceHandle
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a 0x%04X\n",
    "Array Handle",
    Record.Standard.Type20->MemoryArrayMappedAddressHandle
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d\n",
    "Row Position",
    Record.Standard.Type20->PartitionRowPosition
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d\n",
    "Data Depth",
    Record.Standard.Type20->InterleavedDataDepth
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d\n",
    "Interleave Position",
    Record.Standard.Type20->InterleavePosition
    ));
}

VOID
SmbiosDebugPortableBatteryDevice (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Location",
    SmbiosGetString (Record, Record.Standard.Type22->Location)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Manufacturer",
    SmbiosGetString (Record, Record.Standard.Type22->Manufacturer)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Serial Number",
    SmbiosGetString (Record, Record.Standard.Type22->SerialNumber)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "Device Name",
    SmbiosGetString (Record, Record.Standard.Type22->DeviceName)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "SBDS Version",
    SmbiosGetString (Record, Record.Standard.Type22->SBDSVersionNumber)
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %a\n",
    "SBDS Chemistry",
    SmbiosGetString (Record, Record.Standard.Type22->SBDSDeviceChemistry)
    ));
}

VOID
SmbiosDebugBootInformation (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a 0x%02X\n",
    "BootStatus",
    Record.Standard.Type32->BootStatus
    ));
}

VOID
SmbiosDebugAppleFirmwareVolume (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a 0x%08X\n",
    "Features",
    Record.Type128->FirmwareFeatures
    ));

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a 0x%08X\n",
    "Features Mask",
    Record.Type128->FirmwareFeaturesMask
    ));
}

VOID
SmbiosDebugAppleProcessorType (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %04X\n",
    "Cpu Type",
    Record.Type131->ProcessorType
    ));
}

VOID
SmbiosDebugAppleProcessorSpeed (
  IN APPLE_SMBIOS_STRUCTURE_POINTER  Record
  )
{
  SmbiosDebugGeneric (Record);

  DEBUG_SMBIOS ((
    DEBUG_INFO,
    " %-16a %d\n",
    "Cpu Bus Speed",
    Record.Type132->ProcessorBusSpeed
    ));
}