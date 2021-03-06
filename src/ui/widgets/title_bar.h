/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEEPIN_APPSTORE_UI_WIDGETS_TITLE_BAR_H
#define DEEPIN_APPSTORE_UI_WIDGETS_TITLE_BAR_H

#include <QFrame>
#include <QLabel>
#include <DIconButton>
#include <QStackedLayout>
#include <dbuttonbox.h>
#include <QMouseEvent>

using namespace  Dtk::Widget;

namespace dstore
{

class SearchEdit;
class UserMenu;

// Customize widget in TitleBar.
class TitleBar : public QFrame
{
    Q_OBJECT

public:
    explicit TitleBar(bool support_sign_in, QWidget *parent = nullptr);
    ~TitleBar() override;

    QString getSearchText() const;
    void mousePressEvent(QMouseEvent *event) override;

Q_SIGNALS:
    void loginRequested(bool login);

    void commentRequested();
    //void requestDonates();
    void requestApps();

    void backwardButtonClicked();
    void forwardButtonClicked();

    void searchTextChanged(const QString &text);
    void downKeyPressed();
    void enterPressed();
    void titlePressed();
    void upKeyPressed();
    void focusChanged(bool onFocus);
    void titleDoubleClicked();

public Q_SLOTS:
    void setBackwardButtonActive(bool active);
    void setForwardButtonActive(bool active);
    void setUserInfo(const QVariantMap &info);

    void refreshAvatar();
private:
    void initUI(bool support_sign_in);
    void initConnections();
    void saveUserAvatar(const QImage &image, const QString &filePath);

    Dtk::Widget::DButtonBox *buttonBox { nullptr};
    DButtonBoxButton *back_button_ = nullptr;
    DButtonBoxButton *forward_button_ = nullptr;
    SearchEdit *search_edit_ = nullptr;
    QString user_name_ = "";
    UserMenu *user_menu_ = nullptr;
    DIconButton *avatar_button_ = nullptr;
    QIcon *avatar_icon = nullptr;

private slots:
    void onSearchTextChanged();
};

}  // namespace dstore

#endif  // DEEPIN_APPSTORE_UI_WIDGETS_TITLE_BAR_H
