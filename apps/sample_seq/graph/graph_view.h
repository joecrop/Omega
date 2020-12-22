#ifndef SAMPLE_GRAPH_VIEW_H
#define SAMPLE_GRAPH_VIEW_H

#include "../../shared/function_graph_view.h"
#include "../sequence_store.h"

namespace Sample
{

  class GraphView : public Shared::FunctionGraphView
  {
  public:
    GraphView(SampleStore *sequenceStore, Shared::InteractiveCurveViewRange *graphRange,
              Shared::CurveViewCursor *cursor, Shared::BannerView *bannerView, Shared::CursorView *cursorView);
    void drawRect(KDContext *ctx, KDRect rect) const override;

  private:
    SampleStore *m_sequenceStore;
  };

} // namespace Sample

#endif
