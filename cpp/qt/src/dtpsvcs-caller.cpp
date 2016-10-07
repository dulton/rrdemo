/* ************************************************************************//*!
 * \copyright The MIT License
 ******************************************************************************/

#include <QDesktopServices>

namespace {

void openUrl(const QUrl &url) {
   QDesktopServices::openUrl(url);
}

}  // namespace
