#ifndef DEPTHMAPOPTIONS_H
#define DEPTHMAPOPTIONS_H

#include <qtGlobal.h>

#include <QtGui/QWidget>

class vtkActor;

class DepthMapOptionsPrivate;

class DepthMapOptions : public QWidget
{
  Q_OBJECT

public:
  explicit DepthMapOptions(const QString &settingsGroup,
                           QWidget *parent = 0, Qt::WindowFlags flags = 0);
  virtual ~DepthMapOptions();

  void addActor(vtkActor* actor);
signals:
  void modified();

protected slots:

private:
  QTE_DECLARE_PRIVATE_RPTR(DepthMapOptions)
  QTE_DECLARE_PRIVATE(DepthMapOptions)

  QTE_DISABLE_COPY(DepthMapOptions)
};

#endif // DEPTHMAPOPTIONS_H