/* ************************************************************************//*!
 * \copyright The MIT License
 ******************************************************************************/

#include <QCryptographicHash>

namespace {

QByteArray hash(const QByteArray &data) {
   QCryptographicHash md5(QCryptographicHash::Md5);
   md5.addData(data);
   return md5.result().toHex().toUpper();
}

}  // namespace
