#pragma once
#include "ICompressionMethod.h"
#include "StoreMethod.h"
#include "../compression/lzma/lzma_encoder.h"
#include "../compression/lzma/lzma_decoder.h"

#include <memory>

class LzmaMethod :
  public ICompressionMethodMayBeStored
{
  public:
    ZIP_METHOD_CLASS_PROLOGUE(
      LzmaMethod,
      lzma_encoder, lzma_decoder,
      /* CompressionMethod */ 14,
      /* VersionNeededToExtract */ 63
    );

    enum class CompressionLevel : int
    {
      L0 = 0,
      L1 = 1,
      L2 = 2,
      L3 = 3,
      L4 = 4,
      L5 = 5,
      L6 = 6,
      L7 = 7,
      L8 = 8,
      L9 = 9,

      Stored = L0,
      Fastest = L1,
      Default = L6,
      Best = L9
    };

    bool GetIsMultithreaded() const { return _props.IsMultithreaded; }
    void SetIsMultithreaded(bool isMultithreaded) { _props.IsMultithreaded = isMultithreaded; }

    CompressionLevel GetCompressionLevel() const { return static_cast<CompressionLevel>(_props.CompressionLevel); }
    void SetCompressionLevel(CompressionLevel compressionLevel) 
    {
      this->SetIsStored(compressionLevel == CompressionLevel::L0);
      _props.CompressionLevel = static_cast<int>(compressionLevel);
    }

  private:
    lzma_encoder_properties _props;
};