/* This file is part of Clementine.

   Clementine is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Clementine is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Clementine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LIBRARYVIEW_H
#define LIBRARYVIEW_H

#include "widgets/autoexpandingtreeview.h"

#include <QStyledItemDelegate>

class LibraryModel;

class LibraryItemDelegate : public QStyledItemDelegate {
 public:
  LibraryItemDelegate(QObject* parent);
  void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
};

class LibraryView : public AutoExpandingTreeView {
  Q_OBJECT

 public:
  LibraryView(QWidget* parent = 0);

  static const char* kSettingsGroup;

  void SetLibrary(LibraryModel* library);

  // QTreeView
  void keyboardSearch(const QString &search);
  void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible);

 public slots:
  void TotalSongCountUpdated(int count);
  void ReloadSettings();

 signals:
  void ShowConfigDialog();
  void Load(const QModelIndex& index);
  void AddToPlaylist(const QModelIndex& index);

 protected:
  // QWidget
  void paintEvent(QPaintEvent* event);
  void mouseReleaseEvent(QMouseEvent* e);
  void contextMenuEvent(QContextMenuEvent* e);

 private slots:
  void Load();
  void AddToPlaylist();
  void ShowInVarious();
  void NoShowInVarious();

 private:
  void RecheckIsEmpty();
  void ShowInVarious(bool on);

 private:
  LibraryModel* library_;
  int total_song_count_;

  QPixmap nomusic_;

  QMenu* context_menu_;
  QModelIndex context_menu_index_;
  QAction* load_;
  QAction* add_to_playlist_;
  QAction* show_in_various_;
  QAction* no_show_in_various_;

  bool is_in_keyboard_search_;
};

#endif // LIBRARYVIEW_H
