/*ckwg +29
 * Copyright 2016-2018 by Kitware, Inc.
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

#ifndef TELESCULPTOR_COLORIZESURFACEOPTIONS_H_
#define TELESCULPTOR_COLORIZESURFACEOPTIONS_H_

#include <vital/config/config_block_types.h>
#include <vital/types/camera_map.h>

#include <qtGlobal.h>

#include <QWidget>

class vtkActor;

class ColorizeSurfaceOptionsPrivate;
class MeshColoration;

class ColorizeSurfaceOptions : public QWidget
{
  Q_OBJECT

public:
  explicit ColorizeSurfaceOptions(QString const& settingsGroup,
                                  QWidget* parent = nullptr,
                                  Qt::WindowFlags flags = {});
  ~ColorizeSurfaceOptions() override;

  void addColorDisplay(std::string name);

  void initFrameSampling(int nbFrames);
  int getFrameSampling() const;

  void setCurrentFrame(kwiver::vital::frame_id_t frame);
  void setOcclusionThreshold(double occlusionThreshold)
  {
    this->OcclusionThreshold = occlusionThreshold;
  }
  void setRemoveOccluded(double removeOccluded)
  {
    this->RemoveOccluded = removeOccluded;
  }
  void setRemoveMasked(double removeMasked)
  {
    this->RemoveMasked = removeMasked;
  }
  double getOcclusionThreshold()
  {
    return this->OcclusionThreshold;
  }

  void setActor(vtkActor* actor);
  void setVideoConfig(std::string const& path,
                      kwiver::vital::config_block_sptr config);
  kwiver::vital::config_block_sptr getVideoConfig() const;
  std::string getVideoPath() const;

  void setMaskConfig(std::string const& path,
                     kwiver::vital::config_block_sptr config);
  kwiver::vital::config_block_sptr getMaskConfig() const;
  std::string getMaskPath() const;

  void setCamera(kwiver::vital::frame_id_t id,
                 kwiver::vital::camera_sptr const& camera);
  kwiver::vital::camera_map_sptr getCameras() const;
  void enableMenu(bool);
  void forceColorize();

signals:
  void colorModeChanged(QString);

public slots:
  void changeColorDisplay();
  void colorize();
  void meshColorationHandleResult(MeshColoration* coloration);
  void enableAllFramesParameters(bool);
  void allFrameSelected();
  void currentFrameSelected();
  void updateOcclusionThreshold();
  void removeOccludedChanged(int removeOccluded);
  void removeMaskedChanged(int removeMasked);


protected:
  double OcclusionThreshold;
  bool RemoveOccluded;
  bool RemoveMasked;
  bool InsideColorize;
  const int INVALID_FRAME = -2;
  kwiver::vital::frame_id_t LastColorizedFrame;

private:

  QTE_DECLARE_PRIVATE_RPTR(ColorizeSurfaceOptions)
  QTE_DECLARE_PRIVATE(ColorizeSurfaceOptions)

  QTE_DISABLE_COPY(ColorizeSurfaceOptions)
};

#endif // COLORIZESURFACEOPTIONS_H
