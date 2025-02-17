#ifndef ZFLYEMTODOITEM_H
#define ZFLYEMTODOITEM_H

#include <map>
#include "dvid/zdvidannotation.h"

class ZFlyEmToDoItem : public ZDvidAnnotation
{
public:
  /*!
   * \brief Default constructor
   *
   * The object is always set to invalid kind by default.
   */
  ZFlyEmToDoItem();

  /*!
   * \brief Constructor with initial position
   *
   * With a position given, the object is set to a valid type.
   */
  ZFlyEmToDoItem(const ZIntPoint &pos);
  ZFlyEmToDoItem(int x, int y, int z);

//  const std::string& className() const;
  void display(ZPainter &painter, int slice, EDisplayStyle option,
               neutu::EAxis sliceAxis) const;

  static ZStackObject::EType GetType() {
    return ZStackObject::EType::FLYEM_TODO_ITEM;
  }

  friend std::ostream& operator<< (
      std::ostream &stream, const ZFlyEmToDoItem &synapse);

  bool isChecked() const;
  void setChecked(bool checked);
  int getPriority() const;

  void setAction(neutu::EToDoAction action);
  neutu::EToDoAction getAction() const;

  void setAction(const std::string &action);

  QColor getDisplayColor() const;

  void removeActionTag();

  void setPriority(int p);

private:
  void syncActionTag();
  static std::string GetActionTag(neutu::EToDoAction action);

public:
  static const char *ACTION_KEY;
  static const char *ACTION_GENERAL;
  static const char *ACTION_SPLIT;
  static const char *ACTION_SUPERVOXEL_SPLIT;
  static const char *ACTION_IRRELEVANT;
  static const char *ACTION_MERGE;
  static const char *ACTION_SPLIT_TAG;
  static const char *ACTION_SUPERVOXEL_SPLIT_TAG;
  static const char *ACTION_IRRELEVANT_TAG;
  static const char *ACTION_MERGE_TAG;

  static const std::map<std::string, neutu::EToDoAction> m_actionMap;

private:
  void init();
  void init(EKind kind);
};

#endif // ZFLYEMTODOITEM_H
