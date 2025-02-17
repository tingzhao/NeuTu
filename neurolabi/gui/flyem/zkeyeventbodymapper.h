#ifndef ZKEYEVENTBODYMAPPER_H
#define ZKEYEVENTBODYMAPPER_H

#include <QMap>
#include "zobject3dscan.h"
#include "neutube.h"

class ZKeyEventBodyMapper
{
public:
  ZKeyEventBodyMapper();

public:
  ZKeyEventBodyMapper(neutu::Document::ETag tag);

//  ZStroke2d::EOperation getOperation(QKeyEvent *event);
  void setTag(neutu::Document::ETag tag);

private:
  void initKeyMap();
  void updateKeyMap();

private:
//  QMap<int, ZStroke2d::EOperation> m_plainKeyMap;
//  QMap<int, ZStroke2d::EOperation> m_controlKeyMap;
//  QMap<int, ZStroke2d::EOperation> m_altKeyMap;
//  QMap<int, ZStroke2d::EOperation> m_shiftKeyMap;

  neutu::Document::ETag m_docTag;
};

#endif // ZKEYEVENTBODYMAPPER_H
