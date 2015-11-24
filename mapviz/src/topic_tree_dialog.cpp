// *****************************************************************************
//
// Copyright (c) 2015, Southwest Research Institute® (SwRI®)
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

#include <mapviz/topic_tree_dialog.h>

#include <ros/master.h>

#include "ui_topic_select_tree.h"

namespace mapviz
{
  TopicTreeDialog::TopicTreeDialog(QWidget *parent, QStringList types) : 
    QDialog(parent),
    ui_(new Ui::topic_select_tree()),
    types_(types)
  {
    ui_->setupUi(this);
  }

  int TopicTreeDialog::exec()
  {
    std::vector<ros::master::TopicInfo> topics;
    ros::master::getTopics(topics);
    
    std::map<QString, QTreeWidgetItem*> tree_items;
    
    for (size_t i = 0; i < topics.size(); i++)
    {
      QString topic = QString(topics[i].name.c_str());
      for (size_t j = 0; j < types_.size(); j++)
      {
        if (topics[i].datatype == types_[j].toStdString())
        {
          QStringList topic_tokens = topic.split(QString("/"));
          QString topic_root("");
          for (size_t k = 0; k < topic_tokens.size(); k++)
          {
            if (topic_root == "")
            {
              topic_root += "/";
              topic_root += topic_tokens[k];
              if (tree_items.count(topic_root) == 0)
              {
                QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui_->displaylist);
                treeItem->setText(0, topic_tokens[k]);
              }
            }
            else
            {
              QTreeWidgetItem *parent = tree_items[topic_root];
              
              topic_root += "/";
              topic_root += topic_tokens[k];
              
              if (tree_items.count(topic_root) == 0)
              {
                QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui_->displaylist);
                treeItem->setText(0, topic_tokens[k]);
                parent->addChild(treeItem);
              }
            }
          }
        }
      }
    }
    
    return QDialog::exec();
  }
  
  int TopicTreeDialog::SelectedCount() const
  {
    return ui_->displaylist->selectedItems().count();
  }
  
  QString TopicTreeDialog::CurrentTopic() const
  {
    QTreeWidgetItem* current_item = ui_->displaylist->currentItem();
    
    // TODO
    
    return QString("");
  }
}

