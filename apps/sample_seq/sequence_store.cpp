#include "sequence_store.h"
#include <ion/storage.h>
extern "C"
{
#include <assert.h>
#include <stddef.h>
}

namespace Sample
{

  constexpr const char *SampleStore::k_sequenceNames[MaxNumberOfSequences];

  const char *SampleStore::firstAvailableName(int *nameIndex)
  {
    // Choose available name
    int currentNameIndex = 0;
    while (currentNameIndex < MaxNumberOfSequences)
    {
      const char *name = k_sequenceNames[currentNameIndex];
      if (Ion::Storage::sharedStorage()->recordBaseNamedWithExtension(name, Ion::Storage::seqExtension).isNull())
      {
        if (nameIndex)
        {
          *nameIndex = currentNameIndex;
        }
        return name;
      }
      currentNameIndex++;
    }
    return nullptr;
  }

  Ion::Storage::Record::ErrorStatus SampleStore::addEmptyModel()
  {
    // Choose available name
    int nameIndex;
    const char *name = firstAvailableName(&nameIndex);
    assert(name);
    // Choose the corresponding color
    assert(nameIndex < Palette::numberOfDataColors());
    KDColor color = Palette::DataColor[nameIndex];
    Sequence::RecordDataBuffer data(color);
    // m_sequences
    return Ion::Storage::sharedStorage()->createRecordWithExtension(name, modelExtension(), &data, sizeof(data));
  }

  int SampleStore::sequenceIndexForName(char name)
  {
    for (int i = 0; i < MaxNumberOfSequences; i++)
    {
      if (k_sequenceNames[i][0] == name)
      {
        return i;
      }
    }
    assert(false);
    return 0;
  }

  Shared::ExpressionModelHandle *SampleStore::setMemoizedModelAtIndex(int cacheIndex, Ion::Storage::Record record) const
  {
    assert(cacheIndex >= 0 && cacheIndex < maxNumberOfMemoizedModels());
    int index = cacheIndex;
    if (!record.isNull())
    {
      index = SampleStore::sequenceIndexForName(record.fullName()[0]);
    }
    m_sequences[index] = Sequence(record);
    return &m_sequences[index];
  }

  Shared::ExpressionModelHandle *SampleStore::memoizedModelAtIndex(int cacheIndex) const
  {
    assert(cacheIndex >= 0 && cacheIndex < maxNumberOfMemoizedModels());
    return &m_sequences[cacheIndex];
  }

} // namespace Sample
