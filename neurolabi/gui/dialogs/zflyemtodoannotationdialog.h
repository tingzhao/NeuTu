#ifndef ZFLYEMTODOANNOTATIONDIALOG_H
#define ZFLYEMTODOANNOTATIONDIALOG_H

#include <QDialog>

class ZFlyEmToDoItem;

namespace Ui {
class ZFlyEmTodoAnnotationDialog;
}

class ZFlyEmTodoAnnotationDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ZFlyEmTodoAnnotationDialog(QWidget *parent = 0);
  ~ZFlyEmTodoAnnotationDialog();

  void init(const ZFlyEmToDoItem &item);
  void annotate(ZFlyEmToDoItem *item);

private:
  void initActionBox();
  int getPriority() const;

private:
  Ui::ZFlyEmTodoAnnotationDialog *ui;
};

#endif // ZFLYEMTODOANNOTATIONDIALOG_H
