#ifndef FLYEMMVCDIALOGMANAGER_H
#define FLYEMMVCDIALOGMANAGER_H

class ZFlyEmProofMvc;
class NeuprintSetupDialog;
class ZContrastProtocalDialog;
class ZFlyEmRoiToolDialog;
class ZFlyEmSplitUploadOptionDialog;
class ZFlyEmBodyChopDialog;
class ZInfoDialog;
class ZFlyEmGrayscaleDialog;
class FlyEmBodyIdDialog;
class ZFlyEmMergeUploadDialog;
class ZFlyEmProofSettingDialog;
class ZFlyEmSkeletonUpdateDialog;
class FlyEmTodoDialog;
class ZDvidTargetProviderDialog;
class FlyEmBodyInfoDialog;
class ZFlyEmSplitCommitDialog;
class ZFlyEmBodyAnnotationDialog;
class NeuPrintQueryDialog;

/*!
 * \brief The class for managing dialogs used by ZFlyEmProofMvc.
 *
 * This class is not expected to be used by other classes except ZFlyEmProofMvc
 * and its derivatives.
 */
class FlyEmMvcDialogManager
{
public:
  FlyEmMvcDialogManager(ZFlyEmProofMvc *parent);

  ZDvidTargetProviderDialog* getDvidDlg();
  FlyEmBodyInfoDialog* getBodyInfoDlg();
  FlyEmBodyInfoDialog* getBodyQueryDlg();
  FlyEmBodyInfoDialog* getNeuprintBodyDlg();
  ZFlyEmSplitCommitDialog* getSplitCommitDlg();
  FlyEmTodoDialog* getTodoDlg();
  ZFlyEmRoiToolDialog* getRoiDlg();
  ZFlyEmSplitUploadOptionDialog* getSplitUploadDlg();
  ZFlyEmBodyChopDialog* getBodyChopDlg();
  ZInfoDialog* getInfoDlg();
  ZFlyEmSkeletonUpdateDialog* getSkeletonUpdateDlg();
  ZFlyEmGrayscaleDialog* getGrayscaleDlg();
  FlyEmBodyIdDialog* getBodyIdDialog();
  ZFlyEmMergeUploadDialog* getMergeUploadDlg();
  ZFlyEmProofSettingDialog* getSettingDlg();
  ZFlyEmBodyAnnotationDialog* getAnnotationDlg();
  NeuPrintQueryDialog* getNeuprintQueryDlg();
  NeuprintSetupDialog* getNeuprintSetupDlg();
  ZContrastProtocalDialog* getContrastDlg();

  void setDvidDlg(ZDvidTargetProviderDialog *dlg);
  bool isDvidDlgReady() const;
  bool isRoiDlgReady() const;
  bool isBodyInfoDlgReady() const;
  bool isSplitUploadDlgReady() const;

private:
  inline bool isNull(void *dlg) const {
    return (dlg == nullptr);
  }

  template <typename T>
  bool createIfNecessary(T* &dlg);
//  bool creationRequired(void *dlg) const;

private:
  template<typename T>
  FlyEmBodyInfoDialog* makeBodyInfoDlg(const T &flag);

private:
  ZFlyEmProofMvc *m_parent = nullptr;

  ZDvidTargetProviderDialog *m_dvidDlg = nullptr;
  FlyEmBodyInfoDialog *m_bodyInfoDlg = nullptr;
  FlyEmBodyInfoDialog *m_bodyQueryDlg = nullptr;
  FlyEmBodyInfoDialog *m_neuprintBodyDlg = nullptr;
  ZFlyEmSplitCommitDialog *m_splitCommitDlg = nullptr;
  FlyEmTodoDialog *m_todoDlg = nullptr;
  ZFlyEmRoiToolDialog *m_roiDlg = nullptr;
  ZFlyEmSplitUploadOptionDialog *m_splitUploadDlg = nullptr;
  ZFlyEmBodyChopDialog *m_bodyChopDlg = nullptr;
  ZInfoDialog *m_infoDlg = nullptr;
  ZFlyEmSkeletonUpdateDialog *m_skeletonUpdateDlg = nullptr;
  ZFlyEmGrayscaleDialog *m_grayscaleDlg = nullptr;
  FlyEmBodyIdDialog *m_bodyIdDialog = nullptr;
  ZFlyEmMergeUploadDialog *m_mergeUploadDlg = nullptr;
  ZFlyEmProofSettingDialog *m_settingDlg = nullptr;
  ZFlyEmBodyAnnotationDialog *m_annotationDlg = nullptr;
  NeuPrintQueryDialog *m_neuprintQueryDlg = nullptr;
  NeuprintSetupDialog *m_neuprintSetupDlg = nullptr;
  ZContrastProtocalDialog *m_contrastDlg = nullptr;

};

#endif // FLYEMMVCDIALOGGROUP_H
