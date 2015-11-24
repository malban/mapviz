// *****************************************************************************
//
// Copyright (c) 2014, Southwest Research Institute® (SwRI®)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Southwest Research Institute® (SwRI®) nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// *****************************************************************************

#ifndef MAPVIZ_PLUGINS_IMAGE_PLUGIN_H_
#define MAPVIZ_PLUGINS_IMAGE_PLUGIN_H_

// C++ standard libraries
#include <string>
#include <list>

#include <mapviz/mapviz_plugin.h>

// QT libraries
#include <QGLWidget>
#include <QObject>
#include <QWidget>
#include <QColor>

// ROS libraries
#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include <sensor_msgs/Image.h>
#include <opencv/highgui.h>
#include <cv_bridge/cv_bridge.h>

#include <mapviz/map_canvas.h>

// QT autogenerated files
#include "ui_image_config.h"

namespace mapviz_plugins
{
  class ImagePlugin : public mapviz::MapvizPlugin
  {
    Q_OBJECT

  public:
    enum Anchor {
      TOP_LEFT,
      TOP_CENTER,
      TOP_RIGHT,
      CENTER_LEFT,
      CENTER,
      CENTER_RIGHT,
      BOTTOM_LEFT,
      BOTTOM_CENTER,
      BOTTOM_RIGHT};

    enum Units {PIXELS, PERCENT};

    ImagePlugin();
    virtual ~ImagePlugin();

    bool Initialize(QGLWidget* canvas);
    void Shutdown() {}

    void Draw(double x, double y, double scale);

    void Transform() {}

    void LoadConfig(const YAML::Node& node, const std::string& path);
    void SaveConfig(YAML::Emitter& emitter, const std::string& path);

    QWidget* GetConfigWidget(QWidget* parent);

  protected:
    void PrintError(const std::string& message);
    void PrintInfo(const std::string& message);
    void PrintWarning(const std::string& message);

  protected Q_SLOTS:
    void SelectTopic();
    void TopicEdited();
    void SetAnchor(QString anchor);
    void SetUnits(QString units);
    void SetOffsetX(int offset);
    void SetOffsetY(int offset);
    void SetWidth(int width);
    void SetHeight(int height);

  private:
    Ui::image_config ui_;
    QWidget* config_widget_;

    std::string topic_;
    Anchor anchor_;
    Units units_;
    int offset_x_;
    int offset_y_;
    int width_;
    int height_;

    bool has_image_;

    int last_width_;
    int last_height_;

    ros::Subscriber image_sub_;
    bool has_message_;

    sensor_msgs::Image image_;

    cv_bridge::CvImagePtr cv_image_;
    cv::Mat scaled_image_;

    void imageCallback(const sensor_msgs::ImageConstPtr image);

    void ScaleImage(int width, int height);
    void DrawIplImage(cv::Mat *image);

    std::string AnchorToString(Anchor anchor);
    std::string UnitsToString(Units units);
  };
}

#endif  // MAPVIZ_PLUGINS_IMAGE_PLUGIN_H_
