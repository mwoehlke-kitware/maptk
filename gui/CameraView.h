/*ckwg +29
 * Copyright 2017-2018 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither the name Kitware, Inc. nor the names of any contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TELESCULPTOR_CAMERAVIEW_H_
#define TELESCULPTOR_CAMERAVIEW_H_

#include "EditMode.h"

#include <vital/vital_types.h>

#include <qtGlobal.h>

#include <QWidget>

class vtkImageData;

namespace kwiver {

namespace arrows {

namespace vtk {

class vtkKwiverCamera;

} // namespace vtk

} // namespace arrows

namespace vital {

class landmark_map;
class track;

} // namespace vital

} // namespace kwiver

class GroundControlPointsWidget;
class RulerWidget;

class CameraViewPrivate;

class CameraView : public QWidget
{
  Q_OBJECT

public:
  explicit CameraView(QWidget* parent = nullptr, Qt::WindowFlags flags = {});
  ~CameraView() override;

  void addFeatureTrack(kwiver::vital::track const&);
  GroundControlPointsWidget* groundControlPointsWidget() const;
  GroundControlPointsWidget* registrationPointsWidget() const;
  RulerWidget* rulerWidget() const;

  void enableAntiAliasing(bool enable);

signals:
  void pointPlacementEnabled(bool);
  void cameraComputationRequested();

public slots:
  void setBackgroundColor(QColor const&);

  void setImagePath(QString const&);
  void setImageData(vtkImageData* data, QSize dimensions);

  void setLandmarksData(kwiver::vital::landmark_map const&);

  void setEditMode(EditMode);

  void setActiveCamera(kwiver::arrows::vtk::vtkKwiverCamera*);
  void setActiveFrame(kwiver::vital::frame_id_t);

  void addLandmark(kwiver::vital::landmark_id_t id, double x, double y);
  void addResidual(kwiver::vital::track_id_t id,
                   double x1, double y1,
                   double x2, double y2,
                   bool inlier);

  void clearLandmarks();
  void clearResiduals();
  void clearFeatureTracks();
  void clearGroundControlPoints();

  void resetView();
  void resetViewToFullExtents();
  void render();

protected slots:
  void setImageVisible(bool);
  void setLandmarksVisible(bool);
  void setResidualsVisible(bool);
  void setOutlierResidualsVisible(bool);

  void updateFeatures();

private:
  QTE_DECLARE_PRIVATE_RPTR(CameraView)
  QTE_DECLARE_PRIVATE(CameraView)

  QTE_DISABLE_COPY(CameraView)
};

#endif
