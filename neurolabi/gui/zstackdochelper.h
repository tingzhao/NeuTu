#ifndef ZSTACKDOCHELPER_H
#define ZSTACKDOCHELPER_H

#include"zintpoint.h"
#include "neutube_def.h"

class ZStackDoc;
class ZIntCuboid;
class ZStack;
class ZFlyEmProofDoc;
class QColor;

/*!
 * \brief The helper class for providing miscellaneous information of a ZStackDoc object
 *
 * Example:
 *
 * ZStacDocHelper helper;
 * ...
 * helper.extractCurrentZ(doc);
 * if (helper.hasCurrentZ()) {
 *   std::cout << "Current Z position: " << helper.getCurrentZ() << std::endl
 * } else {
 *   std::cout << "No information about the current Z position." << std::endl
 * }
 *
 */
class ZStackDocHelper
{
public:
  ZStackDocHelper();
  ~ZStackDocHelper();

  void extractCurrentZ(const ZStackDoc *doc);

  int getCurrentZ() const;
  bool hasCurrentZ() const;

  ZStack *getSparseStack(const ZStackDoc *doc);
  ZIntPoint getSparseStackDsIntv() const {
    return m_sparseStackDsIntv;
  }

  static ZIntCuboid getVolumeBoundBox(const ZStackDoc *doc);
  static QColor GetBodyColor(const ZFlyEmProofDoc *doc, uint64_t bodyId);
  static bool HasMultipleBodySelected(
      const ZFlyEmProofDoc *doc, neutube::EBodyLabelType type);
  static int CountSelectedBody(
      const ZFlyEmProofDoc *doc, neutube::EBodyLabelType type);
  static bool HasBodySelected(const ZFlyEmProofDoc *doc);
  static void ClearBodySelection(ZFlyEmProofDoc *doc);

private:
  int m_currentZ;
  bool m_hasCurrentZ;
  ZStack *m_sparseStack;
  ZIntPoint m_sparseStackDsIntv;
};

#endif // ZSTACKDOCHELPER_H
