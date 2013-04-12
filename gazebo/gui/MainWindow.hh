/*
 * Copyright 2012 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef _MAINWINDOW_HH_
#define _MAINWINDOW_HH_

#include <map>
#include <string>
#include <vector>
#include <list>

#include "gui/qt.h"
#include "common/Event.hh"
#include "msgs/MessageTypes.hh"
#include "transport/TransportTypes.hh"

namespace gazebo
{
  namespace gui
  {
    class RenderWidget;
    class ToolsWidget;
    class ModelListWidget;
    class Editor;

    class MainWindow : public QMainWindow
    {
      Q_OBJECT

      public: MainWindow();
      public: virtual ~MainWindow();

      public: void Load();
      public: void Init();

      public: unsigned int GetEntityId(const std::string &_name);
      public: bool HasEntityName(const std::string &_name);

      /// \brief Add a widget to the left column stack of widgetes.
      /// \param[in] _name Name of the widget
      /// \param[in] _widget Pointer to the widget to add.
      public: void AddToLeftColumn(const std::string &_name, QWidget *_widget);

      /// \brief Show a widget in the left column.
      /// \sa AddToLeftColumn
      /// \param[in] _name Name of the widge to show. The widget must have
      /// been added using AddToLeftColumn. The string "default" will show
      /// the main tab.
      public: void ShowLeftColumnWidget(const std::string &_name = "default");

      /// \brief Get a pointer to the render widget.
      /// \return A pointer to the render widget.
      public: RenderWidget *GetRenderWidget() const;

      /// \brief Play simulation.
      public slots: void Play();

      /// \brief Pause simulation.
      public slots: void Pause();

      protected: void closeEvent(QCloseEvent *_event);

      private: void OnGUI(ConstGUIPtr &_msg);

      private slots: void ItemSelected(QTreeWidgetItem *, int);
      private slots: void New();
      private slots: void Open();
      private slots: void Import();
      private slots: void Save();
      private slots: void SaveAs();
      private slots: void About();
      private slots: void Step();
      private slots: void NewModel();
      private slots: void Arrow();
      private slots: void Translate();
      private slots: void Rotate();

      private slots: void CreateBox();
      private slots: void CreateSphere();
      private slots: void CreateCylinder();
      private slots: void CreateMesh();
      private slots: void CreatePointLight();
      private slots: void CreateSpotLight();
      private slots: void CreateDirectionalLight();

      /// \brief Qt callback when the screenshot action is triggered
      private slots: void CaptureScreenshot();

      private slots: void InsertModel();
      private slots: void ShowGrid();
      private slots: void ShowCollisions();
      private slots: void ShowJoints();
      private slots: void ShowContacts();
      private slots: void ShowCOM();
      private slots: void Reset();
      private slots: void FullScreen();
      private slots: void FPS();
      private slots: void Orbit();
      private slots: void OnResetModelOnly();
      private slots: void OnResetWorld();
      private slots: void SetTransparent();
      private slots: void SetWireframe();

      /// \brief Qt call back when the play action state changes
      private slots: void OnPlayActionChanged();

      /// \brief QT slot to open the data logger utility
      private slots: void DataLogger();

      /// \brief Callback when topic selection action.
      private slots: void SelectTopic();

      /// \brief Callback for diagnostics action.
      private slots: void Diagnostics();

      private: void OnFullScreen(bool _value);
      private: void OnMoveMode(bool _mode);

      /// \brief Create most of the actions.
      private: void CreateActions();

      /// \brief Create menus.
      private: void CreateMenus();

      /// \brief Create the toolbars.
      private: void CreateToolbars();

      /// \brief Create the main menu bar.
      private: void CreateMenuBar();

      /// \brief Create all the editors.
      private: void CreateEditors();

      /// \brief Show a custom menubar. If NULL is used, the default menubar
      /// is shown.
      /// \param[in] _bar The menubar to show. NULL will show the default
      /// menubar.
      public: void ShowMenuBar(QMenuBar *_bar = NULL);

      private: void OnModel(ConstModelPtr &_msg);
      private: void OnResponse(ConstResponsePtr &_msg);
      private: void OnWorldModify(ConstWorldModifyPtr &_msg);
      private: void OnManipMode(const std::string &_mode);
      private: void OnSetSelectedEntity(const std::string &_name,
                                        const std::string &_mode);
      private: void OnStats(ConstWorldStatisticsPtr &_msg);

      /// \brief Handle event for changing the manual step size.
      /// \param[in] _value New input step size.
      private: void OnInputStepSizeChanged(int _value);

      private: QToolBar *playToolbar;

      private: RenderWidget *renderWidget;
      private: ToolsWidget *toolsWidget;
      private: ModelListWidget *modelListWidget;

      private: transport::NodePtr node;
      private: transport::PublisherPtr worldControlPub;
      private: transport::PublisherPtr serverControlPub;
      private: transport::PublisherPtr selectionPub;
      private: transport::PublisherPtr requestPub;
      private: transport::PublisherPtr scenePub;
      private: transport::SubscriberPtr responseSub;
      private: transport::SubscriberPtr guiSub;
      private: transport::SubscriberPtr newEntitySub, statsSub;
      private: transport::SubscriberPtr worldModSub;

      private: QDockWidget *toolsDock;

      private: std::vector<event::ConnectionPtr> connections;

      // A map that associates physics_id's with entity names
      private: std::map<std::string, unsigned int> entities;

      /// \brief Message used to field requests.
      private: msgs::Request *requestMsg;

      /// \brief The left-hand tab widget
      private: QTabWidget *tabWidget;

      /// \brief Mainwindow's menubar
      private: QMenuBar *menuBar;

      /// \brief A layout for the menu bar.
      private: QHBoxLayout *menuLayout;

      /// \brief Used to control size of each pane.
      private: QStackedWidget *leftColumn;

      /// \brief Map of names to widgets in the leftColumn QStackedWidget
      private: std::map<std::string, int> leftColumnStack;

      /// \brief The filename set via "Save As". This filename is used by
      /// the "Save" feature.
      private: std::string saveFilename;

      /// \brief User specified step size for manually stepping the world
      private: int inputStepSize;

      /// \brief List of all the editors.
      private: std::list<Editor*> editors;
    };
  }
}
#endif
