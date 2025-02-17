#ifndef ZFLYEMBODYANNOTATIONTEST_H
#define ZFLYEMBODYANNOTATIONTEST_H

#include "ztestheader.h"
#include "flyem/zflyembodyannotation.h"
#include "zjsonobject.h"
#include "flyem/zflyembodyannotationmerger.h"
#include "neutubeconfig.h"

#ifdef _USE_GTEST_

TEST(ZFlyEmBodyAnnotation, Basic)
{
  ZFlyEmBodyAnnotation annot;
  ASSERT_EQ(uint64_t(0), annot.getBodyId());

  ZJsonObject json;
  json.setEntry("status", "Hard to trace");
  json.setEntry("comment", "test");
  json.setEntry("body ID", 123);
  json.setEntry("name", "KC");
  json.setEntry("class", "neuron");
  json.setEntry("user", "zhaot");
  json.setEntry("naming user", "mock");

  annot.loadJsonObject(json);

  ASSERT_EQ(uint64_t(123), annot.getBodyId());
  ASSERT_EQ("Hard to trace", annot.getStatus());
  ASSERT_EQ("test", annot.getComment());
  ASSERT_EQ("KC", annot.getName());
  ASSERT_EQ("neuron", annot.getType());
  ASSERT_EQ("zhaot", annot.getUser());
  ASSERT_EQ("mock", annot.getNamingUser());

  annot.clear();
  ASSERT_EQ(uint64_t(0), annot.getBodyId());
  ASSERT_EQ("", annot.getStatus());
  ASSERT_EQ("", annot.getComment());
  ASSERT_EQ("", annot.getName());
  ASSERT_EQ("", annot.getType());
  ASSERT_EQ("", annot.getUser());
  ASSERT_EQ("", annot.getNamingUser());
}

TEST(ZFlyEmBodyAnnotation, merge)
{
  ZFlyEmBodyAnnotation annotation1;
  ZFlyEmBodyAnnotation annotation2;

  annotation1.setStatus("Orphan");
  annotation2.setStatus("");

  annotation1.mergeAnnotation(annotation2, &ZFlyEmBodyAnnotation::GetStatusRank);
  ASSERT_EQ("Orphan", annotation1.getStatus());

  annotation1.setStatus("Orphan");

  annotation2.setStatus("Orphan hotknife");
  annotation1.mergeAnnotation(annotation2, &ZFlyEmBodyAnnotation::GetStatusRank);
  ASSERT_EQ("Orphan hotknife", annotation1.getStatus());

  annotation2.setStatus("Leaves");
  annotation1.mergeAnnotation(annotation2, &ZFlyEmBodyAnnotation::GetStatusRank);
  ASSERT_EQ("Leaves", annotation1.getStatus());

  annotation2.setStatus("Hard to trace");
  annotation1.mergeAnnotation(annotation2, &ZFlyEmBodyAnnotation::GetStatusRank);
  ASSERT_EQ("Hard to trace", annotation1.getStatus());

  annotation1.setStatus("Not examined");
  annotation1.mergeAnnotation(annotation2, &ZFlyEmBodyAnnotation::GetStatusRank);
  ASSERT_EQ("Hard to trace", annotation1.getStatus());

  annotation2.setStatus("Partially traced");
  annotation1.mergeAnnotation(annotation2, &ZFlyEmBodyAnnotation::GetStatusRank);
  ASSERT_EQ("Partially traced", annotation1.getStatus());

  annotation2.setStatus("Prelim Roughly traced");
  annotation1.mergeAnnotation(annotation2, &ZFlyEmBodyAnnotation::GetStatusRank);
  ASSERT_EQ("Prelim Roughly traced", annotation1.getStatus());

  annotation2.setStatus("Roughly traced");
  annotation1.mergeAnnotation(annotation2, &ZFlyEmBodyAnnotation::GetStatusRank);
  ASSERT_EQ("Roughly traced", annotation1.getStatus());

  annotation2.setStatus("Anchor");
  annotation1.mergeAnnotation(annotation2, &ZFlyEmBodyAnnotation::GetStatusRank);
  ASSERT_EQ("Roughly traced", annotation1.getStatus());

  annotation2.setStatus("Traced in ROI");
  annotation1.mergeAnnotation(annotation2, &ZFlyEmBodyAnnotation::GetStatusRank);
  ASSERT_EQ("Traced in ROI", annotation1.getStatus());

  annotation2.setStatus("traced");
  annotation1.mergeAnnotation(annotation2, &ZFlyEmBodyAnnotation::GetStatusRank);
  ASSERT_EQ("traced", annotation1.getStatus());

  annotation2.setStatus("Finalized");
  annotation1.mergeAnnotation(annotation2, &ZFlyEmBodyAnnotation::GetStatusRank);
  ASSERT_EQ("Finalized", annotation1.getStatus());
}

TEST(ZFlyEmBodyAnnotation, Merger)
{
  ZFlyEmBodyAnnotationMerger annotMerger;
  ZJsonObject jsonObj;
  jsonObj.load(GET_BENCHMARK_DIR + "/body_status.json");
  annotMerger.loadJsonObject(jsonObj);

  QMap<uint64_t, ZFlyEmBodyAnnotation> annotMap;

  {
    ZFlyEmBodyAnnotation annot;
    annot.setStatus("anchor");
    annotMap[1] = annot;
  }

  {
    ZFlyEmBodyAnnotation annot;
    annot.setStatus("Anchor");
    annotMap[2] = annot;
  }

  {
    ZFlyEmBodyAnnotation annot;
    annot.setStatus("Finalized");
    annotMap[3] = annot;
  }

  {
    ZFlyEmBodyAnnotation annot;
    annot.setStatus("Roughly traced");
    annotMap[4] = annot;
  }

  std::vector<std::vector<uint64_t>> bodySet =
      annotMerger.getConflictBody(annotMap);
  ASSERT_EQ(1, int(bodySet.size()));

  std::vector<uint64_t> bodyArray = bodySet[0];
  ASSERT_EQ(3, int(bodyArray.size()));

  ASSERT_EQ(1, int(bodyArray[0]));
  ASSERT_EQ(2, int(bodyArray[1]));
  ASSERT_EQ(4, int(bodyArray[2]));

  ASSERT_EQ(9999, annotMerger.getStatusRank(""));
  ASSERT_EQ(999, annotMerger.getStatusRank("test"));
  ASSERT_EQ(0, annotMerger.getStatusRank("Finalized"));
  ASSERT_EQ(10, annotMerger.getStatusRank("Traced"));
  ASSERT_EQ(20, annotMerger.getStatusRank("Traced in roi"));
  ASSERT_EQ(30, annotMerger.getStatusRank("roughly Traced"));
  ASSERT_EQ(40, annotMerger.getStatusRank("Prelim Roughly traced"));
  ASSERT_EQ(120, annotMerger.getStatusRank("ORPHAN"));

  ASSERT_TRUE(annotMerger.isFinal("Finalized"));
  ASSERT_FALSE(annotMerger.isFinal("Hard to trace"));

}

#endif

#endif // ZFLYEMBODYANNOTATIONTEST_H
