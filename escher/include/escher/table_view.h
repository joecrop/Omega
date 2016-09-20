#ifndef ESCHER_TABLE_VIEW_H
#define ESCHER_TABLE_VIEW_H

#include <escher/scroll_view.h>

class TableViewDataSource {
public:
  virtual int numberOfCells() = 0;
  virtual void willDisplayCellForIndex(View * cell, int index);
  virtual KDCoordinate cellHeight() = 0;
  virtual View * reusableCell(int index) = 0;
  virtual int reusableCellCount() = 0;
};

class TableView : public ScrollView {
public:
  TableView(TableViewDataSource * dataSource);

  void scrollToRow(int index);
  View * cellAtIndex(int index);
protected:
#if ESCHER_VIEW_LOGGING
  const char * className() const override;
#endif
private:
  class ContentView : public View {
  public:
    ContentView(TableView * tableView, TableViewDataSource * dataSource);

    KDCoordinate height() const;
    void scrollToRow(int index) const;
    View * cellAtIndex(int index);
  protected:
#if ESCHER_VIEW_LOGGING
    const char * className() const override;
#endif
  private:
    int numberOfSubviews() const override;
    View * subviewAtIndex(int index) override;
    void layoutSubviews() override;

    int numberOfDisplayableCells() const;
    int cellScrollingOffset() const;
    bool cellAtIndexIsBeforeFullyVisibleRange(int index) const;
    bool cellAtIndexIsAfterFullyVisibleRange(int index) const;
    TableView * m_tableView;
    TableViewDataSource * m_dataSource;
  };

  void layoutSubviews() override;

  ContentView m_contentView;
};

#endif
