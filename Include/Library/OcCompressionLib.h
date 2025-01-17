/** @file
  Copyright (C) 2019, vit9696. All rights reserved.

  All rights reserved.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
**/

#ifndef OC_COMPRESSION_LIB_H
#define OC_COMPRESSION_LIB_H

/**
  Maximumum compression and decompression buffer size may vary from
  0 to OC_COMPRESSION_MAX_LENGTH inclusive.
**/
#define OC_COMPRESSION_MAX_LENGTH BASE_1GB

/**
  Compress buffer with LZSS algorithm.

  @param[out]  Dst         Destination buffer.
  @param[in]   DstLen      Destination buffer size.
  @param[in]   Src         Source buffer.
  @param[in]   SrcLen      Source buffer size.

  @return  Dst + CompressedLen on success otherwise NULL.
**/
UINT8 *
CompressLZSS (
  OUT UINT8   *Dst,
  IN  UINT32  DstLen,
  IN  UINT8   *Src,
  IN  UINT32  SrcLen
  );

/**
  Decompress buffer with LZSS algorithm.

  @param[out]  Dst         Destination buffer.
  @param[in]   DstLen      Destination buffer size.
  @param[in]   Src         Source buffer.
  @param[in]   SrcLen      Source buffer size.

  @return  DecompressedLen on success otherwise 0.
**/
UINT32
DecompressLZSS (
  OUT UINT8   *Dst,
  IN  UINT32  DstLen,
  IN  UINT8   *Src,
  IN  UINT32  SrcLen
  );

/**
  Decompress buffer with LZVN algorithm.

  @param[out]  Dst         Destination buffer.
  @param[in]   DstLen      Destination buffer size.
  @param[in]   Src         Source buffer.
  @param[in]   SrcLen      Source buffer size.

  @return  DecompressedLen on success otherwise 0.
**/
UINTN
DecompressLZVN (
  OUT UINT8        *Dst,
  IN  UINTN        DstLen,
  IN  CONST UINT8  *Src,
  IN  UINTN        SrcLen
  );

#endif // OC_COMPRESSION_LIB_H
