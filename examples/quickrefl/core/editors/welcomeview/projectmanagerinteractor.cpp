// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "projectmanagerinteractor.h"
#include "welcomeviewsettings.h"
#include <QDebug>
#include <QFileDialog>

ProjectManagerInteractor::ProjectManagerInteractor(QWidget* parent, WelcomeViewSettings* settings)
    : m_parent(parent), m_settings(settings)
{
}

//! Returns directory on disk selected by the user via QFileDialog.
std::string ProjectManagerInteractor::onSelectDirRequest()
{
    qDebug() << "WelcomeView::onSelectDirRequest()";
    return {};
}

//! Returns new directory on disk created by the user via QFileDialog.
std::string ProjectManagerInteractor::onCreateDirRequest()
{
    qDebug() << "WelcomeView::onCreateDirRequest()" << m_settings->currentWorkdir();
    QString dirname = QFileDialog::getExistingDirectory(
        m_parent, "Select directory", m_settings->currentWorkdir(),
        QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);

    qDebug() << "       dirname:" << dirname;
    m_settings->updateWorkdirFromSelection(dirname);

    return dirname.toStdString();
}

//! Returns save/cancel/discard changes choice provided by the user.
int ProjectManagerInteractor::onSaveChangesRequest()
{
    qDebug() << "WelcomeView::onSaveChangesRequest()";
    return 0;
}
